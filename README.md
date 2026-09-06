# BloodLink – Blood Donor Eligibility & Matching System

BloodLink is a C++ console-based Blood Donor Eligibility and Matching System designed to help manage donor information, blood requests, donor eligibility, and matching donors with blood requirements.

The project demonstrates the use of Object-Oriented Programming (OOP), STL, file handling, and exception handling in C++.

## Features

* Register new blood donors
* Store donor information using file handling
* View registered donors
* Create blood requests
* Find suitable donors based on blood group
* Check donor eligibility based on donation history
* Consider donor location/locality during matching
* View previous blood requests
* Handle invalid input using exception handling
* Maintain donor and request data using text files

## Technologies Used

* **Language:** C++
* **Concepts:** OOP, STL, File Handling, Exception Handling
* **Data Storage:** Text files
* **Development Environment:** Visual Studio Code

## How It Works

The system provides a menu-driven console interface.

1. Donors can be registered in the system.
2. Donor information is stored in `data/donors.txt`.
3. A user can create a blood request by providing the required blood group and other details.
4. The system searches the donor records.
5. Donors are filtered according to blood-group compatibility and eligibility.
6. Suitable donors are displayed to the user.
7. Blood request information is stored in `data/requests.txt`.

## Project Structure

```text
BloodLink/
│
├── main.cpp
├── README.md
├── .gitignore
│
└── data/
    ├── donors.txt
    └── requests.txt
```


## Sample Output

```text
========================================
              BLOODLINK
========================================

1. Register Donor
2. View Donors
3. Create Blood Request
4. Find Matching Donors
5. View Request History
6. Exit

Enter your choice:
```

### Example: Finding Matching Donors

```text
Enter required blood group: O+

Searching for matching donors...

Matching Donors:
----------------------------------------
Name       : Rahul
Blood Group: O+
Location   : Pune
Eligible   : Yes
----------------------------------------

Matching donor found successfully.
```

## Data Storage

BloodLink uses text files for persistent storage.

```text
data/
├── donors.txt
└── requests.txt
```

This allows donor and request information to remain available even after the application is closed.

## Key C++ Concepts Demonstrated

* Classes and Objects
* Encapsulation
* Constructors
* STL Containers
* Vectors
* File Input/Output
* Exception Handling
* String Processing
* Conditional Logic
* Functions
* Menu-driven Programming

## Future Improvements

* Database integration using MySQL
* GUI or web-based interface
* Advanced location-based matching
* Email/SMS notifications for donors
* Admin authentication
* Online donor registration

## Author

**Vedant Shelke**

B.Tech Computer Science Engineering
