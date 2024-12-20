#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#define MAX_CUSTOMERS 100
#define MAX_TRANSACTIONS 100
#define MAX_VEHICLES 10
#define MAX_VEHICLES2 5

void mainMenu();
void customerLogin();
void customerMenu();
void rentVehicleMenu();
void employeeMenu();
void cashierMenu();
void maintenanceMenu();
void ownerMenu();

void rentToOwnFeature();
void standardRentFeature();
void rentedVehicleDetails(int customerId);
void returnVehicle(int customerId);
void availableVehicles();
void transactionHistory();
void rentedVehicles();
void repairVehicle();
void addTransaction(int vehicleChoice, int rentalDays);
void formatDate(time_t rawTime, char *formattedDate);

void clearScreen() {
    system("cls");
}

typedef struct {
    char userName[30];
    char password[30];
} customer;


// Vehicle models
char *vehicleNames[MAX_VEHICLES] = {
    "Toyota Corolla", "Honda Civic", "Ford Mustang", "Chevrolet",
    "Tesla Model 3", "BMW X5 - Class", "Mercedes-Benz",
    "Jeep Wrangler", "Hyundai Tucson", "Kia Sportage"
};

char *vehicleNames2[MAX_VEHICLES2] = {
    "Toyota Love Life", "Suzuki Jimny", "Nissan Navarra", "Honda Vios", "Toyota Wigo"
};

int vehicleStock[MAX_VEHICLES];
int vehicleStock2[MAX_VEHICLES2];
int customerIDs[10] = {1101, 1102, 1103, 1104, 1105, 1106, 1107, 1108, 1109, 1110};

// Transaction structure
typedef struct {
    char vehicleModel[50];
    int daysRented;
    char startDateTime[40];
    char returnDateTime[40];
} Transaction;

Transaction transactions[MAX_TRANSACTIONS];
int transactionCount = 0;

int main() {
    srand(time(NULL));
    for (int i = 0; i < MAX_VEHICLES; i++) {
        vehicleStock[i] = rand() % 50 + 30; // Mo generate ug andom stock between 30 and 50
    }
    for (int i = 0; i < MAX_VEHICLES2; i++) {
    vehicleStock2[i] = rand() % 3 + 3; // mo generate random stock between 3 and 5
    }

    printf("\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("\t\t\t\t\t    ----------------------------\n");
    printf("\t\t\t\t\t   |  VEHICLE RENTING SERVICES  |\n");
    printf("\t\t\t\t\t    ----------------------------\n");

    sleep(4);
    mainMenu();
    return 0;
}

void mainMenu() {
    int choice;

    clearScreen();

    do {

    printf("\n\n\n\n\n\n\n\n\n");
    printf("  \t\t\t\t\t\t   ------------\n");
    printf(" \t\t\t\t\t\t  |  MAIN MENU |\n");
    printf("   \t\t\t\t\t\t   ------------\n");
    printf("\t\t\t\t\t\t1. CUSTOMER\n");
    printf("\t\t\t\t\t\t2. EMPLOYEE\n");
    printf("\t\t\t\t\t\t3. OWNER\n");
    printf("\t\t\t\t\t\t4. EXIT\n");
    printf("\t\t\t\t\t\tEnter your choice: ");
    scanf("%d", &choice);

        switch (choice) {
            case 1:
                customerLogin();
                break;
            case 2:
                employeeMenu();
                break;
            case 3:
                ownerMenu();
                break;
            case 4:
                printf("Exiting... Have a good day!\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
        clearScreen();
    } while (choice != 4);
}

void customerLogin() {
    int choice, customerId;
    char userName[30];
    char password[30];
    
    customer customer[MAX_CUSTOMERS];

    clearScreen();
    
    do {
      printf("\n\n\n\n\n\n\n\n\n");
      printf("  \t\t\t\t\t\t -------------------\n");
      printf(" \t\t\t\t\t\t|  CUSTOMER SIGN IN  |\n");
      printf("  \t\t\t\t\t\t -------------------\n");
      printf("\t\t\t\t\t      Username:");
      scanf("%29s", userName);
      
      for(int i=0; i<MAX_CUSTOMERS; i++) {
        
        if(strcmp(userName,customer[i].userName)==0) {
          
          do {
            printf("\n\n\n\n\n\n\n\n\n");

            printf("  \t\t\t\t\t\t -------------------\n");

            printf(" \t\t\t\t\t\t|  CUSTOMER SIGN IN  |\n");
            printf("  \t\t\t\t\t\t -------------------\n");
            printf("\t\t\t\t\t      Password:");
            scanf("%29s", password);
            
            if(strcmp(userName,customer[i].password)==0)
            {
                customerMenu(customer);
            }
          } while(1);
          
        }
        
        else {
          printf("\n\n\n\n\n\n\n\n\n");
          printf("  \t\t\t\t\t\t -------------------\n");
          printf(" \t\t\t\t\t\t|  INVALID USERNAME  |\n");
          printf("  \t\t\t\t\t\t -------------------\n");
        }
        break;
      }
      
    } while(1);
}

void customerMenu(customer customer[]) {
      int choice;
      do {

        printf("\n\n\n\n\n\n\n\n\n");

        printf("  \t\t\t\t\t\t -------------------\n");
        printf(" \t\t\t\t\t\t|  CUSTOMER'S MENU  |\n");
        printf("  \t\t\t\t\t\t -------------------\n");
        printf("\t\t\t\t\t      1. RENT A VEHICLE\n");
        printf("\t\t\t\t\t      2. DETAILS OF YOUR RENTED VEHICLES\n");
        printf("\t\t\t\t\t      3. RETURN A RENTED VEHICLE\n");
        printf("\t\t\t\t\t      4. ACCOUNT SETTINGS\n");
        printf("\t\t\t\t\t      5. BACK\n");
        printf("\t\t\t\t\t      Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                rentVehicleMenu();
                break;
            case 2:
                printf("Enter your Customer ID: ");
                scanf("%d", &customerId);
                rentedVehicleDetails(customerId);
                break;
            case 3:
                printf("Enter your Customer ID: ");
                scanf("%d", &customerId);
                returnVehicle(customerId);
                break;
            case 4:
                accountSettings(customer)
                break;
            case 5:
                printf("Returning to Main Menu...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
        clearScreen();
    } while (choice != 5);
}

void rentVehicleMenu() {
    int choice, vehicleChoice, rentalDays;
    char password[20];
    const char correctPassword[] = "customer123";

       printf("\t\t\t\t\t      Enter your password: ");
    scanf("%s", password);

    clearScreen();

    if (strcmp(password, correctPassword) != 0) {
        printf("Incorrect password. Access denied.\n");
        return;
    }

    do {
        printf("\n\n\n\n\n\n\n\n\n");
        printf(" \t\t\t\t\t\t -----------------------\n");
        printf(" \t\t\t\t\t\t|  RENT A VEHICLE MENU  |\n");
        printf("  \t\t\t\t\t\t -----------------------\n");
        printf("\t\t\t\t\t       1. RENT - TO - OWN\n");
        printf("\t\t\t\t\t       2. STANDARD RENT\n");
        printf("\t\t\t\t\t       3. BACK\n");
        printf("\t\t\t\t\t       Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:

                clearScreen();
                printf("\n\n\n\n\n\n\n\n\n");
                printf("\t\t\t\t\t     Available Vehicles for Rent-to-Own:\n");
                for (int i = 0; i < MAX_VEHICLES2; i++) {
                    printf("\t\t\t\t\t     %d. %s (%d available)\n", i + 1, vehicleNames2[i], vehicleStock2[i]);
                }
                printf("\t\t\t\t\t     Choose a vehicle to rent-to-own (1-%d): ", MAX_VEHICLES2);
                scanf("%d", &vehicleChoice);

                if (vehicleChoice < 1 || vehicleChoice > MAX_VEHICLES2 || vehicleStock2[vehicleChoice - 1] <= 0) {
                    printf("Invalid choice or vehicle unavailable.\n");
                } else {
                    printf("\t\t\t\t\t     Enter the number of days to rent-to-own: ");
                    scanf("%d", &rentalDays);
                    addTransaction(vehicleChoice, rentalDays);
                    vehicleStock2[vehicleChoice - 1]--;
                }
                break;
            case 2:

                clearScreen();

                printf("\n\n\n\n\n\n\n\n\n");
                printf("\t\t\t\t\t       Available Vehicles:\n");
                for (int i = 0; i < MAX_VEHICLES; i++) {
                    printf("\t\t\t\t\t       %d. %s (%d available)\n", i + 1, vehicleNames[i], vehicleStock[i]);
                }
                printf("\t\t\t\t\t       Choose a vehicle to rent (1-%d): ", MAX_VEHICLES);
                scanf("%d", &vehicleChoice);

                if (vehicleChoice < 1 || vehicleChoice > MAX_VEHICLES || vehicleStock[vehicleChoice - 1] <= 0) {
                    printf("Invalid choice or vehicle unavailable.\n");
                } else {
                    printf("\t\t\t\t\t       Enter the number of days to rent: ");
                    scanf("%d", &rentalDays);
                    addTransaction(vehicleChoice, rentalDays);
                    vehicleStock[vehicleChoice - 1]--;
                }
                break;
            case 3:
                printf("\t\t\t\t\t       Returning to Customer Menu...\n");
                break;
            default:
                printf("\t\t\t\t\t       Invalid choice. Please try again.\n");
        }

    } while (choice != 3);
    clearScreen();
}

void accountSettings() {
    int choice;
    
    do {
        printf("\n\n\n\n\n\n\n\n\n");
        printf("  \t\t\t\t\t\t -------------------\n");
        printf(" \t\t\t\t\t\t|  ACCOUNT SETTINGS  |\n");
        printf("  \t\t\t\t\t\t -------------------\n");
        printf("\t\t\t\t\t      1. RENT A VEHICLE\n");
        printf("\t\t\t\t\t      2. DETAILS OF YOUR RENTED VEHICLES\n");
        printf("\t\t\t\t\t      3. RETURN A RENTED VEHICLE\n");
        printf("\t\t\t\t\t      4. ACCOUNT SETTINGS\n");
        printf("\t\t\t\t\t      5. BACK\n");
        printf("\t\t\t\t\t      Enter your choice: ");
        scanf("%d", &choice);
    } while (choice!=);   
}

void employeeMenu() {
    int choice;

    clearScreen();

    do {
        printf("\n\n\n\n\n\n\n\n\n");
        printf(" \t\t\t\t\t\t -------------------\n");
        printf(" \t\t\t\t\t\t|  EMPLOYEE'S MENU  |\n");
        printf("  \t\t\t\t\t\t -------------------\n");
        printf("\t\t\t\t\t       1. CASHIER\n");
        printf("\t\t\t\t\t       2. MAINTENANCE\n");
        printf("\t\t\t\t\t       3. BACK\n");
        printf("\t\t\t\t\t       Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                cashierMenu();
                break;
            case 2:
                maintenanceMenu();
                break;
            case 3:
                printf("Returning to Main Menu...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
        clearScreen();
    } while (choice != 3);
}

void cashierMenu() {
    int choice;

    clearScreen();

    do {
        printf("\n\n\n\n\n\n\n\n\n");
        printf(" \t\t\t\t\t\t ------------------\n");
        printf(" \t\t\t\t\t\t|  CASHIER'S MENU  |\n");
        printf("  \t\t\t\t\t\t ------------------\n");
        printf("\t\t\t\t\t       1. AVAILABLE VEHICLES\n");
        printf("\t\t\t\t\t       2. TRANSACTION HISTORY\n");
        printf("\t\t\t\t\t       3. RENTED VEHICLES\n");
        printf("\t\t\t\t\t       4. BACK\n");
        printf("\t\t\t\t\t       Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:

                availableVehicles();
                break;
            case 2:
                transactionHistory();
                break;
            case 3:
                rentedVehicles();
                break;
            case 4:
                printf("Returning to Employee Menu...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);
}

void maintenanceMenu() {
    int choice;

    clearScreen();

    do {
        printf("\n\n\n\n\n\n\n\n\n");
        printf(" \t\t\t\t\t\t ----------------------\n");
        printf(" \t\t\t\t\t\t|  MAINTENANCE'S MENU  |\n");
        printf("  \t\t\t\t\t\t----------------------\n");
        printf("\t\t\t\t\t     1. REPAIR A VEHICLE\n");
        printf("\t\t\t\t\t     2. BACK\n");
        printf("\t\t\t\t\t     Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                repairVehicle();
                break;
            case 2:
                printf("Returning to Employee Menu...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
        clearScreen();
    } while (choice != 2);
}

void ownerMenu() {

    clearScreen();

    printf("\n\n\n\n\n\n\n\n\n");
    printf(" \t\t\t\t\t\t --------------\n");
    printf(" \t\t\t\t\t\t| OWNER'S MENU |\n");
    printf("  \t\t\t\t\t\t--------------\n");
    printf("Feature coming soon...\n");
}

void rentedVehicleDetails(int customerId) {

    clearScreen();

    printf("Fetching rented vehicles for Customer ID: %d\n", customerId);
}

void returnVehicle(int customerId) {

    clearScreen();

    printf("Returning rented vehicle for Customer ID: %d\n", customerId);
}

void availableVehicles() {

    clearScreen();

    printf("\n\n\n\n\n\n\n");
    printf("\t\t\t\t\t Available Vehicles:\n");
    for (int i = 0; i < MAX_VEHICLES; i++) {
        printf("\t\t\t\t\t %s\t: %d available\n", vehicleNames[i], vehicleStock[i]);
    }
}

void transactionHistory() {

    clearScreen();

    if (transactionCount == 0) {
        printf("No transactions available.\n");
        return;
    }

    printf("\nTransaction History:\n");
    printf(" ----------------------------------------------------------------------------------------------\n");
    printf("| Vehicle Model        | Start Date & Time        | Return Date & Time           | Days Rented |\n");
    printf(" ----------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < transactionCount; i++) {
        printf("| %-20s | %-22s | %-22s     | %-11d |\n",
               transactions[i].vehicleModel,
               transactions[i].startDateTime,
               transactions[i].returnDateTime,
               transactions[i].daysRented);
    }

    printf("-----------------------------------------------------------------------------------------------\n");
}

void rentedVehicles() {

    clearScreen();

    int rentedCount[MAX_VEHICLES] = {0};

    for (int i = 0; i < transactionCount; i++) {
        for (int j = 0; j < MAX_VEHICLES; j++) {
            if (strcmp(transactions[i].vehicleModel, vehicleNames[j]) == 0) {
                rentedCount[j]++;
                break;
            }
        }
    }

    printf("\nRented Vehicles and Counts:\n");
    printf(" --------------------------------\n");
    printf("| Vehicle Model         | Rented |\n");
    printf(" --------------------------------\n");
    for (int i = 0; i < MAX_VEHICLES; i++) {
        if (rentedCount[i] > 0) {
            printf("| %-20s | %-6d |\n", vehicleNames[i], rentedCount[i]);
        }
    }

    printf("\nVehicles That Are Already Rented:\n");
    printf(" --------------------------------\n");
    printf("| Vehicle Model         | Count  |\n");
    printf(" --------------------------------\n");

    for (int i = 0; i < 5; i++){
        int randomVehicle = rand() % MAX_VEHICLES;
        int randomCount = rand() % 10 + 1;
        printf("| %-20s  | %-6d |\n", vehicleNames[randomVehicle], randomCount);
    }
    printf(" --------------------------------\n");
}

void repairVehicle() {
    printf("Repairing a vehicle...\n");
}

void addTransaction(int vehicleChoice, int rentalDays) {
    if (transactionCount >= MAX_TRANSACTIONS) {
        printf("Transaction limit reached!\n");
        return;
    }

    time_t startTime = time(NULL);
    time_t returnTime = startTime + (rentalDays * 24 * 3600);

    strcpy(transactions[transactionCount].vehicleModel, vehicleNames[vehicleChoice - 1]);
    transactions[transactionCount].daysRented = rentalDays;

    formatDate(startTime, transactions[transactionCount].startDateTime);
    formatDate(returnTime, transactions[transactionCount].returnDateTime);


    vehicleStock[vehicleChoice - 1]--;

    transactionCount++;
    printf("\n\n\n\n\n\n\n\n\n");
    printf("\t\t\t\t\t    Transaction Details:\n");
    printf("\t\t\t\t\t    Vehicle: %s\n", transactions[transactionCount - 1].vehicleModel);
    printf("\t\t\t\t\t    Days Rented: %d\n", rentalDays);
    printf("\t\t\t\t\t    Start Date/Time: %s\n", transactions[transactionCount - 1].startDateTime);
    printf("\t\t\t\t\t    Return Date/Time: %s\n", transactions[transactionCount - 1].returnDateTime);
    printf("\n\t\t\t\t\t   Transaction Successful! Thank you for renting with us.\n");

    // Write transaction data to file
    FILE *file = fopen("transactions.txt", "a");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    fprintf(file, "Vehicle: %s\n", transactions[transactionCount - 1].vehicleModel);
    fprintf(file, "Days Rented: %d\n", rentalDays);
    fprintf(file, "Start Date/Time: %s\n", transactions[transactionCount - 1].startDateTime);
    fprintf(file, "Return Date/Time: %s\n", transactions[transactionCount - 1].returnDateTime);
    fprintf(file, "----------------------------------------------------------------\n");
    fclose(file);

    printf("\n\t\t\t\t\t      Transaction Successful! Details have been saved.\n");
}

void formatDate(time_t rawTime, char *formattedDate) {
    struct tm *timeInfo = localtime(&rawTime);
    strftime(formattedDate, 40, "%Y-%m-%d | %I:%M:%S %p", timeInfo);
}
