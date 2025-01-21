{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";

    # Version of requirements.txt installed in pythonEnv
    zephyr.url = "github:zmkfirmware/zephyr/v3.5.0+zmk-fixes";
    zephyr.flake = false;

    # Zephyr sdk and toolchain
    zephyr-nix.url = "github:urob/zephyr-nix";
    zephyr-nix.inputs.zephyr.follows = "zephyr";
    zephyr-nix.inputs.nixpkgs.follows = "nixpkgs";
  };

  outputs = { nixpkgs, zephyr-nix, ... }: let
    systems = [ "x86_64-linux" "aarch64-linux" "x86_64-darwin" "aarch64-darwin" ];
    forAllSystems = nixpkgs.lib.genAttrs systems;
  in {
    devShells = forAllSystems (system: let
      pkgs = nixpkgs.legacyPackages.${system};
      zephyr = zephyr-nix.packages.${system};
      keymap_drawer = pkgs.python3Packages.callPackage ./nix/keymap-drawer.nix { };

    in {
      default = pkgs.mkShellNoCC {
        packages = [
          zephyr.pythonEnv
          (zephyr.sdk-0_16.override { targets = [ "arm-zephyr-eabi" ]; })

          pkgs.cmake
          pkgs.dtc
          pkgs.ninja

          pkgs.just
          pkgs.yq # make sure we use the python version

          # -- Uncomment these if you don't have system-wide versions --
          # pkgs.gawk             # awk
          # pkgs.unixtools.column # column
          # pkgs.coreutils        # cp, cut, echo, mkdir, sort, tail, tee, uniq, wc
          # pkgs.diffutils        # diff
          # pkgs.findutils        # find, xargs
          # pkgs.gnugrep          # grep
          # pkgs.gnused           # sed

        ]
        # Temporary disable keymap_drawer on aarch64-linux due to:
        # https://github.com/NixOS/nixpkgs/issues/372375
        ++ pkgs.lib.optionals (system != "aarch64-linux") [ keymap_drawer ];

        shellHook = ''
          export ZMK_BUILD_DIR=$(pwd)/.build;
          export ZMK_SRC_DIR=$(pwd)/zmk/app;
        '';
      };
    });
  };
}
