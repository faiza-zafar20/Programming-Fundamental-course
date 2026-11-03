// Name: Faiza | Roll No: 26k0019
// Q2 - Amicable Pairs up to n - Part A

#include <stdio.h>
#include <math.h> // For sqrt()

// Function to return sum of proper divisors of a number
int sumProperDivisors(int x) {
    if (x <= 1) {
        return 0; // 1 has no proper divisor
    }
    int sum = 1; // 1 is always a divisor
    int root = (int)sqrt(x);

    for (int i = 2; i <= root; i++) {
        if (x % i == 0) {
            int other = x / i;
            sum = sum + i; // add divisor i
            if (other != i && other != x) {
                sum = sum + other; // add paired divisor, avoid square root twice
            }
        }
    }
    return sum;
}

int main() {
    // Header for Sir requirement
    printf("Name: Faiza - Roll No: 26k0019\n");
    printf("Assignment 2 - Q2 Amicable Pairs\n\n");

    int n; // User input
    printf("Enter value of n: ");
    scanf("%d", &n);

    int totalPairs = 0; // Counter for pairs found
    printf("\nAmicable pairs up to %d:\n", n);

    // Loop from 2 to n
    for (int a = 2; a <= n; a++) {
        int b = sumProperDivisors(a); // sum of divisors of a

        // Rule 2: Do not display perfect numbers (e.g. 6, 28)
        // Rule 1 & 3: b must be different, greater than a (to display smaller first), and within n
        if (b > a && b <= n && b != a) {
            // Check if sum of divisors of b equals a
            if (sumProperDivisors(b) == a) {
                printf("(%d, %d)\n", a, b);
                totalPairs++; // Increment count
            }
        }
    }

    // Rule 4: Display total count
    if (totalPairs == 0) {
        printf("No amicable pairs found up to %d\n", n);
    } else {
        printf("Total pairs: %d\n", totalPairs);
    }

    return 0;
}