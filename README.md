# Vehicle Rental System

This program simulates a vehicle rental service where customers can rent vehicles, view rented vehicles, return vehicles, and manage their accounts. Employees can manage vehicle inventories and handle transactions. Owners can manage the entire operation, including profits and employee management.

## Features

### Customer Features:
- **Login:** Customers can log in with their username and password.
- **Menu:** Once logged in, customers can access:
  - Rent a vehicle (choose between "Rent-to-own" or "Standard Rent").
  - View details of rented vehicles.
  - Return a rented vehicle.
  - Manage account settings (change username or password).
  
### Employee Features:
- **Employee Menu:** Employees have access to various functionalities (currently empty).

### Owner Features:
- **Owner Menu:** Owners can manage vehicles, track profits, and hire employees (currently empty).

### Vehicle Management:
- Vehicles are available for rent or rent-to-own.
- **Vehicle Stock:** The system tracks the stock of available vehicles for rent.

### Transaction Handling:
- Transactions are recorded each time a customer rents a vehicle.

---

## Code Structure

### `mainMenu(customer customer[])`
- Displays the main menu to the user, allowing navigation to customer, employee, or owner menus.

### `customerLogin(customer customer[])`
- Allows customers to log in using their username and password. If successful, the customer is directed to their menu.

### `customerMenu(customer customer[], int num)`
- Allows customers to access different actions like renting a vehicle, checking rented vehicles, returning vehicles, and managing account settings.

### `rentVehicleMenu()`
- Allows customers to rent a vehicle, with the option to choose between "Rent-to-own" or "Standard Rent".

### `accountSettings(customer customer[], int num)`
- Allows customers to change their username or password.

### `employeeMenu()`, `ownerMenu(vehicle vehicle[])`, `cashierMenu()`, `maintenanceMenu()`
- These functions are placeholders and are coming soon.
  
---

## Coming Soon Features

- **Employee Menu:** Functionality for employees to manage vehicles and transactions (currently empty).
- **Owner Menu:** Functionality for owners to manage vehicles, track profits, and hire employees (currently empty).
- **Cashier Menu:** Functionality to process payments (currently empty).
- **Maintenance Menu:** Functionality for vehicle maintenance (currently empty).

---

## Compilation and Execution

1. Clone or download the repository.
2. Compile the code using a C compiler, for example:
   ```bash
   gcc vehicle_rental_system.c -o vehicle_rental_system