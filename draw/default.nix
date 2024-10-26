{
  lib,
  buildPythonApplication,
  fetchPypi,
  poetry-core,
  pydantic,
  pcpp,
  pyparsing,
  pyyaml,
  platformdirs,
  pydantic-settings,
}:
buildPythonApplication rec {
  pname = "keymap-drawer";
  version = "0.18.1";
  pyproject = true;

  src = fetchPypi {
    pname = "keymap_drawer";
    inherit version;
    hash = "sha256-MHjxsopXoYWZFuXUbeaI7BCSx3HkRaeVidY+mc8lj+s=";
  };

  build-system = [poetry-core];

  propagatedBuildInputs = [
    pydantic
    pcpp
    pyparsing
    pyyaml
    platformdirs
    pydantic-settings
  ];

  doCheck = false;

  meta = {
    homepage = "https://github.com/caksoylar/keymap-drawer";
    description = "Parse QMK & ZMK keymaps and draw them as vector graphics";
    license = lib.licenses.mit;
  };
}
