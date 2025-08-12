#include <stdio.h>
#include <string.h>


#define MAX_USERS 5


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
                manageProfile(loggedInUser);
            }
        } 
        else if (choice == 3) {
            printf("Exiting...\n");
            break;
        } 
        else {
            printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}


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
        printf("3. Logout\n");
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
            printf("Logging out...\n");
            break;
        } 
        else {
            printf("Invalid choice! Try again.\n");
        }
    }
}