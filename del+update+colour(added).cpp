#include <iostream>
#include <string>
#include <windows.h> // Required for console colors
using namespace std;

struct student {
    string name;
    string roll;
    string clas;
    string room_no;
    string contact;
    string ID_card_no;
    student* next;
};

student* head = NULL; // there is no student in our linked list till now
const int MAX_STUDENTS = 30; // maximum rooms available
int studentCount = 0; // how many students are currently in Hostel

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // Global console handle

//=========================================================
// Function to check if a roll number already exists
//=========================================================
bool isRollExists(string roll) {
    student* temp = head;
    while (temp != NULL) {
        if (temp->roll == roll)
            return true; // roll number already exists
        temp = temp->next;
    }
    return false; // roll number is unique
}

//=========================================================
// Function to check no same id is written for 2 students
//=========================================================
bool isIDExists(string id) {
    student* temp = head;
    while (temp != NULL) {
        if (temp->ID_card_no == id)
            return true; // ID already exists
        temp = temp->next;
    }
    return false; // ID is unique
}

//=========================================================
// Function to add students
//=========================================================
void addStudent_end_of_list() {
    if (studentCount >= MAX_STUDENTS) {
        SetConsoleTextAttribute(hConsole, 12); // Red for warning
        cout << "Cannot add more students. Maximum rooms reached.\n";
        SetConsoleTextAttribute(hConsole, 15); // Reset to white
        return;
    }
    string input;
    SetConsoleTextAttribute(hConsole, 11); // Cyan 
    cout << "How many students do you want to add? ";
    SetConsoleTextAttribute(hConsole, 15);
    getline(cin, input);
    int n = stoi(input);
    if (studentCount + n > MAX_STUDENTS) {
        SetConsoleTextAttribute(hConsole, 12);
        cout << "Cannot add " << n << " students. ";
        cout << "Only " << (MAX_STUDENTS - studentCount) << " can be added." << endl;
        SetConsoleTextAttribute(hConsole, 15);
        return;
    }
    for (int i = 0; i < n; i++) {
        cout << endl;
        SetConsoleTextAttribute(hConsole, 11);
        cout << "Enter details of student " << studentCount + 1 << endl;
        SetConsoleTextAttribute(hConsole, 15);
        student* newStudent = new student;
        cout << "Enter name: ";
        getline(cin, newStudent->name);

        // Roll number validation
        while (true) {
            cout << "Enter roll number: ";
            getline(cin, newStudent->roll);
            if (isRollExists(newStudent->roll)) {
                SetConsoleTextAttribute(hConsole, 12);
                cout << "This roll number already exists! Please enter a different roll number." << endl;
                SetConsoleTextAttribute(hConsole, 15);
            }
            else
                break; // roll number is unique
        }

        cout << "Enter class: ";
        getline(cin, newStudent->clas);
        cout << "Enter room number: ";
        getline(cin, newStudent->room_no);
        cout << "Enter contact: ";
        getline(cin, newStudent->contact);

        // ID card number validation
        while (true) {
            cout << "Enter ID card number: ";
            getline(cin, newStudent->ID_card_no);
            if (isIDExists(newStudent->ID_card_no)) {
                SetConsoleTextAttribute(hConsole, 12);
                cout << "This ID card number already exists! Please enter a different ID." << endl;
                SetConsoleTextAttribute(hConsole, 15);
            }
            else
                break; // ID is unique
        }

        newStudent->next = NULL;

        // Add student to linked list
        if (head == NULL)
            head = newStudent;
        else {
            student* temp = head;
            while (temp->next != NULL)
                temp = temp->next;
            temp->next = newStudent;
        }
        studentCount++;
        SetConsoleTextAttribute(hConsole, 9); // Blue for info
        cout << "Student added successfully." << endl;
        SetConsoleTextAttribute(hConsole, 15);
    }
}

//=========================================================
// Giving All stored Students
//=========================================================
void Display_All() {
    if (head == nullptr) {
        SetConsoleTextAttribute(hConsole, 12); // Red warning
        cout << "Database is empty" << endl;
        cout << "NO STUDENT TO DISPLAY!\n";
        SetConsoleTextAttribute(hConsole, 15);
        return;
    }
    student* temp = head;
    while (temp != NULL) {
        SetConsoleTextAttribute(hConsole, 9); // Blue student info
        cout << "Name: " << temp->name << endl;
        cout << "Roll: " << temp->roll << endl;
        cout << "Class: " << temp->clas << endl;
        cout << "Room: " << temp->room_no << endl;
        cout << "Contact: " << temp->contact << endl;
        cout << "ID Card: " << temp->ID_card_no << endl;
        SetConsoleTextAttribute(hConsole, 10); // Green separator
        cout << "---------------------------\n";
        temp = temp->next;
    }
    SetConsoleTextAttribute(hConsole, 15);
}

//=========================================================
// Giving Data of specific Student (roll no wise)
//=========================================================
void search_by_Roll() {
    if (head == NULL) {
        SetConsoleTextAttribute(hConsole, 12); // Red warning
        cout << "Empty Database" << endl;
        cout << "Nothing to Display" << endl;
        SetConsoleTextAttribute(hConsole, 15);
        return;
    }
    student* temp = head;
    string searchRoll;
    cout << "Enter roll number to search: ";
    getline(cin, searchRoll);
    while (temp != nullptr) {
        if (temp->roll == searchRoll) {
            SetConsoleTextAttribute(hConsole, 9); // Blue student info
            cout << "Name: " << temp->name << endl;
            cout << "Roll: " << temp->roll << endl;
            cout << "Class: " << temp->clas << endl;
            cout << "Room: " << temp->room_no << endl;
            cout << "Contact: " << temp->contact << endl;
            cout << "ID Card: " << temp->ID_card_no << endl;
            SetConsoleTextAttribute(hConsole, 15);
            return;
        }
        temp = temp->next;
    }
    SetConsoleTextAttribute(hConsole, 12); // Red not found
    cout << "Student with Roll Number " << searchRoll << " not Found!" << endl;
    SetConsoleTextAttribute(hConsole, 15);
}

//=========================================================
// Giving Data of specific Student (ID Card no wise)
//=========================================================
void search_by_ID() {
    if (head == NULL) {
        SetConsoleTextAttribute(hConsole, 12);
        cout << "Empty Database" << endl;
        cout << "Nothing to Display" << endl;
        SetConsoleTextAttribute(hConsole, 15);
        return;
    }
    student* temp = head;
    string searchID;
    cout << "Enter ID card number to search: ";
    getline(cin, searchID);
    while (temp != nullptr) {
        if (temp->ID_card_no == searchID) {
            SetConsoleTextAttribute(hConsole, 9); // Blue student info
            cout << "Name: " << temp->name << endl;
            cout << "Roll: " << temp->roll << endl;
            cout << "Class: " << temp->clas << endl;
            cout << "Room: " << temp->room_no << endl;
            cout << "Contact: " << temp->contact << endl;
            cout << "ID Card: " << temp->ID_card_no << endl;
            SetConsoleTextAttribute(hConsole, 15);
            return;
        }
        temp = temp->next;
    }
    SetConsoleTextAttribute(hConsole, 12);
    cout << "Student with ID card Number " << searchID << " not Found!" << endl;
    SetConsoleTextAttribute(hConsole, 15);
}

//=========================================================
// Delete students function
//=========================================================
void deleteall() {
    if (head == NULL) {
        SetConsoleTextAttribute(hConsole, 12);
        cout << "Database is empty" << endl;
        cout << "Nothing to delete" << endl;
        SetConsoleTextAttribute(hConsole, 15);
    }
    else {
        student* temp;
        while (head != nullptr) {
            temp = head;
            head = head->next;
            delete temp;
        }
        SetConsoleTextAttribute(hConsole, 10); // Green for separators
        cout << "========================================================" << endl;
        cout << "==================*ALL RECORD DELETED*==================" << endl;
        cout << "========================================================" << endl;
        SetConsoleTextAttribute(hConsole, 15);
        studentCount = 0;
    }
}
//=========================================================
// Delete specific student by Roll Number
//=========================================================
void deleteByRoll()
{
    if (head == NULL)
    {
        SetConsoleTextAttribute(hConsole, 12);
        cout << "Database is empty" << endl;
        cout << "Nothing to delete" << endl;
        SetConsoleTextAttribute(hConsole, 15);
        return;
    }

    string roll;
    cout << "Enter Roll Number to delete: ";
    getline(cin, roll);

    // Case 1: First node needs to be deleted
    if (head->roll == roll)
    {
        student* temp = head;
        head = head->next;
        delete temp;
        studentCount--;

        SetConsoleTextAttribute(hConsole, 10);
        cout << "Student with Roll Number " << roll << " deleted successfully." << endl;
        SetConsoleTextAttribute(hConsole, 15);
        return;
    }

    // Case 2: Middle or last node
    student* previous = head;
    student* current = head->next;

    while (current != NULL)
    {
        if (current->roll == roll)
        {
            previous->next = current->next;
            delete current;
            studentCount--;

            SetConsoleTextAttribute(hConsole, 10);
            cout << "Student with Roll Number " << roll << " deleted successfully." << endl;
            SetConsoleTextAttribute(hConsole, 15);
            return;
        }
        previous = current;
        current = current->next;
    }

    // If roll number not found
    SetConsoleTextAttribute(hConsole, 12);
    cout << "Student with Roll Number " << roll << " not found." << endl;
    SetConsoleTextAttribute(hConsole, 15);
}
//=========================================================
// Update student record (Roll & ID are fixed)
//=========================================================
void updateStudentByRoll()
{
    if (head == NULL)
    {
        SetConsoleTextAttribute(hConsole, 12);
        cout << "Database is empty" << endl;
        cout << "Nothing to update" << endl;
        SetConsoleTextAttribute(hConsole, 15);
        return;
    }

    string roll;
    cout << "Enter Roll Number to update record: ";
    getline(cin, roll);

    student* temp = head;

    while (temp != NULL)
    {
        if (temp->roll == roll)
        {
            SetConsoleTextAttribute(hConsole, 14);
            cout << endl;
            cout << "--- Updating Student Record ---" << endl;
            SetConsoleTextAttribute(hConsole, 15);

            cout << "Current Name: " << temp->name << endl;
            cout << "Enter new Name: ";
            getline(cin, temp->name);

            cout << "Current Class: " << temp->clas << endl;
            cout << "Enter new Class: ";
            getline(cin, temp->clas);

            cout << "Current Room: " << temp->room_no << endl;
            cout << "Enter new Room: ";
            getline(cin, temp->room_no);

            cout << "Current Contact: " << temp->contact << endl;
            cout << "Enter new Contact: ";
            getline(cin, temp->contact);

            SetConsoleTextAttribute(hConsole, 10);
            cout << endl;
            cout << "Record updated successfully!" << endl;
            SetConsoleTextAttribute(hConsole, 15);
            return;
        }
        temp = temp->next;
    }

    SetConsoleTextAttribute(hConsole, 12);
    cout << "Student with Roll Number " << roll << " not found." << endl;
    SetConsoleTextAttribute(hConsole, 15);
}



//=========================================================
// MAIN FUNCTION
//=========================================================
int main() {

    string password;
    string correctPassword = "admin123";
    int attempts = 3;

    MessageBox(NULL,
        L"Welcome!\nYou have 3 attempts to enter the password.",
        L"Password Required",
        MB_OK | MB_ICONINFORMATION);

    while (attempts > 0)
    {
        cout << "Enter password: ";
        cin >> password;

        if (password == correctPassword)
        {
            MessageBox(NULL,
                L"Access Granted!\nProgram will continue.",
                L"Success",
                MB_OK | MB_ICONINFORMATION);
            break;
        }
        else
        {
            attempts--;
            MessageBox(NULL,
                L"Wrong Password!",
                L"Error",
                MB_OK | MB_ICONERROR);
        }
    }

    if (attempts == 0)
    {
        MessageBox(NULL,
            L"You entered wrong password 3 times.\nProgram will exit.",
            L"Access Denied",
            MB_OK | MB_ICONSTOP);
        return 0;
    }
    cin.ignore(); // clears input buffer
    cout << endl;
    SetConsoleTextAttribute(hConsole, 10); // Green separator
    cout << "=============================================================================================" << endl;
    SetConsoleTextAttribute(hConsole, 14); // Yellow title
    cout << "===========================*Welcome To Hostel Management Database*===========================" << endl;
    SetConsoleTextAttribute(hConsole, 10); // Green separator
    cout << "=============================================================================================" << endl;


    while (true) {
        SetConsoleTextAttribute(hConsole, 11); // Cyan menu
        cout << "1. Add student(s)" << endl;
        cout << "2. Display All students data" << endl;
        cout << "3. Search student by Roll Number" << endl;
        cout << "4. Search student by ID Card Number" << endl;
        cout << "5. Delete All Students" << endl;
        cout << "6. Delete Specific Student (By Roll Number)" << endl;
        cout << "7. Update Student Record" << endl;
        cout << "8. Exit Database" << endl;

        cout << "Enter your choice: ";
        SetConsoleTextAttribute(hConsole, 15);

        string choice;
        getline(cin, choice);

        if (choice == "1") {
            addStudent_end_of_list();
        }
        else if (choice == "2") {
            SetConsoleTextAttribute(hConsole, 10);
            cout << "=======================================STUDENT RECORD========================================" << endl;
            SetConsoleTextAttribute(hConsole, 15);
            Display_All();
            SetConsoleTextAttribute(hConsole, 10);
            cout << "=============================================================================================" << endl;
            SetConsoleTextAttribute(hConsole, 15);
        }
        else if (choice == "3") {
            SetConsoleTextAttribute(hConsole, 10);
            cout << "=============================================================================================" << endl;
            SetConsoleTextAttribute(hConsole, 15);
            search_by_Roll();
            SetConsoleTextAttribute(hConsole, 10);
            cout << "=============================================================================================" << endl;
            SetConsoleTextAttribute(hConsole, 15);
        }
        else if (choice == "4") {
            SetConsoleTextAttribute(hConsole, 10);
            cout << "=============================================================================================" << endl;
            SetConsoleTextAttribute(hConsole, 15);
            search_by_ID();
            SetConsoleTextAttribute(hConsole, 10);
            cout << "=============================================================================================" << endl;
            SetConsoleTextAttribute(hConsole, 15);
        }
        else if (choice == "5") {
            SetConsoleTextAttribute(hConsole, 10);
            cout << "=============================================================================================" << endl;
            SetConsoleTextAttribute(hConsole, 15);
            deleteall();
            SetConsoleTextAttribute(hConsole, 10);
            cout << "=============================================================================================" << endl;
            SetConsoleTextAttribute(hConsole, 15);
        }
        else if (choice == "6") {
            SetConsoleTextAttribute(hConsole, 10);
            cout << "=============================================================================================" << endl;
            SetConsoleTextAttribute(hConsole, 15);
            deleteByRoll();
            SetConsoleTextAttribute(hConsole, 10);
            cout << "=============================================================================================" << endl;
            SetConsoleTextAttribute(hConsole, 15);
        }
        else if (choice == "7") {
            SetConsoleTextAttribute(hConsole, 10);
            cout << "=============================================================================================" << endl;
            SetConsoleTextAttribute(hConsole, 15);
            updateStudentByRoll();
            SetConsoleTextAttribute(hConsole, 10);
            cout << "=============================================================================================" << endl;
            SetConsoleTextAttribute(hConsole, 15);
        }
        else if (choice == "8") {
            SetConsoleTextAttribute(hConsole, 14);
            cout << "...Exiting program..." << endl;
            SetConsoleTextAttribute(hConsole, 15);
            break;
        }
        else {
            SetConsoleTextAttribute(hConsole, 12); // Red invalid choice
            cout << "Invalid choice! Try again." << endl;
            SetConsoleTextAttribute(hConsole, 15);
        }
    }

    return 0;
}