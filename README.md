# fcitx-virtual-keyboard-adapter

(Note: not a real `fcitx::VirtualKeyboardUserInterface`)

A simple addon that calls commands when a text field is focused/unfocused

A stopgap until I find a good enough on-screen-keyboard that auto shows/hides...

## Usage

Build and install addon with

```
mkdir build
cd build
cmake ..
cmake --build .
make install
```

Specify activate/deactivate commands with:

```
# ~/.config/fcitx5/conf/virtualkeyboardadapter.conf

ActivateCmd="pkill -SIGUSR2 wvkbd"
DeactivateCmd="pkill -SIGUSR1 wvkbd"
```
