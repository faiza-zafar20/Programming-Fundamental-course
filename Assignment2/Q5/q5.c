// Name: Faiza | Roll No: 26k0019
// Q5 - University Library Management System

#include <stdio.h>
#include <string.h>

#define TOTAL_BOOKS 4

// Function 1: Display Menu
void displayMenu() {
    printf("\n===== University Library Menu =====\n");
    printf("1. Member Registration\n");
    printf("2. Display Available Books\n");
    printf("3. Borrow a Book\n");
    printf("4. Return a Book\n");
    printf("5. Display Member Record\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
}

// Function 2: Register Member
void registerMember(char name[], int *studentID, int *memberType) {
    printf("\n--- Member Registration ---\n");
    printf("Enter name: ");
    scanf(" %[^\n]", name); // Read name with spaces
    printf("Enter Student ID: ");
    scanf("%d", studentID);
    printf("Enter Membership Type (0 for Student, 1 for Faculty): ");
    scanf("%d", memberType);
    // 0 = Student (14 days), 1 = Faculty (30 days)
    if (*memberType == 0) {
        printf("Registered as Student. Allowed 14 days per book.\n");
    } else {
        printf("Registered as Faculty. Allowed 30 days per book.\n");
    }
}

// Function 3: Display Books in tabular format
void displayBooks(int bookIDs[], char bookTitles[][50], int availableCopies[], int totalBooks) {
    printf("\n--- Available Books ---\n");
    printf("%-10s %-30s %-10s\n", "ID", "Title", "Copies");
    printf("---------------------------------------------------\n");
    for (int i = 0; i < totalBooks; i++) {
        printf("%-10d %-30s %-10d\n", bookIDs[i], bookTitles[i], availableCopies[i]);
    }
}

// Function 4: Borrow a Book
void borrowBook(int bookIDs[], char bookTitles[][50], int availableCopies[], int totalBooks, int borrowedBookIDs[], int *borrowedCount, int memberType) {
    if (*borrowedCount >= 3) {
        printf("Cannot borrow! Maximum 3 books allowed at a time.\n");
        return;
    }

    int bID, days;
    printf("\nEnter Book ID to borrow: ");
    scanf("%d", &bID);
    printf("Enter number of days you intend to keep: ");
    scanf("%d", &days);

    if (days <= 0) {
        printf("Invalid days! Must be positive.\n");
        return;
    }

    // Find book index
    int index = -1;
    for (int i = 0; i < totalBooks; i++) {
        if (bookIDs[i] == bID) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Invalid Book ID!\n");
        return;
    }
    if (availableCopies[index] <= 0) {
        printf("No copies available for '%s'\n", bookTitles[index]);
        return;
    }

    // Record borrowing
    borrowedBookIDs[*borrowedCount] = bID;
    (*borrowedCount)++;
    availableCopies[index]--;
    printf("Successfully borrowed '%s'. Remaining copies: %d\n", bookTitles[index], availableCopies[index]);
}

// Function 5: Return a Book
float returnBook(int bookIDs[], int availableCopies[], int totalBooks, int borrowedBookIDs[], int *borrowedCount, int memberType, float *totalFine) {
    int bID, actualDays;
    printf("\nEnter Book ID to return: ");
    scanf("%d", &bID);
    printf("Enter actual number of days book was kept: ");
    scanf("%d", &actualDays);

    if (actualDays <= 0) {
        printf("Invalid days!\n");
        return 0;
    }

    // Verify member has borrowed this book
    int pos = -1;
    for (int i = 0; i < *borrowedCount; i++) {
        if (borrowedBookIDs[i] == bID) {
            pos = i;
            break;
        }
    }
    if (pos == -1) {
        printf("You have not borrowed this book!\n");
        return 0;
    }

    // Find book index in inventory
    int index = -1;
    for (int i = 0; i < totalBooks; i++) {
        if (bookIDs[i] == bID) {
            index = i;
            break;
        }
    }

    // Increase copies
    availableCopies[index]++;

    // Calculate late fine
    int allowedDays = (memberType == 0) ? 14 : 30;
    int extra = actualDays - allowedDays;
    float fine = 0;
    if (extra > 0) {
        float rate = (memberType == 0) ? 20.0 : 10.0; // Student 20, Faculty 10
        fine = extra * rate;
        *totalFine = *totalFine + fine; // Update cumulative before waiver
        printf("Late by %d days. Fine: Rs. %.2f\n", extra, fine);
    } else {
        printf("Returned on time. No fine.\n");
    }

    // Waiver code check LIB2026
    char code[20];
    float finalPayable = fine;
    if (fine > 0) {
        printf("Enter membership code for waiver (if any): ");
        scanf("%s", code);
        if (strcmp(code, "LIB2026") == 0) {
            finalPayable = fine * 0.5;
            printf("Code correct! 50%% waiver applied. Final fine for this book: Rs. %.2f\n", finalPayable);
        } else {
            printf("Invalid code. No waiver. Final fine: Rs. %.2f\n", finalPayable);
        }
    }

    // Remove from borrowed list
    for (int i = pos; i < *borrowedCount - 1; i++) {
        borrowedBookIDs[i] = borrowedBookIDs[i + 1];
    }
    (*borrowedCount)--;

    return finalPayable; // Return payable for current return
}

// Function 6: Display Member Record
void displayMemberRecord(char name[], int studentID, int memberType, int borrowedBookIDs[], int borrowedCount, float totalFine, float finalAfterWaiver) {
    printf("\n--- Member Record ---\n");
    printf("Name: %s\n", name);
    printf("Student ID: %d\n", studentID);
    printf("Membership Type: %s\n", (memberType == 0) ? "Student" : "Faculty");
    printf("Currently Borrowed Books (%d): ", borrowedCount);
    if (borrowedCount == 0) {
        printf("None\n");
    } else {
        for (int i = 0; i < borrowedCount; i++) {
            printf("%d ", borrowedBookIDs[i]);
        }
        printf("\n");
    }
    printf("Total fine charged before waiver: Rs. %.2f\n", totalFine);
    printf("Final fine payable after waiver: Rs. %.2f\n", finalAfterWaiver);
}

// Main
int main() {
    printf("Name: Faiza - Roll No: 26k0019\n");
    printf("Q5 - University Library Management System\n");

    // Initialize inventory
    int bookIDs[TOTAL_BOOKS] = {101, 102, 103, 104};
    char bookTitles[TOTAL_BOOKS][50] = {"Programming in C", "Data Structures", "Database Systems", "Computer Networks"};
    int availableCopies[TOTAL_BOOKS] = {5, 3, 0, 4};

    char memberName[50] = "";
    int studentID = 0;
    int memberType = 0; // 0 Student, 1 Faculty
    int borrowedBookIDs[10];
    int borrowedCount = 0;
    float totalFineBefore = 0; // Cumulative before waiver
    float totalFinalAfter = 0; // Cumulative after waiver
    int isRegistered = 0;

    int choice;
    do {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerMember(memberName, &studentID, &memberType);
                isRegistered = 1;
                borrowedCount = 0;
                totalFineBefore = 0;
                totalFinalAfter = 0;
                break;
            case 2:
                displayBooks(bookIDs, bookTitles, availableCopies, TOTAL_BOOKS);
                break;
            case 3:
                if (!isRegistered) { printf("Please register member first!\n"); break; }
                borrowBook(bookIDs, bookTitles, availableCopies, TOTAL_BOOKS, borrowedBookIDs, &borrowedCount, memberType);
                break;
            case 4:
                if (!isRegistered) { printf("Please register member first!\n"); break; }
                float pay = returnBook(bookIDs, availableCopies, TOTAL_BOOKS, borrowedBookIDs, &borrowedCount, memberType, &totalFineBefore);
                totalFinalAfter += pay;
                break;
            case 5:
                if (!isRegistered) { printf("Please register member first!\n"); break; }
                displayMemberRecord(memberName, studentID, memberType, borrowedBookIDs, borrowedCount, totalFineBefore, totalFinalAfter);
                break;
            case 6:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice! Try again.\n");
        }
    } while (choice != 6);

    return 0;
}