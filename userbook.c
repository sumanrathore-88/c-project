#include <stdio.h>
#include <string.h>

#define MAX_USERS 5
#define MAX_BUSES 50


struct User {
    char username[30];
    char password[30];
    char name[50];
    int age;
};

struct User users[MAX_USERS];
int userCount = 0;

void registerUser();
int loginUser();
void manageProfile(int userIndex);


char busNo[MAX_BUSES][10];
char busType[MAX_BUSES][20];
int capacity[MAX_BUSES];

char source[MAX_BUSES][30];
char destination[MAX_BUSES][30];
char stops[MAX_BUSES][200];

char departure[MAX_BUSES][10];
char arrival[MAX_BUSES][10];
char date[MAX_BUSES][15];

int busCount = 0;

void addRecord();
void displayRecords();
void searchByBusNo();
void busMenu();

// ---------------------- MAIN ----------------------
int main() {
    int choice, loggedInUser;

    while (1) {
        printf("\n=== USER SYSTEM ===\n");
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            registerUser();
        } 
        else if (choice == 2) {
            loggedInUser = loginUser();
            if (loggedInUser != -1) {
                busMenu(); 
            }
        } 
        else if (choice == 3) {
            printf("Exiting program...\n");
            break;
        } 
        else {
            printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}

// ---------------------- USER FUNCTIONS ----------------------
void registerUser() {
    if (userCount >= MAX_USERS) {
        printf("User limit reached! Cannot register more users.\n");
        return;
    }

    printf("\n=== Register User ===\n");
    printf("Enter username: ");
    scanf("%s", users[userCount].username);
    printf("Enter password: ");
    scanf("%s", users[userCount].password);
    printf("Enter full name: ");
    scanf(" %[^\n]", users[userCount].name); 
    printf("Enter age: ");
    scanf("%d", &users[userCount].age);

    userCount++;
    printf("Registration successful!\n");
}

int loginUser() {
    char username[30], password[30];
    int i;

    printf("\n=== Login ===\n");
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    for (i = 0; i < userCount; i++) {
        if (strcmp(username, users[i].username) == 0 &&
            strcmp(password, users[i].password) == 0) {
            printf("Login successful! Welcome, %s.\n", users[i].name);
            return i;
        }
    }

    printf("Invalid username or password.\n");
    return -1;
}

void manageProfile(int userIndex) {
    int choice;

    while (1) {
        printf("\n=== PROFILE MENU ===\n");
        printf("1. View Profile\n");
        printf("2. Edit Profile\n");
        printf("3. Back\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("\n--- Profile Details ---\n");
            printf("Username: %s\n", users[userIndex].username);
            printf("Name: %s\n", users[userIndex].name);
            printf("Age: %d\n", users[userIndex].age);
        } 
        else if (choice == 2) {
            printf("\nEnter new full name: ");
            scanf(" %[^\n]", users[userIndex].name);
            printf("Enter new age: ");
            scanf("%d", &users[userIndex].age);
            printf("Profile updated successfully!\n");
        } 
        else if (choice == 3) {
            break;
        } 
        else {
            printf("Invalid choice! Try again.\n");
        }
    }
}

// ---------------------- BUS FUNCTIONS ----------------------
void addRecord() {
    if (busCount >= MAX_BUSES) {
        printf("\nDatabase full! Cannot add more records.\n");
    } else {
        printf("\nEnter Bus Number: ");
        scanf("%s", busNo[busCount]);

        printf("Enter Bus Type (AC/Non-AC): ");
        scanf("%s", busType[busCount]);

        printf("Enter Capacity: ");
        scanf("%d", &capacity[busCount]);

        printf("Enter Source: ");
        scanf(" %[^\n]", source[busCount]);

        printf("Enter Destination: ");
        scanf(" %[^\n]", destination[busCount]);

        printf("Enter Stops (comma separated): ");
        scanf(" %[^\n]", stops[busCount]);

        printf("Enter Departure Time (HH:MM): ");
        scanf("%s", departure[busCount]);

        printf("Enter Arrival Time (HH:MM): ");
        scanf("%s", arrival[busCount]);

        printf("Enter Date (DD/MM/YYYY): ");
        scanf("%s", date[busCount]);

        busCount++;
        printf("\nRecord added successfully!\n");
    }
}

void displayRecords() {
    if (busCount == 0) {
        printf("\nNo records found.\n");
    } else {
        int i;
        printf("\n%-10s %-10s %-8s %-15s %-15s %-20s %-10s %-10s %-12s\n",
               "BusNo", "Type", "Capacity", "Source", "Destination", "Stops",
               "Depart", "Arrive", "Date");
        printf("-----------------------------------------------------------------------------------------------------------\n");

        for (i = 0; i < busCount; i++) {
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

    for (int i = 0; i < busCount; i++) {
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

// ---------------------- BUS MENU ----------------------
void busMenu() {
    int choice;
    while (1) {
        printf("\n=== BUS MANAGEMENT MENU ===\n");
        printf("1. Add New Bus/Route/Schedule\n");
        printf("2. Display All Records\n");
        printf("3. Search by Bus Number\n");
        printf("4. Manage Profile\n");
        printf("5. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            addRecord();
        } 
        else if (choice == 2) {
            displayRecords();
        } 
        else if (choice == 3) {
            searchByBusNo();
        } 
        else if (choice == 4) {
            // Profile management of the currently logged-in user
            printf("Feature available only from main login session.\n");
        } 
        else if (choice == 5) {
            printf("\nLogging out...\n");
            break;
        } 
        else {
            printf("\nInvalid choice! Please try again.\n");
        }
    }
}
