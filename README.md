# Course Registration System (C++ Project)

## Introduction

This is a simple Course Registration System made using C++. It runs on the console and allows students to register, choose courses, and manage their course enrollments. I made this project mainly to practice file handling, classes, and STL in C++.

---

## Features

- Student registration with validation (Name, Email, Phone, DOB, Percentage)
- Shows list of available courses
- Students can register in eligible courses (based on percentage)
- Seats are limited for each course
- Drop course option available
- All student data and courses are saved using file handling
- Can export registered students into a `.csv` file

---

## Files Used

| File            | Description                              |
|-----------------|------------------------------------------|
| `main.cpp`      | Main source code                         |
| `course.txt`    | List of available courses                |
| `student.txt`   | Stores student data + their course list  |
| `registrations.csv` | Final exported data (can open in Excel) |

---

## How It Works

### Student Registration
- Student enters name, email, phone, DOB, and 12th percentage.
- System checks if email or phone already exists to avoid duplicates.

### Course Registration
- Shows all available courses.
- Student can enroll only if eligible and if seats are available.
- Duplicate course registration is blocked.

### Drop Course
- Student can drop any of their registered courses.

### Export to CSV
- All data is exported to `registrations.csv` in proper format.

---

## How to Run

Make sure you have a C++ compiler installed (like g++).

---

## Notes

- The system uses `student.txt` and `course.txt` to load and save data.
- On first run, if `course.txt` is empty or not available, it loads default courses in code.
- After course registration or drop, data is auto-saved.

---

## Why I Built This

I made this project to get better at:
- Using classes and vectors in C++
- Working with files (read/write)
- Validating user input
- Structuring a real-world program using functions and objects

---

## Made By

**Priyanka Suthar and Prachi Parwani**  
