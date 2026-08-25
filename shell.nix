{ pkgs ? import <nixpkgs> {} }:

(pkgs.buildFHSEnv {
  name = "arduino-cli-env";
  
  targetPkgs = pkgs: with pkgs; [
    arduino-cli
    
    # specific arduino utils
    udev       
    libusb1    
    pkg-config
    zlib
    
    llvmPackages.clang-tools     # required for arduino lsp (maybe not?)
    arduino-language-server # lsp, duh
  ];

  # fucky directory stuff
  profile = ''
    export ARDUINO_DATA_DIR="$HOME/.arduino15"
  '';
}).env
