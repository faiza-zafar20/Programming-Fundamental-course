# Q2 - Amicable Pairs

**Name:** Faiza | **Roll No:** 26k0019

### Question
Find all amicable pairs up to n. Example (220, 284) is amicable pair.

### Logic
- Function `sumProperDivisors(x)` calculates sum of proper divisors (divisors except x itself).
- Optimization: Check divisors only up to sqrt(x) to be fast.
- Perfect numbers like 6 and 28 are excluded because sum == number itself.
- Pair is displayed only once with smaller number first: `(a, b)` where `a < b`.

### How to Run
```bash
gcc q2.c -o q2 -lm
./q2
# Input: 3000
