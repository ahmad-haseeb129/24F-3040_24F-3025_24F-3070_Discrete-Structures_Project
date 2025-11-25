#ifndef CONSISTENCY_CHECKER_H
#define CONSISTENCY_CHECKER_H

#include "DataStructures.h"
#include <vector>
#include <string>

class ConsistencyChecker 
{
private:
    vector<Student> students;
    vector<Course> courses;
    vector<Faculty> faculty;
    vector<Room> rooms;

public:
    void setStudents(const vector<Student>& students);
    void setCourses(const vector<Course>& courses);
    void setFaculty(const vector<Faculty>& faculty);
    void setRooms(const vector<Room>& rooms);

    // Consistency checks
    bool checkPrerequisiteViolations();
    bool checkCourseOverlaps();
    bool checkStudentOverload(int maxCreditHours);
    bool checkRoomCapacityViolations();

    // Get all violations
    vector<string> getAllViolations();
};

#endif // CONSISTENCY_CHECKER_H