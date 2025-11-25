#include "ConsistencyChecker.h"
#include <algorithm>

void ConsistencyChecker::setStudents(const vector<Student>& students) 
{
    this->students = students;
}

void ConsistencyChecker::setCourses(const vector<Course>& courses) 
{
    this->courses = courses;
}

void ConsistencyChecker::setFaculty(const vector<Faculty>& faculty) 
{
    this->faculty = faculty;
}

void ConsistencyChecker::setRooms(const vector<Room>& rooms) 
{
    this->rooms = rooms;
}

bool ConsistencyChecker::checkPrerequisiteViolations() 
{
    for (const Student& student : students) 
    {
        for (const string& courseId : student.currentCourses) 
        {
            // Find the course
            for (const Course& course : courses) 
            {
                if (course.id == courseId) 
                {
                    // Check if all prerequisites are satisfied
                    for (const string& prereqId : course.prerequisites) 
                    {
                        bool hasCompleted = false;
                        for (const string& completed : student.completedCourses) 
                        {
                            if (completed == prereqId) 
                            {
                                hasCompleted = true;
                                break;
                            }
                        }

                        if (!hasCompleted) 
                        {
                            return true; // Found a violation
                        }
                    }
                    break;
                }
            }
        }
    }

    return false; // No violations
}

bool ConsistencyChecker::checkCourseOverlaps() 
{
    return false;
}

bool ConsistencyChecker::checkStudentOverload(int maxCreditHours) 
{
    for (const Student& student : students) 
    {
        int totalCredits = 0;

        for (const string& courseId : student.currentCourses) 
        {
            for (const Course& course : courses) 
            {
                if (course.id == courseId) 
                {
                    totalCredits += course.creditHours;
                    break;
                }
            }
        }

        if (totalCredits > maxCreditHours) 
        {
            return true; // Found an overload
        }
    }

    return false; // No overloads
}

bool ConsistencyChecker::checkRoomCapacityViolations() 
{
    return false;
}

vector<string> ConsistencyChecker::getAllViolations() 
{
    vector<string> violations;

    if (checkPrerequisiteViolations()) 
    {
        violations.push_back("Prerequisite violations found");
    }

    if (checkCourseOverlaps()) 
    {
        violations.push_back("Course schedule overlaps found");
    }

    if (checkStudentOverload(21)) 
    { // Assuming 21 credits is the maximum allowed
        violations.push_back("Student credit hour overloads found");
    }

    if (checkRoomCapacityViolations()) 
    {
        violations.push_back("Room capacity violations found");
    }

    return violations;
}