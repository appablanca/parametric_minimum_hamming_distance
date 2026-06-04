# Parameterized Minimum Hamming Distance

This project implements a parameterized algorithm for the **Minimum Maximum Hamming Distance** problem.

Given a set of strings of equal length, the goal is to find a string $begin:math:text$ s $end:math:text$ that minimizes the maximum Hamming distance to all input strings.

---

## Problem Definition

Given strings

$begin:math:display$
S \= \\\{s\_1\, s\_2\, \\dots\, s\_n\\\}
$end:math:display$

find a string $begin:math:text$ x $end:math:text$ such that

$begin:math:display$
\\max\_i d\_H\(x\,s\_i\)
$end:math:display$

is minimized, where $begin:math:text$ d\_H $end:math:text$ denotes the Hamming distance.

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

- First line: number of strings $begin:math:text$ n $end:math:text$
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

The program performs a binary search on the optimal value $begin:math:text$ k $end:math:text$.

Example output:

```text
Trying k = 7
Trying k = 3
Trying k = 5
Trying k = 4
Best k found: 4
```

A solution file is generated automatically:

```text
solutionstrings/string0.in
```

(or generally `solution<instance-name>`).

---

## Algorithm

### Binary Search

The optimal maximum Hamming distance is searched using binary search.

- Lower bound: `0`
- Upper bound: maximum distance from the first input string to any other input string

For a candidate value $begin:math:text$ k $end:math:text$, the algorithm checks feasibility.

---

### Feasibility Test

The first input string is used as the initial **holy string**.

The recursive branching procedure works as follows:

1. Find a string whose Hamming distance to the current candidate exceeds $begin:math:text$ k $end:math:text$.
2. If no such string exists, a valid solution has been found.
3. Otherwise, choose one differing position.
4. Change the candidate string at that position to match the violating string.
5. Recurse.

The search depth is bounded by $begin:math:text$ k $end:math:text$.

A pruning rule is used:

```cpp
if (d - depthLeft > k)
    return false;
```

where

- `d` is the distance to the violating string,
- `depthLeft` is the remaining number of allowed modifications.

If even changing all remaining positions cannot reduce the distance below $begin:math:text$ k $end:math:text$, the branch is discarded.

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

The provided validator can be used to evaluate a produced solution:

```bash
python3 validator.py strings/string0.in solutions/solutionstring0.in
```

The validator reports the maximum Hamming distance of the candidate string to the input strings.

---

## Complexity

Let

- $begin:math:text$ n $end:math:text$ = number of strings,
- $begin:math:text$ m $end:math:text$ = string length,
- $begin:math:text$ k $end:math:text$ = optimal maximum Hamming distance.

The feasibility procedure branches on differing positions and has worst-case complexity

$begin:math:display$
O\(m\^k\)
$end:math:display$

while each validation step requires

$begin:math:display$
O\(nm\)\.
$end:math:display$

Binary search introduces an additional factor of

$begin:math:display$
O\(\\log m\)\.
$end:math:display$

Thus the algorithm is fixed-parameter tractable with respect to $begin:math:text$ k $end:math:text$.

---