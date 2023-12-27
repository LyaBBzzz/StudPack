#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>

// Класс Студент
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

// Класс Учитель
class Teacher {
public:
    Teacher(const std::string& name, bool goodMood) : name(name), goodMood(goodMood) {}

    void giveGrades(Student& student, int numGrades) {
        std::random_device rd;
        std::mt19937 gen(rd());

        for (int i = 0; i < numGrades; ++i) {
            int baseGrade = student.isExcellentStudent() ? getExcellentGrade(gen) : getRegularGrade(gen);
            student.addGrade(baseGrade);
        }
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

// Класс Занятие
class Lesson {
public:
    Lesson(const std::string& teacherName, const std::vector<std::string>& studentNames, int numGradesPerStudent)
        : teacherName(teacherName), studentNames(studentNames), numGradesPerStudent(numGradesPerStudent) {}

    const std::string& getTeacherName() const {
        return teacherName;
    }

    const std::vector<std::string>& getStudentNames() const {
        return studentNames;
    }

    int getNumGradesPerStudent() const {
        return numGradesPerStudent;
    }

private:
    std::string teacherName;
    std::vector<std::string> studentNames;
    int numGradesPerStudent;
};

class StudentManager {
public:
    void addStudent(const std::string& name) {
        students.push_back(Student(name));
    }

    void addTeacher(const std::string& name, bool goodMood) {
        teachers.push_back(Teacher(name, goodMood));
    }

    void addLesson(const std::string& teacherName, const std::vector<std::string>& studentNames, int numGradesPerStudent) {
        lessons.push_back(Lesson(teacherName, studentNames, numGradesPerStudent));
    }

    void conductLesson(const std::string& teacherName) {
        auto lessonIt = std::find_if(lessons.begin(), lessons.end(),
            [teacherName](const Lesson& lesson) {
                return lesson.getTeacherName() == teacherName;
            });
        if (lessonIt != lessons.end()) {
            auto teacherIt = findTeacher(teacherName);
            if (teacherIt != teachers.end()) {
                int numGradesPerStudent = lessonIt->getNumGradesPerStudent();
                for (const std::string& studentName : lessonIt->getStudentNames()) {
                    auto studentIt = findStudent(studentName);
                    if (studentIt != students.end()) {
                        teacherIt->giveGrades(*studentIt, numGradesPerStudent);
                    }
                }
            }
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
    std::vector<Lesson> lessons;

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
    std::vector<std::string> studentNames = {
        "Alice", "Bob", "Charlie", "David", "Eva",
        "Frank", "Grace", "Harry", "Ivy", "Jack",
        "Kelly", "Leo", "Mia", "Nick", "Olivia",
        "Paul", "Quinn", "Rachel", "Sam"
    };
    for (const std::string& name : studentNames) {
        studentManager.addStudent(name);
    }

    // Добавляем преподавателей
    studentManager.addTeacher("ProfessorSmith", true);  // В хорошем настроении
    studentManager.addTeacher("DrJohnson", false);      // В плохом настроении
    studentManager.addTeacher("MsDavis", false);         // В хорошем настроении

    // Добавляем занятия
    studentManager.addLesson("ProfessorSmith", studentNames, 3);  // 3 оценки на занятии
    studentManager.addLesson("DrJohnson", studentNames, 2);      // 2 оценки на занятии
    studentManager.addLesson("MsDavis", studentNames, 4);         // 4 оценки на занятии

    // Проводим занятия
    studentManager.conductLesson("ProfessorSmith");
    studentManager.conductLesson("DrJohnson");
    studentManager.conductLesson("MsDavis");

    // Выводим оценки студентов
    studentManager.printStudentGrades();

    // Выводим отличников
    studentManager.printExcellentStudents();

    return 0;
}
