#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

#define INTERVAL_SECONDS 5 // Time interval for logging

#define TIME_FILE "time.txt"
#define VEHICLE_FILE "vehicles.txt"

#define MAX_CUSTOMERS 100
#define MAX_EMPLOYEE 100
#define MAX_VEHICLES 100
#define MAX_CASHIERS 50
#define MAX_MAINTENANCE 50

// Rental Duration Options (Pricing for each vehicle)
typedef enum {
    THREE_HOURS = 3,
    SIX_HOURS = 6,
    TWELVE_HOURS = 12,
    TWENTY_FOUR_HOURS = 24,
    THREE_DAYS = 3,
    SEVEN_DAYS = 7,
    TWO_WEEKS = 14,
    ONE_MONTH = 30,
    THREE_MONTHS = 90,
    SIX_MONTHS = 180,
    ONE_YEAR = 365
} rental_duration;

typedef struct {
    char userName[30];
    char password[30];
} customer;

typedef struct {
    char userName[30];
    char password[30];
} cashier;

typedef struct {
    char userName[30];
    char password[30];
} maintenance;

typedef struct {
    char make[50];
    char model[50];
    int year;
    char color[20];
    char licensePlate[20];
    char vin[20];
    int seatCapacity;
    time_t rentedTime;
    time_t returnTime;
    int isRented;
    char location[100];  // For Pickup Location
    double pricing[11];   // Pricing for each rental duration
    char rentToOwnTerms[200];  // Rental-to-own rules and terms
    double interestRate;       // Interest rate for overdue payments
    double totalPayment;
    double interestPrice;
    double finalPrice;
    double ownPrice;           // Price for owning the car after rental period
} vehicle;

typedef struct {
    char name[50];
    char role[20];
    int hoursWorked;
    float salary;
    char contractStart[10];
    char contractEnd[10];
} employee;

void saveTime(int signum);
void loadTime();
void updateTime();
char *formatTime(time_t timeValue);
void mainMenu(customer customer[]);
void customerLogin(customer customer[]);
void customerMenu(customer customer[], int num);
void accountSettings(customer customer[], int num);
void rentVehicleMenu(vehicle vehicle[], int vehicleCount, customer customer[], int customerIndex);
void signUpCashier();
void loginCashier();
void signUpMaintenance();
void loginMaintenance();
void employeeMenu();
void cashierMenu();
void maintenanceMenu();
void ownerMenu(vehicle vehicle[]);

void rentToOwnMenu(vehicle vehicles[], int vehicleCount, customer customers[], int customerIndex);
void standardRentFeature();
void rentedVehicleDetails(int customerId);
void returnVehicle(int customerId);
void availableVehicles();
void transactionHistory();
void rentedVehicles();
void repairVehicle();
void addTransaction(int vehicleChoice, int rentalDays);
void formatDate(time_t rawTime, char *formattedDate);

int loadVehicles(vehicle vehicle[]);
void addVehicle(vehicle vehicle[], int *index);
void deleteVehicle(vehicle vehicle[]);
void profitAnalytics(vehicle vehicle[]);
void hireEmployee(employee employee[]);
void manageEmployee(employee employee[]);

void clearScreen() {
    system("cls");
}

// Global variable to store the current time
time_t globalTime;

cashier cashiers[MAX_CASHIERS];
int cashierCount = 0;

maintenance maintenanceStaff[MAX_MAINTENANCE];
int maintenanceCount = 0;

void saveTime(int signum) {
    FILE *file = fopen(TIME_FILE, "w");
    if (file == NULL) {
        perror("Error opening file to save time");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "%ld\n", globalTime); // Save the time as a timestamp
    fclose(file);
    printf("\nTime saved: %s", ctime(&globalTime));
    exit(0);
}

void loadTime() {
    FILE *file = fopen(TIME_FILE, "r");
    if (file == NULL) {
        // File doesn't exist, start from the current time
        printf("No saved time found. Starting from the current time.\n");
        globalTime = time(NULL);
        return;
    }

    if (fscanf(file, "%ld", &globalTime) != 1) {
        perror("Error reading saved time");
        fclose(file);
        exit(EXIT_FAILURE);
    }
    fclose(file);
    printf("Loaded last tracked time: %s", ctime(&globalTime));
}

void updateTime() {
    while (1) {
        globalTime++; // Increment the time by 1 second
        printf("\rCurrent Time: %s", ctime(&globalTime)); // Display the updated time
        fflush(stdout);
        sleep(1); // Wait for 1 second
    }
}

char *formatTime(time_t timeValue) {
    static char buffer[50];
    struct tm *timeInfo = localtime(&timeValue);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeInfo);
    return buffer;
}

int main() {
    // Set up the signal handler to save the time when the program exits
    signal(SIGINT, saveTime);

    // Load the last saved time or initialize to the current time
    loadLastTrackedTime();

    // Start updating the time
    //printf("Real-time tracker started. Press Ctrl+C to exit and save.\n");
    updateTime();

    customer customer[MAX_CUSTOMERS];

    printf("\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("\t\t\t\t\t     ----------------------------\n");
    printf("\t\t\t\t\t    |  VEHICLE RENTING SERVICES  |\n");
    printf("\t\t\t\t\t     ----------------------------\n");

    sleep(4);
    mainMenu(customer);
    return 0;
}

void mainMenu(customer customer[]) {
    int choice;
    vehicle vehicle[MAX_VEHICLES];
    clearScreen();

    do {
        printf("\n\n\n\n\n\n\n\n");
        printf("  \t\t\t\t\t\t   ------------\n");
        printf(" \t\t\t\t\t\t  |  MAIN MENU |\n");
        printf("   \t\t\t\t\t\t   ------------\n");
        printf("\t\t\t\t\t\t1. CUSTOMER\n");
        printf("\t\t\t\t\t\t2. CASHIER\n");
        printf("\t\t\t\t\t\t3. MAINTENANCE\n");
        printf("\t\t\t\t\t\t4. OWNER\n");
        printf("\t\t\t\t\t\t5. EXIT\n");
        printf("\t\t\t\t\t\tEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                customerLogin(customer);
                break;
            case 2:
                cashierMenu();
                break;
            case 3:
                maintenanceMenu();
                break;
            case 4:
                ownerMenu(vehicle);
                break;
            case 5:
                printf("Exiting... Have a good day!\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
        clearScreen();
    } while (choice != 5);
}

void cashierMenu() {
    int choice;
    clearScreen();
 do {
        printf("\n\n\n\n\n\n\n\n");
        printf("  \t\t\t\t\t\t    --------------\n");
        printf(" \t\t\t\t\t\t   |  CASHIER MENU |\n");
        printf("   \t\t\t\t\t\t    --------------\n");
        printf("\t\t\t\t\t\t 1. SIGN UP\n");
        printf("\t\t\t\t\t\t 2. LOG IN\n");
        printf("\t\t\t\t\t\t 3. BACK TO MAIN MENU\n");
        printf("\t\t\t\t\t\t Enter your choice: ");
        scanf("%d", &choice);

    switch (choice) {
        case 1:
            clearScreen();
            signUpCashier();
            break;
        case 2:
            clearScreen();
            loginCashier();
            break;
        case 3:
            return;
        default:
            printf("Invalid choice.\n");
    }
 }while (choice != 3);
}

void maintenanceMenu() {
    int choice;
    clearScreen();

        printf("\n\n\n\n\n\n\n\n");
        printf("  \t\t\t\t\t\t    -----------------\n");
        printf(" \t\t\t\t\t\t   | MAINTENANCE MENU |\n");
        printf("   \t\t\t\t\t\t    -----------------\n");
        printf("\t\t\t\t\t\t 1. SIGN UP\n");
        printf("\t\t\t\t\t\t 2. LOG IN\n");
        printf("\t\t\t\t\t\t 3. BACK TO MAIN MENU\n");
        printf("\t\t\t\t\t\t Enter your choice: ");
        scanf("%d", &choice);

    switch (choice) {
        case 1:
            clearScreen();
            signUpMaintenance();
            break;
        case 2:
            clearScreen();
            loginMaintenance();
            break;
        case 3:
            return;
        default:
            printf("Invalid choice.\n");
    }
}

void signUpCashier() {
    if (cashierCount >= MAX_CASHIERS) {
        printf("Maximum number of cashiers reached.\n");
        return;
    }

    printf("\n\t\t\t\t\t\tEnter Username: ");
    scanf("%s", cashiers[cashierCount].userName);
    printf("\t\t\t\t\t\tEnter Password: ");
    scanf("%s", cashiers[cashierCount].password);

    cashierCount++;
    printf("\t\t\t\t\t\tCashier signed up successfully!\n");
}

void loginCashier() {
    char userName[30], password[30];
    printf("\n\t\t\t\t\t\tEnter Username: ");
    scanf("%s", userName);
    printf("\t\t\t\t\t\tEnter Password: ");
    scanf("%s", password);

    for (int i = 0; i < cashierCount; i++) {
        if (strcmp(cashiers[i].userName, userName) == 0 && strcmp(cashiers[i].password, password) == 0) {
            printf("\t\t\t\t\t\tLogin successful!\n");
            cashierActions();
            return;
        }
    }
    printf("\t\t\t\t\t\tInvalid input.\n");
}

void cashierActions() {
    int choice;

    do {
        printf("\n\n\n\t\t\t\t\t\t\t-----------------\n");
        printf("\t\t\t\t\t\t      | CASHIER ACTIONS |\n");
        printf("\t\t\t\t\t\t       -----------------\n");
        printf("\t\t\t\t\t\t 1. TRANSACTION HISTORY\n");
        printf("\t\t\t\t\t\t 2. LOG OUT\n");
        printf("\t\t\t\t\t\t Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                transactionHistory();
                break;
            case 2:
                printf("\t\t\t\t\t\tLogging out...\n");
                sleep(2);
                return;
            default:
                printf("\t\t\t\t\t\tInvalid choice. Please try again.\n");
        }
    } while (choice != 2);
}

void signUpMaintenance() {
    if (maintenanceCount >= MAX_MAINTENANCE) {
        printf("\t\t\t\t\t\tMaximum number of maintenance staff reached.\n");
        return;
    }

    printf("\n\t\t\t\t\t\tEnter Username: ");
    scanf("%s", maintenanceStaff[maintenanceCount].userName);
    printf("\t\t\t\t\t\tEnter Password: ");
    scanf("%s", maintenanceStaff[maintenanceCount].password);

    maintenanceCount++;
    printf("\t\t\t\t\t\tMaintenance staff signed up successfully!\n");
}

void loginMaintenance() {
    char userName[30], password[30];
    printf("\n\t\t\t\t\t\tEnter Username: ");
    scanf("%s", userName);
    printf("\t\t\t\t\t\tEnter Password: ");
    scanf("%s", password);

    for (int i = 0; i < maintenanceCount; i++) {
        if (strcmp(maintenanceStaff[i].userName, userName) == 0 && strcmp(maintenanceStaff[i].password, password) == 0) {
            printf("\t\t\t\t\t\tLogin successful!\n");
            return;
        }
    }
    printf("\t\t\t\t\t\tInvalid input.\n");
}

void customerLogin(customer customer[]) {
    int choice, customerId;
    char userName[30];
    char password[30];

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
                customerMenu(customer,i);
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

void customerMenu(customer customer[], int num) {
      int choice, customerId;
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
                rentVehicleMenu(customer, num);
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
                accountSettings(customer, num);
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

void rentVehicleMenu(vehicle vehicle[], int vehicleCount, customer customer[], int customerIndex) {
  
    int choice, vehicleChoice, rentalDays;
    
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
                rentToOwnMenu(vehicle vehicles[], int vehicleCount, customer customers[], int customerIndex);
                
                break;
            case 2:

                clearScreen();
                rentToOwnMenu(vehicle vehicles[], int vehicleCount, customer customers[], int customerIndex);
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

void rentToOwnMenu(vehicle vehicle[], int vehicleCount, customer customer[], int customerIndex) {
    if (vehicleCount == 0) {
        printf("No vehicles available for Rent to Own.\n");
        return;
    }

    // Display vehicle options for rent-to-own
    printf("\n--- Rent-to-Own Vehicles ---\n");
    for (int i = 0; i < vehicleCount; i++) {
        if (!vehicle[i].isRented) {
            printf("%d. %s %s (%d) - Price to Own: %.2lf\n", i + 1,
                   vehicle[i].make, vehicle[i].model, vehicle[i].year, vehicle[i].ownPrice);
        }
    }

    int choice;
    printf("\nEnter the number of the vehicle to rent-to-own: ");
    scanf("%d", &choice);
    getchar(); // Clear newline from input buffer

    if (choice < 1 || choice > vehicleCount || vehicle[choice - 1].isRented) {
        printf("Invalid choice or vehicle is already rented.\n");
        return;
    }

    int index = choice - 1;

    // Display vehicle details
    printf("\n--- Vehicle Details ---\n");
    printf("Make: %s\n", vehicle[index].make);
    printf("Model: %s\n", vehicle[index].model);
    printf("Year: %d\n", vehicle[index].year);
    printf("Color: %s\n", vehicle[index].color);
    printf("License Plate: %s\n", vehicle[index].licensePlate);
    printf("VIN: %s\n", vehicle[index].vin);
    printf("Seat Capacity: %d\n", vehicle[index].seatCapacity);
    printf("Rental Rate (per month): %.2lf\n", vehicle[index].rentalRate);
    printf("Rental Terms and Conditions: %s\n", vehicle[index].rentToOwnTerms);
    printf("Pick-up Location: %s\n", vehicle[index].location);
    printf("Price to Own: %.2lf\n", vehicle[index].ownPrice);
    printf("Interest Rate (if past due): %.2lf%%\n", vehicle[index].interestRate);

    // Choose payment frequency
    printf("\nChoose payment frequency (1 for Monthly, 2 for Annually): ");
    int frequency;
    scanf("%d", &frequency);

    // Calculate payment based on frequency
    double paymentAmount;
    if (frequency == 1) {
        paymentAmount = vehicle[index].price[7]; // Monthly payment
        printf("\nMonthly Payment: %.2lf\n", paymentAmount);
    } else if (frequency == 2) {
        paymentAmount = vehicle[index].price[10]; // Annual payment
        printf("\nAnnual Payment: %.2lf\n", paymentAmount);
    } else {
        printf("Invalid payment frequency choice.\n");
        return;
    }

    // Confirm rental duration
    printf("\nEnter the number of years you want to rent-to-own (1, 2, or 3 years): ");
    int years;
    scanf("%d", &years);

    if (years < 1 || years > 3) {
        printf("Invalid number of years.\n");
        return;
    }

    // Calculate total payment and overdue interest
    vehicle[index].totalPayment = paymentAmount * years * (frequency == 1 ? 12 : 1);
    vehicle[index].ownPrice = paymentAmount * years * (frequency == 1 ? 12 : 1);
    vehicle[index].interestPrice = totalPayment * (vehicles[index].interestRate / 100);
    vehicle[index].finalPrice = totalPayment + overdueInterest;

    // Mark vehicle as rented
    vehicle[index].isRented = 1;

    // Save updated vehicle data
    saveVehicles(vehicle, vehicleCount);

    // Display rental details
    printf("\n--- Rent to Own Details ---\n");
    printf("Total Payment for %d years: %.2lf\n", years, vehicle[index].totalPayment);
    printf("Overdue Interest (if applicable): %.2lf\n", vehicle[index].interestPrice);
    printf("Final Total Price (including interest): %.2lf\n", vehicle[index].finalPrice);

    printf("\nVehicle rented to own successfully!\n");
}

void accountSettings(customer customer[], int num) {
    int choice;
    char oldPassword[30];
    char newPassword[30];
    char confirmPassword[30];

    do {
        printf("\n\n\n\n\n\n\n\n\n");
        printf("  \t\t\t\t\t\t -------------------\n");
        printf(" \t\t\t\t\t\t|  ACCOUNT SETTINGS  |\n");
        printf("  \t\t\t\t\t\t -------------------\n");
        printf("\t\t\t\t\t      1. CHANGE USERNAME\n");
        printf("\t\t\t\t\t      2. CHANGE PASSWORD\n");
        printf("\t\t\t\t\t      3. BACK\n");
        printf("\t\t\t\t\t      Enter your choice: ");
        scanf("%d", &choice);

        if(choice==1) {
          printf("\n\n\n\n\n\n\n\n\n");
          printf("  \t\t\t\t\t\t -------------------\n");
          printf(" \t\t\t\t\t\t|  CHANGE ACCOUNT USERNAME  |\n");
          printf("  \t\t\t\t\t\t -------------------\n");
          printf("\t\t\t\t\t      NEW USERNAME:\n");
          ;

          if(scanf("%29s", customer[num].userName)==1) {
                printf("\n\n\n\n\n\n\n\n\n");
                printf("  \t\t\t\t\t\t -------------------\n");
                printf(" \t\t\t\t\t\t|  USERNAME CHANGED SUCCESSFULLY!  |\n");
                printf("  \t\t\t\t\t\t -------------------\n");
                printf("\t\t\t\t\t      NEW USERNAME:%s\n", customer[num].userName);
          } else {
              printf("\n\n\n\n\n\n\n\n\n");
              printf("  \t\t\t\t\t\t -------------------\n");
              printf(" \t\t\t\t\t\t|  ERROR: UNABLE TO READ INPUT   |\n");
              printf("  \t\t\t\t\t\t -------------------\n");
            }
        } else if(choice==2) {
            printf("\n\n\n\n\n\n\n\n\n");
            printf("  \t\t\t\t\t\t -------------------\n");
            printf(" \t\t\t\t\t\t|  CHANGE ACCOUNT PASSWORD  |\n");
            printf("  \t\t\t\t\t\t -------------------\n");

            // Input the old password
            printf("\t\t\t\t\t      Enter OLD PASSWORD: ");
            scanf("%29s", oldPassword);

            // Check if the old password matches
            if (strcmp(oldPassword, customer[num].password) == 0) {
                // Input new password
                printf("\t\t\t\t\t      Enter NEW PASSWORD: ");
                scanf("%29s", newPassword);

                // Confirm new password
                printf("\t\t\t\t\t      Confirm NEW PASSWORD: ");
                scanf("%29s", confirmPassword);

                // Check if new password matches confirmation
                if (strcmp(newPassword, confirmPassword) == 0) {
                    // Update the password
                    strcpy(customer[num].password, newPassword);

                    printf("\n\n\n\n\n\n\n\n\n");
                    printf("  \t\t\t\t\t\t -------------------\n");
                    printf(" \t\t\t\t\t\t|  PASSWORD CHANGED SUCCESSFULLY!  |\n");
                    printf("  \t\t\t\t\t\t -------------------\n");
                } else {
                    printf("\n\n\n\n\n\n\n\n\n");
                    printf("  \t\t\t\t\t\t -------------------\n");
                    printf(" \t\t\t\t\t\t|  ERROR: PASSWORDS DO NOT MATCH!  |\n");
                    printf("  \t\t\t\t\t\t -------------------\n");
                }
            } else {
                printf("\n\n\n\n\n\n\n\n\n");
                printf("  \t\t\t\t\t\t -------------------\n");
                printf(" \t\t\t\t\t\t|  ERROR: INCORRECT OLD PASSWORD!  |\n");
                printf("  \t\t\t\t\t\t -------------------\n");
           }
        }
    } while (choice!=3);

}

void ownerMenu(vehicle vehicle[]) {

    int choice;
    int vehicleCount = loadVehicles(vehicle);
    employee employee[MAX_EMPLOYEE];
    clearScreen();

    printf("\n\n\n\n\n\n\n\n\n");
    printf(" \t\t\t\t\t\t --------------\n");
    printf(" \t\t\t\t\t\t| OWNER'S MENU |\n");
    printf("  \t\t\t\t\t\t--------------\n");
    printf("\t\t\t\t\t     1. ADD A VEHICLE\n");
    printf("\t\t\t\t\t     2. DELETE VEHICLE\n");
    printf("\t\t\t\t\t     3. PROFIT ANALYTICS\n");
    printf("\t\t\t\t\t     4. HIRE AN EMPLOYEE\n");
    printf("\t\t\t\t\t     5. MANAGE YOUR EMPLOYEES\n");
    printf("\t\t\t\t\t     6. BACK\n");
    printf("\t\t\t\t\t     Enter your choice: ");
    scanf("%d", &choice);

    switch(choice) {
      case 1:
        addVehicle(vehicle, &vehicleCount);
        break;
      case 2:
        deleteVehicle(vehicle);
        break;
      case 3:
        profitAnalytics(vehicle);
        break;
      case 4:
        hireEmployee(employee);
        break;
      case 5:
        manageEmployee(employee);
        break;
      default:
        printf("\t\t\t\t\t     INVALID CHOICE. PLEASE TRY AGAIN");
        break;
    }
}

int saveVehicles(vehicle vehicles[], int *index) {
    FILE *file = fopen(VEHICLE_FILE, "a");

    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Save vehicle details to file
    fprintf(file, "%s,%s,%d,%s,%s,%s,%d,%ld,%ld,%d,%s,%s,%.2lf,%.2lf,%.2lf,%.2lf\n",
            vehicles[*index].make,
            vehicles[*index].model,
            vehicles[*index].year,
            vehicles[*index].color,
            vehicles[*index].licensePlate,
            vehicles[*index].vin,
            vehicles[*index].seatCapacity,
            vehicles[*index].rentedTime,
            vehicles[*index].returnTime,
            vehicles[*index].isRented,
            vehicles[*index].location);
            vehicles[*index].rentToOwnTerms,
            vehicles[*index].interestRate,
            vehicles[*index].totalPayment,
            vehicles[*index].interestPrice,
            vehicles[*index].finalPrice,
            vehicles[*index].ownPrice);

    // Save pricing array
    for (int i = 0; i < 11; i++) {
        fprintf(file, "%.2lf", vehicles[*index].pricing[i]);
        if (i < 10) {
            fprintf(file, ",");
        }
    }

    fclose(file);
    (*index)++;

    return 0; // Success
}

int loadVehicles(vehicle vehicles[]) {
    FILE *file = fopen(VEHICLE_FILE, "r");
    if (file == NULL) {
        printf("No previous data found. Starting fresh.\n");
        return 0;
    }

    int count = 0;
    while (fscanf(file, "%49[^,],%49[^,],%d,%19[^,],%19[^,],%19[^,],%d,%ld,%ld,%d,%99[^,]",
                  vehicles[count].make,
                  vehicles[count].model,
                  &vehicles[count].year,
                  vehicles[count].color,
                  vehicles[count].licensePlate,
                  vehicles[count].vin,
                  &vehicles[count].seatCapacity,
                  &vehicles[count].rentedTime,
                  &vehicles[count].returnTime,
                  &vehicles[count].isRented,
                  vehicles[count].location) == 11) {
        
        // Load pricing values up to the 7th index
        for (int i = 0; i < 7; i++) {
            if (fscanf(file, ",%lf", &vehicles[count].pricing[i]) != 1) {
                printf("Error loading pricing data for vehicle %d.\n", count + 1);
                fclose(file);
                return count;
            }
        }

        // Load rent-to-own terms
        if (fscanf(file, ",%199[^\n]\n", vehicles[count].rentToOwnTerms) != 1) {
            printf("Error loading terms for vehicle %d.\n", count + 1);
            fclose(file);
            return count;
        }

        count++;
        if (count >= MAX_VEHICLES) {
            printf("Reached maximum vehicle storage capacity.\n");
            break;
        }
    }

    fclose(file);
    printf("Data loaded from file successfully. %d records found.\n", count);
    return count;
}


void addVehicle(vehicle vehicle[], int *index) {
    if (*index >= MAX_VEHICLES) {
        printf("Vehicle storage is full.\n");
        return;
    }

    // Input basic vehicle details
    printf("Enter Vehicle Make: ");
    fgets(vehicle[*index].make, sizeof(vehicle[*index].make), stdin);
    vehicle[*index].make[strcspn(vehicle[*index].make, "\n")] = '\0';

    printf("Enter Vehicle Model: ");
    fgets(vehicle[*index].model, sizeof(vehicle[*index].model), stdin);
    vehicle[*index].model[strcspn(vehicle[*index].model, "\n")] = '\0';

    printf("Enter Vehicle Year: ");
    scanf("%d", &vehicle[*index].year);
    getchar();

    printf("Enter Vehicle Color: ");
    fgets(vehicle[*index].color, sizeof(vehicle[*index].color), stdin);
    vehicle[*index].color[strcspn(vehicle[*index].color, "\n")] = '\0';

    printf("Enter License Plate: ");
    fgets(vehicle[*index].licensePlate, sizeof(vehicle[*index].licensePlate), stdin);
    vehicle[*index].licensePlate[strcspn(vehicle[*index].licensePlate, "\n")] = '\0';

    printf("Enter VIN: ");
    fgets(vehicle[*index].vin, sizeof(vehicle[*index].vin), stdin);
    vehicle[*index].vin[strcspn(vehicle[*index].vin, "\n")] = '\0';

    // Input customer and driver details

    printf("Enter the rent-to-own terms and conditions for this vehicle:\n");
    getchar();  // Clear newline buffer
    fgets(vehicle[*index].rentToOwnTerms, sizeof(vehicle[*index].rentToOwnTerms), stdin);
    vehicle[*index].rentToOwnTerms[strcspn(vehicle[*index].rentToOwnTerms, "\n")] = '\0'; // Remove newline

    // Input pricing for different rental durations (3 hours, 6 hours, etc.)
    printf("Enter rental prices for the following durations:\n");
    printf("3 hours: ");
    scanf("%lf", &vehicle[*index].pricing[0]);
    printf("6 hours: ");
    scanf("%lf", &vehicle[*index].pricing[1]);
    printf("12 hours: ");
    scanf("%lf", &vehicle[*index].pricing[2]);
    printf("24 hours: ");
    scanf("%lf", &vehicle[*index].pricing[3]);
    printf("3 days: ");
    scanf("%lf", &vehicle[*index].pricing[4]);
    printf("7 days: ");
    scanf("%lf", &vehicle[*index].pricing[5]);
    printf("2 weeks: ");
    scanf("%lf", &vehicle[*index].pricing[6]);
    printf("1 month: ");
    scanf("%lf", &vehicle[*index].pricing[7]);
    printf("3 months: ");
    scanf("%lf", &vehicle[*index].pricing[8]);
    printf("6 months: ");
    scanf("%lf", &vehicle[*index].pricing[9]);
    printf("1 year: ");
    scanf("%lf", &vehicle[*index].pricing[10]);
    getchar(); // Clear any leftover newline

    // Input vehicle's rent-to-own terms
    printf("Enter Rent-to-Own Terms: ");
    fgets(vehicle[*index].rentToOwnTerms, sizeof(vehicle[*index].rentToOwnTerms), stdin);
    vehicle[*index].rentToOwnTerms[strcspn(vehicle[*index].rentToOwnTerms, "\n")] = '\0'; // Remove newline

    // Input vehicle's interest rate for overdue payments
    printf("Enter interest rate for overdue payments (in percentage): ");
    scanf("%lf", &vehicle[*index].interestRate);

    // Input price for owning the vehicle after the rental period
    printf("Enter the price to own this vehicle after the rental period: ");
    scanf("%lf", &vehicle[*index].ownPrice);

    // Save the new vehicle data to the file
    saveVehicles(vehicle, *index);
    printf("Vehicle added and saved successfully!\n");

    // Increment index to add next vehicle
    (*index)++;
}


void deleteVehicle(vehicle vehicle[], int *count) {
    if (*count == 0) {
        printf("No vehicles to delete.\n");
        return;
    }

    char licensePlate[20], vin[20];
    printf("Enter License Plate of the vehicle to delete: ");
    fgets(licensePlate, sizeof(licensePlate), stdin);
    licensePlate[strcspn(licensePlate, "\n")] = '\0';

    printf("Enter VIN of the vehicle to delete: ");
    fgets(vin, sizeof(vin), stdin);
    vin[strcspn(vin, "\n")] = '\0';

    int found = -1;
    for (int i = 0; i < *count; i++) {
        if (strcmp(vehicle[i].licensePlate, licensePlate) == 0 && 
            strcmp(vehicle[i].vin, vin) == 0) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("Vehicle with License Plate '%s' and VIN '%s' not found.\n", licensePlate, vin);
        return;
    }

    // Shift all vehicles after the found index
    for (int i = found; i < *count - 1; i++) {
        vehicle[i] = vehicle[i + 1];
    }

    (*count)--; // Decrease count of vehicles

    // Save updated vehicles back to the file
    saveVehicles(vehicle, *count);
    printf("Vehicle deleted successfully and data saved to file.\n");
}

void profitAnalytics(vehicle vehicle[]) {
  printf("Features Coming Soon");
}

void hireEmployee(employee employee[]) {
  printf("Features Coming Soon");
}

void manageEmployee(employee employee[]) {
  printf("Features Coming Soon");
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
