#include "Graduate.h"

const std::string& Graduate::get_thesis_title() const { return thesis_title; }
const std::string& Graduate::get_advisor() const { return advisor; }

void Graduate::set_thesis_title(const std::string& thesis_title) { this->thesis_title = thesis_title; }
void Graduate::set_advisor(const std::string& advisor) { this->advisor = advisor; }

Graduate::Graduate(HUMAN_TAKE_PARAMETERS, STUDENT_TAKE_PARAMETERS, GRADUATE_TAKE_PARAMETERS)
    : Student(HUMAN_GIVE_PARAMETERS, STUDENT_GIVE_PARAMETERS)
{
    set_thesis_title(thesis_title);
    set_advisor(advisor);
    std::cout << "GConstructor:\t" << this << std::endl;
}

Graduate::Graduate(const Student& student, const std::string& thesis_title) : Student(student)
{
    set_thesis_title(thesis_title);
    std::cout << "GConstructor:\t" << this << std::endl;
}

Graduate::~Graduate()
{
    std::cout << "GDestructor:\t" << this << std::endl;
}

std::ostream& Graduate::print(std::ostream& os) const
{
    return Student::print(os) << " " << thesis_title << " " << advisor;
}