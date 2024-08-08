{
  inputs = {
    # Pin to 23.11 to provide python38 dependency for sdk
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-23.11";

    # Zephyr version determining which requirements.txt to use to install python dependencies
    zephyr.url = "github:zephyrproject-rtos/zephyr/v3.5.0";
    zephyr.flake = false;

    # Zephyr sdk and host tools
    zephyr-nix.url = "github:urob/zephyr-nix";
    zephyr-nix.inputs.nixpkgs.follows = "nixpkgs";
    zephyr-nix.inputs.zephyr.follows = "zephyr";
  };

  outputs = { self, nixpkgs, zephyr-nix, ... }: let
    system = "x86_64-linux";
    pkgs = nixpkgs.legacyPackages.${system};
    zephyr = zephyr-nix.packages.${system};
  in {
    devShells.${system}.default = pkgs.mkShell {
      packages = [
        zephyr.hosttools
        zephyr.pythonEnv
        zephyr.sdkFull
        pkgs.cmake
        pkgs.dtc
        pkgs.ninja
        pkgs.yq
      ];
    };
  };
}
