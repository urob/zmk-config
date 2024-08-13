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
  version = "0.18.0";
  pyproject = true;

  src = fetchPypi {
    pname = "keymap_drawer";
    inherit version;
    hash = "sha256-faJB+cjj740Ny2wqVwc5t/+grEWBIEyhex3RoLCuIs8=";
  };

  postPatch = ''
    substituteInPlace pyproject.toml --replace 'platformdirs = "^3.5.1"' 'platformdirs = "^4.0.0"'
  '';

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
