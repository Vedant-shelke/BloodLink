# BloodLink – Blood Donor Eligibility & Matching System

## Project Overview

BloodLink is a **C++ console-based blood donor management and matching system**. It helps find suitable blood donors when a person needs blood.

The system stores donor information such as name, phone number, date of birth, blood group, area, weight, and last donation date. When a blood request is created, BloodLink checks blood-group compatibility and donor eligibility before displaying suitable donors.

The project was built to solve the problem of manually checking multiple donor records and to apply important C++ concepts to a practical real-world problem.

## Features

* Register new blood donors
* Store donor details
* View all registered donors
* Create blood requests
* Automatically generate request IDs
* Check blood-group compatibility
* Check donor eligibility
* Age validation
* Minimum weight validation
* 56-day donation-gap validation
* Find compatible and eligible donors
* Sort matching donors
* View blood request history
* Save donor data using file handling
* Save request history using file handling
* Validate user input
* Handle invalid input using exception handling
* Load previously saved donor and request data when the program starts

## Technologies Used

* **Language:** C++
* **Concepts:** Object-Oriented Programming (OOP)
* **STL:** `vector`, `unordered_map`, `sort`
* **File Handling:** `ifstream`, `ofstream`
* **Exception Handling:** `try`, `catch`, `throw`
* **Data Storage:** Text files

## How It Works

The system follows a simple process:

```text
Register Donor
      ↓
Validate Donor Information
      ↓
Save Donor Information
      ↓
Create Blood Request
      ↓
Generate Request ID
      ↓
Check Blood Group Compatibility
      ↓
Check Donor Eligibility
      ↓
Find Matching Donors
      ↓
Sort Matching Donors
      ↓
Display Suitable Donors
      ↓
Save Request History
```

### 1. Donor Registration

The user can register a donor by entering:

* Name
* Phone number
* Date of birth
* Blood group
* Area
* Weight
* Last donation date

The system validates the entered information and stores the donor record.

### 2. Blood Request

A requester can create a blood request by entering:

* Requester name
* Required blood group
* Required units
* Urgency
* Area

The system automatically generates a unique request ID.

### 3. Blood Compatibility

BloodLink uses an `unordered_map` to store blood-group compatibility rules.

For example:

```text
B+ → O-, O+, B-, B+
O- → O-
```

When a blood request is created, the system looks up the required blood group and gets the compatible donor blood groups.

### 4. Donor Eligibility

After checking compatibility, the system checks whether the donor is eligible.

The current implementation checks:

* Age between 18 and 65 years
* Weight of at least 50 kg
* At least 56 days since the last donation

If a donor fails any of these checks, the donor is not included in the matching results.

### 5. Matching Donors

The system goes through the registered donors one by one.

```text
Donor
  ↓
Blood group compatible?
  ↓
Yes
  ↓
Eligibility checks
  ↓
Eligible?
  ↓
Yes
  ↓
Add to matching list
```

After checking all donors, the suitable donors are sorted and displayed.

### 6. File Handling

BloodLink uses text files to maintain data between program executions.

```text
data/
├── donors.txt
└── requests.txt
```

Donor information is saved in `donors.txt`, while blood request history is saved in `requests.txt`.

When the program starts, previously stored information can be loaded from these files.

### 7. Input Validation and Exception Handling

The system validates user input such as:

* Blood group
* Date format
* Weight
* Number of units
* Urgency

Invalid data is handled using validation and exception handling so that incorrect input does not unnecessarily terminate the program.

## Project Structure

```text
BloodLink/
│
├── main.cpp
│
├── data/
│   ├── donors.txt
│   └── requests.txt
│
└── README.md
```


## Main Menu

```text
=====================================
          BLOODLINK SYSTEM
=====================================
1. Register Donor
2. View Donors
3. Create Blood Request & Find Donors
4. View Request History
5. Exit

Enter your choice:
```


## C++ Concepts Demonstrated

This project demonstrates practical use of:

* Classes and Objects
* Inheritance
* Encapsulation
* Constructors
* Member Functions
* STL `vector`
* STL `unordered_map`
* STL `sort`
* Loops and Conditional Statements
* String Handling
* Date Validation
* File Input/Output
* Exception Handling
* Input Validation

## Objective

The main objective of BloodLink is to provide a simple system that can **store donor information, process blood requests, check compatibility and eligibility, and display suitable donors** while demonstrating practical C++ programming and OOP concepts.
