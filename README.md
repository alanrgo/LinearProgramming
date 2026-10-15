# LinearProgramming

Examples and coursework in linear programming and integer linear programming, implemented with C++, AMPL, and LaTeX.

## Contents

### [`LP with Lemon`](LP%20with%20Lemon/)

A C++ linear-programming model built with the [Lemon graph and optimization library](https://lemon.cs.elte.hu/trac/lemon). The program models monthly cash-flow and investment decisions across savings, CDB, and stock accounts, then solves each test case using Lemon's LP interface.

Source file:

- [`lab6.cpp`](LP%20with%20Lemon/lab6.cpp)

The program reads test cases from standard input and prints the investment and withdrawal decisions for each month, followed by the resulting inheritance balance.

### [`ILP with glpsol`](ILP%20with%20glpsol/)

An AMPL integer linear programming model intended to be solved with [GLPK's `glpsol`](https://www.gnu.org/software/glpk/). The model assigns scenes to recording days while minimizing actors' waiting costs. It includes binary variables for recording days and pre-/post-recording periods.

Model file:

- [`pli.mod`](ILP%20with%20glpsol/pli.mod)

The model expects data such as the number of scenes and actors, the scene/actor participation matrix, and each actor's daily waiting cost.

## Requirements

- A C++ compiler with C++ standard library support.
- [Lemon](https://lemon.cs.elte.hu/trac/lemon), including its LP interface and a configured LP solver backend.
- [GNU GLPK](https://www.gnu.org/software/glpk/) and `glpsol` for the AMPL model.
- An AMPL-compatible modeling environment for running `.mod` files.
- A LaTeX distribution if you want to build the included report source.

## Building the C++ example

The exact compile command depends on how Lemon was installed. A typical command is:

```bash
g++ -std=c++11 -O2 -I/path/to/lemon/include \\
  "LP with Lemon/lab6.cpp" -o lab6 \\
  -L/path/to/lemon/lib -lemon
```

Run the resulting executable with input redirected from a test file:

```bash
./lab6 < input.txt
```

The input format is defined by the program: first provide the number of test cases; each case then provides the initial balance and rates followed by the monthly rate and expense data.

## Running the AMPL model with GLPK

The model contains an example command in its comments. From the `ILP with glpsol` directory, run:

```bash
glpsol --model pli.mod --data e0806.dat --output pli.opt --wcpxlp pli.lp
```

The referenced data file must be supplied separately and follow the parameters and sets declared in `pli.mod`. The model writes the selected scene schedule and objective value to `saida.txt`.

## Project structure

```text
.
├── ILP with glpsol/
│   └── pli.mod
└── LP with Lemon/
    ├── lab6.cpp
    └── relatorio.tex
```

## Notes

This repository contains educational examples and assignment materials. Paths, input files, solver configuration, and output formats may need to be adapted to your local environment.

## License

No license is currently specified for this repository. Unless a license is added, the code should be considered all rights reserved.
