#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>

using namespace std;

class Student {
public:
    Student() { name = "-N-"; }

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

    double getAverageGrade() const {
        if (!grades.empty()) {
            double totalGrade = 0.0;
            for (int grade : grades) {
                totalGrade += static_cast<double>(grade);
            }
            return totalGrade / grades.size();
        }
        return 0.0;
    }

private:
    std::string name;
    std::vector<int> grades;
};

class Teacher {
public:
    Teacher() { name = "NN"; goodMood = true; }
    Teacher(const std::string& name, bool goodMood, bool alwaysGive5, bool alwaysGive2)
        : name(name), goodMood(goodMood), alwaysGive5(alwaysGive5), alwaysGive2(alwaysGive2), gradeCounter(0) {}

    void giveGrades(Student& student, int numGrades) {
        std::random_device rd;
        std::mt19937 gen(rd());

        for (int i = 0; i < numGrades; ++i) {
            if (alwaysGive5) {
                student.addGrade(5);
            }
            else if (alwaysGive2) {
                student.addGrade(2);
            }
            else {
                int baseGrade = student.isExcellentStudent() ? getExcellentGrade(gen) : getRegularGrade(gen);
                student.addGrade(baseGrade);
            }
            gradeCounter++;
            if (gradeCounter % 5 == 0) {
                changeMoodRandomly();
            }
        }
    }

    const std::string& getName() const {
        return name;
    }

private:
    std::string name;
    bool goodMood;
    bool alwaysGive5;
    bool alwaysGive2;
    int gradeCounter;

    int getExcellentGrade(std::mt19937& gen) const {
        return 5;
    }

    int getRegularGrade(std::mt19937& gen) const {
        std::uniform_int_distribution<> dis(goodMood ? 4 : 2, 5);
        return dis(gen);
    }

    void changeMoodRandomly() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 1);

        goodMood = (dis(gen) == 0);
    }
};

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

class Parent {
public:
    Parent() { name = "-N-"; goodMood = true; }
    Parent(const std::string& name, bool goodMood) : name(name), goodMood(goodMood), children({}) {}

    const std::string& getName() const {
        return name;
    }

    void addChild( Student& child) {
        children.push_back(child);
    }

    vector<Student> getStudents() {
        return this->children;
    }

    string getName() {
        return name;
    }

    bool getMood() {
        return goodMood;
    }

    bool isChildMe(string child) {
        if (this->children.size() == 0)
            return false;

        for (int i = 0; i < this->children.size(); i++) {
            if (child == this->children[i].getName())
                return true;
        }
        return false;
    }

    void tellAboutChild(const Student& child) const {
        std::cout << "Child " << child.getName() << ": " << (goodMood ? "Happy " : "Unhappy ")
            << (child.isExcellentStudent() ? "Excellent" : "Not an excellent") << " student.\n";
    }

    void tellAboutRandomChild() const{
        if (!children.empty()) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(0, children.size() - 1);
            tellAboutChild(children[dis(gen)]);
        }
        else {
            std::cout << "Parent " << name << " has no children to talk about.\n";
        }
    }

    void tellAboutAllChildren() {
        std::vector<Student> childrenCopy = children;
        std::cout << "Parent " << name << " says about all children:\n";
        for (const Student& child : childrenCopy) {
            tellAboutChild(child);
        }
    }

    void tellAboutSpecificChild(const Student& child) const {
        auto it = std::find_if(children.begin(), children.end(), [&child](const Student& c) {
            return c.getName() == child.getName();
            });

        if (it != children.end()) {
            tellAboutChild(child);
        }
        else {
            std::cout << "Error: " << child.getName() << " is not a child of parent " << name << ".\n";
        }
    }

    void tellAboutAllChildrenSummary() const {
        std::vector<Student> childrenCopy = children;
        std::cout << "Parent " << name << " says about all children in summary:\n";
        if (!childrenCopy.empty()) {
            double averageGrade = calculateAverageGrade(childrenCopy);
            if (goodMood && averageGrade >= 4.5) {
                std::cout << "Happy and proud of excellent children.\n";
            }
            else {
                std::cout << "May express some emotions about the children.\n";
            }
        }
        else {
            std::cout << "Parent " << name << " has no children to talk about.\n";
        }
    }

private:
    std::string name;
    bool goodMood;
    std::vector<Student> children;

    double calculateAverageGrade(const std::vector<Student>& children) const {
        if (!children.empty()) {
            double totalGrade = 0.0;
            for (const Student& child : children) {
                totalGrade += child.getAverageGrade();
            }
            return totalGrade / children.size();
        }
        return 0.0;
    }
};

class Sobranie {
private:
    std::vector<Parent> Parents;
    std::vector<Teacher> Teachers;
    std::vector<Lesson> Lessons;
public:
    //initialization
    Sobranie(std::vector<Parent>& parents, std::vector<Teacher>& teachers, std::vector<Lesson>& lessons) {
        Parents = parents;
        Teachers = teachers;
        Lessons = lessons;
    };

    void StartDiscuss(vector<Student>& studentss) {
        vector<string> ShadowChilds;
        vector<string> LessonStudents;
        Student StudOfParent;
        Parent StudParent;
        bool TeacherFactor = false;

        for (int i = 0; i < Lessons.size(); i++) {
            cout << "Lesson number " << i + 1 << " : \n";
            LessonStudents = Lessons[i].getStudentNames();
            for (int j = 0; j < LessonStudents.size(); j++) {
                //проверим,есть ли у нас родитель этого ученика
                bool HaveParent = false;
                // Parent StudParent;
                for (int g = 0; g < Parents.size(); g++) {
                    if (Parents[g].isChildMe(LessonStudents[j]) == true) {
                        HaveParent = true;
                         StudParent = Parents[g];   
                         StudOfParent = studentss[j];
                    }
                }
                //если родителя студента нет - кидаю его в список
                if (HaveParent == false and find(ShadowChilds.begin(),ShadowChilds.end(),LessonStudents[j]) == ShadowChilds.end())
                    ShadowChilds.push_back(LessonStudents[j]);
                else if (HaveParent!= false){
                    vector<int> subjMarks = StudOfParent.getGrades();
                    if (subjMarks.size() >= 1) {
                        StudParent.tellAboutSpecificChild(StudOfParent);

                        string Prepod = this->Lessons[i].getTeacherName();
                        for (int i = 0; i < Teachers.size(); i++) {
                            if (Prepod == Teachers[i].getName()) {
                                if (StudOfParent.getAverageGrade() >= 4.5)
                                    cout << "Good boy!\n";
                                else cout << "Bad boy!\n";
                                TeacherFactor = true;
                            }
                        }

                        if (!TeacherFactor) {
                            cout <<" Teacher otsutstvuet(( \n";
                        }
                       
                    }
                }
            }
        }
        //вывел список детей,чьих родителей не было
        cout << "Spisok otsutstvuet parent on \n";
        for (int i = 0; i < ShadowChilds.size(); i++) {
            cout << ShadowChilds[i] << endl;
        }

    };


};

class StudentManager {
public:
    void addStudent(const std::string& name) {
        students.push_back(Student(name));
    }

    void addTeacher(const std::string& name, bool goodMood, bool alwaysGive5, bool alwaysGive2) {
        teachers.push_back(Teacher(name, goodMood, alwaysGive5, alwaysGive2));
    }

    void addParent(const std::string& name, bool goodMood) {
        parents.push_back(Parent(name, goodMood));
    }

    void assignChildToParent(const std::string& parentName, const std::string& childName) {
        auto parentIt = findParent(parentName);
        auto childIt = findStudent(childName);

        if (parentIt != parents.end() && childIt != students.end()) {
            parentIt->addChild(*childIt);
        }
        else {
            std::cout << "Error: Unable to assign child to parent.\n";
        }
    }

    void addLesson(const std::string& teacherName, const std::vector<std::string>& studentNames, int numGradesPerStudent) {
        lessons.push_back(Lesson(teacherName, studentNames, numGradesPerStudent));
    }

    void addSobranie() {
        sobraniya.push_back(Sobranie(parents, teachers, lessons));
    }

    void StartMeetings() {
        for (int i = 0; i < sobraniya.size(); i++) {
            sobraniya[i].StartDiscuss(students);
        }
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

    void parentActions()  {
        for ( Parent& parent : parents) {
            parent.tellAboutAllChildren();
            parent.tellAboutRandomChild();
            std::vector<Student> childrenCopy = students;
            if (!childrenCopy.empty()) {
                std::random_device rd;
                std::mt19937 gen(rd());
                std::shuffle(childrenCopy.begin(), childrenCopy.end(), gen);
                parent.tellAboutSpecificChild(childrenCopy.front());
            }
            else {
                std::cout << "There are no students to talk about.\n";
            }
        }
    }

    void tellAboutAllChildrenSummary() {
        for ( Parent& parent : parents) {
            parent.tellAboutAllChildrenSummary();
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
    std::vector<Parent> parents;
    std::vector<Sobranie> sobraniya;

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

    std::vector<Parent>::iterator findParent(const std::string& parentName) {
        return std::find_if(parents.begin(), parents.end(),
            [parentName](const Parent& parent) {
                return parent.getName() == parentName;
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
    studentManager.addTeacher("ProfessorSmith", true, false, false);
    studentManager.addTeacher("DrJohnson", false, false, false);
    studentManager.addTeacher("MsDavis", true, false, false);
    studentManager.addTeacher("ProfessorAlways5", true, true, false);
    studentManager.addTeacher("ProfessorAlways2", true, false, true);

    // Добавляем родителей
    studentManager.addParent("Mom", true);
    studentManager.addParent("Dad", false);

    // Привязываем детей к родителям
    studentManager.assignChildToParent("Mom", "Alice");
    studentManager.assignChildToParent("Mom", "Bob");
    studentManager.assignChildToParent("Dad", "Charlie");
    studentManager.assignChildToParent("Dad", "David");

    // Добавляем занятия
    studentManager.addLesson("ProfessorSmith", studentNames, 3);
    studentManager.addLesson("DrJohnson", studentNames, 2);
    studentManager.addLesson("MsDavis", studentNames, 4);
    studentManager.addLesson("ProfessorAlways5", studentNames, 1);
    studentManager.addLesson("ProfessorAlways2", studentNames, 1);

    // Проводим занятия
    studentManager.conductLesson("ProfessorSmith");
    studentManager.conductLesson("DrJohnson");
    studentManager.conductLesson("MsDavis");
    studentManager.conductLesson("ProfessorAlways5");
    studentManager.conductLesson("ProfessorAlways2");

    // Действия родителей
    studentManager.parentActions();
    studentManager.tellAboutAllChildrenSummary();

    // Выводим оценки студентов
    studentManager.printStudentGrades();

    // Выводим отличников
    studentManager.printExcellentStudents();

     //Добавляем собрание
     studentManager.addSobranie();
     //начинаем собрание 
     studentManager.StartMeetings();
   
    return 0;
}