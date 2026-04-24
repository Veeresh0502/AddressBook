# 📒 Address Book Management System in C

## 📌 Project Overview

This project is a **console-based Address Book Management System** developed in C. It allows users to manage contacts efficiently with features like adding, editing, deleting, searching, and listing contacts.

The application ensures **data persistence** using CSV files and includes **input validation** along with checks to prevent duplicate phone numbers and email addresses.

---

## 🚀 Features

* ➕ Add new contacts
* ✏️ Edit existing contacts
* ❌ Delete contacts
* 🔍 Search contacts (by name, phone, or email)
* 📋 Display all contacts
* 💾 Persistent storage using CSV files
* ⚠️ Input validation & duplicate prevention

---

## 🛠️ Technologies Used

* C Programming
* File Handling (CSV & TXT)
* Structures & Pointers
* Arrays & Functions
* Command Line Interface (CLI)
* Makefile

---

## 📂 Project Structure

```
.
├── main.c
├── contact.c
├── contact.h
├── file.c
├── file.h
├── populate.c
├── populate.h
├── contacts.csv
├── contacts.txt
├── addressbook
└── a.out
```

---

## ⚙️ How to Run

### 🔧 Compile

```bash
gcc main.c contact.c file.c populate.c -o addressbook
```

### ▶️ Execute

```bash
./addressbook
```

---

## 📊 Data Storage

* Contacts are stored in:

  * `contacts.csv` (primary storage)
  * `contacts.txt` (backup or alternate format)

---

## 🧠 Key Learnings

* Implemented a **menu-driven CLI application**
* Worked with **file handling and CSV parsing**
* Ensured **data validation and uniqueness constraints**
* Applied **modular programming using header files**
* Improved understanding of **memory management in C**

---

## ⚠️ Challenges Faced

* Handling file I/O efficiently
* Preventing duplicate entries
* Managing structured data using arrays
* Implementing search and sort operations

---

## 📌 Future Improvements

* Dynamic memory allocation (instead of fixed-size arrays)
* GUI-based version
* Database integration (SQLite/MySQL)
* Export/Import features

---

## 👨‍💻 Author

**Veeresh T**

---

## ⭐ Acknowledgment

This project was developed as part of learning **C programming and system-level concepts**.

---

## 📎 License

This project is open-source and free to use.
