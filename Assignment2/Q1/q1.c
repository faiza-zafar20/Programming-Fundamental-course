/**********************************************
// File Name: q1_cinema_booking.c
// Student Name: Faiza
// Roll No: 26k0019
// Course Name: Programming Fundamentals
// Assignment No: 2, Fall 2026
// Question No: 1 - Cinema Hall Seat Booking
// Description: Manages cinema seats using 2D array, searches from middle row for k consecutive seats
**********************************************/

#include <stdio.h> // For input output //header//

int main(){
    int rows = 0; // Number of rows //rows//
    int seats = 0; // Seats per row //seats//
    int hall[20][20]; // 2D array for seating //hall//
    
    printf("Enter number of rows: "); // Prompt //prompt//
    scanf("%d", &rows); // Read rows //input//
    printf("Enter number of seats per row: "); // Prompt //prompt//
    scanf("%d", &seats); // Read seats //input//

    printf("Enter seating status (0=free, 1=booked):\n"); // Instruction //msg//
    for(int i=0; i<rows; i++){ // Loop rows //row loop//
        for(int j=0; j<seats; j++){ // Loop seats //col loop//
            scanf("%d", &hall[i][j]); // Read seat status //read//
        }
    }

    // 2. Display Seating Arrangement //display part//
    printf("\nSeating Plan (_=free, X=booked):\n"); // Title //title//
    printf("   "); // Space for row labels //space//
    for(int j=0; j<seats; j++) printf("%d ", j); // Print seat numbers //seat header//
    printf("\n"); // New line //line//
    for(int i=0; i<rows; i++){ // Row loop //loop//
        printf("R%d ", i); // Print row number //row no//
        for(int j=0; j<seats; j++){ // Seat loop //loop//
            if(hall[i][j]==0) printf("_ "); // Free seat //free//
            else printf("X "); // Booked seat //booked//
        }
        printf("\n"); // Next row //line//
    }

    // 3. Seat Availability Report //report part//
    int freePerRow[20] = {0}; // Free count per row //count array//
    int totalFree = 0; // Total free seats //total//
    for(int i=0; i<rows; i++){ // Check each row //loop//
        int count = 0; // Counter for row //counter//
        for(int j=0; j<seats; j++){ // Check seats //loop//
            if(hall[i][j]==0) count++; // Increment if free //free check//
        }
        freePerRow[i] = count; // Store row free //store//
        totalFree += count; // Add to total //add total//
    }
    printf("\nFree seats per row: "); // Label //label//
    for(int i=0; i<rows; i++) printf("%d ", freePerRow[i]); // Print per row //print//
    printf(" Total free: %d\n", totalFree); // Print total //print total//

    // 4. Group Booking //booking part//
    int k = 0; // Group size //k//
    printf("\nEnter number of customers (k) who want to sit together: "); // Prompt //prompt//
    scanf("%d", &k); // Read k //input k//

    // Validation //validation//
    if(k <= 0 || k > seats){ // Check valid range //check//
        printf("Invalid group size! Must be >0 and <= %d\n", seats); // Error //error//
        return 0; // Exit //exit//
    }

    // 5. Seat Allocation Rules //allocation//
    int middleRow = rows / 2; // Calculate middle row //middle//
    int foundRow = -1; // Row where block found //found row//
    int foundStart = -1; // Starting seat of block //found seat//

    // Create search order array //order array//
    int searchOrder[20]; // Order of rows to search //order//
    int orderIdx = 0; // Index for order //index//
    
    for(int d=0; d<rows; d++){ // Distance loop //distance//
        int row1 = middleRow - d; // Row below middle //row1//
        int row2 = middleRow + d; // Row above middle //row2//
        if(d==0){ // For middle itself //middle check//
            if(row1>=0 && row1<rows) searchOrder[orderIdx++] = row1; // Add middle //add//
        } else {
            if(row1>=0 && row1<rows) searchOrder[orderIdx++] = row1; // Add smaller first //add small//
            if(row2>=0 && row2<rows) searchOrder[orderIdx++] = row2; // Add larger //add large//
        }
    }

    int isFound = 0; // Flag for found //flag//
    for(int o=0; o<rows && !isFound; o++){ // Loop search order //search loop//
        int r = searchOrder[o]; // Current row to check //current row//
        int consecutive = 0; // Count of free in sequence //consec//
        for(int c=0; c<seats; c++){ // Scan seats left to right //scan//
            if(hall[r][c]==0){ // If free //free//
                consecutive++; // Increase count //inc//
                if(consecutive==k){ // Block found //found check//
                    foundRow = r; // Save row //save row//
                    foundStart = c - k + 1; // Calculate start seat //save start//
                    isFound = 1; // Set flag //set flag//
                    break; // Stop scanning this row //break//
                }
            } else {
                consecutive = 0; // Reset on booked seat //reset//
            }
        }
    }

    // 6. Confirm Booking //confirm//
    if(isFound){ // If block found //if found//
        printf("\nGroup of %d seated in Row %d, Seats %d to %d\n", k, foundRow, foundStart, foundStart+k-1); // Show allocation //allocation msg//
        for(int c=foundStart; c<foundStart+k; c++){ // Book seats //booking//
            hall[foundRow][c]=1; // Mark as booked //mark//
        }

        printf("\nUpdated Seating Plan:\n"); // Title //title//
        printf("   "); // Space //space//
        for(int j=0; j<seats; j++) printf("%d ", j); // Seat numbers //header//
        printf("\n"); // Line //line//
        for(int i=0; i<rows; i++){ // Display updated //loop//
            printf("R%d ", i); // Row no //row//
            for(int j=0; j<seats; j++){ // Seats //loop//
                if(hall[i][j]==0) printf("_ "); // Free //free//
                else printf("X "); // Booked //booked//
            }
            printf("\n"); // Line //line//
        }
        totalFree = totalFree - k; // Update remaining //update total//
        printf("\nRemaining free seats: %d\n", totalFree); // Show remaining //remaining//
    } else {
        // 7. Handle Unsuccessful Bookings //unsuccessful//
        printf("\nSorry, no row contains %d consecutive available seats. Booking failed.\n", k); // Fail msg //fail//
    }

    return 0; // End program //end//
}