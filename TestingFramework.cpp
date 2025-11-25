#include "TestingFramework.h"
#include <iostream>

TestingFramework::TestingFramework() : passedTests(0), failedTests(0) {
    setupTestData();
}

void TestingFramework::setupTestData() {
    // Create test courses
    testCourses.push_back(Course("CS101", "Intro to CS", 3));
    testCourses.push_back(Course("CS201", "Data Structures", 4));
    testCourses.push_back(Course("CS301", "Algorithms", 4));
    testCourses.push_back(Course("MATH101", "Calculus I", 3));

    // Add prerequisites
    testCourses[1].prerequisites.push_back("CS101");  // CS201 requires CS101
    testCourses[2].prerequisites.push_back("CS201");  // CS301 requires CS201

    // Create test students
    testStudents.push_back(Student("S001", "John Smith"));
    testStudents.push_back(Student("S002", "Jane Doe"));
    testStudents.push_back(Student("S003", "Bob Johnson"));

    // Add completed and current courses
    testStudents[0].completedCourses.push_back("CS101");
    testStudents[0].currentCourses.push_back("CS201");

    testStudents[1].completedCourses.push_back("CS101");
    testStudents[1].completedCourses.push_back("CS201");
    testStudents[1].currentCourses.push_back("CS301");

    testStudents[2].currentCourses.push_back("CS101");
    testStudents[2].currentCourses.push_back("MATH101");

    // Create test faculty
    testFaculty.push_back(Faculty("F001", "Dr. Smith"));
    testFaculty.push_back(Faculty("F002", "Dr. Johnson"));

    testFaculty[0].assignedCourses.push_back("CS101");
    testFaculty[0].assignedCourses.push_back("CS301");
    testFaculty[1].assignedCourses.push_back("CS201");
    testFaculty[1].assignedCourses.push_back("MATH101");

    // Create test rooms
    testRooms.push_back(Room("R001", 30));
    testRooms.push_back(Room("R002", 50));
    testRooms.push_back(Room("R003", 100));
}

void TestingFramework::addTestResult(const string& testName, bool passed, const string& message) {
    if (passed) {
        passedTests++;
        testResults.push_back(testName + ": PASSED" + (message.empty() ? "" : " - " + message));
    }
    else {
        failedTests++;
        testResults.push_back(testName + ": FAILED" + (message.empty() ? "" : " - " + message));
    }
}

void TestingFramework::runAllTests() 
{
    cout << "Running all tests...\n";

    testCourseScheduler();
    testStudentGrouper();
    testPrerequisiteVerifier();
    testLogicEngine();
    testSetOperator();
    testRelationsManager();
    testFunctionMapper();
    testProofVerifier();
    testConsistencyChecker();

    printTestResults();
}

void TestingFramework::testCourseScheduler() {
    cout << "Testing CourseScheduler...\n";

    CourseScheduler scheduler;

    // Add test courses
    for (const Course& course : testCourses) {
        scheduler.addCourse(course);
    }

    // Test isPrerequisite
    bool prereqTest1 = scheduler.isPrerequisite("CS201", "CS101");
    bool prereqTest2 = scheduler.isPrerequisite("CS101", "CS201");

    addTestResult("CourseScheduler.isPrerequisite - Direct", prereqTest1, "CS101 is a prerequisite for CS201");
    addTestResult("CourseScheduler.isPrerequisite - Reverse", !prereqTest2, "CS201 is not a prerequisite for CS101");

    // Test generateValidSequences
    auto sequences = scheduler.getAllValidSequences();
    bool hasSequences = !sequences.empty();

    addTestResult("CourseScheduler.getAllValidSequences", hasSequences,
        "Found " + to_string(sequences.size()) + " valid sequences");

    if (hasSequences) {
        // Check that the first sequence respects prerequisites
        bool validSequence = true;
        vector<string> completedCourses;

        for (const string& courseId : sequences[0]) {
            // Find the course
            Course* course = scheduler.getCourse(courseId);
            if (course) {
                // Check if all prerequisites are in completedCourses
                for (const string& prereq : course->prerequisites) {
                    if (find(completedCourses.begin(), completedCourses.end(), prereq) == completedCourses.end()) {
                        validSequence = false;
                        break;
                    }
                }
            }
            completedCourses.push_back(courseId);
        }

        addTestResult("CourseScheduler.sequenceValidity", validSequence, "Sequence respects prerequisites");
    }
}

void TestingFramework::testStudentGrouper() {
    cout << "Testing StudentGrouper...\n";

    StudentGrouper grouper;

    // Add test students
    for (const Student& student : testStudents) {
        grouper.addStudent(student);
    }

    // Test createProjectGroups
    auto groups = grouper.createProjectGroups(2);
    bool hasGroups = !groups.empty();

    addTestResult("StudentGrouper.createProjectGroups", hasGroups,
        "Created " + to_string(groups.size()) + " groups");

    // Test assignToLabSessions
    auto labSessions = grouper.assignToLabSessions(2);
    bool hasLabs = labSessions.size() == 2;

    addTestResult("StudentGrouper.assignToLabSessions", hasLabs, "Created 2 lab sessions");
}

void TestingFramework::testPrerequisiteVerifier() {
    cout << "Testing PrerequisiteVerifier...\n";

    PrerequisiteVerifier verifier;

    // Add test courses
    for (const Course& course : testCourses) {
        verifier.addCourse(course);
    }

    // Test verifyDirectPrerequisites
    bool canTake1 = verifier.verifyDirectPrerequisites("CS201", { "CS101" });
    bool canTake2 = verifier.verifyDirectPrerequisites("CS201", {});

    addTestResult("PrerequisiteVerifier.verifyDirectPrerequisites - With Prereq", canTake1,
        "Can take CS201 with CS101 completed");
    addTestResult("PrerequisiteVerifier.verifyDirectPrerequisites - Without Prereq", !canTake2,
        "Cannot take CS201 without CS101");

    // Test verifyAllPrerequisites (strong induction)
    bool canTake3 = verifier.verifyAllPrerequisites("CS301", { "CS101", "CS201" });
    bool canTake4 = verifier.verifyAllPrerequisites("CS301", { "CS201" });

    addTestResult("PrerequisiteVerifier.verifyAllPrerequisites - Complete Chain", canTake3,
        "Can take CS301 with all prerequisites");
    addTestResult("PrerequisiteVerifier.verifyAllPrerequisites - Incomplete Chain", !canTake4,
        "Cannot take CS301 with incomplete prerequisite chain");
}

void TestingFramework::testLogicEngine() {
    cout << "Testing LogicEngine...\n";

    LogicEngine engine;

    // Add test rules
    engine.addRule("Professor F001 teaches CS101", "Lab must be R001");
    engine.addRule("Student S001 takes CS201", "Student S001 must have taken CS101");

    // Test evaluateRule
    bool rule1 = engine.evaluateRule("Professor F001 teaches CS101");
    bool rule2 = engine.evaluateRule("Some other rule");

    addTestResult("LogicEngine.evaluateRule - Existing Rule", rule1, "Rule exists");
    addTestResult("LogicEngine.evaluateRule - Nonexistent Rule", !rule2, "Rule does not exist");

    // Test verifyAllocation
    bool validAllocation = engine.verifyAllocation("F001", "CS101", "R001");
    bool invalidAllocation = engine.verifyAllocation("F001", "CS101", "R002");

    addTestResult("LogicEngine.verifyAllocation - Valid", validAllocation, "Allocation is valid");
    addTestResult("LogicEngine.verifyAllocation - Invalid", !invalidAllocation, "Allocation is invalid");
}

void TestingFramework::testSetOperator() {
    cout << "Testing SetOperator...\n";

    SetOperator setOperator;

    // Add test data
    for (const Student& student : testStudents) {
        setOperator.addStudent(student);
    }
    for (const Course& course : testCourses) {
        setOperator.addCourse(course);
    }

    // Test findStudentsInBothCourses
    auto studentsInBoth = setOperator.findStudentsInBothCourses("CS101", "MATH101");
    bool hasStudentsInBoth = !studentsInBoth.empty();

    addTestResult("SetOperator.findStudentsInBothCourses", hasStudentsInBoth,
        "Found " + to_string(studentsInBoth.size()) + " students in both courses");

    // Test isSubset
    bool isSubset1 = setOperator.isSubset({ "CS101" }, { "CS101", "CS201" });
    bool isSubset2 = setOperator.isSubset({ "CS301" }, { "CS101", "CS201" });

    addTestResult("SetOperator.isSubset - Valid", isSubset1, "CS101 is a subset of {CS101, CS201}");
    addTestResult("SetOperator.isSubset - Invalid", !isSubset2, "CS301 is not a subset of {CS101, CS201}");

    // Test getCoursesWithoutPrerequisites
    auto noPrereqCourses = setOperator.getCoursesWithoutPrerequisites();
    bool hasNoPrereqCourses = !noPrereqCourses.empty();

    addTestResult("SetOperator.getCoursesWithoutPrerequisites", hasNoPrereqCourses,
        "Found " + to_string(noPrereqCourses.size()) + " courses without prerequisites");
}

void TestingFramework::testRelationsManager() {
    cout << "Testing RelationsManager...\n";

    RelationsManager relManager;

    // Add test relations
    relManager.addRelation("S001", "CS101", "student-course");
    relManager.addRelation("S001", "CS201", "student-course");
    relManager.addRelation("S002", "CS201", "student-course");
    relManager.addRelation("S002", "CS301", "student-course");

    // Add reflexive relations for testing
    relManager.addRelation("S001", "S001", "student-student");
    relManager.addRelation("S002", "S002", "student-student");

    // Add symmetric relations for testing
    relManager.addRelation("S001", "S002", "friend");
    relManager.addRelation("S002", "S001", "friend");

    // Add transitive relations for testing
    relManager.addRelation("CS101", "CS201", "prereq");
    relManager.addRelation("CS201", "CS301", "prereq");
    relManager.addRelation("CS101", "CS301", "prereq");

    // Test isReflexive
    bool isReflexive1 = relManager.isReflexive("student-student");
    bool isReflexive2 = relManager.isReflexive("student-course");

    addTestResult("RelationsManager.isReflexive - Reflexive", isReflexive1, "student-student is reflexive");
    addTestResult("RelationsManager.isReflexive - Non-reflexive", !isReflexive2, "student-course is not reflexive");

    // Test isSymmetric
    bool isSymmetric1 = relManager.isSymmetric("friend");
    bool isSymmetric2 = relManager.isSymmetric("prereq");

    addTestResult("RelationsManager.isSymmetric - Symmetric", isSymmetric1, "friend is symmetric");
    addTestResult("RelationsManager.isSymmetric - Non-symmetric", !isSymmetric2, "prereq is not symmetric");

    // Test isTransitive
    bool isTransitive1 = relManager.isTransitive("prereq");
    bool isTransitive2 = relManager.isTransitive("student-course");

    addTestResult("RelationsManager.isTransitive - Transitive", isTransitive1, "prereq is transitive");
    addTestResult("RelationsManager.isTransitive - Non-transitive", !isTransitive2, "student-course is not transitive");

    // Test isEquivalenceRelation
    // Create a test equivalence relation
    relManager.addRelation("A", "A", "equiv");
    relManager.addRelation("B", "B", "equiv");
    relManager.addRelation("C", "C", "equiv");
    relManager.addRelation("A", "B", "equiv");
    relManager.addRelation("B", "A", "equiv");
    relManager.addRelation("B", "C", "equiv");
    relManager.addRelation("C", "B", "equiv");
    relManager.addRelation("A", "C", "equiv");
    relManager.addRelation("C", "A", "equiv");

    bool isEquiv1 = relManager.isEquivalenceRelation("equiv");
    bool isEquiv2 = relManager.isEquivalenceRelation("prereq");

    addTestResult("RelationsManager.isEquivalenceRelation - Equivalence", isEquiv1, "equiv is an equivalence relation");
    addTestResult("RelationsManager.isEquivalenceRelation - Non-equivalence", !isEquiv2, "prereq is not an equivalence relation");
}

void TestingFramework::testFunctionMapper() {
    cout << "Testing FunctionMapper...\n";

    FunctionMapper mapper;

    // Add test mappings (course -> faculty)
    mapper.addMapping("CS101", "F001");
    mapper.addMapping("CS301", "F001");
    mapper.addMapping("CS201", "F002");
    mapper.addMapping("MATH101", "F002");

    // Test isInjective
    bool isInjective = mapper.isInjective();

    addTestResult("FunctionMapper.isInjective", !isInjective,
        "Multiple courses map to the same faculty, so not injective");

    // Test getDomain and getCodomain
    auto domain = mapper.getDomain();
    auto codomain = mapper.getCodomain();

    bool domainSize = domain.size() == 4;  // 4 courses
    bool codomainSize = codomain.size() == 2;  // 2 faculty members

    addTestResult("FunctionMapper.getDomain", domainSize, "Domain contains 4 courses");
    addTestResult("FunctionMapper.getCodomain", codomainSize, "Codomain contains 2 faculty members");

    // Test isSurjective
    // Create a test set with domain and codomain
    vector<string> testDomain = { "CS101", "CS201", "CS301", "MATH101" };
    vector<string> testCodomain = { "F001", "F002" };

    bool isSurjective = mapper.isSurjective(testDomain, testCodomain);

    addTestResult("FunctionMapper.isSurjective", isSurjective,
        "Every faculty in codomain is mapped to by at least one course");
}

void TestingFramework::testProofVerifier() {
    cout << "Testing ProofVerifier...\n";

    ProofVerifier verifier;
    verifier.setCourses(testCourses);
    verifier.setStudents(testStudents);

    // Test generatePrerequisiteProof
    string proof1 = verifier.generatePrerequisiteProof("S001", "CS201");
    string proof2 = verifier.generatePrerequisiteProof("S003", "CS201");

    bool validProof1 = !proof1.empty() && proof1.find("CAN") != string::npos;
    bool invalidProof2 = !proof2.empty() && proof2.find("CANNOT") != string::npos;

    addTestResult("ProofVerifier.generatePrerequisiteProof - Valid", validProof1,
        "Generated valid proof for student who can take course");
    addTestResult("ProofVerifier.generatePrerequisiteProof - Invalid", invalidProof2,
        "Generated invalid proof for student who cannot take course");

    // Test verifyCoursesConsistency
    bool isConsistent = verifier.verifyCoursesConsistency();

    addTestResult("ProofVerifier.verifyCoursesConsistency", isConsistent,
        "Course prerequisites are consistent (no circular dependencies)");
}

void TestingFramework::testConsistencyChecker() {
    cout << "Testing ConsistencyChecker...\n";

    ConsistencyChecker checker;

    // Set the test data
    checker.setStudents(testStudents);
    checker.setCourses(testCourses);
    checker.setFaculty(testFaculty);
    checker.setRooms(testRooms);

    // Test checkPrerequisiteViolations
    bool hasViolations = checker.checkPrerequisiteViolations();

    addTestResult("ConsistencyChecker.checkPrerequisiteViolations", hasViolations,
        "Found prerequisite violations (expected for our test data)");

    // Test getAllViolations
    auto violations = checker.getAllViolations();
    bool hasAllViolations = !violations.empty();

    addTestResult("ConsistencyChecker.getAllViolations", hasAllViolations,
        "Found " + to_string(violations.size()) + " violations");
}

void TestingFramework::printTestResults() {
    cout << "\n===== TEST RESULTS =====\n";
    cout << "Total tests: " << (passedTests + failedTests) << "\n";
    cout << "Passed: " << passedTests << "\n";
    cout << "Failed: " << failedTests << "\n\n";

    cout << "Detailed Results:\n";
    for (const string& result : testResults) {
        cout << result << "\n";
    }
}