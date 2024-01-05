{
  cmake,
  fcitx5,
  stdenv,
}:
stdenv.mkDerivation {
  pname = "fcitx5-virtualkeyboard-adapter";
  version = "0.1.0";

  src = ./.;

  nativeBuildInputs = [cmake];
  buildInputs = [fcitx5];
}
