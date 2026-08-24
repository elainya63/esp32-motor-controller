{ pkgs ? import <nixpkgs> {} }:

(pkgs.buildFHSEnv {
  name = "arduino-cli-env";
  
  targetPkgs = pkgs: with pkgs; [
    arduino-cli
    udev       # Provides libudev.so.1 for tools like picotool
    libusb1    # Needed for various programmer boards
    pkg-config # Helps tools discover installed libraries
    zlib       # Common dependency for compiled tools
  ];

  # Ensures arduino-cli uses standard data directories in your home folder
  profile = ''
    export ARDUINO_DATA_DIR="$HOME/.arduino15"
  '';
}).env
