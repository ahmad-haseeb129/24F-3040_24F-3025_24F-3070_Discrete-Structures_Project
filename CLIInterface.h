#ifndef CLI_INTERFACE_H
#define CLI_INTERFACE_H

#include "DataStructures.h"
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

class CLIInterface 
{
private:
    // Data
    vector<Student> students;
    vector<Course> courses;
    vector<Faculty> faculty;
    vector<Room> rooms;

    // Modules
    CourseScheduler scheduler;
    StudentGrouper grouper;
    PrerequisiteVerifier prereqVerifier;
    LogicEngine logicEngine;
    SetOperator setOperator;
    RelationsManager relationsManager;
    FunctionMapper functionMapper;
    ProofVerifier proofVerifier;
    ConsistencyChecker consistencyChecker;

    // Menu handlers
    void showMainMenu();
    void handleAddStudent();
    void handleAddCourse();
    void handleAddFaculty();
    void handleAddRoom();
    void handleAddRule();
    void handleVerifyPrerequisites();
    void handleGenerateValidSequences();
    void handleCreateGroups();
    void handleSetOperations();
    void handleCheckRelations();
    void handleMapFunctions();
    void handleGenerateProof();
    void handleCheckConsistency();

    // Helper function to display results
    void displayResults(const string& title, const vector<string>& results);

public:
    // Run the CLI
    void run();
};

#endif // CLI_INTERFACE_H