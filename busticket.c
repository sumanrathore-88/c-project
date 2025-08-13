#include <stdio.h>

#define MAX_USERS   50
#define MAX_BUSES    3
#define MAX_SEATS   10
#define MAX_LEN     21   


char usernames[MAX_USERS][MAX_LEN];
char passwords[MAX_USERS][MAX_LEN];
int user_count = 0;


int seats[MAX_BUSES][MAX_SEATS];

char bus_names[MAX_BUSES][20] = { "City Express", "Highway Rider", "Night Star" };


int str_eq(const char a[], const char b[]) {
    int i;
    for (i = 0; i < MAX_LEN; i++) {
        if (a[i] != b[i]) return 0;
        if (a[i] == '\0') return 1;
    }
    return 1;
}

void str_copy(char dst[], const char src[]) {
    int i;
    for (i = 0; i < MAX_LEN; i++) {
        dst[i] = src[i];
        if (src[i] == '\0') break;
    }
    if (i == MAX_LEN) dst[MAX_LEN - 1] = '\0';
}


void init_data() {
    int b, s;
    for (b = 0; b < MAX_BUSES; b++) {
        for (s = 0; s < MAX_SEATS; s++) {
            seats[b][s] = -1;
        }
    }
}

void pause_enter() {
    int c;
    printf("\nPress ENTER to continue...");
    
    c = getchar();
    if (c != '\n') {
        
        for (; c != '\n' && c != EOF; c = getchar()) { }
    }
    
    c = getchar();
    if (c != '\n') {
        for (; c != '\n' && c != EOF; c = getchar()) { }
    }
}

void show_buses() {
    int i;
    printf("\nAvailable Buses:\n");
    for (i = 0; i < MAX_BUSES; i++) {
        printf("  %d) %s\n", i + 1, bus_names[i]);
    }
}

void check_bus_status() {
    int b, s;
    show_buses();
    printf("\nEnter bus number to view status: ");
    if (scanf("%d", &b) != 1) { printf("Invalid input.\n"); return; }
    b = b - 1;
    if (b < 0 || b >= MAX_BUSES) {
        printf("Invalid bus choice. Please choose from the menu options.\n");
        return;
    }

    printf("\nBus: %s\n", bus_names[b]);
    printf("Seats (X = booked):\n");
    for (s = 0; s < MAX_SEATS; s++) {
        if (seats[b][s] == -1) {
            printf("%2d ", s + 1);
        } else {
            printf(" X ");
        }
        if ((s + 1) % 10 == 0) printf("\n");
    }
    printf("\n");
}

int find_user_index(const char name[]) {
    int i;
    for (i = 0; i < user_count; i++) {
        if (str_eq(usernames[i], name)) return i;
    }
    return -1;
}

void register_user() {
    char name[MAX_LEN], pass[MAX_LEN];
    int i;

    if (user_count >= MAX_USERS) {
        printf("User limit reached. Cannot register more users.\n");
        return;
    }

    printf("\n--- User Registration ---\n");
    printf("Username (no spaces, max %d chars): ", MAX_LEN - 1);
    if (scanf("%20s", name) != 1) { printf("Invalid input.\n"); return; }

    if (find_user_index(name) != -1) {
        printf("Username already exists. Try a different one.\n");
        return;
    }

    printf("Password (no spaces, max %d chars): ", MAX_LEN - 1);
    if (scanf("%20s", pass) != 1) { printf("Invalid input.\n"); return; }

    str_copy(usernames[user_count], name);
    str_copy(passwords[user_count], pass);
    user_count++;

    printf("Registration successful. You can now login.\n");
}

int login_user() {
    char name[MAX_LEN], pass[MAX_LEN];
    int idx;

    printf("\n--- Login ---\n");
    printf("Username: ");
    if (scanf("%20s", name) != 1) { printf("Invalid input.\n"); return -1; }
    printf("Password: ");
    if (scanf("%20s", pass) != 1) { printf("Invalid input.\n"); return -1; }

    idx = find_user_index(name);
    if (idx == -1) {
        printf("No such user. Please register first.\n");
        return -1;
    }
    if (str_eq(passwords[idx], pass)) {
        printf("Login successful. Welcome, %s!\n", usernames[idx]);
        return idx;
    } else {
        printf("Incorrect password.\n");
        return -1;
    }
}

void book_ticket(int user_idx) {
    int b, s;
    show_buses();
    printf("\nEnter bus number to book: ");
    if (scanf("%d", &b) != 1) { printf("Invalid input.\n"); return; }
    b = b - 1;

    if (b < 0 || b >= MAX_BUSES) {
        printf("Invalid bus choice. Please choose from the menu options.\n");
        return;
    }

    printf("Enter seat number (1-%d): ", MAX_SEATS);
    if (scanf("%d", &s) != 1) { printf("Invalid input.\n"); return; }
    s = s - 1;

    if (s < 0 || s >= MAX_SEATS) {
        printf("Invalid seat number.\n");
        return;
    }
    if (seats[b][s] != -1) {
        printf("Seat already booked.\n");
        return;
    }

    seats[b][s] = user_idx;
    printf("Booked seat %d on %s for user %s.\n", s + 1, bus_names[b], usernames[user_idx]);
}

void cancel_ticket(int user_idx) {
    int b, s;
    show_buses();
    printf("\nEnter bus number to cancel from: ");
    if (scanf("%d", &b) != 1) { printf("Invalid input.\n"); return; }
    b = b - 1;

    if (b < 0 || b >= MAX_BUSES) {
        printf("Invalid bus choice. Please choose from the menu options.\n");
        return;
    }

    printf("Enter seat number (1-%d) to cancel: ", MAX_SEATS);
    if (scanf("%d", &s) != 1) { printf("Invalid input.\n"); return; }
    s = s - 1;

    if (s < 0 || s >= MAX_SEATS) {
        printf("Invalid seat number.\n");
        return;
    }
    if (seats[b][s] == -1) {
        printf("That seat is not booked.\n");
        return;
    }
    if (seats[b][s] != user_idx) {
        printf("You can only cancel seats you booked.\n");
        return;
    }

    seats[b][s] = -1;
    printf("Canceled seat %d on %s.\n", s + 1, bus_names[b]);
}

void user_menu(int user_idx) {
    int choice, running;
    running = 1;

    for (; running; ) {
        printf("\n--- User Menu ---\n");
        printf("1) Book Ticket\n");
        printf("2) Cancel Ticket\n");
        printf("3) Check Bus Status\n");
        printf("4) Logout\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter one of the menu options.\n");
            
            {
                int c;
                for (c = getchar(); c != '\n' && c != EOF; c = getchar()) { }
            }
        } else {
            if (choice == 1) {
                book_ticket(user_idx);
            } else if (choice == 2) {
                cancel_ticket(user_idx);
            } else if (choice == 3) {
                check_bus_status();
            } else if (choice == 4) {
                printf("Logging out...\n");
                running = 0;
            } else {
                printf("Invalid choice. Please enter one of the menu options.\n");
            }
        }
    }
}

int main() {
    int choice;
    int logged_user;

    init_data();

    for (;;) {
        printf("\n=== Bus Reservation System ===\n");
        printf("1) Register\n");
        printf("2) Login\n");
        printf("3) Check Bus Status\n");
        printf("4) Exit\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter one of the menu options.\n");
            
            {
                int c;
                for (c = getchar(); c != '\n' && c != EOF; c = getchar()) { }
            }
        } else {
            if (choice == 1) {
                register_user();
            } else if (choice == 2) {
                logged_user = login_user();
                if (logged_user != -1) {
                    user_menu(logged_user);
                }
            } else if (choice == 3) {
                check_bus_status();
            } else if (choice == 4) {
                printf("Goodbye!\n");
                break;
            } else {
                printf("Invalid choice. Please enter one of the menu options.\n");
            }
        }
        
    }

    return 0;
}