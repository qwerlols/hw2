#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm> 

enum class StudyField {
    MECHANICAL_ENGINEERING = 1,
    SOFTWARE_ENGINEERING = 2,
    FOOD_TECHNOLOGY = 3,
    URBANISM_ARCHITECTURE = 4,
    VETERINARY_MEDICINE = 5
};

class Student {
private:
    std::string firstName;
    std::string lastName;
    std::string email;
    std::string enrollmentDate;
    std::string dateOfBirth;

public:
    Student(std::string first_name, std::string last_name, std::string email, std::string enrollment_date, std::string date_of_birth)
        : firstName(first_name), lastName(last_name), email(email), enrollmentDate(enrollment_date), dateOfBirth(date_of_birth) {}

    std::string getEmail() const {
        return email;
    }
};

class Faculty {
private:
    std::string name;
    std::string abbreviation;
    std::vector<Student> students;
    StudyField studyField;

public:
    Faculty(std::string name, std::string abbreviation, StudyField study_field)
        : name(name), abbreviation(abbreviation), studyField(study_field) {}

    void addStudent(const Student& student) {
        students.push_back(student);
    }

    std::string getName() const {
        return name;
    }

    std::vector<Student> getStudents() const {
        return students;
    }

    StudyField getStudyField() const {
        return studyField;
    }

    bool hasStudent(const std::string& studentEmail) const {
        for (const auto& student : students) {
            if (student.getEmail() == studentEmail) {
                return true;
            }
        }
        return false;
    }

    void graduateStudent(const std::string& studentEmail) {
        students.erase(std::remove_if(students.begin(), students.end(),
                                       [&](const Student& student) { return student.getEmail() == studentEmail; }),
                        students.end());
    }

    void displayCurrentEnrolledStudents() const {
        for (const auto& student : students) {
            std::cout << student.getEmail() << std::endl;
        }
    }
};

class University {
private:
    std::vector<Faculty> faculties;

public:
    void createFaculty(std::string name, std::string abbreviation, StudyField study_field) {
        Faculty faculty(name, abbreviation, study_field);
        faculties.push_back(faculty);
    }

    bool assignStudentToFaculty(const std::string& student_email, const std::string& faculty_name) {
        for (auto& faculty : faculties) {
            if (faculty.getName() == faculty_name) {
                Student student(student_email, "", "", "", "");
                faculty.addStudent(student);
                return true;
            }
        }
        return false;
    }

    std::string searchFacultyByStudentEmail(const std::string& student_email) {
        for (const auto& faculty : faculties) {
            if (faculty.hasStudent(student_email)) {
                return faculty.getName();
            }
        }
        return "Student not found";
    }

    void displayUniversityFaculties() {
        for (const auto& faculty : faculties) {
            std::cout << faculty.getName() << std::endl;
        }
    }

    void displayAllFacultiesByField(StudyField study_field) {
        for (const auto& faculty : faculties) {
            if (faculty.getStudyField() == study_field) {
                std::cout << faculty.getName() << std::endl;
            }
        }
    }

void saveState(const std::string& filename) {
        std::ofstream file(filename);
        if (file.is_open()) {
            for (const auto& faculty : faculties) {
                file << faculty.getName() << "," << static_cast<int>(faculty.getStudyField()) << ",";
                for (const auto& student : faculty.getStudents()) {
