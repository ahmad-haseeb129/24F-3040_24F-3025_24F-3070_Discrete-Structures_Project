#ifndef PREREQUISITE_VERIFIER_H
#define PREREQUISITE_VERIFIER_H

#include "DataStructures.h"
#include <vector>
#include <string>

class PrerequisiteVerifier 
{
private:
    vector<Course> courses;

public:
    void addCourse(const Course& course);
    // Basic induction to verify direct prerequisites
    bool verifyDirectPrerequisites(const string& courseId, const vector<string>& completedCourses);
    // Strong induction to verify all prerequisites in the chain
    bool verifyAllPrerequisites(const string& courseId, const vector<string>& completedCourses);
    // Helper method to get all prerequisites (direct and indirect)
    vector<string> getAllPrerequisites(const string& courseId);
};

#endif // PREREQUISITE_VERIFIER_H