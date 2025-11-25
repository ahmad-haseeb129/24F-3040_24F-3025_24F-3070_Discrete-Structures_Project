#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include <string>
#include <vector>
#include <iostream>
using namespace std;
// Basic structures
struct Course 
{
    string id;
    string name;
    int creditHours;
    vector<string> prerequisites;

    Course(string id, string name, int creditHours): id(id), name(name), creditHours(creditHours) {}
};

struct Student 
{
    string id;
    string name;
    vector<string> completedCourses;
    vector<string> currentCourses;

    Student(string id, string name): id(id), name(name) {}
};

struct Faculty 
{
    string id;
    string name;
    vector<string> assignedCourses;

    Faculty(string id, string name): id(id), name(name) {}
};

struct Room 
{
    string id;
    int capacity;

    Room(string id, int capacity): id(id), capacity(capacity) {}
};

struct Rule 
{
    string condition;
    string consequence;

    Rule(string condition, string consequence): condition(condition), consequence(consequence) {}
};

struct Relation 
{
    string from;
    string to;
    string type; // "student-course", "faculty-course", "course-room"

    Relation(string from, string to, string type): from(from), to(to), type(type) {}
};

struct Mapping 
{
    string from;
    string to;

    Mapping(string from, string to) : from(from), to(to) {}
};

#endif // DATA_STRUCTURES_H