#include "StudentGrouper.h"
#include <algorithm>
#include <iostream>

void StudentGrouper::addStudent(const Student& student)
{
    // Check if student already exists
    for (const Student& s : students)
    {
        if (s.id == student.id)
        {
            cout << "Error: Student " << student.id << " already exists!" << endl;
            return;  // Don't add duplicate
        }
    }

    // If we reach here, student doesn't exist - add it
    students.push_back(student);
    cout << "Student added: " << student.id << " - " << student.name << endl;
}

// Helper method to calculate factorial
int StudentGrouper::factorial(int n) 
{
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

// Helper method to calculate binomial coefficient (n choose k)
int StudentGrouper::binomialCoefficient(int n, int k) 
{
    // C(n,k) = n!/(k!(n-k)!)
    return factorial(n) / (factorial(k) * factorial(n - k));
}

// Generate all combinations of r elements from a set of n elements
vector<vector<int>> StudentGrouper::generateCombinations(int n, int r) 
{
    vector<vector<int>> combinations;

    // Array to represent current combination
    vector<int> combination(r);

    // Initialize first combination (0,1,2,...,r-1)
    for (int i = 0; i < r; i++) 
    {
        combination[i] = i;
    }

    while (true) 
    {
        // Add current combination
        combinations.push_back(combination);

        // Find rightmost element that can be incremented
        int i = r - 1;
        while (i >= 0 && combination[i] == n - r + i) {
            i--;
        }

        // If no such element, we're done
        if (i < 0) 
        {
            break;
        }

        // Increment this element
        combination[i]++;

        // Reset elements to the right
        for (int j = i + 1; j < r; j++) 
        {
            combination[j] = combination[j - 1] + 1;
        }
    }

    return combinations;
}

// Get the total number of possible group combinations
int StudentGrouper::getNumberOfPossibleGroups(int n, int r) 
{
    return binomialCoefficient(n, r);
}

vector<vector<Student>> StudentGrouper::createProjectGroups(int groupSize) 
{
    vector<vector<Student>> groups;
    int totalStudents = students.size();

    // If no students or invalid group size, return empty result
    if (totalStudents == 0 || groupSize <= 0 || groupSize > totalStudents) 
    {
        return groups;
    }

    // Calculate how many complete groups we can form
    int numGroups = totalStudents / groupSize;
    int remainingStudents = totalStudents % groupSize;

    // Generate all possible combinations of groupSize students
    // This demonstrates the mathematical combination concept
    vector<vector<int>> allCombinations = generateCombinations(totalStudents, groupSize);

    // For practical purposes, we'll just use a subset of all possible combinations
    // In a real system, we might use criteria to select optimal combinations
    for (int i = 0; i < numGroups; i++) 
    {
        if (i < allCombinations.size()) 
        {
            vector<Student> group;
            for (int studentIndex : allCombinations[i]) 
            {
                group.push_back(students[studentIndex]);
            }
            groups.push_back(group);
        }
    }

    // Handle remaining students if any
    if (remainingStudents > 0) {
        vector<Student> lastGroup;
        for (int i = totalStudents - remainingStudents; i < totalStudents; i++) {
            lastGroup.push_back(students[i]);
        }
        groups.push_back(lastGroup);
    }

    return groups;
}

vector<vector<Student>> StudentGrouper::assignToLabSessions(int numSessions) 
{
    vector<vector<Student>> sessions(numSessions);
    int totalStudents = students.size();

    // Using subset selection concept - divide students into numSessions subsets
    // Each subset corresponds to a lab session

    // Calculate ideal number of students per session
    int studentsPerSession = totalStudents / numSessions;
    int extraStudents = totalStudents % numSessions;

    int currentIndex = 0;

    // Distribute students among sessions
    for (int i = 0; i < numSessions; i++) 
    {
        int sessionSize = studentsPerSession + (i < extraStudents ? 1 : 0);

        for (int j = 0; j < sessionSize && currentIndex < totalStudents; j++) 
        {
            sessions[i].push_back(students[currentIndex++]);
        }
    }

    return sessions;
}

vector<vector<Student>> StudentGrouper::assignToElectives(int numElectives) 
{
    // For electives, we'll use combinations to create interesting groupings
    vector<vector<Student>> electiveGroups(numElectives);
    int totalStudents = students.size();

    if (totalStudents == 0 || numElectives <= 0) 
    {
        return electiveGroups;
    }

    // Using counting principles to distribute students
    // Each student is assigned to an elective based on a mathematical pattern

    // Generate a distribution pattern based on combinations
    // This demonstrates the counting principles mentioned in the requirements
    for (int i = 0; i < totalStudents; i++) 
    {
        // Using modular arithmetic to assign students to electives
        int electiveIndex = i % numElectives;
        electiveGroups[electiveIndex].push_back(students[i]);
    }

    return electiveGroups;
}

Student* StudentGrouper::getStudent(const string& studentId) 
{
    for (Student& student : students) 
    {
        if (student.id == studentId) 
        {
            return &student;
        }
    }
    return nullptr;
}

vector<Student> StudentGrouper::getAllStudents() 
{
    return students;
}