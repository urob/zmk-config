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
  version = "0.20.0+revert-poetry";
  pyproject = true;

  src = fetchFromGitHub {
    owner = "caksoylar";
    repo = pname;
    rev = "a2a3b37c54ddb449428b4597b39c3c28b331a7da";
    hash = "sha256-GKGjEHQ/GsLhCzjuglDuztAEIpeaz+fHHmNJJcLmQT8=";
  };

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
