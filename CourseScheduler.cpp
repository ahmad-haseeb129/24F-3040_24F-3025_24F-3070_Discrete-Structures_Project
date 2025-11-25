#include "CourseScheduler.h"
#include <algorithm>
#include <iostream>
using namespace std;
void CourseScheduler::addCourse(const Course& course) //where is this used? // 
{
    // Check if course already exists
    for (const Course& c : courses)
    {
        if (c.id == course.id)
        {
            cout << "Error: Course " << course.id << " already exists!" << endl;
            return;  // Don't add duplicate
        }
    }

    // If we reach here, course doesn't exist - add it
    courses.push_back(course);
    cout << "Course added: " << course.id << endl;
}

bool CourseScheduler::isPrerequisite(const string& course, const string& prereq) 
{
    for (const Course& c : courses) 
    {
        if (c.id == course) 
        {
            for (const string& p : c.prerequisites) 
            {
                if (p == prereq) 
                {
                    return true;
                }
            }
            return false;
        }
    }
    return false;
}

void CourseScheduler::generateValidSequences(const vector<string>& remainingCourses, vector<string>& currentSequence) 
{
    // Base case: if no courses remain, we have a valid sequence
    if (remainingCourses.empty()) 
    {
        validSequences.push_back(currentSequence);
        return;
    }

    // Try adding each remaining course to the sequence
    for (int i = 0; i < remainingCourses.size(); i++) 
    {
        string courseId = remainingCourses[i];

        // Check if all prerequisites for this course are in the current sequence
        bool canTake = true;
        for (const Course& course : courses) 
        {
            if (course.id == courseId) 
            {
                for (const string& prereq : course.prerequisites) 
                {
                    // If prerequisite is not in current sequence, can't take this course yet
                    if (find(currentSequence.begin(), currentSequence.end(), prereq) == currentSequence.end()) {
                        canTake = false;
                        break;
                    }
                }
                break;
            }
        }

        // If we can take this course, add it to sequence and recurse
        if (canTake) 
        {
            // Create new vectors without the current course
            vector<string> newRemaining = remainingCourses;
            newRemaining.erase(newRemaining.begin() + i);

            vector<string> newSequence = currentSequence;
            newSequence.push_back(courseId);

            // Recursive call with updated sequences
            generateValidSequences(newRemaining, newSequence);
        }
    }
}

vector<vector<string>> CourseScheduler::getAllValidSequences() 
{
    validSequences.clear();

    // Get all course IDs
    vector<string> allCourseIds;
    for (const Course& course : courses) 
    {
        allCourseIds.push_back(course.id);
    }

    // Generate all valid sequences
    vector<string> currentSequence;
    generateValidSequences(allCourseIds, currentSequence);

    return validSequences;
}

Course* CourseScheduler::getCourse(const string& courseId) 
{
    for (Course& course : courses) 
    {
        if (course.id == courseId) 
        {
            return &course;
        }
    }
    return nullptr;
}

vector<Course> CourseScheduler::getAllCourses() 
{
    return courses;
}