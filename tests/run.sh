#!/usr/bin/env bash
# Simple test runner for optimized/norm.c (pipex)
# - Compiles with: cc -Wall -Werror -Wextra
# - Tests format: infile|cmd1|cmd2|...|outfile|expected
# - Produces tests/report.txt with the format requested by the user

set -u
repo_root="$(cd "$(dirname "$0")/.." && pwd)"
exe="$repo_root/a.out"
report="$repo_root/tests/report.txt"
compile_log="$repo_root/tests/compile_err.log"
run_err="$repo_root/tests/run_err.log"

CC=cc
CFLAGS=( -Wall -Werror -Wextra -I"$repo_root" )
SRC=("$repo_root/optimized/norm.c" "$repo_root/sources"/*.c "$repo_root/sources/ft_printf"/*.c)

# Compile
echo "Compiling with: ${CC} ${CFLAGS[*]} ${SRC[*]}" > "$report"
"$CC" "${CFLAGS[@]}" "${SRC[@]}" -o "$exe" 2> "$compile_log"
if [ $? -ne 0 ]; then
  echo "COMPILE FAILED. See $compile_log" >> "$report"
  cat "$compile_log" >> "$report" || true
  exit 1
fi

# Define tests: each entry is a single string with fields separated by '|'
# Fields: infile | cmd1 | cmd2 | ... | outfile | expected
TESTS=(
  "tests/infiles/infile1.txt|cat|wc -l|tests/outfile/outfile1.txt|tests/outfile/expected_outfile1.txt"
  "tests/infiles/infile2.txt|cat|cat|tests/outfile/outfile2.txt|tests/outfile/expected_outfile2.txt"
)

# Ensure out dir exists
mkdir -p "$repo_root/tests/outfile"

# Start running
n=0
: > "$run_err" || true
for t in "${TESTS[@]}"; do
  ((n++))
  # split by |
  IFS='|' read -ra parts <<< "$t"
  plen=${#parts[@]}
  if [ $plen -lt 4 ]; then
    echo "Skipping malformed test entry: $t" >> "$report"
    continue
  fi
  infile=${parts[0]}
  expected=${parts[$((plen-1))]}
  outfile=${parts[$((plen-2))]}
  # commands are parts[1] .. parts[plen-3]
  cmds=()
  for ((i=1; i<=plen-3; i++)); do
    cmds+=("${parts[i]}")
  done

  # build argv list for program: infile, cmd1, cmd2, ..., outfile
  args=("$repo_root/$infile")
  for c in "${cmds[@]}"; do
    args+=("$c")
  done
  args+=("$repo_root/$outfile")

  # Header in report
  echo "----TEST $n-----" >> "$report"
  # Print command line in requested format: ./a.out infile cmd1 cmd2 outfile
  # Use relative ./a.out and paths relative to repo for clarity
  printf './a.out %s' "$infile" >> "$report"
  for c in "${cmds[@]}"; do
    printf ' %s' "$c" >> "$report"
  done
  printf ' %s\n' "$outfile" >> "$report"

  # clear previous outfile
  rm -f "$repo_root/$outfile"

  # Run with timeout 5s
  timeout 5s "$exe" "${args[@]}" >/dev/null 2> "$run_err"
  rc=$?
  if [ $rc -eq 0 ]; then
    if cmp -s "$repo_root/$outfile" "$repo_root/$expected"; then
      echo "passed" >> "$report"
    else
      echo "failed" >> "$report"
      echo "----- diff (expected vs actual) -----" >> "$report"
      diff -u "$repo_root/$expected" "$repo_root/$outfile" >> "$report" || true
      echo "----- stderr (truncated) -----" >> "$report"
      tail -n 200 "$run_err" >> "$report" || true
    fi
  elif [ $rc -eq 124 ]; then
    echo "failed" >> "$report"
    echo "(timeout)" >> "$report"
    echo "----- stderr (truncated) -----" >> "$report"
    tail -n 200 "$run_err" >> "$report" || true
  else
    echo "failed" >> "$report"
    echo "(exit code $rc)" >> "$report"
    echo "----- stderr (truncated) -----" >> "$report"
    tail -n 200 "$run_err" >> "$report" || true
  fi
  echo >> "$report"
done

# Final message
echo "Test run complete. Report at: $report"
