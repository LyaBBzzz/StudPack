#include <iostream>
#include <vector>
#include <string>

class Student {
public:
    Student(const std::string& name) : name(name), grades({}) {}

    void addGrade(int grade) {
        grades.push_back(grade);
    }

    bool isExcellentStudent() const {
        double averageGrade = calculateAverageGrade();
        return averageGrade > 4.5;
    }

    const std::string& getName() const {
        return name;
    }

private:
    double calculateAverageGrade() const {
        if (grades.empty()) {
            return 0.0;
        }

        double sum = 0.0;
        for (int grade : grades) {
            sum += grade;
        }

        return sum / grades.size();
    }

    std::string name;
    std::vector<int> grades;
};

class StudentManager {
public:
    void addStudent(const std::string& name) {
        students.push_back(Student(name));
    }

    void addGrade(const std::string& studentName, const std::vector<int>& grades) {
        auto it = findStudent(studentName);
        if (it != students.end()) {
            for (int grade : grades) {
                it->addGrade(grade);
            }
        }
    }

    void printExcellentStudents() const {
        std::cout << "Excellent Students:\n";
        for (const Student& student : students) {
            if (student.isExcellentStudent()) {
                std::cout << student.getName() << "\n";
            }
        }
    }

private:
    std::vector<Student> students;

    std::vector<Student>::iterator findStudent(const std::string& studentName) {
        return std::find_if(students.begin(), students.end(),
            [studentName](const Student& student) {
                return student.getName() == studentName;
            });
    }
};

int main() {
    StudentManager studentManager;

    // Добавляем студентов
    studentManager.addStudent("Alice");
    studentManager.addStudent("Bob");
    studentManager.addStudent("Charlie");

    // Выставляем оценки
    studentManager.addGrade("Alice", { 5, 4, 5 });
    studentManager.addGrade("Bob", { 4, 3, 4 });
    studentManager.addGrade("Charlie", { 5, 5, 4 });

    // Выводим отличников
    studentManager.printExcellentStudents();

    return 0;
}
