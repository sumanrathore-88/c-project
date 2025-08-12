#include <stdio.h>
#define SEATS 10

void bookTicket(int bus[], int n);
void cancelTicket(int bus[], int n);
void checkStatus(int bus[], int n);

int main() {
    int bus[SEATS] = {0}; 
    int choice;

    printf("Welcome to Bus Ticket Booking System\n");

    while (1) {
        printf("\nMenu:\n");
        printf("1. Book a Ticket\n");
        printf("2. Cancel a Ticket\n");
        printf("3. Check Bus Status\n");
        printf("4. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            bookTicket(bus, SEATS);
        }
        else if (choice == 2) {
            cancelTicket(bus, SEATS);
        }
        else if (choice == 3) {
            checkStatus(bus, SEATS);
        }
        else if (choice == 4) {
            printf("Logging out... Goodbye!\n");
            break;
        }
        else {
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

void bookTicket(int bus[], int n) {
    int seatNumber;
    printf("Enter seat number (1-%d) to book: ", n);
    scanf("%d", &seatNumber);

    if (seatNumber < 1 || seatNumber > n) {
        printf("Invalid seat number.\n");
    } else if (bus[seatNumber - 1] == 1) {
        printf("Seat already booked.\n");
    } else {
        bus[seatNumber - 1] = 1;
        printf("Seat %d booked successfully.\n", seatNumber);
    }
}

void cancelTicket(int bus[], int n) {
    int seatNumber;
    printf("Enter seat number (1-%d) to cancel: ", n);
    scanf("%d", &seatNumber);

    if (seatNumber < 1 || seatNumber > n) {
        printf("Invalid seat number.\n");
    } else if (bus[seatNumber - 1] == 0) {
        printf("Seat is not booked.\n");
    } else {
        bus[seatNumber - 1] = 0;
        printf("Seat %d booking canceled successfully.\n", seatNumber);
    }
}

void checkStatus(int bus[], int n) {
    printf("\nBus Seat Status:\n");
    for (int i = 0; i < n; i++) {
        if (bus[i] == 0)
            printf("Seat %d: Empty\n", i + 1);
        else
            printf("Seat %d: Booked\n", i + 1);
    }
}


