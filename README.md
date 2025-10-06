# Gaussian Elimination (C++ CLI Tool)

A command-line program written in C++ that solves systems of linear equations using the **Gaussian Elimination** algorithm.

---

## Features
- Performs forward elimination to reduce a matrix to row echelon form
- Back substitution to compute solutions
- Detects inconsistent or singular systems (if applicable)
- Lightweight, single-file implementation — easy to compile and run

---

## Build & Run

### Linux / macOS (GCC/Clang)
```bash
g++ -O2 -std=c++17 -o gauss Gaussian-Elimination.cpp
./gauss
