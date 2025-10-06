# Gaussian Elimination (C++ CLI Tool)

A command-line program in C++ for solving linear systems \(A x = b\) using **Gaussian Elimination** on general
\(m \times n\) systems. It can print **intermediate row operations**, compute **ranks** (of \(A\) and \([A|b]\)),
and report whether the system has a **unique solution**, **infinitely many solutions**, or **no solution**.

## Features
- Works with **rectangular systems** \(A \in \mathbb{R}^{m \times n}\): under-, well-, and over-determined
- **Forward elimination** → Row Echelon Form (REF)
- **Back substitution** when applicable
- **Rank computation**: `rank(A)` and `rank([A|b])` to test consistency
- **Intermediate steps**: print each row swap/scale/combination
- Detects **no solution** (inconsistent), **unique solution**, or **infinitely many solutions**
- Lightweight single-file implementation

## Build & Run

### Linux / macOS (GCC/Clang)
```bash
g++ -O2 -std=c++17 -o gauss Gaussian-Elimination.cpp
./gauss
```

### Windows (MSVC)
```bash
cl /O2 /std:c++17 Gaussian-Elimination.cpp /Fe:gauss.exe
gauss.exe
```

## Usage

The program expects:
1. Two integers **m n** (number of equations and variables)  
2. The **m × n** coefficient matrix **A** (row by row)  
3. The **m × 1** vector **b**

It then performs elimination. If intermediate printing is enabled in the program (e.g., via a prompt),
you’ll see each row operation and the evolving matrix.

## Input / Output Examples

### Square system (unique solution)
**Input**
3 3
2 1 -1
-3 -1 2
-2 1 2
8 -11 -3

**Abridged output**
[Step] R2 <- R2 + 1.5 * R1
[Step] R3 <- R3 + 1.0 * R1
...
rank(A) = 3
rank([A|b]) = 3
Unique solution:
x1 = 2
x2 = 3
x3 = -1

### Rectangular system (infinitely many solutions)
**Input**
2 3
1 2 3
2 4 6
5
10

**Abridged output**
[Step] R2 <- R2 - 2 * R1
...
rank(A) = 1
rank([A|b]) = 1
Infinitely many solutions (free variables present)


### Inconsistent system (no solution)
**Input**
2 2
1 1
1 1
1
2

**Abridged output**
rank(A) = 1
rank([A|b]) = 2
No solution (system inconsistent)


## Notes & Tips
- **Numerical stability:** partial pivoting (swapping the row with the largest pivot) is recommended.
- **Verification:** printing a residual like \|A x − b\| helps sanity-check solutions.
- **Extensions:** you can add flags (e.g., `--steps`, `--rref`) for nicer UX.

## Project Structure
Gaussian-Elimination.cpp # Main program
README.md # Project overview
LICENSE # MIT License
.gitignore # Ignore build artifacts

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.


