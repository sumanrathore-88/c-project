#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_USERS 50
#define MAX_BUSES 10
#define MAX_SEATS 40
#define MAX_BOOKINGS 200


typedef struct {
    char username[21];   
    char password[21];   
    int active;       
} User;

typedef struct {
    int busNo;               
    char type[8];              
    char source[20];
    char destination[20];
    float baseFare;            
    int seats[MAX_SEATS];      
} Bus;

typedef struct {
    int bookingId;             
    char username[21];
    int busNo;
    int seatNo;               
    float fare;                
    int paid;              
    int active;                
} Booking;


User users[MAX_USERS];
Bus buses[MAX_BUSES];
Booking bookings[MAX_BOOKINGS];
int userCount = 0;
int bookingCount = 0;


const char *SOURCES[] = {"jodhpur","delhi","mumbai","jaipur","gujrat"};
const int SOURCES_LEN = 5;
const char *DESTS[]   = {"delhi","mumbai","gujrat","sikar","ajmer","pune"};
const int DESTS_LEN = 6;


int isLettersOnly(const char *s){
    if(!s || !*s) return 0;
    for(int i=0;s[i];i++){
        if(!isalpha((unsigned char)s[i])) return 0;
    }
    return 1;
}

int isAlphaNum(const char *s){
    if(!s || !*s) return 0;
    for(int i=0;s[i];i++){
        if(!isalnum((unsigned char)s[i])) return 0;
    }
    return 1;
}

int readInt(){
    int x; 
    if(scanf("%d", &x)!=1){
        // clear invalid input
        int c; while((c=getchar())!='\n' && c!=EOF){} 
        return -1; 
    }
    return x;
}

void pressEnter(){
    printf("\nPress ENTER to continue...");
    int c; while((c=getchar())!='\n' && c!=EOF){} // flush line
    getchar();
}

// ----------------------------- Users -----------------------------
int findUserIndex(const char *username){
    for(int i=0;i<userCount;i++){
        if(users[i].active && strcmp(users[i].username, username)==0) return i;
    }
    return -1;
}

void registerUser(){
    if(userCount >= MAX_USERS){
        printf("\n[!] User limit reached.\n");
        return;
    }
    char u[21], p[21];
    printf("\n--- User Registration ---\n");
    printf("Enter username (letters only, max 20): ");
    scanf("%20s", u);
    if(!isLettersOnly(u)){
        printf("Invalid username. Use letters only.\n");
        return;
    }
    if(findUserIndex(u) != -1){
        printf("Username already exists. Try login.\n");
        return;
    }
    printf("Enter password (letters & digits, max 20): ");
    scanf("%20s", p);
    if(!isAlphaNum(p)){
        printf("Invalid password. Use letters and digits only.\n");
        return;
    }
    strcpy(users[userCount].username, u);
    strcpy(users[userCount].password, p);
    users[userCount].active = 1;
    userCount++;
    printf("\n[✔] Registration successful. You can now login.\n");
}

int loginUser(){
    char u[21], p[21];
    printf("\n--- Login ---\nUsername: ");
    scanf("%20s", u);
    printf("Password: ");
    scanf("%20s", p);
    int idx = findUserIndex(u);
    if(idx == -1){
        printf("No such user. Please register first.\n");
        return -1;
    }
    if(strcmp(users[idx].password, p)==0){
        printf("\n[✔] Login successful. Welcome, %s!\n", users[idx].username);
        return idx;
    } else {
        printf("Incorrect password.\n");
        return -1;
    }
}


void initBuses(){
    
    struct {int no; const char* type; const char* src; const char* dst; float fare;} init[] = {
        {1,  "AC",     "jodhpur", "delhi",  850},
        {2,  "Non-AC", "jodhpur", "jaipur", 450},
        {3,  "AC",     "delhi",   "mumbai", 1600},
        {4,  "Non-AC", "jaipur",  "ajmer",  300},
        {5,  "AC",     "mumbai",  "pune",   600},
        {6,  "Non-AC", "delhi",   "sikar",  550},
        {7,  "AC",     "jaipur",  "delhi",  700},
        {8,  "Non-AC", "gujrat",  "mumbai", 900},
        {9,  "AC",     "gujrat",  "pune",   1200},
        {10, "Non-AC", "mumbai",  "gujrat", 900}
    };

    for(int i=0;i<MAX_BUSES;i++){
        buses[i].busNo = init[i].no;
        strcpy(buses[i].type, init[i].type);
        strcpy(buses[i].source, init[i].src);
        strcpy(buses[i].destination, init[i].dst);
        buses[i].baseFare = init[i].fare;
        for(int s=0;s<MAX_SEATS;s++) buses[i].seats[s] = 0;
    }
}

int findBusIndexByNo(int busNo){
    for(int i=0;i<MAX_BUSES;i++) if(buses[i].busNo==busNo) return i;
    return -1;
}

void listRoutesPool(){
    printf("\nAvailable Sources: ");
    for(int i=0;i<SOURCES_LEN;i++) printf("%s%s", SOURCES[i], (i==SOURCES_LEN-1)?"":" | ");
    printf("\nAvailable Destinations: ");
    for(int i=0;i<DESTS_LEN;i++) printf("%s%s", DESTS[i], (i==DESTS_LEN-1)?"":" | ");
    printf("\n");
}

void listBuses(){
    printf("\n--- Bus & Route List ---\n");
    printf("BusNo  Type     Route (Source -> Destination)   Base Fare\n");
    printf("-----------------------------------------------------------\n");
    for(int i=0;i<MAX_BUSES;i++){
        printf("%-6d %-7s  %s -> %s %24.2f\n", 
               buses[i].busNo, buses[i].type, buses[i].source, buses[i].destination, buses[i].baseFare);
    }
}

void showSeats(int busIdx){
    printf("\nSeats for Bus %d (%s %s->%s):\n", buses[busIdx].busNo, buses[busIdx].type, buses[busIdx].source, buses[busIdx].destination);
    printf("[0=free, 1=booked]\n");
    for(int i=0;i<MAX_SEATS;i++){
        printf("%d:%d%s", i+1, buses[busIdx].seats[i], ((i+1)%10==0)?"\n":"  ");
    }
}

int availableSeatCount(int busIdx){
    int c=0; for(int i=0;i<MAX_SEATS;i++) if(buses[busIdx].seats[i]==0) c++; return c;
}


float calculateFare(int busIdx){
    
    float fare = buses[busIdx].baseFare;
    if(strcmp(buses[busIdx].type, "AC") == 0) fare *= 1.125f;
    fare += 20.0f; // booking fee
    return fare;
}

int processPayment(float amount){
    int method;
    printf("\n--- Payment ---\n");
    printf("Amount payable: %.2f\n", amount);
    printf("1) UPI\n2) Card\n3) Cash\nChoose method: ");
    method = readInt();
    if(method<1 || method>3){
        printf("Invalid method. Payment failed.\n");
        return 0;
    }
    float paid;
    printf("Enter amount tendered: ");
    if(scanf("%f", &paid)!=1){
        int c; while((c=getchar())!='\n' && c!=EOF){}
        printf("Invalid amount.\n");
        return 0;
    }
    if((paid + 0.005f) < amount){
        printf("Insufficient amount. Payment failed.\n");
        return 0;
    }
    float change = paid - amount;
    if(change < 0) change = 0;
    printf("Payment successful. Change: %.2f\n", change);
    return 1;
}


int nextBookingId(){ return bookingCount + 1001; }

int createBooking(const char* username, int busIdx, int seatNo, float fare){
    if(bookingCount >= MAX_BOOKINGS) return -1;
    bookings[bookingCount].bookingId = nextBookingId();
    strcpy(bookings[bookingCount].username, username);
    bookings[bookingCount].busNo = buses[busIdx].busNo;
    bookings[bookingCount].seatNo = seatNo;
    bookings[bookingCount].fare = fare;
    bookings[bookingCount].paid = 1;
    bookings[bookingCount].active = 1;
    bookingCount++;
    return bookings[bookingCount-1].bookingId;
}

int findBookingIndex(int bookingId){
    for(int i=0;i<bookingCount;i++){
        if(bookings[i].active && bookings[i].bookingId==bookingId) return i;
    }
    return -1;
}

void showMyTickets(const char* username){
    int found=0;
    printf("\n--- Your Tickets ---\n");
    for(int i=0;i<bookingCount;i++){
        if(bookings[i].active && strcmp(bookings[i].username, username)==0){
            int bIdx = findBusIndexByNo(bookings[i].busNo);
            printf("ID:%d  Bus:%d  %s->%s  Type:%s  Seat:%d  Fare:%.2f\n",
                   bookings[i].bookingId,
                   bookings[i].busNo,
                   buses[bIdx].source,
                   buses[bIdx].destination,
                   buses[bIdx].type,
                   bookings[i].seatNo,
                   bookings[i].fare);
            found=1;
        }
    }
    if(!found) printf("No active tickets.\n");
}

void bookTicket(const char* username){
    listBuses();
    printf("\nEnter Bus Number to book: ");
    int busNo = readInt();
    int bIdx = findBusIndexByNo(busNo);
    if(bIdx==-1){ printf("Invalid bus number.\n"); return; }

    int freeSeats = availableSeatCount(bIdx);
    if(freeSeats==0){ printf("No seats available on this bus.\n"); return; }

    showSeats(bIdx);
    printf("\nSelect seat number (1-%d): ", MAX_SEATS);
    int seatNo = readInt();
    if(seatNo<1 || seatNo>MAX_SEATS){ printf("Invalid seat number.\n"); return; }
    if(buses[bIdx].seats[seatNo-1]==1){ printf("Seat already booked.\n"); return; }

    float fare = calculateFare(bIdx);
    printf("\nCalculated Fare: %.2f\n", fare);
    if(!processPayment(fare)){
        printf("Booking aborted due to payment failure.\n");
        return;
    }

    buses[bIdx].seats[seatNo-1] = 1;
    int bid = createBooking(username, bIdx, seatNo, fare);
    if(bid==-1){
        printf("System full, couldn't create booking.\n");
        buses[bIdx].seats[seatNo-1] = 0; 
        return;
    }
    printf("\n[✔] Ticket booked! Booking ID: %d\n", bid);
}

void cancelTicket(const char* username){
    printf("\nEnter Booking ID to cancel: ");
    int id = readInt();
    int idx = findBookingIndex(id);
    if(idx==-1){ printf("Invalid Booking ID.\n"); return; }
    if(strcmp(bookings[idx].username, username)!=0){
        printf("You can only cancel your own tickets.\n");
        return;
    }

    int bIdx = findBusIndexByNo(bookings[idx].busNo);
    int seat = bookings[idx].seatNo;
    float refund = bookings[idx].fare * 0.80f; 

    bookings[idx].active = 0;
    buses[bIdx].seats[seat-1] = 0;

    printf("\n[✔] Ticket cancelled. Refund amount: %.2f\n", refund);
}

void modifyTicket(const char* username){
    printf("\nEnter Booking ID to modify: ");
    int id = readInt();
    int idx = findBookingIndex(id);
    if(idx==-1){ printf("Invalid Booking ID.\n"); return; }
    if(strcmp(bookings[idx].username, username)!=0){
        printf("You can only modify your own tickets.\n");
        return;
    }

    int bIdx = findBusIndexByNo(bookings[idx].busNo);
    printf("\nModify Options:\n1) Change Seat (same bus)\n2) Change Bus (same route only)\nChoose: ");
    int ch = readInt();

    if(ch==1){
        showSeats(bIdx);
        printf("\nEnter new seat number: ");
        int newSeat = readInt();
        if(newSeat<1 || newSeat>MAX_SEATS){ printf("Invalid seat.\n"); return; }
        if(buses[bIdx].seats[newSeat-1]==1){ printf("Seat already booked.\n"); return; }
        // free old seat, occupy new
        buses[bIdx].seats[bookings[idx].seatNo-1] = 0;
        buses[bIdx].seats[newSeat-1] = 1;
        bookings[idx].seatNo = newSeat;
        printf("[✔] Seat changed successfully.\n");
    }
    else if(ch==2){
        
        printf("\nAvailable buses on same route (%s->%s):\n", buses[bIdx].source, buses[bIdx].destination);
        int candidates[ MAX_BUSES ]; int c=0;
        for(int i=0;i<MAX_BUSES;i++){
            if(i==bIdx) continue;
            if(strcmp(buses[i].source, buses[bIdx].source)==0 && strcmp(buses[i].destination, buses[bIdx].destination)==0){
                printf("Bus %d (%s), free seats: %d\n", buses[i].busNo, buses[i].type, availableSeatCount(i));
                candidates[c++] = i;
            }
        }
        if(c==0){ printf("No alternate bus on same route.\n"); return; }
        printf("Enter new Bus Number: ");
        int newBusNo = readInt();
        int newIdx = findBusIndexByNo(newBusNo);
        if(newIdx==-1){ printf("Invalid bus number.\n"); return; }
        if(!(strcmp(buses[newIdx].source, buses[bIdx].source)==0 && strcmp(buses[newIdx].destination, buses[bIdx].destination)==0)){
            printf("Route mismatch. Can only change within same route.\n");
            return;
        }
        if(availableSeatCount(newIdx)==0){ printf("No seats available on selected bus.\n"); return; }
        showSeats(newIdx);
        printf("Select new seat: ");
        int ns = readInt();
        if(ns<1 || ns>MAX_SEATS || buses[newIdx].seats[ns-1]==1){ printf("Seat unavailable.\n"); return; }
        // free old, occupy new
        buses[bIdx].seats[bookings[idx].seatNo-1] = 0;
        buses[newIdx].seats[ns-1] = 1;
        bookings[idx].busNo = buses[newIdx].busNo;
        bookings[idx].seatNo = ns;
        
        float newFare = calculateFare(newIdx);
        if(newFare > bookings[idx].fare){
            float diff = newFare - bookings[idx].fare;
            printf("Additional fare %.2f required.\n", diff);
            if(!processPayment(diff)){
                
                buses[newIdx].seats[ns-1] = 0;
                buses[bIdx].seats[bookings[idx].seatNo-1] = 1;
                bookings[idx].busNo = buses[bIdx].busNo;
                bookings[idx].seatNo = bookings[idx].seatNo; 
                printf("Modification aborted.\n");
                return;
            }
            bookings[idx].fare = newFare;
        } else if(newFare < bookings[idx].fare){
            float refund = bookings[idx].fare - newFare;
            bookings[idx].fare = newFare;
            printf("Fare decreased. Refund: %.2f\n", refund);
        } else {
            printf("Fare unchanged.\n");
        }
        printf("[✔] Bus changed successfully.\n");
    }
    else {
        printf("Invalid choice.\n");
    }
}

void showMainMenu(){
    printf("\n================ BUS RESERVATION SYSTEM ================\n");
    printf("1) Register\n2) Login\n3) View Routes/Bus List\n0) Exit\nChoose: ");
}

void showUserMenu(const char* username){
    printf("\n================ Welcome, %s ================\n", username);
    printf("1) View Routes/Bus List\n");
    printf("2) Check Seats for a Bus\n");
    printf("3) Book Ticket\n");
    printf("4) My Tickets\n");
    printf("5) Cancel Ticket\n");
    printf("6) Modify Ticket\n");
    printf("0) Logout\n");
    printf("Choose: ");
}

void checkSeatsFlow(){
    listBuses();
    printf("\nEnter Bus Number to view seats: ");
    int busNo = readInt();
    int bIdx = findBusIndexByNo(busNo);
    if(bIdx==-1){ printf("Invalid bus number.\n"); return; }
    showSeats(bIdx);
}


int main(){
    initBuses();
    int running = 1;

    while(running){
        showMainMenu();
        int ch = readInt();
        switch(ch){
            case 1: registerUser(); break;
            case 2: {
                int idx = loginUser();
                if(idx!=-1){
                    int loggedIn = 1;
                    while(loggedIn){
                        showUserMenu(users[idx].username);
                        int c = readInt();
                        switch(c){
                            case 1: listRoutesPool(); listBuses(); break;
                            case 2: checkSeatsFlow(); break;
                            case 3: bookTicket(users[idx].username); break;
                            case 4: showMyTickets(users[idx].username); break;
                            case 5: cancelTicket(users[idx].username); break;
                            case 6: modifyTicket(users[idx].username); break;
                            case 0: loggedIn=0; break;
                            default: printf("Invalid option.\n");
                        }
                    }
                }
            } break;
            case 3: listRoutesPool(); listBuses(); break;
            case 0: running = 0; break;
            default: printf("Invalid option.\n");
        }
    }

    printf("\nThank you for using the Bus Reservation System.\n");
    return 0;
}
