# Validation

- Implemented the abstract role hierarchy in `Role.hpp`, without namespace-level
  variables or additional public gameplay methods. Shared battle resolution
  handles type effectiveness, defense, retaliation, and target-first death output.
- `main.cpp` reproduces the supplied battle driver and uses automatic ownership.
- Build: `cmake -S . -B build && cmake --build build`.
- Randomized verification: `python3 tests/check.py build/code` passed 500 battles.
- Focused tests: `g++ -std=c++17 -fsanitize=address,undefined -I. tests/roles.cpp
  -o build/roles_test && build/roles_test` passed.
- The README sample passed. The advertised local test-data directory was absent.

## Online Judge

The live problem API accepts only `cpp`, despite the Git-submission instructions
in the supplied README. The Git request was rejected with HTTP 400 and returned
no submission ID. The client was repaired to support both Git and source uploads.

Submitted `Role.hpp` from commit `0427818` as C++ source:

- Problem: 1778
- Submission ID: **879475**
- Result: **Accepted**, **100/100**, all **42** test points passed
- Valid submissions used: **1 of 5**

All source changes were committed and pushed before submission, and the remote
commit was verified with `git ls-remote`. No files or remote branches were
changed while the submission was being judged.
