#include<iostream>
#include<fstream>
#include<string>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define delimiter "\n----------------------------------------------\n"

#define HUMAN_TAKE_PARAMETERS const std::string& last_name, const std::string& first_name, int age
#define HUMAN_GIVE_PARAMETERS last_name, first_name, age
class Human
{
    std::string last_name;
    std::string first_name;
    int age;
public:
    const std::string& get_last_name()const
    {
        return last_name;
    }
    const std::string& get_first_name()const
    {
        return first_name;
    }
    int get_age()const
    {
        return age;
    }
    void set_last_name(const std::string& last_name)
    {
        this->last_name = last_name;
    }
    void set_first_name(const std::string& first_name)
    {
        this->first_name = first_name;
    }
    void set_age(int age)
    {
        this->age = age;
    }

    //              Constructors:
    Human(HUMAN_TAKE_PARAMETERS)
    {
        set_last_name(last_name);
        set_first_name(first_name);
        set_age(age);
        cout << "HConstructor:\t" << this << endl;
    }
    virtual ~Human()
    {
        cout << "HDestructor:\t" << this << endl;
    }

    //              Methods:
    virtual std::ostream& print(std::ostream& os)const
    {
        return os << last_name << " " << first_name << " " << age;
    }
};

#define STUDENT_TAKE_PARAMETERS const std::string& speciality, const std::string& group, double rating, double attendance
#define STUDENT_GIVE_PARAMETERS speciality, group, rating, attendance
class Student : public Human
{
    std::string speciality;
    std::string group;
    double rating;
    double attendance;
public:
    const std::string& get_speciality()const
    {
        return speciality;
    }
    const std::string& get_group()const
    {
        return group;
    }
    double get_rating()const
    {
        return rating;
    }
    double get_attendance()const
    {
        return attendance;
    }
    void set_speciality(const std::string& speciality)
    {
        this->speciality = speciality;
    }
    void set_group(const std::string& group)
    {
        this->group = group;
    }
    void set_rating(double rating)
    {
        this->rating = rating;
    }
    void set_attendance(double attendance)
    {
        this->attendance = attendance;
    }

    //              Constructors:
    Student(HUMAN_TAKE_PARAMETERS, STUDENT_TAKE_PARAMETERS) :Human(HUMAN_GIVE_PARAMETERS)
    {
        set_speciality(speciality);
        set_group(group);
        set_rating(rating);
        set_attendance(attendance);
        cout << "SConstructor:\t" << this << endl;
    }
    Student(const Human& human, STUDENT_TAKE_PARAMETERS) : Human(human)
    {
        set_speciality(speciality);
        set_group(group);
        set_rating(rating);
        set_attendance(attendance);
        cout << "SConstructor:\t" << this << endl;
    }
    ~Student()
    {
        cout << "SDestructor:\t" << this << endl;
    }

    //              Methods:
    std::ostream& print(std::ostream& os)const override
    {
        return Human::print(os) << " " << speciality << " " << group << " " << rating << " " << attendance;
    }
};

#define TEACHER_TAKE_PARAMETERS const std:: string& speciality, int experience
#define TEACHER_GIVE_PARAMETERS speciality, experience
class Teacher :public Human
{
    std::string speciality;
    int experience;
public:
    const std::string& get_speciality()const
    {
        return speciality;
    }
    int get_experiance()const
    {
        return experience;
    }
    void set_speciality(const std::string& speciality)
    {
        this->speciality = speciality;
    }
    void set_experience(int experience)
    {
        this->experience = experience;
    }

    //               Constructors:
    Teacher(HUMAN_TAKE_PARAMETERS, TEACHER_TAKE_PARAMETERS) :Human(HUMAN_GIVE_PARAMETERS)
    {
        set_speciality(speciality);
        set_experience(experience);
        cout << "TConstructor:\t" << this << endl;
    }
    ~Teacher()
    {
        cout << "TDestructor:\t" << this << endl;
    }

    //              Methods:
    std::ostream& print(std::ostream& os)const override
    {
        return Human::print(os) << " " << speciality << " " << experience << "years";
    }
};

#define GRADUATE_TAKE_PARAMETERS const std::string& thesis_title, const std::string& advisor
#define GRADUATE_GIVE_PARAMETERS thesis_title, advisor
class Graduate : public Student
{
    std::string thesis_title;
    std::string advisor;
public:
    const std::string& get_thesis_title()const
    {
        return thesis_title;
    }
    const std::string& get_advisor()const
    {
        return advisor;
    }
    void set_thesis_title(const std::string& thesis_title)
    {
        this->thesis_title = thesis_title;
    }
    void set_advisor(const std::string& advisor)
    {
        this->advisor = advisor;
    }

    //                 Constructors:
    Graduate(HUMAN_TAKE_PARAMETERS, STUDENT_TAKE_PARAMETERS, GRADUATE_TAKE_PARAMETERS)
        : Student(HUMAN_GIVE_PARAMETERS, STUDENT_GIVE_PARAMETERS)
    {
        set_thesis_title(thesis_title);
        set_advisor(advisor);
        cout << "GConstructor:\t" << this << endl;
    }
    Graduate(const Student& student, const std::string& thesis_title) :Student(student)
    {
        set_thesis_title(thesis_title);
        cout << "GConstructor:\t" << this << endl;
    }
    ~Graduate()
    {
        cout << "GDestructor:\t" << this << endl;
    }

    //                  Methods:
    std::ostream& print(std::ostream& os)const override
    {
        return Student::print(os) << " " << thesis_title << " " << advisor;
    }
};
std::ostream& operator<<(std::ostream& os, const Human& obj)
{
    return obj.print(os);
}

void Print(Human* group[], const int n)
{
    cout << delimiter << endl;
    for (int i = 0; i < n; i++)
    {
        //group[i]->print();
        cout << *group[i] << endl;
        cout << delimiter << endl;
    }
}

void Clear(Human* group[], const int n)
{
    for (int i = 0; i < n; i++)
    {
        delete group[i];
    }
}

void ClearFile(const std::string& filename)
{
    std::ofstream fout;
    fout.open(filename, std::ofstream::out | std::ofstream::trunc);
    if (fout.is_open())
    {
        cout << "File cleared successfully.\n";
        fout.close();
    }
    else
    {
        std::cerr << "Error: File not found" << endl;
    }
}

//#define INTHERITANCE_1
//#define INTHERITANCE_2

void main()
{
    setlocale(LC_ALL, "");
    //cout << "Hello Academy" << endl;

#ifdef INTHERITANCE_1
    Human human("Richter", "Jeffrey", 40);
    human.print();

    cout << delimiter << endl;
    Student student("Pinkman", "Jessi", 20, "Chemistry", "WW_220", 95, 90);
    student.print();

    cout << delimiter << endl;
    Teacher teacher("White", "Walter", 50, "Chemistry", 25);
    teacher.print();

    cout << delimiter << endl;
    Graduate graduate("Doe", "Johns", 24, "Chemistry", "WW_220", 88.5, 92.3, "Methods of nanocomposite synthesis", "Dr. White");
    graduate.print();
    cout << delimiter << endl;
#endif // INTHERITANCE_1

#ifdef INTHERITANCE_2
    Human human("Vercetty", "Tommy", 30);
    human.print();

    cout << delimiter << endl;
    Student student(human, "Theft", "Vice", 95, 90);
    student.print();

    cout << delimiter << endl;
    Graduate graduate(student, "How to make money");
    graduate.print();
    cout << delimiter << endl;
#endif // INTHERITANCE_2

    Human* group[] =
    {
        new Student("Pinkman", "Jessi", 20, "Chemistry", "WW_220", 95, 90),
        new Teacher("White", "Walter", 50, "Chemistry", 25),
        new Graduate("Doe", "Johns", 24, "Chemistry", "WW_220", 88.5, 92.3, "Methods of nanocomposite synthesis", "Dr. White"),
        new Student("Vercetti", "Tommy",30,"Theft", "Vice", 95, 90),
        new Teacher("Diaz","Ricardo",50,"Weapons distribution",20)
    };

    char clearFile;
    cout << "Do you want to clear the file? (y/n): ";
    cin >> clearFile;
    if (clearFile == 'y' || clearFile == 'Y')
    {
        ClearFile("Group.txt");
    }

    std::ofstream fout;
    fout.open("Group.txt", std::ios_base::app);
    for (int i = 0; i < sizeof(group) / sizeof(group[0]); i++)
    {
        fout << *group[i] << endl;
    }
    fout.close();

    Print(group, sizeof(group) / sizeof(group[0]));
    Clear(group, sizeof(group) / sizeof(group[0]));

    cout << delimiter << endl;

    std::ifstream fin("Group.txt");
    if (fin.is_open())
    {
        while (!fin.eof())
        {
            const int SIZE = 1024;
            char buffer[SIZE]{};
            fin.getline(buffer, SIZE);
            cout << buffer << endl;
        }
        fin.close();
    }
    system("notepad Group.txt");

}

