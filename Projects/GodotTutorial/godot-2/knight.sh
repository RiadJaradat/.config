#!/bin/sh
printf '\033c\033]0;%s\a' godot2
base_path="$(dirname "$(realpath "$0")")"
"$base_path/knight.x86_64" "$@"
