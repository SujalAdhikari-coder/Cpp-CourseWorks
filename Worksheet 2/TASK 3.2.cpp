//Create a program that:
//1.	Reads student records (roll, name, marks) from a text file
//2.	Throws an exception if marks are not between 0 and 100
//3.	Allows adding new records with proper validation
//4.	Saves modified records back to file
#include <iostream>
#include <fstream>  //For file handling
#include <stdexcept>  //For exception handling
#include <string>
#include <vector>  //For storing records in memory
using namespace std;
//Structure to store student data
struct Student {
    int roll;
    string name;
    int marks;
};
//Function to validate marks
void validateMarks(int marks) {
    if (marks < 0 || marks > 100) {
        throw out_of_range("Marks must be between 0 and 100.");
    }
}
//Function to read student records from a file
vector<Student> readRecords(string fileName) {
    vector<Student> students;
    ifstream inFile(fileName);
    if (!inFile) {
        cout << "File doesn't exist. It will be created when saving new records.\n";
        return students;  //Return empty list
    }
    Student student;
    while (inFile >> student.roll >> student.name >> student.marks) {
        students.push_back(student);
    }
    inFile.close();
    return students;
}
//Function to write student records back to the file
void saveRecords(string fileName, vector<Student> students) {
    ofstream outFile(fileName);
    if (!outFile) {
        cout << "Error opening file for writing!\n";
        return;
    }
    for (const auto& student : students) {
        outFile << student.roll << " " << student.name << " " << student.marks << endl;
    }
    outFile.close();
}
int main() {
    string fileName = "students.txt";
    vector<Student> students = readRecords(fileName);
    // Display existing records
    if (!students.empty()) {
        cout << "Existing Student Records:\n";
        for (const auto& student : students) {
            cout << "Roll: " << student.roll << ", Name: " << student.name << ", Marks: " << student.marks << endl;
        }
    } else {
        cout << "No student records found.\n";
    }
    int choice;
    cout << "\nChoose an option:\n";
    cout << "1. Add a new student record\n";
    cout << "2. Modify an existing student record\n";
    cout << "Enter choice: ";
    cin >> choice;
    if (choice == 1) {
        // Adding a new student
        Student newStudent;
        cout << "Enter Roll: ";
        cin >> newStudent.roll;
        cin.ignore();  //Ignore newline left by previous input
        cout << "Enter Name: ";
        getline(cin, newStudent.name);
        cout << "Enter Marks: ";
        cin >> newStudent.marks;
        try {
            validateMarks(newStudent.marks);
            students.push_back(newStudent);
            cout << "Student record added successfully.\n";
        } catch (const out_of_range& e) {
            cout << "Error: " << e.what() << endl;
        }
    } else if (choice == 2) {
        //Modifying an existing student record
        int rollNumber;
        cout << "Enter roll number to modify: ";
        cin >> rollNumber;
        bool found = false;
        for (auto& student : students) {
            if (student.roll == rollNumber) {
                found = true;
                cout << "Enter new marks: ";
                int newMarks;
                cin >> newMarks;

                try {
                    validateMarks(newMarks);
                    student.marks = newMarks;
                    cout << "Marks updated successfully.\n";
                } catch (const out_of_range& e) {
                    cout << "Error: " << e.what() << endl;
                }
                break;
            }
        }
        if (!found) {
            cout << "Student with roll number " << rollNumber << " not found.\n";
        }
    } else {
        cout << "Invalid choice.\n";
    }
    //Save the modified records back to the file
    saveRecords(fileName, students);
    return 0;
}
