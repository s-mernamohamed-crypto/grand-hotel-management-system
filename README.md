#  Grand Hotel Management System

A high-performance, enterprise-grade **Hotel Management System** built using a hybrid architecture. This project combines the raw speed, efficiency, and Object-Oriented paradigm of **C++** for core business logic and file handling, with a stunning, modern web dashboard built using **Python (Streamlit)**.

The two layers communicate seamlessly through a custom-built **IPC (Inter-Process Communication) bridge** using Python's `subprocess` module to pass command-line arguments to the compiled C++ executable and parse stdout responses.

---

##  System Architecture & Workflow

1. **Frontend Layer (Python - Streamlit):** Provides a sleek, cyber-luxurious dark-themed user interface. Handles user inputs, input validation, and real-time visual analytics.
2. **IPC Bridge (`subprocess`):** The Python layer triggers the compiled C++ executable, passing action keywords (like `LOGIN`, `REGISTER`, `BOOK`) and form data as command-line arguments.
3. **Core Backend Layer (C++ OOP):** The engine of the application. It processes commands via `UI::ProcessCommand`, runs core business algorithms (e.g., dynamic billing, checking availability), and enforces data constraints.
4. **Data Persistence Layer (Flat File DB):** Controlled by a custom C++ `FileManager` that manages ACID-like read/write operations on plain text databases (`.txt` files) ensuring no data loss upon exit.

---

##  Key Features

###  Advanced C++ Backend (OOP Design)
* **Inheritance & Polymorphism:** A base `User` class with distinct derived classes for `Guest` and `Receptionist` (Admin) controlling specific permission matrices.
* **Complex Data Management:** Tracks rooms, guest profiles, room reservations, meal plans (Breakfast/Lunch/Dinner counts), and custom event bookings utilizing C++ STL (`std::vector`, `std::string`).
* **Financial Ledger Engine:** Features a comprehensive billing system that dynamically calculates base room rates over durations alongside custom service charges (Spa, Medical, Catering).

###  Modern Python Frontend (Streamlit)
* **Interactive Dashboard:** Real-time data visualization of room statuses, booking history, and active check-ins.
* **Role-Based Views:** Seamless dynamic routing based on login response; guests see reservation tools, admins see hotel logs and operational controls.
* **Custom CSS Injection:** Fully overhauled glassmorphism UI widgets, tailored cards, and refined visual layout.

---

##  Class Structure & OOP Overview

* **`User` (Base), `Guest` & `Receptionist` (Derived):** Handles authentication, session permissions, and role-specific transactions.
* **`Room`:** Manages room indexing, categorization (`Single`, `Suite`), availability states, and baseline pricing.
* **`Reservation` & `EventReservation`:** Object encapsulates timeline logic, durations, check-in/out calendars, and auxiliary bookings (concerts, gala dinners).
* **`FileManager`:** Custom parser that processes tokenized/comma-separated strings (`.txt` files) into full OOP memory structures upon boot, and serializes them back to disk upon exit.
* **`ApplicationManager`:** The global system controller orchestrating class communication and system states.

---

##  Tech Stack & Dependencies
* **Core Logic:** C++ (Standard Template Library, Input/Output File Streams `fstream`).
* **UI & Dashboard:** Python 3.x, Streamlit, Pandas, Matplotlib, Seaborn.
* **Inter-Process Connection:** Python standard `subprocess` API.
* **Data Stores:** Flat Text File Databases (`rooms.txt`, `users.txt`, `reservations.txt`, `events.txt`).

---

##  Compilation & Setup

To run this hybrid application locally, follow these steps:

1. **Compile the C++ Backend:**
   Compile all `.cpp` files into an executable named `hotel_backend`:
   ```bash
   g++ -O3 hotel_backend.cpp ApplicationManager.cpp Room.cpp Reservation.cpp EventReservation.cpp FileManager.cpp Helper.cpp HotelServices.cpp UI.cpp User.cpp -o hotel_backend
