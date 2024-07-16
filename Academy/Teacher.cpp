#include "Teacher.h"

const std::string& Teacher::get_speciality() const { return speciality; }
int Teacher::get_experience() const { return experience; }

void Teacher::set_speciality(const std::string& speciality) { this->speciality = speciality; }
void Teacher::set_experience(int experience) { this->experience = experience; }

Teacher::Teacher(HUMAN_TAKE_PARAMETERS, TEACHER_TAKE_PARAMETERS) : Human(HUMAN_GIVE_PARAMETERS)
{
    set_speciality(speciality);
    set_experience(experience);
    std::cout << "TConstructor:\t" << this << std::endl;
}

Teacher::~Teacher()
{
    std::cout << "TDestructor:\t" << this << std::endl;
}

std::ostream& Teacher::print(std::ostream& os) const
{
    return Human::print(os) << " " << speciality << " " << experience << " years";
}