#include "CLIInterface.h"
#include <iostream>

void CLIInterface::run() 
{
    bool running = true;

    cout << "===== Welcome to UNIDISC ENGINE - FAST University System =====\n";

    while (running) 
    {
        showMainMenu();

        int choice;
        cin >> choice;

        switch (choice) 
        {
        case 1: handleAddStudent(); break;
        case 2: handleAddCourse(); break;
        case 3: handleAddFaculty(); break;
        case 4: handleAddRoom(); break;
        case 5: handleAddRule(); break;
        case 6: handleVerifyPrerequisites(); break;
        case 7: handleGenerateValidSequences(); break;
        case 8: handleCreateGroups(); break;
        case 9: handleSetOperations(); break;
        case 10: handleCheckRelations(); break;
        case 11: handleMapFunctions(); break;
        case 12: handleGenerateProof(); break;
        case 13: handleCheckConsistency(); break;
        case 0: running = false; break;
        default: cout << "Invalid choice. Please try again.\n";
        }
    }

    cout << "Thank you for using UNIDISC ENGINE!\n";
}

void CLIInterface::showMainMenu() 
{
    cout << "\n===== UNIDISC ENGINE - MAIN MENU =====\n";
    cout << "1. Add Student\n";
    cout << "2. Add Course\n";
    cout << "3. Add Faculty\n";
    cout << "4. Add Room\n";
    cout << "5. Add Rule\n";
    cout << "6. Verify Prerequisites\n";
    cout << "7. Generate Valid Course Sequences\n";
    cout << "8. Create Student Groups\n";
    cout << "9. Set Operations\n";
    cout << "10. Check Relations\n";
    cout << "11. Map Functions\n";
    cout << "12. Generate Proof\n";
    cout << "13. Check System Consistency\n";
    cout << "0. Exit\n";
    cout << "Enter your choice: ";
}

void CLIInterface::handleAddStudent()
{
    // Check if there are any courses in the system
    if (courses.empty()) 
    {
        cout << "Error: No courses exist in the system. Please add courses first.\n";
        return;
    }

    string id, name;
    cout << "Enter student ID: ";
    cin >> id;
	cin.ignore();

    cout << "Enter student name: ";
    getline(cin, name);

    Student student(id, name);

    // Show available courses
    cout << "\nAvailable courses in the system:\n";
    for (const auto& course : courses) {
        cout << "- " << course.id << ": " << course.name << endl;
    }

    int totalCourses = courses.size();
    int completedCount, currentCount;

    cout << "\nEnter number of completed courses (max " << totalCourses << "): ";
    cin >> completedCount;
    while (cin.fail())
    {
        cin.clear(); // clear the fail state
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
        cout << "Invalid input. Please enter a number: ";
        cin >> completedCount;
    }

    // Validate completed course count
    if (completedCount > totalCourses) 
    {
        cout << "Error: Cannot add " << completedCount << " completed courses when only "
            << totalCourses << " courses exist.\n";
        return;
    }

    int actualCompletedCount = 0;
    while (actualCompletedCount < completedCount)
    {
        string courseId;
        cout << "Enter completed course ID " << (actualCompletedCount + 1) << " (or 'exit' to cancel): ";
        cin >> courseId;

        if (courseId == "exit") 
        {
            cout << "Student addition canceled.\n";
            return;
        }

        // Check if course exists
        bool courseExists = false;
        for (const auto& course : courses) 
        {
            if (course.id == courseId) 
            {
                courseExists = true;
                break;
            }
        }

        if (!courseExists) 
        {
            cout << "Error: Course " << courseId << " does not exist. Please enter a valid course ID.\n";
            continue;
        }

        // Check for duplicates
        bool isDuplicate = false;
        for (const auto& cid : student.completedCourses) 
        {
            if (cid == courseId) 
            {
                isDuplicate = true;
                break;
            }
        }

        if (isDuplicate) 
        {
            cout << "Error: Course " << courseId << " is already in your completed courses list.\n";
            continue;
        }

        // Valid course, add it
        student.completedCourses.push_back(courseId);
        actualCompletedCount++;
    }

    // Remaining available courses
    int remainingCourses = totalCourses - actualCompletedCount;

    cout << "\nEnter number of current courses (max " << remainingCourses << "): ";
    cin >> currentCount;

    // Validate current course count
    if (currentCount > remainingCourses) 
    {
        cout << "Warning: You requested " << currentCount << " current courses but only "
            << remainingCourses << " unused courses remain.\n";
        cout << "Adjusting to " << remainingCourses << " current courses.\n";
        currentCount = remainingCourses;
    }

    int actualCurrentCount = 0;
    while (actualCurrentCount < currentCount)
    {
        string courseId;
        cout << "Enter current course ID " << (actualCurrentCount + 1) << " (or 'exit' to cancel): ";
        cin >> courseId;

        if (courseId == "exit") 
        {
            cout << "Stopping current course entry. Student will be added with "
                << actualCurrentCount << " current courses.\n";
            break;
        }

        // Check if course exists
        bool courseExists = false;
        for (const auto& course : courses) 
        {
            if (course.id == courseId) 
            {
                courseExists = true;
                break;
            }
        }

        if (!courseExists) {
            cout << "Error: Course " << courseId << " does not exist. Please enter a valid course ID.\n";
            continue;
        }

        // Check if course is already completed
        bool isCompleted = false;
        for (const auto& cid : student.completedCourses) {
            if (cid == courseId) {
                isCompleted = true;
                break;
            }
        }

        if (isCompleted) 
        {
            cout << "Error: Course " << courseId << " is already in your completed courses list.\n";
            continue;
        }

        // Check for duplicates
        bool isDuplicate = false;
        for (const auto& cid : student.currentCourses) 
        {
            if (cid == courseId) 
            {
                isDuplicate = true;
                break;
            }
        }

        if (isDuplicate) 
        {
            cout << "Error: Course " << courseId << " is already in your current courses list.\n";
            continue;
        }

        // Valid course, add it
        student.currentCourses.push_back(courseId);
        actualCurrentCount++;
    }

    students.push_back(student);
    grouper.addStudent(student);
    setOperator.addStudent(student);

    cout << "Student added successfully!\n";
}

void CLIInterface::handleAddCourse() 
{
    string id, name;
    int creditHours;

    cout << "Enter course ID: ";
    cin >> id;
    cin.ignore();
    cout << "Enter course name: ";
    getline(cin, name);

    cout << "Enter credit hours: ";
    cin >> creditHours;
    while (cin.fail())
    {
        cin.clear(); // clear the fail state
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
        cout << "Invalid input. Please enter a number: ";
        cin >> creditHours;
    }
    for (const auto& course : courses) 
    {
        if (course.id == id) 
        {
            cout << "Error: A course with ID " << id << " already exists.\n";
            return;
        }
    }

    cin.ignore();
    Course course(id, name, creditHours);

    int prereqCount;
    cout << "Enter number of prerequisites: ";
    cin >> prereqCount;
    while (cin.fail())
    {
        cin.clear(); // clear the fail state
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
        cout << "Invalid input. Please enter a number: ";
        cin >> prereqCount;
    }
    for (int i = 0; i < prereqCount; i++) 
    {
        string prereqId;
        cout << "Enter prerequisite course ID " << (i + 1) << ": ";
        cin >> prereqId;

        // Check if prerequisite course exists
        bool prereqExists = false;
        for (const auto& c : courses) 
        {
            if (c.id == prereqId) 
            {
                prereqExists = true;
                break;
            }
        }

        if (!prereqExists) 
        {
            cout << "Error: Prerequisite course " << prereqId << " does not exist.\n";
            i--;
            continue;
        }

        // Check if prereq is the same as the course itself
        if (prereqId == id) 
        {
            cout << "Error: A course cannot be a prerequisite for itself.\n";
            i--;
            continue;
        }

        // Check for duplicate prerequisites
        bool isDuplicate = false;
        for (const auto& pid : course.prerequisites) 
        {
            if (pid == prereqId) 
            {
                isDuplicate = true;
                break;
            }
        }

        if (isDuplicate) 
        {
            cout << "Error: Course " << prereqId << " is already a prerequisite.\n";
            i--;
            continue;
        }

        course.prerequisites.push_back(prereqId);
    }

    courses.push_back(course);
    scheduler.addCourse(course);
    prereqVerifier.addCourse(course);
    setOperator.addCourse(course);
	cout << "Course added successfully!\n";
}

void CLIInterface::handleAddFaculty() 
{
    // Check if there are any courses in the system
    if (courses.empty()) 
    {
        cout << "Error: No courses exist in the system. Please add courses first.\n";
        return;
    }

    string id, name;
    cout << "Enter faculty ID: ";
    cin >> id;
	cin.ignore();

    // Check for duplicate faculty IDs
    for (const auto& f : faculty) 
    {
        if (f.id == id) 
        {
            cout << "Error: A faculty member with ID " << id << " already exists.\n";
            return;
        }
    }

    cin.ignore();

    cout << "Enter faculty name: ";
    getline(cin, name);

    Faculty newFaculty(id, name);
    faculty.push_back(newFaculty);

    // Display available courses
    cout << "\nAvailable courses in the system:\n";
    for (const auto& course : courses) 
    {
        cout << "- " << course.id << ": " << course.name << endl;
    }

    int totalCourses = courses.size();
    int courseCount;
    cout << "\nEnter number of assigned courses (max " << totalCourses << "): ";
    cin >> courseCount;
    while (cin.fail())
    {
        cin.clear(); // clear the fail state
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
        cout << "Invalid input. Please enter a number: ";
        cin >> courseCount;
    }

    // Validate course count
    if (courseCount > totalCourses) 
    {
        cout << "Error: Cannot assign " << courseCount << " courses when only "
            << totalCourses << " courses exist in the system.\n";
        cout << "Adjusting to " << totalCourses << " courses.\n";
        courseCount = totalCourses;
    }

    int actualAssigned = 0;
    while (actualAssigned < courseCount) 
    {
        string courseId;
        cout << "Enter assigned course ID " << (actualAssigned + 1) << " (or 'exit' to finish): ";
        cin >> courseId;

        if (courseId == "exit") 
        {
            cout << "Stopping course assignment. Faculty will be added with "
                << actualAssigned << " assigned courses.\n";
            break;
        }

        // Check if course exists
        bool courseExists = false;
        for (const auto& course : courses) 
        {
            if (course.id == courseId) 
            {
                courseExists = true;
                break;
            }
        }

        if (!courseExists) 
        {
            cout << "Error: Course " << courseId << " does not exist. Please enter a valid course ID.\n";
            continue;
        }

        // Check for duplicates in assigned courses
        bool isDuplicate = false;
        for (const auto& cid : faculty.back().assignedCourses) 
        {
            if (cid == courseId) 
            {
                isDuplicate = true;
                break;
            }
        }

        if (isDuplicate) 
        {
            cout << "Error: Course " << courseId << " is already assigned to this faculty member.\n";
            continue;
        }

        // Valid course, add it
        faculty.back().assignedCourses.push_back(courseId);
        actualAssigned++;
    }
    setOperator.addFaculty(newFaculty);
    cout << "Faculty added successfully with " << actualAssigned << " assigned courses!\n";
}

void CLIInterface::handleAddRoom() 
{
    string id;
    int capacity;

    cout << "Enter room ID: ";
    cin >> id;
	cin.ignore();

    // Check for duplicate room IDs
    for (const auto& room : rooms) {
        if (room.id == id) {
            cout << "Error: A room with ID " << id << " already exists.\n";
            return;
        }
    }

    cout << "Enter room capacity: ";
    cin >> capacity;
    while (cin.fail())
    {
        cin.clear(); // clear the fail state
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
        cout << "Invalid input. Please enter a number: ";
        cin >> capacity;
    }

    Room room(id, capacity);
    rooms.push_back(room);
    setOperator.addRoom(room);

    cout << "Room added successfully!\n";
}

void CLIInterface::handleAddRule() 
{
    string condition, consequence;

    cin.ignore(); // Clear newline
    cout << "Enter rule condition (e.g., 'Professor X teaches CS101'): ";
    getline(cin, condition);

    cout << "Enter rule consequence (e.g., 'Lab must be Lab A'): ";
    getline(cin, consequence);

    logicEngine.addRule(condition, consequence);

    cout << "Rule added successfully!\n";
}

void CLIInterface::handleVerifyPrerequisites() 
{
    string studentId, courseId;

    cout << "Enter student ID: ";
    cin >> studentId;
    cout << "Enter course ID to verify: ";
    cin >> courseId;

    // Find student
    Student* student = nullptr;
    for (Student& s : students) 
    {
        if (s.id == studentId) 
        {
            student = &s;
            break;
        }
    }

    if (!student) 
    {
        cout << "Student not found!\n";
        return;
    }

    // Verify prerequisites using induction
    bool canTake = prereqVerifier.verifyAllPrerequisites(courseId, student->completedCourses);

    if (canTake) 
    {
        cout << "Student can take the course (all prerequisites satisfied).\n";
    }
    else 
    {
        cout << "Student cannot take the course - prerequisites not satisfied.\n";
    }
}

void CLIInterface::handleGenerateValidSequences() 
{
    cout << "Generating all valid course sequences...\n";

    auto sequences = scheduler.getAllValidSequences();

    cout << "Found " << sequences.size() << " valid sequences.\n";

    if (!sequences.empty()) 
    {
        cout << "First valid sequence:\n";
        int i = 1;
        for (const string& courseId : sequences[0]) 
        {
            // Find course name
            string courseName = courseId;
            for (const Course& course : courses) 
            {
                if (course.id == courseId) 
                {
                    courseName = course.name;
                    break;
                }
            }
            cout << i++ << ". " << courseId << " - " << courseName << "\n";
        }
    }
}

void CLIInterface::handleCreateGroups() 
{
    int groupSize;
    cout << "Enter group size: ";
    cin >> groupSize;
    while (cin.fail())
    {
        cin.clear(); // clear the fail state
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
        cout << "Invalid input. Please enter a number: ";
        cin >> groupSize;
    }
    if (groupSize <= 0) 
    {
        cout << "Error: Group size must be positive.\n";
        return;
    }

    if (groupSize > students.size()) {
        cout << "Error: Group size (" << groupSize << ") is larger than the number of students ("
            << students.size() << ").\n";
        return;
    }
    auto groups = grouper.createProjectGroups(groupSize);

    cout << "Created " << groups.size() << " groups:\n";

    for (size_t i = 0; i < groups.size(); i++) 
    {
        cout << "Group " << (i + 1) << ":\n";
        for (const Student& student : groups[i]) 
        {
            cout << "- " << student.id << ": " << student.name << "\n";
        }
        cout << "\n";
    }
}

void CLIInterface::handleSetOperations() 
{
    cout << "=== Set Operations ===\n";
    cout << "1. Find students in both courses\n";
    cout << "2. Find students in either course\n";
    cout << "3. Find students not in a course\n";
    cout << "4. Get courses without prerequisites\n";
    cout << "Enter your choice: ";

    int choice;
    cin >> choice;
    while (cin.fail())
    {
        cin.clear(); // clear the fail state
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
        cout << "Invalid input. Please enter a number: ";
        cin >> choice;
    }
    switch (choice) 
    {
    case 1: 
    {
        string course1, course2;
        cout << "Enter first course ID: ";
        cin >> course1;
        cout << "Enter second course ID: ";
        cin >> course2;

        auto result = setOperator.findStudentsInBothCourses(course1, course2);

        cout << "Students enrolled in both " << course1 << " and " << course2 << ":\n";
        for (const Student& student : result) 
        {
            cout << "- " << student.id << ": " << student.name << "\n";
        }
        break;
    }
    case 2: 
    {
        string course1, course2;
        cout << "Enter first course ID: ";
        cin >> course1;
        cout << "Enter second course ID: ";
        cin >> course2;

        auto result = setOperator.findStudentsInEitherCourse(course1, course2);

        cout << "Students enrolled in either " << course1 << " or " << course2 << ":\n";
        for (const Student& student : result) 
        {
            cout << "- " << student.id << ": " << student.name << "\n";
        }
        break;
    }
    case 3: 
    {
        string courseId;
        cout << "Enter course ID: ";
        cin >> courseId;

        auto result = setOperator.findStudentsNotInCourse(courseId);

        cout << "Students not enrolled in " << courseId << ":\n";
        for (const Student& student : result) 
        {
            cout << "- " << student.id << ": " << student.name << "\n";
        }
        break;
    }
    case 4: 
    {
        auto result = setOperator.getCoursesWithoutPrerequisites();

        cout << "Courses without prerequisites:\n";
        for (const Course& course : result) 
        {
            cout << "- " << course.id << ": " << course.name << "\n";
        }
        break;
    }
    default:
        cout << "Invalid choice.\n";
    }
}

void CLIInterface::handleCheckRelations() 
{
    cout << "=== Relations Operations ===\n";

    // First, add some relations if none exist
    if (relationsManager.getDomainElements("student-course").empty()) 
    {
        cout << "No relations found. Adding sample relations...\n";

        // Add student-course relations from our data
        for (const Student& student : students) 
        {
            for (const string& courseId : student.currentCourses) 
            {
                relationsManager.addRelation(student.id, courseId, "student-course");
            }
        }

        // Add faculty-course relations
        for (const Faculty& f : faculty) 
        {
            for (const string& courseId : f.assignedCourses) 
            {
                relationsManager.addRelation(f.id, courseId, "faculty-course");
            }
        }

        cout << "Sample relations added.\n";
    }

    cout << "1. Check if relation is reflexive\n";
    cout << "2. Check if relation is symmetric\n";
    cout << "3. Check if relation is transitive\n";
    cout << "4. Check if relation is an equivalence relation\n";
    cout << "5. Check if relation is a partial order\n";
    cout << "6. Detect conflicts\n";
    cout << "Enter your choice: ";

    int choice;
    cin >> choice;
    while (cin.fail())
    {
        cin.clear(); // clear the fail state
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
        cout << "Invalid input. Please enter a number: ";
        cin >> choice;
    }
    string relationType;
    if (choice >= 1 && choice <= 5) 
    {
        cout << "Enter relation type (student-course, faculty-course, course-room, course-prerequisite, faculty-room): ";
        cin >> relationType;
    }

    switch (choice) 
    {
    case 1: 
    {
        bool isReflexive = relationsManager.isReflexive(relationType);
        cout << "The relation " << relationType << " is " << (isReflexive ? "" : "not ")
            << "reflexive.\n";
        break;
    }
    case 2: 
    {
        bool isSymmetric = relationsManager.isSymmetric(relationType);
        cout << "The relation " << relationType << " is " << (isSymmetric ? "" : "not ")
            << "symmetric.\n";
        break;
    }
    case 3: 
    {
        bool isTransitive = relationsManager.isTransitive(relationType);
        cout << "The relation " << relationType << " is " << (isTransitive ? "" : "not ")
            << "transitive.\n";
        break;
    }
    case 4: 
    {
        bool isEquivalence = relationsManager.isEquivalenceRelation(relationType);
        cout << "The relation " << relationType << " is " << (isEquivalence ? "" : "not ")
            << "an equivalence relation.\n";
        break;
    }
    case 5: 
    {
        bool isPartialOrder = relationsManager.isPartialOrder(relationType);
        cout << "The relation " << relationType << " is " << (isPartialOrder ? "" : "not ")
            << "a partial order.\n";
        break;
    }
    case 6: 
    {
        bool hasConflicts = relationsManager.detectConflicts();
        cout << (hasConflicts ? "Conflicts detected in relations." : "No conflicts found in relations.") << "\n";
        break;
    }
    default:
        cout << "Invalid choice.\n";
    }
}

void CLIInterface::handleMapFunctions() 
{
    cout << "=== Function Mapping ===\n";

    // First, add some mappings if none exist
    if (functionMapper.getDomain().empty()) 
    {
        cout << "No mappings found. Adding sample mappings...\n";

        // Add course -> faculty mappings
        for (const Faculty& f : faculty) 
        {
            for (const string& courseId : f.assignedCourses) 
            {
                functionMapper.addMapping(courseId, f.id);
            }
        }

        cout << "Sample mappings added.\n";
    }

    cout << "1. Check if function is injective\n";
    cout << "2. Check if function is surjective\n";
    cout << "3. Check if function is bijective\n";
    cout << "4. Get inverse mapping\n";
    cout << "Enter your choice: ";

    int choice;
    cin >> choice;
    while (cin.fail())
    {
        cin.clear(); // clear the fail state
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
        cout << "Invalid input. Please enter a number: ";
        cin >> choice;
    }
    switch (choice) 
    {
    case 1: 
    {
        bool isInjective = functionMapper.isInjective();
        cout << "The function is " << (isInjective ? "" : "not ") << "injective.\n";
        break;
    }
    case 2: 
    {
        // For simplicity, use the current domain and range
        auto domain = functionMapper.getDomain();
        auto codomain = functionMapper.getCodomain();

        bool isSurjective = functionMapper.isSurjective(domain, codomain);
        cout << "The function is " << (isSurjective ? "" : "not ") << "surjective.\n";
        break;
    }
    case 3: 
    {
        // For simplicity, use the current domain and range
        auto domain = functionMapper.getDomain();
        auto codomain = functionMapper.getCodomain();

        bool isBijective = functionMapper.isBijective(domain, codomain);
        cout << "The function is " << (isBijective ? "" : "not ") << "bijective.\n";
        break;
    }
    case 4: 
    {
        auto inverseMapping = functionMapper.getInverseMapping();

        cout << "Inverse mapping:\n";
        for (const Mapping& mapping : inverseMapping) 
        {
            cout << mapping.from << " -> " << mapping.to << "\n";
        }
        break;
    }
    default:
        cout << "Invalid choice.\n";
    }
}

void CLIInterface::handleGenerateProof() 
{
    cout << "=== Proof Generation ===\n";
    cout << "1. Generate prerequisite proof\n";
    cout << "2. Generate course chain proof\n";
    cout << "3. Verify courses consistency\n";
    cout << "Enter your choice: ";

    int choice;
    cin >> choice;
    while (cin.fail())
    {
        cin.clear(); // clear the fail state
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
        cout << "Invalid input. Please enter a number: ";
        cin >> choice;
    }
    proofVerifier.setCourses(courses);
    proofVerifier.setStudents(students);

    switch (choice) 
    {
    case 1: 
    {
        string studentId, courseId;
        cout << "Enter student ID: ";
        cin >> studentId;
        cout << "Enter course ID: ";
        cin >> courseId;

        string proof = proofVerifier.generatePrerequisiteProof(studentId, courseId);
        cout << "\n=== Proof ===\n" << proof << "\n";
        break;
    }
    case 2: 
    {
        // First, generate a valid sequence
        auto sequences = scheduler.getAllValidSequences();

        if (sequences.empty()) 
        {
            cout << "No valid course sequences found. Add more courses first.\n";
            return;
        }

        string proof = proofVerifier.generateCourseChainProof(sequences[0]);
        cout << "\n=== Proof ===\n" << proof << "\n";
        break;
    }
    case 3: 
    {
        bool isConsistent = proofVerifier.verifyCoursesConsistency();
        cout << "Course system is " << (isConsistent ? "consistent" : "inconsistent")
            << " (no circular dependencies).\n";
        break;
    }
    default:
        cout << "Invalid choice.\n";
    }
}

void CLIInterface::handleCheckConsistency() 
{
    cout << "Checking system consistency...\n";

    consistencyChecker.setStudents(students);
    consistencyChecker.setCourses(courses);
    consistencyChecker.setFaculty(faculty);
    consistencyChecker.setRooms(rooms);

    auto violations = consistencyChecker.getAllViolations();

    if (violations.empty()) 
    {
        cout << "No violations found. System is consistent!\n";
    }
    else 
    {
        cout << "Found " << violations.size() << " violations:\n";
        for (const string& violation : violations) 
        {
            cout << "- " << violation << "\n";
        }
    }
}

void CLIInterface::displayResults(const string& title, const vector<string>& results) 
{
    cout << "\n=== " << title << " ===\n";
    for (const string& result : results) 
    {
        cout << result << "\n";
    }
}