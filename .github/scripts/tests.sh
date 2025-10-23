#./.github/scripts/tests.sh
git fetch origin main

generate_args() {
  local file="$1"
  local args_array=()

  while read -r line || [[ -n "$line" ]]; do
    [[ -z "$line" || "$line" =~ ^# ]] && continue

    read -ra parts <<< "$line"
    for part in "${!parts[@]}"; do
        parts[$part]=$(echo "${parts[$part]}" | tr -d '\r\n\t ')
    done
    local type="${parts[0]}"

    if [[ $type == "int" ]]; then
      local min_val=${parts[1]}
      local max_val=${parts[2]}
      local val=$(( RANDOM % (max_val - min_val + 1) + min_val ))
      args_array+=("$val")

    elif [[ $type == "string" ]]; then
      local options=("${parts[@]:1}")
      local index=$(( RANDOM % ${#options[@]} ))
      args_array+=("${options[$index]}")

    else
      echo "Nieznany typ: $type" >&2
      return 1
    fi
  done < "$file"

  # scala argumenty w jeden string, rozdzielony spacjami
  echo "${args_array[*]}"
}
#$1 = args
#$2 = program path
#$3 = timeout limit
#return cout from program with given args
test_program() {
    #start=$(date +%s%N)
    #end=$(date +%s%N)
    #duration=$(( ($end - $start) / 1000000 )) #should we check for duration to be too long or timesum?
    if ! value=$(echo -e "$1" | timeout "$3" "$2"); then
        echo "Przekroczono limit czasu $3"
        echo -1
    else
        echo $value
    fi
}

changed_dirs=$(git diff --name-only origin/main..HEAD | xargs -n1 dirname | sort -u)
iterations=10
bin="output.exe"

for dir in $changed_dirs; do
    cpp_files=$(find "$dir" -maxdepth 1 -type f -name '*.cpp')
    inputRegex="$dir/input_regex.in"
    #dummy run idk why but first run with timeout will always fail
    args=$(generate_args "$inputRegex")
    val1=$(test_program "$args" "$dir/solution.exe" "1")
    
    for cpp_file in $cpp_files; do
        g++ "./$cpp_file" -o "$dir/$bin"
        if [ -f "$dir/solution.exe" ]; then
            for ((i=0; i<$iterations; i++)); do
                args=$(generate_args "$inputRegex")
                val1=$(test_program "$args" "$dir/solution.exe" "1")
                val2=$(test_program "$args" "$dir/$bin" "1")
                echo "wartosc_sol: $val1"
                echo "wartosc_out: $val2"
            done
        fi
    done
done