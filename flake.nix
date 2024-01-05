{
  description = "A very basic flake";
  outputs = {
    self,
    nixpkgs,
  }: let
    inherit (nixpkgs) lib;
    eachSystem = lib.genAttrs ["x86_64-linux"];
    pkgsFor = eachSystem (
      system:
        import nixpkgs {
          localSystem = system;
          overlays = [self.overlays.default];
        }
    );
  in {
    overlays = {
      default = final: prev: {
        virtualkeyboard-adapter = final.callPackage ./virtualkeyboard-adapter.nix {};
      };
    };

    packages = eachSystem (system: {
      default = self.packages.${system}.virtualkeyboard-adapter;
      inherit (pkgsFor.${system}) virtualkeyboard-adapter;
    });
    devShells = eachSystem (system: let
      pkgs = pkgsFor.${system};
    in {
      default = pkgs.mkShell {
        nativeBuildInputs = with pkgs; [meson cmake pkg-config ninja];
        buildInputs = with pkgs; [
          fcitx5
        ];
      };
    });
  };
}
