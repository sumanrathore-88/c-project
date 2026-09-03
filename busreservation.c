#include <stdio.h>
#include <string.h>

#define MAX_USERS 10
#define MAX_BUSES 3
#define MAX_SEATS 20

// Structure for storing user data
struct User {
    char username[30];
    char password[30];
};

// Structure for storing bus data
struct Bus {
    int seats[MAX_SEATS]; // 0 = empty, 1 = booked
};

struct User users[MAX_USERS];
struct Bus buses[MAX_BUSES];
int userCount = 0;

// Function declarations
void registerUser();
int loginUser();
void bookTicket();
void cancelTicket();
void checkBusStatus();
void menu(int userIndex);

int main() {
    int choice, loggedInUser = -1;

    while (1) {
        printf("\n====== BUS RESERVATION SYSTEM ======\n");
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            registerUser();
        } else if (choice == 2) {
            loggedInUser = loginUser();
            if (loggedInUser != -1) {
                menu(loggedInUser);
            }
        } else if (choice == 3) {
            printf("Exiting... Goodbye!\n");
            break;
        } else {
            printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}

// Function to register a user
void registerUser() {
    if (userCount >= MAX_USERS) {
        printf("User limit reached! Cannot register more users.\n");
        return;
    }

    printf("\nEnter new username: ");
    scanf("%s", users[userCount].username);
    printf("Enter new password: ");
    scanf("%s", users[userCount].password);

    userCount++;
    printf("Registration successful!\n");
}

// Function to log in a user
int loginUser() {
    char username[30], password[30];
    printf("\nEnter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    for (int i = 0; i < userCount; i++) {
        if (strcmp(username, users[i].username) == 0 &&
            strcmp(password, users[i].password) == 0) {
            printf("Login successful! Welcome, %s.\n", username);
            return i;
        }
    }

    printf("Invalid username or password!\n");
    return -1;
}

// Function to book a ticket
void bookTicket() {
    int busNo, seatNo;
    printf("\nEnter Bus Number (1-%d): ", MAX_BUSES);
    scanf("%d", &busNo);
    printf("Enter Seat Number (1-%d): ", MAX_SEATS);
    scanf("%d", &seatNo);

    if (busNo < 1 || busNo > MAX_BUSES || seatNo < 1 || seatNo > MAX_SEATS) {
        printf("Invalid bus or seat number!\n");
        return;
    }

    if (buses[busNo - 1].seats[seatNo - 1] == 0) {
        buses[busNo - 1].seats[seatNo - 1] = 1;
        printf("Seat booked successfully!\n");
    } else {
        printf("Sorry, that seat is already booked.\n");
    }
}

// Function to cancel a ticket
void cancelTicket() {
    int busNo, seatNo;
    printf("\nEnter Bus Number (1-%d): ", MAX_BUSES);
    scanf("%d", &busNo);
    printf("Enter Seat Number (1-%d): ", MAX_SEATS);
    scanf("%d", &seatNo);

    if (busNo < 1 || busNo > MAX_BUSES || seatNo < 1 || seatNo > MAX_SEATS) {
        printf("Invalid bus or seat number!\n");
        return;
    }

    if (buses[busNo - 1].seats[seatNo - 1] == 1) {
        buses[busNo - 1].seats[seatNo - 1] = 0;
        printf("Ticket cancelled successfully!\n");
    } else {
        printf("That seat is not currently booked.\n");
    }
}

// Function to check bus status
void checkBusStatus() {
    for (int b = 0; b < MAX_BUSES; b++) {
        printf("\nBus %d seat status:\n", b + 1);
        for (int s = 0; s < MAX_SEATS; s++) {
            printf("Seat %2d: %s\n", s + 1,
                   buses[b].seats[s] == 0 ? "Empty" : "Booked");
        }
    }
}

// Menu after login
void menu(int userIndex) {
    int choice;
    while (1) {
        printf("\n====== MAIN MENU ======\n");
        printf("1. Book Ticket\n");
        printf("2. Cancel Ticket\n");
        printf("3. Check Bus Status\n");
        printf("4. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            bookTicket();
        } else if (choice == 2) {
            cancelTicket();
        } else if (choice == 3) {
            checkBusStatus();
        } else if (choice == 4) {
            printf("Logging out...\n");
            break;
        } else {
            printf("Invalid choice! Please try again.\n");
        }
    }
}
