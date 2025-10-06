# Gaussian Elimination (C++ CLI Tool)

A command-line program in C++ for solving linear systems Ax = b using **Gaussian Elimination** on general
m times n systems. It can print **intermediate row operations**, compute **ranks** (of [A|b]),
and print the solution(s) to the system of equations (prints solution(s) if it's a **unique solution** or there are **infinitely many solutions**, otherwise, prints that it has **no solution**).

## Features
- Works with **rectangular systems** \(A \in \mathbb{R}^{m \times n}\): under-, well-, and over-determined
- **Forward elimination** → Row Echelon Form (REF)
- **Back substitution** when applicable
- **Rank computation**: `rank(A)` and `rank([A|b])` to test consistency
- **Intermediate steps**: print each row swap/scale/combination
- Detects **no solution** (inconsistent), **unique solution**, or **infinitely many solutions**
- Print solution(s)
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
1. Two integers **m** and **n** (number of equations and variables)  
2. The **m × n** coefficient matrix **A** (row by row)  
3. The **m × 1** vector **b**

It then performs Gaussian elimination. Then it allows the user to either print the intermediate computations, the rank of [A|b], or the solution(s) to the system of equations (prints that there is no solutions if there is none).

## Project Structure
Gaussian-Elimination.cpp # Main program
README.md # Project overview
LICENSE # MIT License
.gitignore # Ignore build artifacts

## 📂 Project Structure
- `Gaussian-Elimination.cpp` — Main program
- `README.md` — Project overview
- `requirements.txt` — Dependencies/notes
- `LICENSE` — MIT License

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.


