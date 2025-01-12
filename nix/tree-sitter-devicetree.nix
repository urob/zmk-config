{
  lib,
  buildPythonPackage,
  fetchFromGitHub,
  setuptools,
  tree-sitter,
}:

buildPythonPackage rec {
  pname = "tree-sitter-devicetree";
  version = "0.12.1";
  pyproject = true;

  src = fetchFromGitHub {
    owner = "joelspadin";
    repo = "tree-sitter-devicetree";
    rev = "16c9cb959675bc9bc4f4e5bebe473d511a12a06d";
    hash = "sha256-UVxLF4IKRXexz+PbSlypS/1QsWXkS/iYVbgmFCgjvZM=";
  };

  build-system = [
    setuptools
  ];

  optional-dependencies = {
    core = [
      tree-sitter
    ];
  };

  # There are no tests
  doCheck = false;
  pythonImportsCheck = [ "tree_sitter_devicetree" ];

  meta = {
    description = "Devicetree grammar for tree-sitter";
    homepage = "https://github.com/joelspadin/tree-sitter-devicetree";
    license = lib.licenses.mit;
  };
}
