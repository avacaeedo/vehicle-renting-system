#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#define VEHICLE_FILE "vehicles.txt"

#define MAX_CUSTOMERS 100
#define MAX_EMPLOYEE 100
#define MAX_TRANSACTIONS 100
#define MAX_VEHICLES 10
#define MAX_VEHICLES2 5

typedef struct {
    char userName[30];
    char password[30];
} customer;

// Transaction structure
typedef struct {
    char vehicleModel[50];
    int daysRented;
    float price;
    char startDateTime[40];
    char returnDateTime[40];
} Transaction;

typedef struct {
  
    // Vehicle Information
    char make[50];
    char model[50];
    int year;
    char color[20];
    char licensePlate[20];
    char vin[20]; // Vehicle Identification Number
    char maintenanceHistory[500];
    
    //Customer Information
    char customerName[100];
    char contactInfo[100];
    char driversLicense[20];
    char paymentDetails[100];
    char rentalHistory[500];
    
    // Rental Agreement Details
    double rentalRate;
    char termsAndConditions[1000];
    char additionalServices[500];
    double mileage;
    double fuelUsage;
    char reportedIncidents[500];
    
} vehicle;

typedef struct {
    char name[50];
    char role[20];
    int hoursWorked;
    float salary;
    char contractStart[10];
    char contractEnd[10];
} employee;

void mainMenu(customer customer[]);
void customerLogin(customer customer[]);
void customerMenu(customer customer[], int num);
void accountSettings(customer customer[], int num);
void rentVehicleMenu();
void employeeMenu();
void cashierMenu();
void maintenanceMenu();
void ownerMenu(vehicle vehicle[]);

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

int loadVehicles(vehicle vehicle[]);
void addVehicle(vehicle vehicle[], int *index);
void deleteVehicle(vehicle vehicle[]);
void profitAnalytics(vehicle vehicle[]);
void hireEmployee(employee employee[]);
void manageEmployee(employee employee[]);

void clearScreen() {
    system("cls");
}

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

Transaction transactions[MAX_TRANSACTIONS];
int transactionCount = 0;

int main() {
    srand(time(NULL));
    for (int i = 0; i < MAX_VEHICLES; i++) {
        vehicleStock[i] = rand() % 50 + 30; // Mo generate ug andom stock between 30 and 50
    }
    for (int i = 0; i < MAX_VEHICLES2; i++) {
    vehicleStock2[i] = rand() % 3 + 3; // mo generate random stock between 3 and 5
    
    
    customer customer[MAX_CUSTOMERS];

    printf("\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("\t\t\t\t\t    ----------------------------\n");
    printf("\t\t\t\t\t   |  VEHICLE RENTING SERVICES  |\n");
    printf("\t\t\t\t\t    ----------------------------\n");

    sleep(4);
    mainMenu(customer);
    return 0;
    }
}

void mainMenu(customer customer[]) {
    int choice;
    vehicle vehicle[MAX_VEHICLES];
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
                customerLogin(customer);
                break;
            case 2:
                employeeMenu();
                break;
            case 3:
                ownerMenu(vehicle);
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

int loadVehicles(vehicle vehicle[]) {
    FILE *file = fopen(VEHICLE_FILE, "r");
    if (file == NULL) {
        printf("No previous data found. Starting fresh.\n");
        return 0;
    }

    int count = 0;
    while (fscanf(file, "%49[^,],%49[^,],%d,%19[^,],%19[^,],%19[^,],%99[^,],%99[^,],%49[^,],%lf\n",
                  vehicle[count].make,
                  vehicle[count].model,
                  &vehicle[count].year,
                  vehicle[count].color,
                  vehicle[count].licensePlate,
                  vehicle[count].vin,
                  vehicle[count].customerName,
                  vehicle[count].contactInfo,
                  vehicle[count].driversLicense,
                  &vehicle[count].rentalRate) == 10) {
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

    printf("Enter Customer Name: ");
    fgets(vehicle[*index].customerName, sizeof(vehicle[*index].customerName), stdin);
    vehicle[*index].customerName[strcspn(vehicle[*index].customerName, "\n")] = '\0';

    printf("Enter Contact Information: ");
    fgets(vehicle[*index].contactInfo, sizeof(vehicle[*index].contactInfo), stdin);
    vehicle[*index].contactInfo[strcspn(vehicle[*index].contactInfo, "\n")] = '\0';

    printf("Enter Driver's License: ");
    fgets(vehicle[*index].driversLicense, sizeof(vehicle[*index].driversLicense), stdin);
    vehicle[*index].driversLicense[strcspn(vehicle[*index].driversLicense, "\n")] = '\0';

    printf("Enter Rental Rate: ");
    scanf("%lf", &vehicle[*index].rentalRate);
    getchar();

    // Save the new vehicle data directly to the file
    FILE *file = fopen(VEHICLE_FILE, "a");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    fprintf(file, "%s,%s,%d,%s,%s,%s,%s,%s,%s,%.2lf\n",
            vehicle[*index].make,
            vehicle[*index].model,
            vehicle[*index].year,
            vehicle[*index].color,
            vehicle[*index].licensePlate,
            vehicle[*index].vin,
            vehicle[*index].customerName,
            vehicle[*index].contactInfo,
            vehicle[*index].driversLicense,
            vehicle[*index].rentalRate);

    fclose(file);
    (*index)++;
    printf("Vehicle added and saved successfully!\n");
}

void deleteVehicle(vehicle vehicle[]) {
  
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
