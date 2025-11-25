#ifndef PROOF_VERIFIER_H
#define PROOF_VERIFIER_H

#include "DataStructures.h"
#include <vector>
#include <string>

class ProofVerifier 
{
private:
    vector<Course> courses;
    vector<Student> students;

public:
    void setCourses(const vector<Course>& courses);
    void setStudents(const vector<Student>& students);

    // Generate formal proofs
    string generatePrerequisiteProof(const string& studentId, const string& courseId);
    string generateCourseChainProof(const vector<string>& courseSequence);
    string generateLogicRuleProof(const string& rule);

    // Verify consistency of course structure
    bool verifyCoursesConsistency();
};

#endif // PROOF_VERIFIER_H