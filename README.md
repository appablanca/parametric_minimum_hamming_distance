# Parameterized Minimum Hamming Distance

This project implements a parameterized algorithm for the **Closest String / Minimum Maximum Hamming Distance** problem.

Given a set of strings of equal length, the goal is to find a string that minimizes the maximum Hamming distance to all input strings.

---

## Problem Definition

Given a set of strings

```text
S = {s1, s2, ..., sn}
```

find a string `x` such that

```text
max dH(x, si)
```

is minimized, where `dH` denotes the Hamming distance.

The program outputs a candidate string whose maximum Hamming distance to all input strings is as small as possible.

---

## Input Format

Input files are stored in the `strings/` directory.

Example:

```text
5
abcde
abfde
bbcde
abcdd
abcdf
```

- First line: number of strings (`n`)
- Remaining lines: strings of equal length

---

## Building

Compile with:

```bash
g++ -O3 -std=c++17 solver.cpp -o solver
```

---

## Running

Run the solver on an instance:

```bash
./solver strings/string0.in
```

The program performs a binary search on the optimal value `k`.

Example output:

```text
Trying k = 7
Trying k = 3
Trying k = 5
Trying k = 4
Best k found: 4
```

A solution file is generated automatically.

---

## Algorithm

### Binary Search

The optimal maximum Hamming distance is searched using binary search.

- Lower bound: `0`
- Upper bound: maximum distance from the first input string to any other input string

For a candidate value `k`, the algorithm checks feasibility.

---

### Feasibility Test

The first input string is used as the initial **holy string**.

The recursive branching procedure works as follows:

1. Find a string whose Hamming distance to the current candidate exceeds `k`.
2. If no such string exists, a valid solution has been found.
3. Otherwise, determine the positions where the candidate and the violating string differ.
4. Branch on these positions by changing one character at a time to match the violating string.
5. Recursively continue the search.

The search depth is bounded by `k`.

A pruning rule is used:

```cpp
if (distance - depthLeft > k)
    return false;
```

where:

- `distance` is the Hamming distance to the violating string.
- `depthLeft` is the remaining number of allowed modifications.

If even changing all remaining positions cannot reduce the distance below `k`, the branch is discarded.

---

## File Structure

```text
.
├── solver.cpp
├── validator.py
├── strings/
│   ├── string0.in
│   ├── string1.in
│   ├── string2.in
│   ├── string3.in
│   └── string4.in
└── solutions/
    ├── solutionstring0.in
    ├── solutionstring1.in
    ├── solutionstring2.in
    ├── solutionstring3.in
    └── solutionstring4.in
```

---

## Validation

Validate a generated solution using:

```bash
python3 validator.py strings/string0.in solutions/solutionstring0.in
```

The validator reports the maximum Hamming distance of the candidate string to the input strings.

---

## Complexity

Let:

- `n` = number of strings
- `m` = string length
- `k` = optimal maximum Hamming distance

The feasibility procedure branches on differing positions and has worst-case complexity:

```text
O(m^k)
```

Each validation step requires:

```text
O(nm)
```

Binary search adds an additional factor:

```text
O(log m)
```

Therefore, the algorithm is **fixed-parameter tractable (FPT)** with respect to `k`.

---