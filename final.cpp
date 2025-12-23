#include <iostream>
#include <string>
#include <windows.h> // Required for MessageBox & Console Colors
#include <fstream>   // Required for File Handling
#include <ctime>     // Required for Random numbers
#include <cstdlib>   // Required for rand() and srand()
#include <conio.h>   // Required for _getch()

using namespace std;

//=========================================================
// 1. STRUCTURES & GLOBAL VARIABLES
//=========================================================
struct student
{
    string name;
    string roll;
    string school;
    string room_no;
    string contact;
    string ID_card_no;
    student *next;
};

// Global Variables
student *head = NULL;
const int MAX_STUDENTS = 30;
int studentCount = 0;

// Console Handle
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

//=========================================================
// 2. FUNCTION PROTOTYPES
//=========================================================
// Validations & File Handling
bool isNumeric(string str);
void saveToFile();
void loadFromFile();

// Security
bool login();

// Features
void addStudent_end_of_list();
void Display_All();
void search_by_Roll();
void search_by_ID();
void search_by_Room();
void deleteByRoll();
void updateStudentByRoll();
void deleteall();
void randomRoomInspection();
void generateReport();

// Helper Functions
bool isRollExists(string roll);
bool isIDExists(string id);
bool isRoomAvail(string room_no);

//=========================================================
// 3. MAIN FUNCTION
//=========================================================
int main()
{
    srand(time(0));

    // SECURITY CHECK
    if (!login())
    {
        return 0; // Exit if failed 3 times
    }

    loadFromFile();
    // MENU
    while (true)
    {
        cout << endl;
        SetConsoleTextAttribute(hConsole, 10);
        cout << "==========================================================" << endl;
        SetConsoleTextAttribute(hConsole, 14);
        cout << "         HOSTEL MANAGEMENT SYSTEM         " << endl;
        SetConsoleTextAttribute(hConsole, 10);
        cout << "==========================================================" << endl;
        SetConsoleTextAttribute(hConsole, 11);

        cout << "1. Add student(s)" << endl;
        cout << "2. Update Student Data" << endl;
        cout << "3. Display All Student data" << endl;
        cout << "4. Search by Roll Number" << endl;
        cout << "5. Search by ID Card Number" << endl;
        cout << "6. Search by Room Number" << endl;
        cout << "7. Delete Specific Student" << endl;
        cout << "8. Delete All Students" << endl;
        cout << "9. Generate Hostel Report " << endl;
        cout << "10. Random Room Inspection " << endl;
        cout << "11. Exit & Save" << endl;

        cout << "Enter your choice: ";
        SetConsoleTextAttribute(hConsole, 15);

        string choice;
        getline(cin, choice);

        if (!isNumeric(choice))
        {
            SetConsoleTextAttribute(hConsole, 12);
            cout << "Invalid input! Please enter a number (1-11)." << endl;
            SetConsoleTextAttribute(hConsole, 15);
            continue;
        }

        if (choice == "1")
            addStudent_end_of_list();
        else if (choice == "2")
            updateStudentByRoll();
        else if (choice == "3")
            Display_All();
        else if (choice == "4")
            search_by_Roll();
        else if (choice == "5")
            search_by_ID();
        else if (choice == "6")
            search_by_Room();
        else if (choice == "7")
            deleteByRoll();
        else if (choice == "8")
            deleteall();
        else if (choice == "9")
            generateReport();
        else if (choice == "10")
            randomRoomInspection();
        else if (choice == "11")
        {
            SetConsoleTextAttribute(hConsole, 14);
            cout << "Saving data..." << endl;
            saveToFile();
            // Memory Clean
            student *temp;
            while (head != NULL)
            {
                temp = head;
                head = head->next;
                delete temp;
            }

            cout << "Exiting program. Goodbye!" << endl;
            SetConsoleTextAttribute(hConsole, 15);
            break;
        }
        else
        {
            SetConsoleTextAttribute(hConsole, 12);
            cout << "Invalid choice! Try again." << endl;
            SetConsoleTextAttribute(hConsole, 15);
        }
    }
    return 0;
}

//=========================================================
// 4. FUNCTION DEFINITIONS
//=========================================================

bool isNumeric(string str)
{
    if (str.empty())
        return false;
    for (char c : str)
    {
        if (!isdigit(c))
            return false;
    }
    return true;
}

bool login()
{
    string password;
    string correctPassword = "admin";
    int attempts = 3;
    char ch;

    // Used MessageBoxA for compatibility with standard strings
    MessageBoxA(NULL,
                "Welcome!\nYou have 3 attempts to enter the password.",
                "Password Required",
                MB_OK | MB_ICONINFORMATION);

    while (attempts > 0)
    {
        system("cls"); // Clean Screen
        SetConsoleTextAttribute(hConsole, 11);
        cout << "\n\n\t\t========================================" << endl;
        cout << "\t\t|          SECURITY CHECK              |" << endl;
        cout << "\t\t========================================" << endl;
        SetConsoleTextAttribute(hConsole, 15);

        cout << "\n\t\t   Attempts Remaining: " << attempts << endl;
        cout << "\t\t   Enter password: ";

        password = "";
        ch = _getch();
        while (ch != 13) // Enter
        {
            if (ch == 8) // Backspace
            {
                if (password.length() > 0)
                {
                    password.pop_back();
                    cout << "\b \b";
                }
            }
            else
            {
                password.push_back(ch);
                cout << "*";
            }
            ch = _getch();
        }

        if (password == correctPassword)
        {
            MessageBoxA(NULL,
                        "Access Granted!\nProgram will continue.",
                        "Success",
                        MB_OK | MB_ICONINFORMATION);
            system("cls");
            return true;
        }
        else
        {
            attempts--;
            if (attempts > 0)
            {
                MessageBoxA(NULL,
                            "Wrong Password!",
                            "Error",
                            MB_OK | MB_ICONERROR);
            }
        }
    }

    if (attempts == 0)
    {
        MessageBoxA(NULL,
                    "You entered wrong password 3 times.\nProgram will exit.",
                    "Access Denied",
                    MB_OK | MB_ICONSTOP);
        return false;
    }
    return false;
}

void saveToFile()
{
    ofstream outFile("hostel_data.txt");
    if (!outFile)
    {
        SetConsoleTextAttribute(hConsole, 12);
        cout << "Error: Could not open file for saving!" << endl;
        SetConsoleTextAttribute(hConsole, 15);
        return;
    }

    student *temp = head;
    while (temp != NULL)
    {
        outFile << temp->name << endl;
        outFile << temp->roll << endl;
        outFile << temp->school << endl;
        outFile << temp->room_no << endl;
        outFile << temp->contact << endl;
        outFile << temp->ID_card_no << endl;
        temp = temp->next;
    }
    outFile.close();
    SetConsoleTextAttribute(hConsole, 10);
    cout << "Data saved successfully. " << endl;
    SetConsoleTextAttribute(hConsole, 15);
}

void loadFromFile()
{
    ifstream inFile("hostel_data.txt");
    if (!inFile)
        return;

    string name, roll, school, room, contact, id;

    while (getline(inFile, name))
    {
        if (name.empty())
            break;

        getline(inFile, roll);
        getline(inFile, school);
        getline(inFile, room);
        getline(inFile, contact);
        getline(inFile, id);

        student *newStudent = new student;
        newStudent->name = name;
        newStudent->roll = roll;
        newStudent->school = school;
        newStudent->room_no = room;
        newStudent->contact = contact;
        newStudent->ID_card_no = id;
        newStudent->next = NULL;

        if (head == NULL)
            head = newStudent;
        else
        {
            student *temp = head;
            while (temp->next != NULL)
                temp = temp->next;
            temp->next = newStudent;
        }
        studentCount++;
    }
    inFile.close();
}

bool isRollExists(string roll)
{
    student *temp = head;
    while (temp != NULL)
    {
        if (temp->roll == roll)
            return true;
        temp = temp->next;
    }
    return false;
}

bool isIDExists(string id)
{
    student *temp = head;
    while (temp != NULL)
    {
        if (temp->ID_card_no == id)
            return true;
        temp = temp->next;
    }
    return false;
}

bool isRoomAvail(string room_no)
{
    int count = 0;
    student *temp = head;
    while (temp != NULL)
    {
        if (temp->room_no == room_no)
            count++;
        temp = temp->next;
    }
    if (count < 2)
        return true;
    else
        return false;
}

void addStudent_end_of_list()
{
    if (studentCount >= MAX_STUDENTS)
    {
        SetConsoleTextAttribute(hConsole, 12);
        cout << "Cannot add more students. Maximum capacity reached.\n";
        SetConsoleTextAttribute(hConsole, 15);
        return;
    }

    string input;
    SetConsoleTextAttribute(hConsole, 11);
    cout << "How many students do you want to add? ";
    SetConsoleTextAttribute(hConsole, 15);
    getline(cin, input);

    if (!isNumeric(input))
    {
        cout << "Invalid input! Please enter a number.\n";
        return;
    }

    int n = stoi(input);

    if (studentCount + n > MAX_STUDENTS)
    {
        SetConsoleTextAttribute(hConsole, 12);
        cout << "Cannot add " << n << " students. Only " << (MAX_STUDENTS - studentCount) << " slots remaining." << endl;
        SetConsoleTextAttribute(hConsole, 15);
        return;
    }

    for (int i = 0; i < n; i++)
    {
        cout << endl;
        SetConsoleTextAttribute(hConsole, 11);
        cout << "Enter Details of student " << studentCount + 1 << endl;
        SetConsoleTextAttribute(hConsole, 15);

        student *newStudent = new student;
        cout << "Enter name: ";
        getline(cin, newStudent->name);

        while (true)
        {
            cout << "Enter roll number: ";
            getline(cin, newStudent->roll);
            if (isRollExists(newStudent->roll))
            {
                SetConsoleTextAttribute(hConsole, 12);
                cout << "This roll no. already exists! Try again." << endl;
                SetConsoleTextAttribute(hConsole, 15);
            }
            else
                break;
        }

        cout << "Enter College/University: ";
        getline(cin, newStudent->school);

        while (true)
        {
            cout << "Enter Room number(1-15): ";
            getline(cin, newStudent->room_no);

            if (!isNumeric(newStudent->room_no))
            {
                SetConsoleTextAttribute(hConsole, 12);
                cout << "Invalid input! Room must be a number." << endl;
                SetConsoleTextAttribute(hConsole, 15);
                continue;
            }

            int r = stoi(newStudent->room_no);
            if (r < 1 || r > 15)
            {
                SetConsoleTextAttribute(hConsole, 12);
                cout << "Invalid! Room must be between 1 and 15." << endl;
                SetConsoleTextAttribute(hConsole, 15);
                continue;
            }

            if (!isRoomAvail(newStudent->room_no))
            {
                SetConsoleTextAttribute(hConsole, 12);
                cout << "This Room is Full! (MAX 2 Students)" << endl;
                SetConsoleTextAttribute(hConsole, 15);
                continue;
            }
            break;
        }

        cout << "Enter Contact no.: ";
        getline(cin, newStudent->contact);

        while (true)
        {
            cout << "Enter ID card number: ";
            getline(cin, newStudent->ID_card_no);
            if (isIDExists(newStudent->ID_card_no))
            {
                SetConsoleTextAttribute(hConsole, 12);
                cout << "This ID card number already exists! Try again." << endl;
                SetConsoleTextAttribute(hConsole, 15);
            }
            else
                break;
        }

        newStudent->next = NULL;

        if (head == NULL)
            head = newStudent;
        else
        {
            student *temp = head;
            while (temp->next != NULL)
                temp = temp->next;
            temp->next = newStudent;
        }
        studentCount++;
        SetConsoleTextAttribute(hConsole, 9);
        cout << "Student added successfully." << endl;
        saveToFile();
        SetConsoleTextAttribute(hConsole, 15);
    }
}

void Display_All()
{
    if (head == NULL)
    {
        SetConsoleTextAttribute(hConsole, 12);
        cout << "No data found!" << endl;
        SetConsoleTextAttribute(hConsole, 15);
        return;
    }
    student *temp = head;
    while (temp != NULL)
    {   SetConsoleTextAttribute(hConsole, 10);
        cout << "---------------------------\n";
        SetConsoleTextAttribute(hConsole, 9);
        cout << "Name: " << temp->name << endl;
        cout << "Roll: " << temp->roll << endl;
        cout << "College/University: " << temp->school << endl;
        cout << "Room: " << temp->room_no << endl;
        cout << "Contact: " << temp->contact << endl;
        cout << "ID Card: " << temp->ID_card_no << endl;
        SetConsoleTextAttribute(hConsole, 10);
        cout << "---------------------------\n";
        temp = temp->next;
    }
    SetConsoleTextAttribute(hConsole, 15);
}

void search_by_Roll()
{
    if (head == NULL)
    {
        cout << "No data to search!\n";
        return;
    }

    student *temp = head;
    string searchRoll;
    cout << "Enter roll number to search: ";
    getline(cin, searchRoll);

    while (temp != NULL)
    {
        if (temp->roll == searchRoll)
        {
            SetConsoleTextAttribute(hConsole, 9);
            cout << "\nFound Record:\n";
            cout << "Name: " << temp->name << endl;
            cout << "Room: " << temp->room_no << endl;
            SetConsoleTextAttribute(hConsole, 15);
            return;
        }
        temp = temp->next;
    }
    SetConsoleTextAttribute(hConsole, 12);
    cout << "Not Found!" << endl;
    SetConsoleTextAttribute(hConsole, 15);
}

void search_by_ID()
{
    if (head == NULL)
    {
        cout << "No data to search!\n";
        return;
    }
    student *temp = head;
    string searchID;
    cout << "Enter ID card number to search: ";
    getline(cin, searchID);
    while (temp != NULL)
    {
        if (temp->ID_card_no == searchID)
        {
            SetConsoleTextAttribute(hConsole, 9);
            cout << "\nFound Record:\n";
            cout << "Name: " << temp->name << endl;
            cout << "Roll: " << temp->roll << endl;
            cout << "Room: " << temp->room_no << endl;
            SetConsoleTextAttribute(hConsole, 15);
            return;
        }
        temp = temp->next;
    }
    cout << "Not Found!" << endl;
}

void search_by_Room()
{
    if (head == NULL)
    {
        cout << "No data to search!\n";
        return;
    }
    student *temp = head;
    string searchRoom;
    bool found = false;
    cout << "Enter Room number to search: ";
    getline(cin, searchRoom);

    cout << endl;
    while (temp != nullptr)
    {
        if (temp->room_no == searchRoom)
        {
            found = true;
            SetConsoleTextAttribute(hConsole, 9);
            cout << "Name: " << temp->name << endl;
            cout << "Roll: " << temp->roll << endl;
            SetConsoleTextAttribute(hConsole, 10);
            cout << "---------------------------" << endl;
        }
        temp = temp->next;
    }
    if (!found)
        cout << "No students found in Room " << searchRoom << "!" << endl;
    SetConsoleTextAttribute(hConsole, 15);
};

void deleteByRoll()
{
    if (head == NULL)
    {
        SetConsoleTextAttribute(hConsole, 12);
        cout << "No data found!\n";
        SetConsoleTextAttribute(hConsole, 15);
        return;
    }

    string roll;
    cout << "Enter Roll Number to delete: ";
    getline(cin, roll);

    if (head->roll == roll)
    {
        student *temp = head;
        head = head->next;
        delete temp;
        studentCount--;

        SetConsoleTextAttribute(hConsole, 10);
        cout << "Deleted successfully." << endl;
        SetConsoleTextAttribute(hConsole, 15);
        saveToFile();
        return;
    }

    student *previous = head;
    student *current = head->next;

    while (current != NULL)
    {
        if (current->roll == roll)
        {
            previous->next = current->next;
            delete current;
            studentCount--;

            SetConsoleTextAttribute(hConsole, 10);
            cout << "Deleted successfully." << endl;
            SetConsoleTextAttribute(hConsole, 15);
            saveToFile();
            return;
        }
        previous = current;
        current = current->next;
    }

    SetConsoleTextAttribute(hConsole, 12);
    cout << "Roll Number not found." << endl;
    SetConsoleTextAttribute(hConsole, 15);
}

void updateStudentByRoll()
{
    if (head == NULL)
    {
        SetConsoleTextAttribute(hConsole, 12);
        cout << "No data found!" << endl;
        SetConsoleTextAttribute(hConsole, 15);
        return;
    }

    string roll;
    cout << "Enter Roll Number to update: ";
    getline(cin, roll);

    student *temp = head;
    while (temp != NULL)
    {
        if (temp->roll == roll)
        {
            SetConsoleTextAttribute(hConsole, 14);
            cout << "\n--- Updating Student Record ---" << endl;
            SetConsoleTextAttribute(hConsole, 15);

            cout << "Current Name: " << temp->name << endl;
            cout << "Enter new Name: ";
            getline(cin, temp->name);

            cout << "Current School: " << temp->school << endl;
            cout << "Enter new School: ";
            getline(cin, temp->school);

            cout << "Current Room: " << temp->room_no << endl;
            while (true)
            {
                cout << "Enter new Room: ";
                string newRoom;
                getline(cin, newRoom);

                if (!isNumeric(newRoom))
                {
                    SetConsoleTextAttribute(hConsole, 12);
                    cout << "Invalid room! Must be a number.\n";
                    SetConsoleTextAttribute(hConsole, 15);
                    continue;
                }

                if (newRoom == temp->room_no)
                    break;

                int r = stoi(newRoom);
                if (r < 1 || r > 15)
                {
                    SetConsoleTextAttribute(hConsole, 12);
                    cout << "Invalid room! Must be 1-15.\n";
                    SetConsoleTextAttribute(hConsole, 15);
                    continue;
                }

                if (!isRoomAvail(newRoom))
                {
                    SetConsoleTextAttribute(hConsole, 12);
                    cout << "Room is full! Choose another.\n";
                    SetConsoleTextAttribute(hConsole, 15);
                    continue;
                }

                temp->room_no = newRoom;
                break;
            }

            cout << "Current Contact: " << temp->contact << endl;
            cout << "Enter new Contact: ";
            getline(cin, temp->contact);

            SetConsoleTextAttribute(hConsole, 10);
            cout << "Record updated successfully!" << endl;
            SetConsoleTextAttribute(hConsole, 15);
            saveToFile();
            return;
        }
        temp = temp->next;
    }

    SetConsoleTextAttribute(hConsole, 12);
    cout << "Roll Number not found." << endl;
    SetConsoleTextAttribute(hConsole, 15);
}

void deleteall()
{
    if (head == NULL)
    {
        cout << "Nothing to delete.\n";
        return;
    }

    SetConsoleTextAttribute(hConsole, 12);
    cout << "WARNING: This will delete ALL records. Continue? (Y/N): ";
    SetConsoleTextAttribute(hConsole, 15);
    string confirm;
    getline(cin, confirm);

    if (confirm == "Y" || confirm == "y")
    {
        student *temp;
        while (head != NULL)
        {
            temp = head;
            head = head->next;
            delete temp;
        }
        studentCount = 0;
        saveToFile();
        cout << "All records deleted.\n";
    }
}

void randomRoomInspection()
{
    if (head == NULL)
    {
        cout << "No students to inspect.\n";
        return;
    }

    int randomRoom = (rand() % 15) + 1;

    SetConsoleTextAttribute(hConsole, 14);
    cout << "\n--- CONDUCTING SURPRISE INSPECTION ON ROOM " << randomRoom << " ---" << endl;

    bool found = false;
    student *temp = head;
    while (temp != NULL)
    {
        if (isNumeric(temp->room_no) && stoi(temp->room_no) == randomRoom)
        {
            found = true;

            int check = rand() % 100;

            cout << "Student: " << temp->name << " | ";

            if (check > 20)
            {
                SetConsoleTextAttribute(hConsole, 10);
                cout << "[PASSED] Cleanliness check (Score: " << check << ")" << endl;
            }
            else
            {
                SetConsoleTextAttribute(hConsole, 12);
                cout << "[FAILED] Fined for messiness (Score: " << check << ")" << endl;
            }
        }
        temp = temp->next;
    }
    SetConsoleTextAttribute(hConsole, 15);

    if (!found)
        cout << "Room " << randomRoom << " is currently empty." << endl;
}

void generateReport()
{
    int totalCapacity = MAX_STUDENTS;
    double occupancyRate = (double(studentCount) / totalCapacity) * 100;

    SetConsoleTextAttribute(hConsole, 14);
    cout << "\n=== HOSTEL SUMMARY REPORT ===" << endl;
    SetConsoleTextAttribute(hConsole, 11);
    cout << "Total Students: " << studentCount << endl;
    cout << "Total Capacity: " << totalCapacity << endl;
    cout << "Occupancy Rate: " << occupancyRate << "%" << endl;
    cout << "Slots Available: " << (totalCapacity - studentCount) << endl;
    if (occupancyRate == 0)
    {
        cout << "Status: Hostel is empty!" << endl;
    }
    else if (occupancyRate > 90)
    {
        SetConsoleTextAttribute(hConsole, 12);
        cout << "Status: Hostel is nearly full!" << endl;
    }
    else
    {
        SetConsoleTextAttribute(hConsole, 10);
        cout << "Status: Normal. " << endl;
    }
    SetConsoleTextAttribute(hConsole, 15);
}