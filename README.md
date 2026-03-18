# 🏦 Advanced Bank Management System (C++)

A comprehensive, industrial-grade Banking Management System developed in **C++**. This project demonstrates advanced programming concepts, including **Multi-level Menu Systems**, **User Permissions**, **Transaction Logging**, and **Currency Exchange** logic.

## 🌟 Key Features

The system is divided into four main specialized modules, all accessible through a secure **Login Screen** that tracks every entry in a **Login Register**.

### 1. 📂 Client Management (Main Menu)
The core of the system for handling bank clients with full CRUD operations:
* **Show Client List:** Displays a formatted table of all clients.
* **Add New Client:** Register new accounts with validation.
* **Delete/Update Client:** Full control over client records.
* **Find Client:** Instant search by account number.

### 2. 💸 Transactions Module
A dedicated sub-menu for financial operations:
* **Deposit & Withdraw:** Update balances with real-time validation.
* **Total Balances:** A summary report of all assets held in the bank.
* **Transfer:** Move funds between two different accounts securely.
* **Transfer Log:** A persistent record of all historical transfers for auditing.

### 3. 👥 User & Security Management
A system for managing the application's operators (Admins/Users):
* **Manage Users:** List, Add, Update, and Delete system users.
* **Permissions:** Define which users can access specific menus (e.g., Transactions, Currency, or User Management).
* **Login Register:** A security feature that logs the `Username`, `Date`, and `Time` of every login session.

### 4. 💱 Currency Exchange System
A specialized module for handling international banking needs:
* **List Currencies:** View global currency codes and names.
* **Find Currency:** Search for specific rates.
* **Update Rate:** Modify exchange rates dynamically.
* **Currency Calculator:** Perform instant conversions between different currencies.

---

## 🖥️ System Interface Preview

### Main Menu
```text
                                        ______________________________________

                                                        Main Screen
                                        ______________________________________

                                        User: Admin
                                        Date: 18/3/2026
                                     ===========================================
                                                        Main Menue
                                     ===========================================
                                        [1] Show Client List.
                                        [2] Add New Client.
                                        [3] Delete Client.
                                        [4] Update Client Info.
                                        [5] Find Client.
                                        [6] Transactions.
                                        [7] Manage Users.
                                        [8] Login Register.
                                        [9] Currency Exchange.
                                        [10] Logout.
                                     ===========================================
                                     Choose what do you want to do? [1 to 10]? 
```

### Transactions Screen
                                        ______________________________________

                                                  Transactions Screen
                                        ______________________________________

                                        User: Admin
                                        Date: 18/3/2026
                                     ===========================================
                                                  Transactions Menue
                                     ===========================================
                                        [1] Deposit.
                                        [2] Withdraw.
                                        [3] Total Balances.
                                        [4] Transfer.
                                        [5] Transfer Log.
                                        [6] Main Menue.
                                     ===========================================
                                     Choose what do you want to do? [1 to 6]? 

### Manage Users Screen
                                        ______________________________________

                                                 Manage Users Screen
                                        ______________________________________

                                        User: Admin
                                        Date: 18/3/2026
                                     ===========================================
                                                  Manage Users Menue
                                     ===========================================
                                        [1] List Users.
                                        [2] Add New User.
                                        [3] Delete User.
                                        [4] Update User.
                                        [5] Find User.
                                        [6] Main Menue.
                                     ===========================================
                                     Choose what do you want to do? [1 to 6]? 

###

                                        ______________________________________

                                                  Currency Exchange Screen
                                        ______________________________________

                                        User: Admin
                                        Date: 18/3/2026
                                     ===========================================
                                                  Currency Exchange Main Screen
                                     ===========================================
                                        [1] List Currencies.
                                        [2] Find Currency.
                                        [3] Update Rate.
                                        [4] Currency Calculator.
                                        [5] Main Menue.
                                     ===========================================
                                     Choose what do you want to do? [1 to 5]? 

# 🛠️ Technical Stack & Skills
Language: C++

File Handling: Binary/Flat file processing for persistent data storage (Clients, Users, Logs).

Data Formatting: Advanced use of <iomanip> for professional CLI tables.

Logic Design: Procedural modularity with clear separation of concerns between menus.

# 🚀 Installation & Setup
Clone the repository:

git clone [https://github.com/MohammedAlrehaili/BankAccountManagementSystem.git]
Compile the source code:

g++ main.cpp -o BankSystem
Run the executable:

./BankSystem

Developed by: Mohammed Alrehaili
