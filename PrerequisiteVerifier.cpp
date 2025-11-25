#include "PrerequisiteVerifier.h"
#include <algorithm>

void PrerequisiteVerifier::addCourse(const Course& course) 
{
    courses.push_back(course);
}

bool PrerequisiteVerifier::verifyDirectPrerequisites(const string& courseId,
    const vector<string>& completedCourses) 
{
    // Base case: Find the course
    for (const Course& course : courses) 
    {
        if (course.id == courseId) 
        {
            // If there are no prerequisites, return true (base case)
            if (course.prerequisites.empty()) 
            {
                return true;
            }

            // Check if all direct prerequisites are completed
            for (const string& prereq : course.prerequisites) 
            {
                if (find(completedCourses.begin(), completedCourses.end(), prereq) == completedCourses.end()) 
                {
                    return false; // Missing prerequisite
                }
            }
            return true; // All prerequisites satisfied
        }
    }
    return false; // Course not found
}

bool PrerequisiteVerifier::verifyAllPrerequisites(const string& courseId,
    const vector<string>& completedCourses) 
{
    // Strong induction: verify all prerequisites in the chain
    vector<string> allPrereqs = getAllPrerequisites(courseId);

    // Check if all prerequisites are completed
    for (const string& prereq : allPrereqs) 
    {
        if (find(completedCourses.begin(), completedCourses.end(), prereq) == completedCourses.end()) 
        {
            return false; // Missing prerequisite
        }
    }
    return true;
}

vector<string> PrerequisiteVerifier::getAllPrerequisites(const string& courseId) 
{
    vector<string> result;
    vector<string> stack;
    vector<string> visited;

    // First, find direct prerequisites of the course
    for (const Course& course : courses) 
    {
        if (course.id == courseId) 
        {
            for (const string& prereq : course.prerequisites) 
            {
                stack.push_back(prereq);
            }
            break;
        }
    }

    // Use depth-first search to find all prerequisites
    while (!stack.empty()) 
    {
        string current = stack.back();
        stack.pop_back();

        // If already visited, skip
        if (find(visited.begin(), visited.end(), current) != visited.end()) 
        {
            continue;
        }

        // Add to result and mark as visited
        result.push_back(current);
        visited.push_back(current);

        // Add its prerequisites to stack
        for (const Course& course : courses) 
        {
            if (course.id == current) 
            {
                for (const string& prereq : course.prerequisites) 
                {
                    stack.push_back(prereq);
                }
                break;
            }
        }
    }

    return result;
}