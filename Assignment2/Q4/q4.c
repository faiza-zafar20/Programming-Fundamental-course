// Name: Faiza | Roll No: 26k0019
// Q4 - Bakery Festival Sales Management System

#include <stdio.h>

// Function 1: Get valid festival days (1-7)
int getValidDays() {
    int days;
    do {
        printf("Enter number of festival days (1-7): ");
        scanf("%d", &days);
        if (days < 1 || days > 7) {
            printf("Invalid input! Days must be between 1 and 7. Try again.\n");
        }
    } while (days < 1 || days > 7);
    return days;
}

// Function 2: Calculate sales for one day
float calculateDailySales(int dayNumber) {
    int numOrders;
    printf("\nDay %d - Number of orders: ", dayNumber);
    scanf("%d", &numOrders);

    float total = 0;
    float highest = 0;
    float amount;

    for (int i = 1; i <= numOrders; i++) {
        // Validate amount > 0
        do {
            printf("  Enter amount for order %d: Rs. ", i);
            scanf("%f", &amount);
            if (amount <= 0) {
                printf("    Invalid amount! Must be greater than zero.\n");
            }
        } while (amount <= 0);

        total = total + amount;
        if (i == 1 || amount > highest) {
            highest = amount;
        }
    }

    float average = total / numOrders;
    printf("  Total sales: Rs. %.2f\n", total);
    printf("  Average order: Rs. %.2f\n", average);
    printf("  Highest order: Rs. %.2f\n", highest);

    return total; // Return total for that day
}

// Function 3: Find day with highest sales
int findHighestSalesDay(float dailySales[], int numberOfDays) {
    int highestDay = 1; // Day number starts from 1
    float maxSales = dailySales[0];

    for (int i = 1; i < numberOfDays; i++) {
        if (dailySales[i] > maxSales) {
            maxSales = dailySales[i];
            highestDay = i + 1; // Convert index to day number
        }
    }
    return highestDay; // Earliest day automatically because we use > not >=
}

// Function 4: Display Bar Chart
void displayBarChart(float dailySales[], int numberOfDays) {
    printf("\n===== DAILY SALES BAR CHART =====\n");
    for (int i = 0; i < numberOfDays; i++) {
        int stars = (int)(dailySales[i] / 100); // One * per Rs.100
        printf("Day %d: ", i + 1);
        for (int j = 0; j < stars; j++) {
            printf("*");
        }
        printf(" (Rs. %.2f)\n", dailySales[i]);
    }
}

int main() {
    printf("Name: Faiza - Roll No: 26k0019\n");
    printf("Q4 - Bakery Festival System\n\n");

    int days = getValidDays(); // Step 1
    float dailySales[7]; // One-dimensional array for 7 days max
    float festivalTotal = 0;

    // Step 2: Daily processing
    for (int i = 0; i < days; i++) {
        dailySales[i] = calculateDailySales(i + 1);
        festivalTotal = festivalTotal + dailySales[i];
    }

    // Step 3: Festival Summary
    int highestDay = findHighestSalesDay(dailySales, days);
    printf("\n===== FESTIVAL SUMMARY =====\n");
    printf("Total festival sales: Rs. %.2f\n", festivalTotal);
    printf("Day with highest sales: Day %d\n", highestDay);
    printf("Highest daily sales: Rs. %.2f\n", dailySales[highestDay - 1]);

    // Step 4: Bar Chart
    displayBarChart(dailySales, days);

    return 0;
}