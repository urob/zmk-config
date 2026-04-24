{ pkgs, dts-linter }:

pkgs.writeShellScriptBin "dts-format" ''
  fix=0
  tab_size=4
  use_tabs=0
  files=()

  while [ $# -gt 0 ]; do
    case "$1" in
      --fix) fix=1 ;;
      --tab-width=*) tab_size="''${1#*=}" ;;
      --tab-width) shift; tab_size="$1" ;;
      --use-tabs) use_tabs=1 ;;
      *) files+=("$1") ;;
    esac
    shift
  done

  if [ "$fix" -eq 1 ]; then
    format_flag="--formatFixAll"
  else
    format_flag="--format"
  fi

  base_args=("$format_flag" --tabSize "$tab_size")
  [ "$use_tabs" -eq 0 ] && base_args+=(--insertSpaces)

  if [ "''${#files[@]}" -gt 0 ]; then
    exec ${dts-linter}/bin/dts-linter "''${base_args[@]}" --file "''${files[@]}"
  else
    exec ${dts-linter}/bin/dts-linter "''${base_args[@]}" \
      --filetypes dts,dtsi,overlay,keymap
  fi
''
