{ lib
, buildPythonApplication
, buildPythonPackage
, callPackage
, fetchFromGitHub
, setuptools
, poetry-core
, pydantic
, pcpp
, pyyaml
, platformdirs
, pydantic-settings
, tree-sitter
}:
let
  tree-sitter-devicetree = callPackage ./tree-sitter-devicetree.nix {};
in
buildPythonApplication rec {
  pname = "keymap-drawer";
  version = "0.20.0";
  pyproject = true;

  src = fetchFromGitHub {
    owner = "caksoylar";
    repo = pname;
    rev = "ea00f44ac5a2ebe97b8b31f9166791bedf9136e5";
    hash = "sha256-F9lDUuqHKl2FOUsUszJrRK7/a/a1UJLw+RUg9Bv2zN0=";
  };

  postPatch = ''
    # nixos-unstable no longer bundles v23 of tree-sitter
    substituteInPlace pyproject.toml --replace 'tree-sitter (>=0.23.2,<0.24.0)' 'tree-sitter (>=0.23.2,<0.25.0)'
  '';

  build-system = [ poetry-core ];

  propagatedBuildInputs = [
    pydantic
    pcpp
    pyyaml
    platformdirs
    pydantic-settings
    tree-sitter
    tree-sitter-devicetree
  ];

  doCheck = false;

  meta = {
    homepage = "https://github.com/caksoylar/keymap-drawer";
    description = "Parse QMK & ZMK keymaps and draw them as vector graphics";
    license = lib.licenses.mit;
  };
}
