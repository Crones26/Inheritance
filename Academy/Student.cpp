#include "Student.h"

const std::string& Student::get_speciality() const { return speciality; }
const std::string& Student::get_group() const { return group; }
double Student::get_rating() const { return rating; }
double Student::get_attendance() const { return attendance; }

void Student::set_speciality(const std::string& speciality) { this->speciality = speciality; }
void Student::set_group(const std::string& group) { this->group = group; }
void Student::set_rating(double rating) { this->rating = rating; }
void Student::set_attendance(double attendance) { this->attendance = attendance; }

Student::Student(HUMAN_TAKE_PARAMETERS, STUDENT_TAKE_PARAMETERS) : Human(HUMAN_GIVE_PARAMETERS)
{
    set_speciality(speciality);
    set_group(group);
    set_rating(rating);
    set_attendance(attendance);
    std::cout << "SConstructor:\t" << this << std::endl;
}

Student::Student(const Human& human, STUDENT_TAKE_PARAMETERS) : Human(human)
{
    set_speciality(speciality);
    set_group(group);
    set_rating(rating);
    set_attendance(attendance);
    std::cout << "SConstructor:\t" << this << std::endl;
}

Student::~Student()
{
    std::cout << "SDestructor:\t" << this << std::endl;
}

std::ostream& Student::print(std::ostream& os) const
{
    return Human::print(os) << " " << speciality << " " << group << " " << rating << " " << attendance;
}