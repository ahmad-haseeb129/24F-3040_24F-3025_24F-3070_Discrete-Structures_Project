#ifndef TESTING_FRAMEWORK_H
#define TESTING_FRAMEWORK_H

#include "CourseScheduler.h"
#include "StudentGrouper.h"
#include "PrerequisiteVerifier.h"
#include "LogicEngine.h"
#include "SetOperator.h"
#include "RelationsManager.h"
#include "FunctionMapper.h"
#include "ProofVerifier.h"
#include "ConsistencyChecker.h"
#include <vector>
#include <string>

class TestingFramework 
{
private:
    // Test data
    vector<Student> testStudents;
    vector<Course> testCourses;
    vector<Faculty> testFaculty;
    vector<Room> testRooms;

    // Test results
    vector<string> testResults;
    int passedTests;
    int failedTests;

    // Helper methods
    void setupTestData();
    void addTestResult(const string& testName, bool passed, const string& message = "");

public:
    TestingFramework();

    // Run all tests
    void runAllTests();

    // Individual test methods
    void testCourseScheduler();
    void testStudentGrouper();
    void testPrerequisiteVerifier();
    void testLogicEngine();
    void testSetOperator();
    void testRelationsManager();
    void testFunctionMapper();
    void testProofVerifier();
    void testConsistencyChecker();

    // Print test results
    void printTestResults();
};

#endif // TESTING_FRAMEWORK_H