#include "DataStructures.h"
#include "CLIInterface.h"
#include "TestingFramework.h"
#include <iostream>

void addSampleData(vector<Student>& students, vector<Course>& courses,
    vector<Faculty>& faculty, vector<Room>& rooms);
int main() 
{
    while (true)
    {
        cout << "===== UNIDISC ENGINE - FAST University =====\n\n";
        cout << "1. Run Interactive Mode\n";
        cout << "2. Run Test Mode\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;
        while (cin.fail())
        {
            cin.clear(); // clear the fail state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
            cout << "Invalid input. Please enter a number: ";
            cin >> choice;
        }

        if (choice == 1)
        {
            CLIInterface cli;
            cli.run();
        }
        else if (choice == 2)
        {
            TestingFramework tests;
            tests.runAllTests();
			system("pause");
			system("cls");
        }
        else if( choice == 0)
        {
            cout << "Exiting the program. Goodbye!\n";
            break;
		}
        else
        {
            cout << "Invalid choice.\n";
        }
    }
    return 0;
}

void addSampleData(vector<Student>& students, vector<Course>& courses,
    vector<Faculty>& faculty, vector<Room>& rooms) 
{
    // Add sample courses
    Course cs101("CS101", "Introduction to Computer Science", 3);
    Course cs201("CS201", "Data Structures", 4);
    cs201.prerequisites.push_back("CS101");
    Course cs301("CS301", "Algorithms", 4);
    cs301.prerequisites.push_back("CS201");
    Course math101("MATH101", "Calculus I", 3);

    courses.push_back(cs101);
    courses.push_back(cs201);
    courses.push_back(cs301);
    courses.push_back(math101);

    // Add sample students
    Student s1("S001", "John Smith");
    s1.completedCourses.push_back("CS101");
    s1.currentCourses.push_back("CS201");

    Student s2("S002", "Jane Doe");
    s2.completedCourses.push_back("CS101");
    s2.completedCourses.push_back("CS201");
    s2.currentCourses.push_back("CS301");

    Student s3("S003", "Bob Johnson");
    s3.currentCourses.push_back("CS101");
    s3.currentCourses.push_back("MATH101");

    students.push_back(s1);
    students.push_back(s2);
    students.push_back(s3);

    // Add sample faculty
    Faculty f1("F001", "Dr. Smith");
    f1.assignedCourses.push_back("CS101");
    f1.assignedCourses.push_back("CS301");

    Faculty f2("F002", "Dr. Johnson");
    f2.assignedCourses.push_back("CS201");
    f2.assignedCourses.push_back("MATH101");

    faculty.push_back(f1);
    faculty.push_back(f2);

    // Add sample rooms
    Room r1("R001", 30);
    Room r2("R002", 50);
    Room r3("R003", 100);

    rooms.push_back(r1);
    rooms.push_back(r2);
    rooms.push_back(r3);
}