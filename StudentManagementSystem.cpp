#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class Student {
public:
    int roll;
    char name[50];
    char branch[30];
    float cgpa;

    void input() {
        cout << "Enter Roll Number: ";
        cin >> roll;
        cin.ignore();

        cout << "Enter Name: ";
        cin.getline(name, 50);

        cout << "Enter Branch: ";
        cin.getline(branch, 30);

        cout << "Enter CGPA: ";
        cin >> cgpa;
    }

    void display() {
        cout << "\nRoll No : " << roll;
        cout << "\nName    : " << name;
        cout << "\nBranch  : " << branch;
        cout << "\nCGPA    : " << cgpa << endl;
    }
};

void addStudent() {
    Student s;
    ofstream file("students.dat", ios::binary | ios::app);
    s.input();
    file.write((char*)&s, sizeof(s));
    file.close();
    cout << "\nStudent record added successfully!\n";
}

void displayAll() {
    Student s;
    ifstream file("students.dat", ios::binary);
    if (!file) {
        cout << "\nNo records found!\n";
        return;
    }
    while (file.read((char*)&s, sizeof(s))) {
        s.display();
        cout << "---------------------";
    }
    file.close();
}

void searchStudent() {
    int roll;
    bool found = false;
    Student s;
    ifstream file("students.dat", ios::binary);

    cout << "\nEnter Roll Number to search: ";
    cin >> roll;

    while (file.read((char*)&s, sizeof(s))) {
        if (s.roll == roll) {
            s.display();
            found = true;
            break;
        }
    }
    file.close();

    if (!found)
        cout << "\nStudent not found!\n";
}

void deleteStudent() {
    int roll;
    Student s;
    ifstream file("students.dat", ios::binary);
    ofstream temp("temp.dat", ios::binary);
    bool found = false;

    cout << "\nEnter Roll Number to delete: ";
    cin >> roll;

    while (file.read((char*)&s, sizeof(s))) {
        if (s.roll != roll) {
            temp.write((char*)&s, sizeof(s));
        } else {
            found = true;
        }
    }

    file.close();
    temp.close();

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
        cout << "\nStudent record deleted successfully!\n";
    else
        cout << "\nStudent not found!\n";
}

int main() {
    int choice;

    do {
        cout << "\n===== STUDENT MANAGEMENT SYSTEM =====";
        cout << "\n1. Add Student";
        cout << "\n2. Display All Students";
        cout << "\n3. Search Student";
        cout << "\n4. Delete Student";
        cout << "\n5. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayAll(); break;
            case 3: searchStudent(); break;
            case 4: deleteStudent(); break;
            case 5: cout << "\nExiting program...\n"; break;
            default: cout << "\nInvalid choice!\n";
        }
    } while (choice != 5);

    return 0;
}
