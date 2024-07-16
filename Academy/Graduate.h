#pragma once

#include "Student.h"

#define GRADUATE_TAKE_PARAMETERS const std::string& thesis_title, const std::string& advisor
#define GRADUATE_GIVE_PARAMETERS thesis_title, advisor

class Graduate : public Student
{
    std::string thesis_title;
    std::string advisor;
public:
    const std::string& get_thesis_title() const;
    const std::string& get_advisor() const;

    void set_thesis_title(const std::string& thesis_title);
    void set_advisor(const std::string& advisor);

    Graduate(HUMAN_TAKE_PARAMETERS, STUDENT_TAKE_PARAMETERS, GRADUATE_TAKE_PARAMETERS);
    Graduate(const Student& student, const std::string& thesis_title);
    ~Graduate();

    std::ostream& print(std::ostream& os) const override;
};
