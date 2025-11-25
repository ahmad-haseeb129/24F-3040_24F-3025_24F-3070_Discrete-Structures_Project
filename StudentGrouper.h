#ifndef STUDENT_GROUPER_H
#define STUDENT_GROUPER_H

#include "DataStructures.h"
#include <vector>

class StudentGrouper 
{
private:
    vector<Student> students;

    // Helper methods for combinations
    vector<vector<int>> generateCombinations(int n, int r);
    int factorial(int n);
    int binomialCoefficient(int n, int k);

public:
    void addStudent(const Student& student);

    // Create project groups using combinations
    vector<vector<Student>> createProjectGroups(int groupSize);

    // Assign students to lab sessions using subset selection
    vector<vector<Student>> assignToLabSessions(int numSessions);

    // Assign students to electives based on combinations
    vector<vector<Student>> assignToElectives(int numElectives);

    // Helper methods
    Student* getStudent(const string& studentId);
    vector<Student> getAllStudents();

    // Get total number of possible group combinations
    int getNumberOfPossibleGroups(int n, int r);
};

#endif // STUDENT_GROUPER_H