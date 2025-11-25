#include "SetOperator.h"
#include <algorithm>

void SetOperator::addStudent(const Student& student) 
{
    students.push_back(student);
}

void SetOperator::addCourse(const Course& course) 
{
    courses.push_back(course);
}

void SetOperator::addFaculty(const Faculty& faculty) 
{
    this->faculty.push_back(faculty);
}

void SetOperator::addRoom(const Room& room) 
{
    rooms.push_back(room);
}

// Intersection operation
vector<Student> SetOperator::findStudentsInBothCourses(const string& course1, const string& course2) 
{
    
    vector<Student> result;

    for (const Student& student : students) 
    {
        bool inCourse1 = false;
        bool inCourse2 = false;

        for (const string& course : student.currentCourses) 
        {
            if (course == course1) inCourse1 = true;
            if (course == course2) inCourse2 = true;
        }

        if (inCourse1 && inCourse2) 
        {
            result.push_back(student);
        }
    }

    return result;
}

// Union operation
vector<Student> SetOperator::findStudentsInEitherCourse(const string& course1, const string& course2) 
{
    vector<Student> result;

    for (const Student& student : students) 
    {
        bool inCourse1 = false;
        bool inCourse2 = false;

        for (const string& course : student.currentCourses) 
        {
            if (course == course1) inCourse1 = true;
            if (course == course2) inCourse2 = true;
        }

        if (inCourse1 || inCourse2) 
        {
            result.push_back(student);
        }
    }

    return result;
}

// Complement operation
vector<Student> SetOperator::findStudentsNotInCourse(const string& courseId) 
{
    vector<Student> result;

    for (const Student& student : students) 
    {
        bool inCourse = false;

        for (const string& course : student.currentCourses) 
        {
            if (course == courseId) 
            {
                inCourse = true;
                break;
            }
        }

        if (!inCourse) 
        {
            result.push_back(student);
        }
    }

    return result;
}

vector<Course> SetOperator::getCoursesWithoutPrerequisites() 
{
    vector<Course> result;

    for (const Course& course : courses) 
    {
        if (course.prerequisites.empty()) 
        {
            result.push_back(course);
        }
    }

    return result;
}

bool SetOperator::isSubset(const vector<string>& set1, const vector<string>& set2) 
{
    // Check if set1 is a subset of set2
    for (const string& item : set1) 
    {
        if (find(set2.begin(), set2.end(), item) == set2.end()) 
        {
            return false; // Item not found in set2
        }
    }
    return true;
}

vector<vector<string>> SetOperator::getPowerSet(const vector<string>& set) 
{
    vector<vector<string>> result;

    // A power set has 2^n subsets
    int powerSetSize = 1 << set.size(); // 2^n

    // Generate each subset
    for (int i = 0; i < powerSetSize; i++) 
    {
        vector<string> subset;

        // Check each bit of i
        for (int j = 0; j < set.size(); j++) 
        {
            // If jth bit is set, include jth element from set
            if ((i & (1 << j)) != 0) 
            {
                subset.push_back(set[j]);
            }
        }

        result.push_back(subset);
    }

    return result;
}