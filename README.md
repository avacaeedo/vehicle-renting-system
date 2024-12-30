# 🚗 Vehicle Renting System

Welcome to the **Rental Management System**! This powerful application helps you manage vehicle rentals, users, and logs efficiently. Built with robust C programming principles, it’s designed to make rental operations seamless. 🌟

---

## 📜 Features

### 🛠️ User Management
- **Customers**: Easily add and manage customer details.
- **Cashiers**: Handle transactions and manage payment operations.
- **Maintenance Staff**: Keep track of vehicle maintenance records.

### ⏳ Rental Durations
Flexible rental periods to suit every need:
- **Short-term**: 3 hours, 6 hours, 12 hours, or 24 hours.
- **Mid-term**: 3 days, 7 days, or 2 weeks.
- **Long-term**: 1 month, 3 months, 6 months, or even a year!

### 📁 File Handling
All data is securely logged into dedicated files for future reference:
- `time.txt`: Tracks time logs.
- `vehicles.txt`: Stores vehicle information.
- `employee.txt`: Maintains employee details.

### ⏲️ Periodic Logging
- Logs data automatically every **5 seconds**. No manual intervention required!

### 🚦 Scalability
- Supports up to **100 customers**, **100 employees**, and **100 vehicles**.
- Manages up to **50 cashiers** and **50 maintenance staff**.
- Logs up to **30 entries** seamlessly.

---

## 🏗️ Build and Run

1. **Compile** the program using `gcc`:
   ```bash
   gcc main.c -o rental_system
   ```

2. **Run** the program:
   ```bash
   ./rental_system
   ```

---

## 📂 File Structure
```
main.c        # Core program file
time.txt      # Log file for time-based events
vehicles.txt  # Stores vehicle data
employee.txt  # Stores employee and staff information
```

---

## 🚀 Future Improvements
- Integration with a database for larger data handling.
- Enhanced UI for better user interaction.
- Additional analytics and reporting features.

---

Feel free to contribute to this project or report any issues! 😊

### 📧 Contact
For any inquiries, email us at `support@rentalmanagement.com`.

---

Made with ❤️ in C programming.
