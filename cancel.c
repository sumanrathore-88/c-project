#include <stdio.h>

// Function to cancel a ticket
void cancelTicket(int tickets[], int totalTickets, int ticketNumber) {
    int found = 0;
    for (int i = 0; i < totalTickets; i++) {
        if (tickets[i] == ticketNumber) {
            tickets[i] = 0; // Mark as canceled (0 means canceled)
            found = 1;
            break;
        }
    }

    if (found) {
        printf("Ticket number %d has been successfully canceled.\n", ticketNumber);
    } else {
        printf("Ticket number %d not found or already canceled.\n", ticketNumber);
    }
}

int main() {
    int tickets[5] = {101, 102, 103, 104, 105}; // Example booked tickets
    int totalTickets = 5;
    int ticketNumber;

    printf("Booked Tickets:\n");
    for (int i = 0; i < totalTickets; i++) {
        if (tickets[i] != 0) {
            printf("%d ", tickets[i]);
        }
    }
    printf("\n");

    printf("Enter ticket number to cancel: ");
    scanf("%d", &ticketNumber);

    cancelTicket(tickets, totalTickets, ticketNumber);

    printf("Updated Tickets:\n");
    for (int i = 0; i < totalTickets; i++) {
        if (tickets[i] != 0) {
            printf("%d ", tickets[i]);
        }
    }
    printf("\n");

    return 0;
}
