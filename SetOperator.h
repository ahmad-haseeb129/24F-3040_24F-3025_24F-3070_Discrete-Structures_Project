#ifndef SET_OPERATOR_H
#define SET_OPERATOR_H

#include "DataStructures.h"
#include <vector>
#include <string>

class SetOperator 
{
private:
    vector<Student> students;
    vector<Course> courses;
    vector<Faculty> faculty;
    vector<Room> rooms;

public:
    void addStudent(const Student& student);
    void addCourse(const Course& course);
    void addFaculty(const Faculty& faculty);
    void addRoom(const Room& room);

    // Set operations
    vector<Student> findStudentsInBothCourses(const string& course1, const string& course2);
    vector<Student> findStudentsInEitherCourse(const string& course1, const string& course2);
    vector<Student> findStudentsNotInCourse(const string& courseId);
    vector<Course> getCoursesWithoutPrerequisites();

    // Subset operations
    bool isSubset(const vector<string>& set1, const vector<string>& set2);
    vector<vector<string>> getPowerSet(const vector<string>& set);
};

#endif // SET_OPERATOR_H