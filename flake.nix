{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";

    # This pins requirements.txt provided by zephyr-nix.pythonEnv.
    zephyr.url = "github:zmkfirmware/zephyr/v4.1.0+zmk-fixes";
    zephyr.flake = false;

    # Zephyr sdk and toolchain.
    zephyr-nix.url = "github:nix-community/zephyr-nix";
    zephyr-nix.inputs.zephyr.follows = "zephyr";
    zephyr-nix.inputs.nixpkgs.follows = "nixpkgs";

    # Devicetree linter; use my fork for nix-package and ZMK-specific tweaks.
    dts-linter.url = "github:urob/dts-linter/zmk";
    dts-linter.inputs.nixpkgs.follows = "nixpkgs";

    # West manifest locking; skipping the flake to build its package.nix with
    # our own nixpkgs and python package set.
    pin-west.url = "github:urob/pin-west";
    pin-west.flake = false;
  };

  outputs = inputs @ { nixpkgs, ... }: let
    systems = ["x86_64-linux" "aarch64-linux" "x86_64-darwin" "aarch64-darwin"];
    forAllSystems = nixpkgs.lib.genAttrs systems;
  in {
    devShells = forAllSystems (
      system: let
        pkgs = nixpkgs.legacyPackages.${system};
        zephyr = inputs.zephyr-nix.packages.${system};
        keymap-drawer = pkgs.python3Packages.callPackage ./nix/keymap-drawer.nix {};
        pin-west = pkgs.python3Packages.callPackage "${inputs.pin-west}/package.nix" {};
        dts-format = pkgs.callPackage ./nix/dts-format.nix {
          # dts-linter = inputs.dts-linter.packages.${system}.dev;  # Use latest dts-lsp
          dts-linter = inputs.dts-linter.packages.${system}.default;  # Use dts-lsp bundled with dts-linter
        };
      in {
        default = pkgs.mkShellNoCC {
          packages =
            [
              zephyr.pythonEnv
              (zephyr.sdk-0_16.override {targets = ["arm-zephyr-eabi"];})

              pkgs.cmake
              pkgs.dtc
              pkgs.gcc
              pkgs.ninja

              pkgs.just
              pkgs.yq # Make sure yq resolves to python-yq.

              dts-format
              keymap-drawer
              pin-west

              # -- Used by just_recipes and west_commands. Most systems already have them. --
              # pkgs.gawk
              # pkgs.unixtools.column
              # pkgs.coreutils # cp, cut, echo, mkdir, sort, tail, tee, uniq, wc
              # pkgs.diffutils
              # pkgs.findutils # find, xargs
              # pkgs.gnugrep
              # pkgs.gnused
            ];

          env = {
            PYTHONPATH = "${zephyr.pythonEnv}/${zephyr.pythonEnv.sitePackages}";
          };

          shellHook = ''
            export ZMK_BUILD_DIR=$(pwd)/.build;
            export ZMK_SRC_DIR=$(pwd)/zmk/app;
          '' + (if pkgs.stdenv.isLinux then
            let libatomic = pkgs.runCommand "libatomic" {} ''
              mkdir -p $out/lib
              cp -d ${pkgs.stdenv.cc.cc.lib}/lib/libatomic.so* $out/lib/
            ''; in ''
            export LD_LIBRARY_PATH="${libatomic}/lib";
          '' else "");
        };
      }
    );
  };
}
