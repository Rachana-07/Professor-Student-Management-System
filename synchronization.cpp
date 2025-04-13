#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <chrono>
#include <cstdlib>

using namespace std;

constexpr int NUM_CHAIRS = 3;
constexpr int NUM_STUDENTS = 5;

mutex chair_mutex;
condition_variable student_cv;
condition_variable faculty_cv;

int waiting_students = 0;
bool student_needs_help = false;

void rand_sleep() {
    int sleep_time = rand() % 3 + 1;
    this_thread::sleep_for(chrono::seconds(sleep_time));
}

// Student thread function
void student_programming(int id) {
    while (true) {
        cout << "Student " << id << " is programming." << endl;
        rand_sleep();

        unique_lock<mutex> lock(chair_mutex);
        if (waiting_students < NUM_CHAIRS) {
            ++waiting_students;
            cout << "Student " << id << " is waiting. Total waiting: " << waiting_students << endl;

            student_needs_help = true;
            student_cv.notify_one(); // Notify faculty
            faculty_cv.wait(lock, [] { return !student_needs_help; }); // Wait to be helped

            cout << "Student " << id << " received help from faculty." << endl;
        } else {
            cout << "No chairs available. Student " << id << " continues programming." << endl;
        }
    }
}

// Faculty thread function
void faculty_teaching() {
    while (true) {
        unique_lock<mutex> lock(chair_mutex);
        student_cv.wait(lock, [] { return student_needs_help; });

        --waiting_students;
        cout << "Faculty is helping a student. Students remaining: " << waiting_students << endl;
        student_needs_help = false;
        faculty_cv.notify_one(); // Help one student
        lock.unlock();

        rand_sleep();

        lock.lock();
        if (waiting_students == 0) {
            cout << "No students waiting. Faculty goes back to sleep." << endl;
        }
    }
}

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    thread faculty_thread(faculty_teaching);
    vector<thread> student_threads;

    for (int i = 0; i < NUM_STUDENTS; ++i) {
        student_threads.emplace_back(student_programming, i + 1);
    }

    faculty_thread.join();
    for (auto& thread : student_threads) {
        thread.join();
    }

    return 0;
}
