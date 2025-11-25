#include "ProofVerifier.h"

void ProofVerifier::setCourses(const vector<Course>& courses)
{
    this->courses = courses;
}

void ProofVerifier::setStudents(const vector<Student>& students)
{
    this->students = students;
}

string ProofVerifier::generatePrerequisiteProof(const string& studentId, const string& courseId)
{
    string proof = "";

    // Find the student
    const Student* student = nullptr;
    for (const Student& s : students)
    {
        if (s.id == studentId)
        {
            student = &s;  // no const_cast needed
            break;
        }
    }

    if (!student)
    {
        return "Error: Student not found";
    }

    // Find the course
    const Course* course = nullptr;
    for (const Course& c : courses)
    {
        if (c.id == courseId)
        {
            course = &c;
            break;
        }
    }

    if (!course)
    {
        return "Error: Course not found";
    }

    // Start building the proof
    proof += "Proof that student " + student->name + " can take " + course->name + ":\n\n";

    // Base case: If there are no prerequisites
    if (course->prerequisites.empty())
    {
        proof += "1. " + course->name + " has no prerequisites.\n";
        proof += "2. Therefore, " + student->name + " can take " + course->name + ".\n";
        return proof;
    }

    // Check prerequisites step by step
    int step = 1;
    for (const string& prereqId : course->prerequisites)
    {
        bool completed = false;

        // Check if the prerequisite is completed
        for (const string& completedCourse : student->completedCourses)
        {
            if (completedCourse == prereqId)
            {
                completed = true;
                break;
            }
        }

        // Find prerequisite course name
        string prereqName = prereqId;
        for (const Course& c : courses)
        {
            if (c.id == prereqId)
            {
                prereqName = c.name;
                break;
            }
        }

        if (completed)
        {
            proof += to_string(step++) + ". " + student->name + " has completed " + prereqName + ".\n";
        }
        else
        {
            proof += to_string(step++) + ". " + student->name + " has NOT completed " + prereqName + ".\n";
            proof += to_string(step) + ". Therefore, " + student->name + " CANNOT take " + course->name + ".\n";
            return proof;
        }
    }

    // If all prerequisites are satisfied
    proof += to_string(step) + ". All prerequisites are satisfied.\n";
    proof += to_string(step + 1) + ". Therefore, " + student->name + " CAN take " + course->name + ".\n";

    return proof;
}

string ProofVerifier::generateCourseChainProof(const vector<string>& courseSequence) 
{
    string proof = "Proof that the course sequence is valid:\n\n";

    if (courseSequence.empty()) 
    {
        proof += "1. The sequence is empty, which is trivially valid.\n";
        return proof;
    }

    // Check each course in the sequence
    int step = 1;
    for (size_t i = 0; i < courseSequence.size(); i++) 
    {
        string courseId = courseSequence[i];

        // Find the course
        const Course* course = nullptr;
        for (const Course& c : courses) 
        {
            if (c.id == courseId) 
            {
                course = &c;
                break;
            }
        }

        if (!course) {
            proof += to_string(step++) + ". Course " + courseId + " not found in the system.\n";
            proof += to_string(step) + ". Therefore, the sequence is invalid.\n";
            return proof;
        }

        // Check prerequisites
        for (const string& prereqId : course->prerequisites) 
        {
            bool foundPrereq = false;

            // Check if prerequisite appears earlier in the sequence
            for (size_t j = 0; j < i; j++) 
            {
                if (courseSequence[j] == prereqId) 
                {
                    foundPrereq = true;
                    break;
                }
            }

            if (!foundPrereq) 
            {
                proof += to_string(step++) + ". Course " + course->name + " requires prerequisite "
                    + prereqId + " which does not appear earlier in the sequence.\n";
                proof += to_string(step) + ". Therefore, the sequence is invalid.\n";
                return proof;
            }

            proof += to_string(step++) + ". Prerequisite " + prereqId + " for course "
                + course->name + " appears earlier in the sequence.\n";
        }

        proof += to_string(step++) + ". Course " + course->name + " can be taken at position "
            + to_string(i + 1) + " in the sequence.\n";
    }

    proof += to_string(step) + ". All courses in the sequence satisfy their prerequisites.\n";
    proof += to_string(step + 1) + ". Therefore, the course sequence is valid.\n";

    return proof;
}

string ProofVerifier::generateLogicRuleProof(const string& rule) 
{
    string proof = "Proof for rule: " + rule + "\n\n";
    proof += "1. Assume " + rule + " is true.\n";
    proof += "2. By the rules of propositional logic, this implies... (proof steps)\n";
    proof += "3. Therefore, the rule is valid.\n";
    return proof;
}

bool ProofVerifier::verifyCoursesConsistency() 
{
    for (const Course& course : courses) 
    {
        vector<string> visited;
        vector<string> stack;

        stack.push_back(course.id);

        while (!stack.empty()) 
        {
            string current = stack.back();
            stack.pop_back();
            visited.push_back(current);

            // Find the course object
            for (const Course& c : courses) 
            {
                if (c.id == current) 
                {
                    for (const string& prereq : c.prerequisites) 
                    {
                        if (prereq == course.id) return false; // cycle

                        if (find(visited.begin(), visited.end(), prereq) == visited.end()) 
                        {
                            stack.push_back(prereq);
                        }
                    }
                    break;
                }
            }
        }
    }

    return true;
}