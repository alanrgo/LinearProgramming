# Linear Programming with Lemon

This example solves a **monthly financial planning and investment allocation problem** using the [Lemon](https://lemon.cs.elte.hu/trac/lemon) linear-programming interface.

## Problem context

The scenario starts with an inheritance or initial amount of money that must be managed over a twelve-month period. Each month has an expense, and the available money can be allocated among three investment options:

- Savings (`poupança`).
- A fixed-income CDB account.
- Stocks (`ações`).

The model can invest additional money in an account or withdraw money from it. Each investment has its own return rate, and withdrawals may have associated costs or penalties. The objective is to maximize the total balance at the end of the planning horizon, after accounting for monthly expenses and investment returns.

The model also applies timing rules, including:

- No withdrawals at the beginning of the first month.
- No new investments in the final month.
- Monthly cash-flow conservation.
- Non-negative balances and transaction amounts.

## Model structure

The implementation in [`lab6.cpp`](lab6.cpp) creates a linear program for each test case. It uses variables for:

- Monthly cash balances.
- Savings investments and withdrawals.
- CDB investments and withdrawals.
- Stock investments and withdrawals.

The objective maximizes the final cash balance together with the final balances of the three investment accounts. If the solver finds an optimal solution, the program prints the recommended monthly transactions and the resulting final balance.

## Input and output

The program reads from standard input. The first value is the number of test cases. Each test case contains:

1. The initial amount and fixed parameters.
2. Twelve CDB return rates.
3. Twelve stock return rates.
4. Twelve monthly expense values.

The program prints a report for each case, including investment and withdrawal amounts for each month and the final inheritance balance. Monetary values are printed with two decimal places.

Run the compiled program with input redirected from a file:

```bash
./lab6 < input.txt
```

## Building

The project requires a C++ compiler and a configured Lemon installation with an LP solver backend. A typical build command is:

```bash
g++ -std=c++11 -O2 -I/path/to/lemon/include \\
  lab6.cpp -o lab6 \\
  -L/path/to/lemon/lib -lemon
```

Adjust the include and library paths for the local Lemon installation.

## Files

- [`lab6.cpp`](lab6.cpp): C++ linear-programming implementation.
- [`relatorio.tex`](relatorio.tex): LaTeX report associated with the assignment.

## Technologies

- C++
- [Lemon](https://lemon.cs.elte.hu/trac/lemon)
- A compatible LP solver supported by the Lemon installation

This example is intended for educational use and demonstrates how financial decisions can be represented as a linear optimization problem.
