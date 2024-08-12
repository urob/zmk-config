{
  inputs = {
    # Pin this to 23.11 to provide py3.8 needed for the sdk-ng without building it ourselves
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-23.11";

    # Zephyr version determining which requirements.txt to use to install python dependencies
    zephyr.url = "github:zephyrproject-rtos/zephyr/v3.5.0";
    zephyr.flake = false;

    # Zephyr sdk and host tools
    zephyr-nix.url = "github:urob/zephyr-nix";
    zephyr-nix.inputs.nixpkgs.follows = "nixpkgs";
    zephyr-nix.inputs.zephyr.follows = "zephyr";
  };

  outputs = { nixpkgs, zephyr-nix, ... }: let
    forAllSystems = nixpkgs.lib.genAttrs ["x86_64-linux" "aarch64-linux" "x86_64-darwin" "aarch64-darwin"];
  in {
    devShells = forAllSystems (system: let
      pkgs = nixpkgs.legacyPackages.${system};
      zephyr = zephyr-nix.packages.${system};
    in {
      default = pkgs.mkShell {
        packages = [
          # zephyr.hosttools-nix
          # (zephyr.pythonEnv.override {extraPackages = pkgs: [pkgs.pyyaml];})
          zephyr.pythonEnv
          zephyr.sdkFull
          pkgs.cmake
          pkgs.dtc
          pkgs.just
          pkgs.ninja
          pkgs.yq
        ];
      };
    });
  };
}
