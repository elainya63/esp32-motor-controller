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
    gnumake
    gcc

    # needed for compiling/uploading
    python3
    python3Packages.pyserial
    
    llvmPackages.clang-tools # required for arduino lsp (maybe not?)
    arduino-language-server # lsp, duh

    # ugh fucking ide might work
    arduino-ide
    xorg.libxkbfile
  ];

  # fucky directory stuff
  profile = ''
    export HOME="/home/elaine"
    export XDG_CONFIG_HOME="$HOME/.config"
    export XDG_DATA_HOME="$HOME/.local/share"
    
    # export ARDUINO_DATA_DIR="$HOME/.arduino15"
    export PATH="${pkgs.python3}/bin:$PATH"
    export LD_LIBRARY_PATH="/run/opengl-driver/lib:/run/current-system/sw/lib:${pkgs.xorg.libxkbfile}/lib:$LD_LIBRARY_PATH"
  '';
}).env
