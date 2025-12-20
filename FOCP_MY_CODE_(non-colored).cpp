#include <iostream>
#include <string>
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
        cout << "Cannot add more students. Maximum rooms reached.\n";
        return;
    }
    string input;
    cout << "How many students do you want to add? ";
    getline(cin, input);
    int n = stoi(input);
    if (studentCount + n > MAX_STUDENTS) {
        cout << "Cannot add " << n << " students. ";
        cout << "Only " << (MAX_STUDENTS - studentCount) << " can be added." << endl;
        return;
    }
    for (int i = 0; i < n; i++) {
        cout << endl;
        cout << "Enter details of student " << studentCount + 1 << endl;
        student* newStudent = new student;
        cout << "Enter name: ";
        getline(cin, newStudent->name);

        // Roll number validation
        while (true) {
            cout << "Enter roll number: ";
            getline(cin, newStudent->roll);
            if (isRollExists(newStudent->roll))
                cout << "This roll number already exists! Please enter a different roll number." << endl;
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
            if (isIDExists(newStudent->ID_card_no))
                cout << "This ID card number already exists! Please enter a different ID." << endl;
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
        cout << "Student added successfully." << endl;
    }
}

//=========================================================
// Giving All stored Students
//=========================================================
void Display_All() {
    if (head == nullptr) {
        cout << "Database is empty" << endl;
        cout << "NO STUDENT TO DISPLAY!\n";
        return;
    }
    student* temp = head;
    while (temp != NULL) {
        cout << "Name: " << temp->name << endl;
        cout << "Roll: " << temp->roll << endl;
        cout << "Class: " << temp->clas << endl;
        cout << "Room: " << temp->room_no << endl;
        cout << "Contact: " << temp->contact << endl;
        cout << "ID Card: " << temp->ID_card_no << endl;
        cout << "---------------------------\n";
        temp = temp->next; // Move to next node
    }
}

//=========================================================
// Giving Data of specific Student (roll no wise)
//=========================================================
void search_by_Roll() {
    if (head == NULL) // checking whether Database is empty or not
    {
        cout << "Empty Database" << endl;
        cout << "Nothing to Display" << endl;
        return;
    }
    else {
        student* temp = head; // temporary pointer to traverse the linked list
        string searchRoll;
        cout << "Enter roll number to search: ";
        getline(cin, searchRoll);
        while (temp != nullptr) {
            if (temp->roll == searchRoll) {
                cout << "Name: " << temp->name << endl;
                cout << "Roll: " << temp->roll << endl;
                cout << "Class: " << temp->clas << endl;
                cout << "Room: " << temp->room_no << endl;
                cout << "Contact: " << temp->contact << endl;
                cout << "ID Card: " << temp->ID_card_no << endl;
                return; // if student found, simply print and leave the function
            }
            temp = temp->next;
        }
        // if not found after checking full linked list
        cout << "Student with Roll Number " << searchRoll << " not Found!" << endl;
    }
}

//=========================================================
// Giving Data of specific Student (ID Card no wise)
//=========================================================
void search_by_ID() {
    if (head == NULL) // checking whether Database is empty or not
    {
        cout << "Empty Database" << endl;
        cout << "Nothing to Display" << endl;
        return;
    }
    else {
        student* temp = head; // temporary pointer to traverse the linked list
        string searchID;
        cout << "Enter ID card number to search: ";
        getline(cin, searchID);
        while (temp != nullptr) {
            if (temp->ID_card_no == searchID) {
                cout << "Name: " << temp->name << endl;
                cout << "Roll: " << temp->roll << endl;
                cout << "Class: " << temp->clas << endl;
                cout << "Room: " << temp->room_no << endl;
                cout << "Contact: " << temp->contact << endl;
                cout << "ID Card: " << temp->ID_card_no << endl;
                return; // if student found, simply print and leave the function
            }
            temp = temp->next;
        }
        // if not found after checking full linked list
        cout << "Student with ID card Number " << searchID << " not Found!" << endl;
    }
}
//=========================================================
// Delete students function
//=========================================================
void deleteall() {
    if (head == NULL) 
    {
        cout << "Database is empty" << endl;
        cout << "Nothing to delete" << endl;
    }
    else {
        student* temp;// temporary pointer will be used to store current node
        while (head != nullptr) 
        {
            temp = head;// initially head is stored in temporary ptr
            // now pointing the head to the next link so that data is not lost
            head = head->next;
        }
        cout<<"========================================================";
        cout<<"==================*ALL RECORD DELETED*==================";
        cout<<"========================================================";
        studentCount = 0;
    }
}

//=========================================================
// MAIN FUNCTION
//=========================================================
int main() {
    while (true) {
        cout << endl;
        cout << "=============================================================================================" << endl;
        cout << "===========================*Welcome To Hostel Management Database*===========================" << endl;
        cout << "=============================================================================================" << endl;
        cout << "1. Add student(s)" << endl;
        cout << "2. Display All students data" << endl;
        cout << "3. Search student by Roll Number" << endl;
        cout << "4. Search student by ID Card Number" << endl;
        cout << "5. Delete All Students" << endl;
        cout << "6. Exit Database" << endl;
        cout << "Enter your choice: ";
        string choice;
        getline(cin, choice);

        if (choice == "1") {
            addStudent_end_of_list(); // add students
        }
        else if (choice == "2") {
            cout << "=======================================STUDENT RECORD========================================" << endl;
            Display_All(); // display all students
            cout << "============================================================================================="<<endl;
        }
        else if (choice == "3") {
            cout << "=============================================================================================" << endl;
            search_by_Roll(); // search student by roll
            cout << "=============================================================================================" << endl;
        }
        else if (choice == "4") {
            cout << "=============================================================================================" << endl;
            search_by_ID(); // search student by ID
            cout << "=============================================================================================" << endl;
        }
        else if (choice == "5") {
            cout << "=============================================================================================" << endl;
            deleteall(); // delete all students
            cout << "All student records deleted successfully."<<endl;
            cout << "=============================================================================================" << endl;
        }
        else if (choice == "6") {
            cout << "...Exiting program..."<<endl;
            break;
            
        }
        else {
            cout << "Invalid choice! Try again."<<endl;
        }
    }
    return 0;
}
