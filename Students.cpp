#include <iostream>
#include <vector>
#include <string>
#include <random>

class Student {
public:
    Student(const std::string& name) : name(name), grades({}) {}

    void addGrade(int grade) {
        grades.push_back(grade);
    }

    bool isExcellentStudent() const {
        return !grades.empty() && std::all_of(grades.begin(), grades.end(), [](int grade) { return grade >= 4.5; });
    }

    const std::string& getName() const {
        return name;
    }

    const std::vector<int>& getGrades() const {
        return grades;
    }

private:
    std::string name;
    std::vector<int> grades;
};

class Teacher {
public:
    Teacher(const std::string& name, bool goodMood) : name(name), goodMood(goodMood) {}

    void giveGrade(Student& student) {
        std::random_device rd;
        std::mt19937 gen(rd());

        int baseGrade = student.isExcellentStudent() ? getExcellentGrade(gen) : getRegularGrade(gen);

        student.addGrade(baseGrade);
    }

    const std::string& getName() const {
        return name;
    }

private:
    std::string name;
    bool goodMood;

    int getExcellentGrade(std::mt19937& gen) const {
        return 5;
    }

    int getRegularGrade(std::mt19937& gen) const {
        std::uniform_int_distribution<> dis(goodMood ? 4 : 2, 5);
        return dis(gen);
    }
};

class StudentManager {
public:
    void addStudent(const std::string& name) {
        students.push_back(Student(name));
    }

    void addTeacher(const std::string& name, bool goodMood) {
        teachers.push_back(Teacher(name, goodMood));
    }

    void addGrade(const std::string& studentName, const std::string& teacherName) {
        auto studentIt = findStudent(studentName);
        auto teacherIt = findTeacher(teacherName);
        if (studentIt != students.end() && teacherIt != teachers.end()) {
            teacherIt->giveGrade(*studentIt);
        }
    }

    void printStudentGrades() const {
        std::cout << "Student Grades:\n";
        for (const Student& student : students) {
            std::cout << student.getName() << " (Grades: ";
            for (int grade : student.getGrades()) {
                std::cout << grade << " ";
            }
            std::cout << ")\n";
        }
    }

    void printExcellentStudents() const {
        std::cout << "Excellent Students:\n";
        for (const Student& student : students) {
            if (student.isExcellentStudent()) {
                std::cout << student.getName() << " (Grades: ";
                for (int grade : student.getGrades()) {
                    std::cout << grade << " ";
                }
                std::cout << ")\n";
            }
        }
    }

private:
    std::vector<Student> students;
    std::vector<Teacher> teachers;

    std::vector<Student>::iterator findStudent(const std::string& studentName) {
        return std::find_if(students.begin(), students.end(),
            [studentName](const Student& student) {
                return student.getName() == studentName;
            });
    }

    std::vector<Teacher>::iterator findTeacher(const std::string& teacherName) {
        return std::find_if(teachers.begin(), teachers.end(),
            [teacherName](const Teacher& teacher) {
                return teacher.getName() == teacherName;
            });
    }
};

int main() {
    StudentManager studentManager;

    // Добавляем студентов
    studentManager.addStudent("Alice");
    studentManager.addStudent("Bob");
    studentManager.addStudent("Charlie");
    studentManager.addStudent("David");
    studentManager.addStudent("Eva");
    studentManager.addStudent("Frank");
    studentManager.addStudent("Grace");
    studentManager.addStudent("Harry");
    studentManager.addStudent("Ivy");
    studentManager.addStudent("Jack");
    studentManager.addStudent("Kelly");
    studentManager.addStudent("Leo");
    studentManager.addStudent("Mia");
    studentManager.addStudent("Nick");
    studentManager.addStudent("Olivia");
    studentManager.addStudent("Paul");
    studentManager.addStudent("Quinn");
    studentManager.addStudent("Rachel");
    studentManager.addStudent("Sam");

    // Добавляем преподавателей
    studentManager.addTeacher("ProfessorSmith", true);  // Преподаватель в хорошем настроении
    studentManager.addTeacher("DrJohnson", false);      // Преподаватель в плохом настроении
    studentManager.addTeacher("MsDavis", true);         // Преподаватель в хорошем настроении

    // Выставляем оценки студентам
    for (int i = 0; i < 5; ++i) {
        studentManager.addGrade("Alice", "ProfessorSmith");
        studentManager.addGrade("Bob", "DrJohnson");
        studentManager.addGrade("Charlie", "ProfessorSmith");
        studentManager.addGrade("David", "MsDavis");
        studentManager.addGrade("Eva", "ProfessorSmith");
        studentManager.addGrade("Frank", "DrJohnson");
        studentManager.addGrade("Grace", "ProfessorSmith");
        studentManager.addGrade("Harry", "MsDavis");
        studentManager.addGrade("Ivy", "DrJohnson");
        studentManager.addGrade("Jack", "ProfessorSmith");
        studentManager.addGrade("Kelly", "MsDavis");
        studentManager.addGrade("Leo", "DrJohnson");
        studentManager.addGrade("Mia", "ProfessorSmith");
        studentManager.addGrade("Nick", "MsDavis");
        studentManager.addGrade("Olivia", "ProfessorSmith");
        studentManager.addGrade("Paul", "DrJohnson");
        studentManager.addGrade("Quinn", "MsDavis");
        studentManager.addGrade("Rachel", "ProfessorSmith");
        studentManager.addGrade("Sam", "DrJohnson");
    }

    // Выводим оценки студентов
    studentManager.printStudentGrades();

    // Выводим отличников
    studentManager.printExcellentStudents();

    return 0;
}
