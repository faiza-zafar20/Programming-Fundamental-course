// Name: Faiza | Roll No: 26k0019
// Q3 - Greenhouse Temperature Monitoring System

#include <stdio.h>
#define MAX_S 50
#define MAX_H 50

// Function 1: Input all temperatures into 2D array
void inputTemperatures(int sensors, int hours, float temp[MAX_S][MAX_H]) {
    for (int i = 0; i < sensors; i++) {
        printf("Enter %d readings for Sensor %d: ", hours, i + 1);
        for (int j = 0; j < hours; j++) {
            scanf("%f", &temp[i][j]); // Reading temperature
        }
    }
}

// Function 2: Analyze one sensor's data
void analyzeSensor(int hours, float readings[], float *total, float *avg, float *max, float *min, int *critical, int *warning, int *longestStreak) {
    *total = 0; // Initialize total
    *max = readings[0]; // First value as max
    *min = readings[0]; // First value as min
    *critical = 0; // Count of >=40C
    *warning = 0; // Count of 35C-39C
    *longestStreak = 0; // Longest >=35C streak
    int currentStreak = 0;

    for (int j = 0; j < hours; j++) {
        float t = readings[j];
        *total = *total + t; // Add to total

        if (t > *max) *max = t; // Check highest
        if (t < *min) *min = t; // Check lowest

        if (t >= 40.0) (*critical)++; // Critical condition
        if (t >= 35.0 && t <= 39.0) (*warning)++; // Warning condition

        // Longest streak of >=35C
        if (t >= 35.0) {
            currentStreak++;
            if (currentStreak > *longestStreak) {
                *longestStreak = currentStreak;
            }
        } else {
            currentStreak = 0; // Break streak if <35
        }
    }
    *avg = *total / hours; // Calculate average
}

// Function 3: Find sensor with highest average temperature
int findHighestAverage(int sensors, float avgs[]) {
    int index = 0;
    float highest = avgs[0];
    for (int i = 1; i < sensors; i++) {
        if (avgs[i] > highest) {
            highest = avgs[i];
            index = i;
        }
    }
    return index; // Return sensor index (0-based)
}

int main() {
    printf("Name: Faiza - Roll No: 26k0019\n");
    printf("Assignment 2 - Q3 Greenhouse System\n\n");

    int sensors, hours;
    printf("Enter number of sensors: ");
    scanf("%d", &sensors); // Input sensors
    printf("Enter number of hourly readings: ");
    scanf("%d", &hours); // Input hours

    float temp[MAX_S][MAX_H]; // 2D array to store readings
    float averages[MAX_S]; // To store averages

    inputTemperatures(sensors, hours, temp); // Call input function

    printf("\n--- Individual Sensor Reports ---\n");
    for (int i = 0; i < sensors; i++) {
        float total, avg, max, min;
        int critical, warning, longest;
        analyzeSensor(hours, temp[i], &total, &avg, &max, &min, &critical, &warning, &longest); // Analyze
        averages[i] = avg; // Save average

        // Display report with 2 decimal places
        printf("Sensor %d: Total=%.2f Avg=%.2f Max=%.2f Min=%.2f Critical=%d Warning=%d Longest hot streak=%d\n",
               i + 1, total, avg, max, min, critical, warning, longest);
    }

    int highestIndex = findHighestAverage(sensors, averages); // Find highest
    printf("\n--- Final Report ---\n");
    printf("Highest Average: Sensor %d (%.2f)\n", highestIndex + 1, averages[highestIndex]);

    return 0;
}