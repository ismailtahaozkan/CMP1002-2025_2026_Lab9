# Lab: Dynamic Memory Management & Static Classes

## Topic
Dynamic memory allocation (`new`/`delete`), deep copy semantics (copy constructor & copy assignment operator), destructors, and static class members in C++.

## Duration
50 minutes

## Learning Objectives
By completing this lab, you will be able to:
1. Allocate and deallocate dynamic memory using `new[]` and `delete[]`
2. Implement a correct destructor to prevent memory leaks
3. Write a copy constructor that performs a deep copy
4. Write a copy assignment operator with self-assignment protection
5. Use `static` member variables and functions to build a utility class
6. Understand object lifetime and scope-based destruction (RAII)

## Prerequisites
- Basic C++ syntax (classes, functions, pointers)
- Understanding of constructors and destructors
- Familiarity with the `this` pointer
- Compilation with `g++` using the command line

## File Structure
```
lab/
├── MainProgram.cpp          # Your implementation (single file)
├── test.cpp                 # Catch2 test cases
├── catch_amalgamated.hpp    # Catch2 header (provided)
├── catch_amalgamated.cpp    # Catch2 source (provided)
├── Makefile                 # Build automation
├── explain.txt              # Quick revision sheet
├── explain.md               # Detailed concept guide
└── README.md                # This file
```

## Instructions

### Step 1: Read the Concept Materials
Read `explain.txt` for a quick overview (2–3 min), then optionally read `explain.md` for more detail.

### Step 2: Open MainProgram.cpp
The file contains a skeleton with `TODO` markers (TODO 1 through TODO 15). Implement each one.

### Step 3: Compile and Run Your Program
```bash
make
./main
```

### Step 4: Run the Automated Tests
```bash
make test
```
This builds and runs all Catch2 tests against your implementation.

You can also run individual test groups to focus on one feature at a time:
```bash
make test_group1    # Construction & Destruction       (20 pts)
make test_group2    # Add & Get Operations             (20 pts)
make test_group3    # RemoveLast                       (10 pts)
make test_group4    # Copy Constructor (Deep Copy)     (15 pts)
make test_group5    # Copy Assignment Operator         (15 pts)
make test_group6    # Tracker (Static Class)           (20 pts)
```

To run the full grading report with a score summary:
```bash
make grade
```

### Step 5: Fix Any Failures
Read the test output carefully. Each test group targets a specific feature. Fix your code and re-run the corresponding `make test_groupN` until it passes, then move to the next group.

### Step 6: Clean Up
```bash
make clean
```

## Compilation Reference
```bash
# Compile student program manually
g++ -Wall --std=c++17 -o main MainProgram.cpp

# Compile tests manually
g++ -Wall --std=c++17 -o test_runner test.cpp catch_amalgamated.cpp
./test_runner
```

## Submission Instructions
1. Submit your completed `MainProgram.cpp` file
2. Ensure `make test` passes all tests before submitting
3. Do not modify `test.cpp`, `catch_amalgamated.hpp`, or `catch_amalgamated.cpp`

## Common Mistakes
| Mistake | Consequence |
|---|---|
| Using `delete` instead of `delete[]` | Undefined behavior for arrays |
| Forgetting self-assignment check in `operator=` | Crash: deleting your own data then reading it |
| Shallow copy (copying the pointer, not the data) | Two objects share same memory; double-free crash |
| Forgetting to call `Tracker::objectCreated()` in copy constructor | Tracker count is wrong |
| Calling `Tracker::objectCreated()` in `operator=` | Over-counting: object already exists |
| Not initializing the static member outside the class | Linker error: undefined reference |
| Off-by-one in `get()` boundary checks | Accessing invalid memory |

## Academic Integrity
This lab is an individual assignment. You may discuss concepts with classmates, but all code must be your own. Copying code from another student, AI tools, or online sources without understanding constitutes an academic integrity violation. If you get stuck, ask your TA for help.
