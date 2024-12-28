
# 🚗 Car Rental & Rent-to-Own System

Welcome to the **Car Rental & Rent-to-Own System**! This system enables customers to rent or rent-to-own vehicles with detailed features like pricing, rental duration, and tracking. It also includes admin controls for vehicle management, overdue interest rates, and various user roles.

---

## 🌟 Features Overview

1. **Customer, Cashier, and Maintenance Management**  
   - Separate structs and functionalities for customers, cashiers, and maintenance staff.
   - User login and authentication.

2. **Vehicle Management**  
   - Add, delete, or view vehicles in the system.  
   - Track details such as make, model, year, seat capacity, and VIN.

3. **Rental Options**  
   - Flexible rental durations:
     - ⏳ Short-term: 3, 6, 12, or 24 hours.
     - 🗓️ Long-term: 3 days, 7 days, 2 weeks, 1 month, 3 months, 6 months, or 1 year.
   - Real-time rental tracking using timestamps.

4. **Rent-to-Own**  
   - Display available vehicles with complete details.  
   - Price to own pre-defined in the vehicle struct.  
   - Monthly or annual payment modes.  
   - Overdue interest rates configured by admins.  

5. **File Management**  
   - Vehicles saved to and loaded from `vehicles.txt`.  
   - Real-time time tracking saved to `time.txt`.

---

## 📂 File Structure

- **`main.c`**: Main implementation file.
- **`vehicles.txt`**: Stores vehicle data.
- **`time.txt`**: Tracks time-related data.

---

## 🛠️ Detailed Functions

### 1. Vehicle Management
#### `addVehicle(vehicle vehicles[], int *vehicleCount)`
- Adds a new vehicle to the system.  
- Includes details like:
  - Make, model, year, color, license plate, VIN.
  - Rental pricing (hourly, daily, monthly, etc.).
  - Pickup location and seat capacity.

#### `deleteVehicle(vehicle vehicles[], int *vehicleCount)`
- Deletes a vehicle by license plate and VIN.  
- Ensures data integrity by shifting array elements.

#### `loadVehicles(vehicle vehicles[])`
- Loads vehicles from `vehicles.txt`.  
- Supports up to `MAX_VEHICLES`.

#### `saveVehicles(vehicle vehicles[], int vehicleCount)`
- Saves all vehicle data to `vehicles.txt`.  
- Ensures all attributes are stored, including rental details.

---

### 2. Rent-to-Own System
#### `rentToOwnMenu(vehicle vehicles[], int vehicleCount, customer customers[], int customerIndex)`
- Displays available vehicles for rent-to-own.  
- Allows customers to:
  - Select a vehicle.
  - Choose payment mode (monthly or annual).  
  - Review terms and conditions.  
  - Calculate total cost including overdue interest.

---

### 3. Real-Time Tracking
#### `logTime()`
- Logs the current time to `time.txt` at regular intervals.  
- Useful for calculating rental duration and overdue interest.

---

### 4. User Management
#### `customerLogin(customer customers[], int *customerCount)`
- Handles customer login and authentication.

#### `registerCustomer(customer customers[], int *customerCount)`
- Registers a new customer with unique credentials.

---

## 💰 Pricing Options

| **Duration**      | **Pricing Index** | **Description** |
|--------------------|-------------------|------------------|
| 3 Hours           | 0                 | Short-term rental. |
| 6 Hours           | 1                 | Half-day rental. |
| 12 Hours          | 2                 | Full-day rental. |
| 1 Day             | 3                 | 24-hour rental. |
| 3 Days            | 4                 | Short trip. |
| 7 Days            | 5                 | Weekly rental. |
| 1 Month           | 6                 | Ideal for long trips. |
| 3 Months          | 7                 | Quarterly rental. |
| 6 Months          | 8                 | Half-year rental. |
| 1 Year            | 9                 | Annual rental. |

---

## 🔧 Setup and Compilation

1. Clone the repository or download the code.
2. Compile using:
   ```bash
   gcc main.c -o car_rental_system
   ```
3. Run the program:
   ```bash
   ./car_rental_system
   ```

---

## 📝 Notes
- **File Dependencies**: Ensure `vehicles.txt` and `time.txt` are accessible.  
- **Error Handling**: The system includes basic error checks (e.g., invalid input, file access issues).  
- **Admin Control**: Overdue interest rates and vehicle prices are set by the admin.

---

## 🎯 Future Enhancements
- Add graphical user interface (GUI).  
- Implement online payment gateways.  
- Integrate GPS tracking for vehicles.

---

Enjoy managing your vehicle rentals with this comprehensive system! 😊
