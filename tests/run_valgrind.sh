#!/usr/bin/env bash
# Test runner that runs multiple tests (>=10), generates expected output via shell pipeline,
# runs the program and valgrind to detect leaks, and writes a report with leak=yes/no.

set -u
repo_root="$(cd "$(dirname "$0")/.." && pwd)"
exe="$repo_root/a.out"
report="$repo_root/tests/report_valgrind.txt"
compile_log="$repo_root/tests/compile_err_valgrind.log"
run_err="$repo_root/tests/run_err_valgrind.log"
vg_log_dir="$repo_root/tests/valgrind_logs"

mkdir -p "$repo_root/tests/outfile"
mkdir -p "$vg_log_dir"

# compile
CC=cc
CFLAGS=( -Wall -Werror -Wextra -I"$repo_root" )
SRC=("$repo_root/optimized/norm.c" "$repo_root/sources"/*.c "$repo_root/sources/ft_printf"/*.c)

echo "Compiling..." > "$report"
"$CC" "${CFLAGS[@]}" "${SRC[@]}" -o "$exe" 2> "$compile_log"
if [ $? -ne 0 ]; then
  echo "COMPILE FAILED" >> "$report"
  cat "$compile_log" >> "$report"
  exit 1
fi

# Is valgrind available?
if command -v valgrind >/dev/null 2>&1; then
  HAVE_VG=1
else
  HAVE_VG=0
fi

# Define >=10 tests. Each test is an array: infile | cmd1 | cmd2 | ... | outfile | expected
# We'll generate expected output dynamically by building the shell pipeline.
TESTS=(
  "tests/infiles/infile1.txt|cat|wc -l|tests/outfile/outfile1.txt|tests/outfile/expected_outfile1.txt"
  "tests/infiles/infile2.txt|cat|cat|cat|cat|cat|cat|tests/outfile/outfile2.txt|tests/outfile/expected_outfile2.txt"
  "tests/infiles/infile1.txt|cat|cat|wc -l|tests/outfile/outfile3.txt|tests/outfile/expected_outfile3.txt"
  "tests/infiles/infile2.txt|cat|wc -c|tests/outfile/outfile4.txt|tests/outfile/expected_outfile4.txt"
  "tests/infiles/infile1.txt|cat|rev|rev|tests/outfile/outfile5.txt|tests/outfile/expected_outfile5.txt"
  "tests/infiles/infile2.txt|cat|tr a-z A-Z|tests/outfile/outfile6.txt|tests/outfile/expected_outfile6.txt"
  "tests/infiles/infile1.txt|cat|cat|cat|cat|cat|cat|cat|cat|cat|cat|tests/outfile/outfile7.txt|tests/outfile/expected_outfile7.txt"
  "tests/infiles/infile2.txt|cat|sed s/world/earth/|tests/outfile/outfile8.txt|tests/outfile/expected_outfile8.txt"
  "tests/infiles/infile1.txt|cat|nl|wc -l|tests/outfile/outfile9.txt|tests/outfile/expected_outfile9.txt"
  'tests/infiles/infile2.txt|cat|awk {print $0}|tests/outfile/outfile10.txt|tests/outfile/expected_outfile10.txt'
)

# Ensure infiles exist (create simple ones if missing)
mkdir -p "$repo_root/tests/infiles"
[ -f "$repo_root/tests/infiles/infile1.txt" ] || printf 'line one\nline two\nline three\n' > "$repo_root/tests/infiles/infile1.txt"
[ -f "$repo_root/tests/infiles/infile2.txt" ] || printf 'hello\nworld\n' > "$repo_root/tests/infiles/infile2.txt"

# Run tests
n=0
: > "$report"
for t in "${TESTS[@]}"; do
  ((n++))
  IFS='|' read -ra parts <<< "$t"
  plen=${#parts[@]}
  infile=${parts[0]}
  expected=${parts[$((plen-1))]}
  outfile=${parts[$((plen-2))]}
  # commands are parts[1..plen-3]
  cmds=()
  for ((i=1;i<=plen-3;i++)); do cmds+=("${parts[i]}"); done

  # generate expected by writing a small temp script that runs the exact pipeline (preserving $ in awk, etc.)
  tmp_script="$repo_root/tests/tmp_pipeline_${n}.sh"
  printf "cat '%s'" "$repo_root/$infile" > "$tmp_script"
  for c in "${cmds[@]}"; do
    printf ' | %s' "$c" >> "$tmp_script"
  done
  printf " > '%s'\n" "$repo_root/$expected" >> "$tmp_script"
  chmod +x "$tmp_script"
  echo "Generating expected by running $tmp_script" >> "$report"
  bash "$tmp_script" > /dev/null 2> /dev/null || true

  # run program
  echo "----TEST $n-----" >> "$report"
  # print in requested format
  printf './a.out %s' "$infile" >> "$report"
  for c in "${cmds[@]}"; do printf ' %s' "$c" >> "$report"; done
  printf ' %s\n' "$outfile" >> "$report"

  rm -f "$repo_root/$outfile"
  timeout 8s "$exe" "$repo_root/$infile" "${cmds[@]}" "$repo_root/$outfile" >/dev/null 2> "$run_err"
  rc=$?
  ok=0
  if [ $rc -eq 0 ]; then
    if cmp -s "$repo_root/$outfile" "$repo_root/$expected"; then
      echo "passed" >> "$report"
      ok=1
    else
      echo "failed" >> "$report"
    fi
  else
    echo "failed (exit $rc or timeout)" >> "$report"
  fi

  # run valgrind if available to check leaks
  leak_status="unknown"
  if [ $HAVE_VG -eq 1 ]; then
    vglog="$vg_log_dir/test${n}_valgrind.txt"
    # run under valgrind and capture output; don't let valgrind change behavior: use --log-file
    valgrind --leak-check=full --show-leak-kinds=all --error-exitcode=0 --log-file="$vglog" "$exe" "$repo_root/$infile" "${cmds[@]}" "$repo_root/$outfile" >/dev/null 2>> "$run_err" || true
    # check the valgrind log for 'definitely lost: 0 bytes'
    # detect no-leak patterns: valgrind may report 'All heap blocks were freed' or 'definitely lost: 0 bytes'
    if grep -q "All heap blocks were freed" "$vglog" 2>/dev/null || grep -q "definitely lost: 0 bytes" "$vglog" 2>/dev/null; then
      leak_status="no"
    else
      if grep -q "definitely lost:" "$vglog" 2>/dev/null; then
        leak_status="yes"
      else
        leak_status="unknown"
      fi
    fi
  else
    leak_status="valgrind-not-found"
  fi

  echo "leak = $leak_status" >> "$report"
  echo >> "$report"
done

# summary
echo "Done. Report: $report"
