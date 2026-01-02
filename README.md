<h1>Hostel Management System</h1>
==========================================================
USER MANUAL: HOSTEL MANAGEMENT SYSTEM
==========================================================

1. SYSTEM REQUIREMENTS
-----------------------
- Operating System: Windows (Required for <windows.h> and <conio.h>)
- IDE: Visual Studio or VS Code with C++ Compiler (MinGW/MSVC)

2. HOW TO START
----------------
1. Open the source code file in your IDE.
2. Build/Compile the project.
3. Run the executable.
4. LOGIN SCREEN: 
   - The system is protected. 
   - Default Password: admin
   - You have 3 attempts. If failed, the program exits.

3. FEATURES GUIDE
------------------
[1] Add Student:
    - Enter student details.
    - validations: Roll No must be unique. Room capacity is capped at 2 students.

[2] Update Student Data:
    - Requires Roll Number to identify the student.
    - You can modify Name, School, Room, and Contact.

[3] Display All:
    - Shows a list of all currently admitted students.

[4-6] Search Options:
    - Search specific records by Roll Number, ID Card, or Room Number.

[7-8] Deletion:
    - Delete a specific student by Roll Number or wipe the entire database.

[9] Generate Report:
    - view the total occupancy percentage and available slots.

[10] Random Room Inspection:
    - A simulation feature that randomly picks a room and assigns a cleanliness score.

[11] Exit & Save:
    - ALWAYS use this option to close the program. 
    - It ensures data is written to 'hostel_data.txt' safely.

4. TROUBLESHOOTING
-------------------
- "Data not saving?": Ensure you exit using Option 11.
- "Console closes immediately": Run the program via the IDE's terminal or Command Prompt.
