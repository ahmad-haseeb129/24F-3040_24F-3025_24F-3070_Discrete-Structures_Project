#ifndef COURSE_SCHEDULER_H
#define COURSE_SCHEDULER_H

#include "DataStructures.h"
#include <vector>
#include <string>

class CourseScheduler 
{
private:
    vector<Course> courses;
    vector<vector<string>> validSequences;

public:
    void addCourse(const Course& course);
    bool isPrerequisite(const string& course, const string& prereq);
    void generateValidSequences(const vector<string>& remainingCourses, vector<string>& currentSequence);
    vector<vector<string>> getAllValidSequences();
    Course* getCourse(const string& courseId);
    vector<Course> getAllCourses();
};

#endif // COURSE_SCHEDULER_H