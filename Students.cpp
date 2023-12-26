#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class Student {
public:
    Student(const std::string& name) : name(name), grades({}), averageGrade(0.0) {}

    void addGrade(int grade) {
        grades.push_back(grade);
        recalculateAverageGrade();
    }

    bool isExcellentStudent() const {
        return getAverageGrade() >= 4.5;
    }

    const std::string& getName() const {
        return name;
    }

    double getAverageGrade() const {
        return averageGrade;
    }

private:
    void recalculateAverageGrade() {
        if (grades.empty()) {
            averageGrade = 0.0;
            return;
        }

        double sum = 0.0;
        for (int grade : grades) {
            sum += grade;
        }

        averageGrade = sum / static_cast<double>(grades.size());
    }

    std::string name;
    std::vector<int> grades;
    double averageGrade;
};

class Teacher {
public:
    void giveGrade(Student& student, int grade) {
        student.addGrade(grade);
    }
};

class StudentManager {
public:
    void addStudent(const std::string& name) {
        students.push_back(Student(name));
    }

    void addTeacher(const std::string& name) {
        teachers.push_back(Teacher(name));
    }

    void addGrade(const std::string& studentName, const std::string& teacherName, int grade) {
        auto studentIt = findStudent(studentName);
        auto teacherIt = findTeacher(teacherName);
        if (studentIt != students.end() && teacherIt != teachers.end()) {
            teacherIt->giveGrade(*studentIt, grade);
        }
    }

    void printExcellentStudents() const {
        std::cout << "Excellent Students:\n";
        for (const Student& student : students) {
            if (student.isExcellentStudent()) {
                std::cout << student.getName() << " (Average Grade: " << student.getAverageGrade() << ")\n";
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

    // Добавляем преподавателей
    studentManager.addTeacher("ProfessorSmith");
    studentManager.addTeacher("DrJohnson");

    // Выставляем оценки студентам
    studentManager.addGrade("Alice", "ProfessorSmith", 5);
    studentManager.addGrade("Bob", "DrJohnson", 4);
    studentManager.addGrade("Charlie", "ProfessorSmith", 5);
    studentManager.addGrade("Charlie", "ProfessorSmith", 4);
    studentManager.addGrade("Charlie", "ProfessorSmith", 4);

    // Выводим отличников
    studentManager.printExcellentStudents();

    return 0;
}
