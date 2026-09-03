#include <stdio.h>

#define MAX 50
char busNo[MAX][10];
char busType[MAX][20];
int capacity[MAX];

char source[MAX][30];
char destination[MAX][30];
char stops[MAX][200];

char departure[MAX][10];
char arrival[MAX][10];
char date[MAX][15];

int count = 0; 


void addRecord() {
    if (count >= MAX) {
        printf("\nDatabase full! Cannot add more records.\n");
    } else {
        printf("\nEnter Bus Number: ");
        scanf("%s", busNo[count]);

        printf("Enter Bus Type (AC/Non-AC): ");
        scanf("%s", busType[count]);

        printf("Enter Capacity: ");
        scanf("%d", &capacity[count]);

        printf("Enter Source: ");
        scanf(" %[^\n]", source[count]);

        printf("Enter Destination: ");
        scanf(" %[^\n]", destination[count]);

        printf("Enter Stops (comma separated): ");
        scanf(" %[^\n]", stops[count]);

        printf("Enter Departure Time (HH:MM): ");
        scanf("%s", departure[count]);

        printf("Enter Arrival Time (HH:MM): ");
        scanf("%s", arrival[count]);

        printf("Enter Date (DD/MM/YYYY): ");
        scanf("%s", date[count]);

        count++;
        printf("\nRecord added successfully!\n");
    }
}


void displayRecords() {
    if (count == 0) {
        printf("\nNo records found.\n");
    } else {
        int i;
        printf("\n%-10s %-10s %-8s %-15s %-15s %-20s %-10s %-10s %-12s\n",
               "BusNo", "Type", "Capacity", "Source", "Destination", "Stops",
               "Depart", "Arrive", "Date");
        printf("-----------------------------------------------------------------------------------------------------------\n");

        for (i = 0; i < count; i++) {
            printf("%-10s %-10s %-8d %-15s %-15s %-20s %-10s %-10s %-12s\n",
                   busNo[i], busType[i], capacity[i],
                   source[i], destination[i], stops[i],
                   departure[i], arrival[i], date[i]);
        }
    }
}


void searchByBusNo() {
    char searchNo[10];
    int found = 0;
    printf("\nEnter Bus Number to Search: ");
    scanf("%s", searchNo);

    for (int i = 0; i < count; i++) {
        if (strcmp(busNo[i], searchNo) == 0) {
            printf("\nBus No: %s\nType: %s\nCapacity: %d\nSource: %s\nDestination: %s\nStops: %s\nDeparture: %s\nArrival: %s\nDate: %s\n",
                   busNo[i], busType[i], capacity[i],
                   source[i], destination[i], stops[i],
                   departure[i], arrival[i], date[i]);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("\nBus Number not found.\n");
    }
}

int main() {
    int choice;

    while (1) {
        printf("\n=== Bus & Route Management System ===\n");
        printf("1. Add New Bus/Route/Schedule\n");
        printf("2. Display All Records\n");
        printf("3. Search by Bus Number\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            addRecord();
        } else if (choice == 2) {
            displayRecords();
        } else if (choice == 3) {
            searchByBusNo();
        } else if (choice == 4) {
            printf("\nExiting Program...\n");
            break;
        } else {
            printf("\nInvalid choice! Please try again.\n");
        }
    }
    return 0;
}



