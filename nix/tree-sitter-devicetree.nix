{
  lib,
  buildPythonPackage,
  fetchFromGitHub,
  setuptools,
  tree-sitter,
}:

buildPythonPackage rec {
  pname = "tree-sitter-devicetree";
  version = "0.14.1";
  pyproject = true;

  src = fetchFromGitHub {
    owner = "joelspadin";
    repo = "tree-sitter-devicetree";
    rev = "6557729f4afaf01dec7481d4e5975515ea8f0edd";
    hash = "sha256-ua+mk++93ooH5nQH/M4vj7VSSvVDis/Uh8S1H34TxKs=";
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
