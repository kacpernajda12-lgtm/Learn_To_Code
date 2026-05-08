# C++ Tutorial

A ground-up walkthrough of C++ fundamentals. Each file is self-contained and heavily commented.

## Files

| # | File | Topic |
|---|------|-------|
| 01 | `01_hello_world.cpp` | Your first C++ program |
| 02 | `02_variables_and_types.cpp` | Data types, variables, constants |
| 03 | `03_operators.cpp` | Arithmetic, comparison, logical operators |
| 04 | `04_control_flow.cpp` | if/else, switch, while, for, break, continue |
| 05 | `05_functions.cpp` | Functions, parameters, return values, recursion |
| 06 | `06_arrays_and_vectors.cpp` | Fixed arrays and dynamic vectors |
| 07 | `07_pointers_and_references.cpp` | Memory addresses, pointers, dynamic allocation |
| 08 | `08_classes_and_oop.cpp` | Classes, inheritance, polymorphism |

### Advanced

| # | File | Topic |
|---|------|-------|
| 09 | `09_templates.cpp` | Function & class templates, specialisation |
| 10 | `10_stl_containers.cpp` | list, deque, map, set, queue, stack |
| 11 | `11_smart_pointers.cpp` | unique_ptr, shared_ptr, weak_ptr |
| 12 | `12_lambdas_and_stl_algorithms.cpp` | Lambdas, sort, transform, accumulate |
| 13 | `13_exception_handling.cpp` | try/catch, custom exceptions, RAII |
| 14 | `14_file_io.cpp` | Read/write text & binary files |
| 15 | `15_move_semantics.cpp` | Rvalue refs, Rule of Five, std::move |
| 16 | `16_multithreading.cpp` | thread, mutex, atomic, future, condition_variable |

## How to compile and run

Using g++ (MinGW / GCC):

```bash
g++ 01_hello_world.cpp -o hello && ./hello
```

Or compile any file:

```bash
g++ <filename>.cpp -o out && ./out
```
