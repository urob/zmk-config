{ pkgs, dts-linter }:

pkgs.writeShellScriptBin "dts-format" ''
  fix=0
  files=()

  for arg in "$@"; do
    case "$arg" in
      --fix) fix=1 ;;
      *) files+=("$arg") ;;
    esac
  done

  if [ "$fix" -eq 1 ]; then
    format_flag="--formatFixAll"
  else
    format_flag="--format"
  fi

  base_args=("$format_flag" --tabSize 4 --insertSpaces)

  if [ "''${#files[@]}" -gt 0 ]; then
    exec ${dts-linter}/bin/dts-linter "''${base_args[@]}" --file "''${files[@]}"
  else
    exec ${dts-linter}/bin/dts-linter "''${base_args[@]}" \
      --filetypes dts,dtsi,overlay,keymap
  fi
''
