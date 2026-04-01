# Bank Management System (OOP)

A console-based bank management application written in **C++**, built using object-oriented programming principles. The system handles client accounts, banking transactions, user management with role-based permissions, and currency exchange — all backed by flat-file storage.

---

## Features

### Client Management
- List all clients
- Add a new client
- Delete a client
- Update client information
- Find a client by account number

### Transactions
- Deposit amounts to an account
- Withdraw amounts from an account
- Transfer funds between two accounts (with transfer log)
- View total balances across all clients

### User Management
- List all system users
- Add, delete, update, and find users
- Role-based permission system using bitwise flags

### Currency Exchange
- List all currencies (150+ countries)
- Find a currency by code or country name
- Update a currency's exchange rate
- Currency calculator (convert between any two currencies)

### Authentication & Logging
- Login screen with username and password
- Locks out after 3 failed attempts
- Every login is recorded in a log file with date, username, and permissions

---

## Permissions System

Permissions are stored as a single integer using bitwise operations. Each permission is a power of 2:

| Permission       | Value |
|-----------------|-------|
| Show Client List | 1     |
| Add New Client   | 2     |
| Delete Client    | 4     |
| Update Client    | 8     |
| Find Client      | 16    |
| Transactions     | 32    |
| Manage Users     | 64    |
| Login Register   | 128   |
| All Permissions  | -1    |

---

## Project Structure

```
BankProject/
│
├── BankProject.cpp              # Entry point
├── Global.h                     # Global CurrentUser variable
│
├── Header Files/
│   ├── core/
│   │   ├── clsPerson.h          # Base class: first name, last name, email, phone
│   │   ├── clsBankClient.h      # Inherits clsPerson; handles client CRUD & transfers
│   │   ├── clsUser.h            # Inherits clsPerson; handles user CRUD & auth
│   │   ├── clsCurrency.h        # Currency data and conversion logic
│   │   └── clsPermistions.h     # Reads and assigns permission flags
│   │
│   ├── lib/
│   │   ├── clsString.h          # String utility functions
│   │   ├── clsDate.h            # Date utility functions
│   │   ├── clsInputValidate.h   # Input reading and validation
│   │   └── clsUtil.h            # General utilities (encryption, file I/O, etc.)
│   │
│   └── screens/
│       ├── clsScreen.h          # Base screen class (header, clear, permission check)
│       ├── clsMainScreen.h      # Main menu
│       ├── Clients/             # All client-related screens
│       ├── Users/               # All user-related screens
│       └── Currencies/          # All currency-related screens
│
└── Data/
    ├── Client.txt               # Client records
    ├── Users.txt                # User records (passwords encrypted)
    ├── Currencies.txt           # Currency rates
    ├── Logs.txt                 # Login history
    └── TransferLogs.txt         # Transfer transaction history
```

---

## Class Hierarchy

```
clsPerson
├── clsBankClient
└── clsUser

clsScreen
├── clsMainScreen
├── clsPermistions
├── Clients screens (Add, Delete, Update, Find, List, Deposit, Withdraw, Transfer...)
├── Users screens (Add, Delete, Update, Find, List, Login, LoginRegister...)
└── Currencies screens (List, Find, UpdateRate, Calculator, ExchangeMenu)
```

---

## Data Storage

All data is stored in plain text files inside the `Data/` folder. Each record uses ` #//# ` as a delimiter between fields.

**Client record format:**
```
FirstName #//# LastName #//# Phone #//# Email #//# AccountNumber #//# PinCode #//# Balance
```

**User record format:**
```
FirstName #//# LastName #//# Email #//# Phone #//# Username #//# EncryptedPassword #//# Permissions
```

**Currency record format:**
```
Country #//# CurrencyCode #//# CurrencyName #//# Rate
```

Passwords are stored with a simple character-shift encryption (key = 2).

---

## How to Build and Run

This project was developed using **Visual Studio 2022** on Windows, with the C++20 standard.

1. Open `BankProject.sln` in Visual Studio.
2. Build the solution (Ctrl+Shift+B).
3. Run the executable. Make sure the `Data/` folder is in the same directory as the `.exe` file.

> The project uses `system("cls")` for clearing the screen, so it is intended for Windows.

---

## Default Login

You can log in using one of the users already in `Data/Users.txt`. The admin user (`User1`) has full permissions (`-1`).

---

## Author

**AbdEssamed Laidani**  
MIT License © 2026
