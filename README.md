# Professor-Student Management System

## Project Overview

The **Professor-Student Management System** is a synchronization-based application that models the interaction between students and faculty in an educational setting. The system simulates students needing help with their programming tasks and the faculty providing assistance when available. It uses threads, mutexes, and condition variables to manage multiple students and a single faculty member in a limited-resource environment (limited chairs for waiting students).

## Key Features

- **Synchronization of Faculty and Students**: The system ensures that the faculty assists students in an orderly fashion while preventing race conditions through thread synchronization techniques.
- **Limited Seating for Waiting Students**: Only a set number of students can wait for help at any given time. If the waiting area is full, students continue their work instead of waiting.
- **Faculty Assistance**: Faculty members provide assistance to one student at a time. If no students are waiting, the faculty "sleeps" until there is a student to help.
- **Multithreading and Concurrency**: The application makes use of C++'s threading library to simulate the concurrent activities of students programming and faculty teaching.

## Technologies Used

- **C++**: For implementing the multithreaded application.
- **Mutexes and Condition Variables**: For synchronization and communication between the student and faculty threads.
- **Standard Library**: For time delays, random number generation, and other utility functions.

## How It Works

1. **Student Threads**: Each student works on programming tasks. When they need help, they attempt to wait in a shared space (limited by the number of available chairs). If a seat is available, the student will notify the faculty that they need help and wait for assistance.
   
2. **Faculty Thread**: The faculty waits until there is at least one student needing help. When notified, the faculty helps one student at a time and then returns to waiting for more students. If no students are waiting, the faculty sleeps.

3. **Synchronization**: The `chair_mutex` ensures that shared resources (like the number of waiting students) are accessed safely by both student and faculty threads. Condition variables (`student_cv` and `faculty_cv`) are used to coordinate the flow of actions between the student and faculty threads.

## Project Structure

```plaintext
|-- synchronization.cpp               # The main file containing all logic
|-- README.md              # Project description













