#include <iostream>
#include <fstream>
#include <string>

using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define delimiter "\n----------------------------------------------\n"

#define HUMAN_TAKE_PARAMETERS const std::string& last_name, const std::string& first_name, int age
#define HUMAN_GIVE_PARAMETERS last_name, first_name, age

class Human {
    std::string last_name;
    std::string first_name;
    int age;

public:
    const std::string& get_last_name() const { return last_name; }
    const std::string& get_first_name() const { return first_name; }
    int get_age() const { return age; }
    void set_last_name(const std::string& last_name) { this->last_name = last_name; }
    void set_first_name(const std::string& first_name) { this->first_name = first_name; }
    void set_age(int age) { this->age = age; }

    Human(HUMAN_TAKE_PARAMETERS) {
        set_last_name(last_name);
        set_first_name(first_name);
        set_age(age);
        cout << "HConstructor:\t" << this << endl;
    }
    virtual ~Human() {
        cout << "HDestructor:\t" << this << endl;
    }

    virtual std::ostream& print(std::ostream& os) const {
        return os << last_name << " " << first_name << " " << age;
    }

    virtual void save(std::ostream& os) const {
        os << "Human" << std::endl;
        os << last_name << std::endl;
        os << first_name << std::endl;
        os << age << std::endl;
    }

    virtual void load(std::istream& is) {
        getline(is, last_name);
        getline(is, first_name);
        is >> age;
        is.ignore(); // Игнорируем остаток строки после возраста
    }
};

#define STUDENT_TAKE_PARAMETERS const std::string& speciality, const std::string& group, double rating, double attendance
#define STUDENT_GIVE_PARAMETERS speciality, group, rating, attendance

class Student : public Human {
    std::string speciality;
    std::string group;
    double rating;
    double attendance;

public:
    const std::string& get_speciality() const { return speciality; }
    const std::string& get_group() const { return group; }
    double get_rating() const { return rating; }
    double get_attendance() const { return attendance; }
    void set_speciality(const std::string& speciality) { this->speciality = speciality; }
    void set_group(const std::string& group) { this->group = group; }
    void set_rating(double rating) { this->rating = rating; }
    void set_attendance(double attendance) { this->attendance = attendance; }

    Student(HUMAN_TAKE_PARAMETERS, STUDENT_TAKE_PARAMETERS) : Human(HUMAN_GIVE_PARAMETERS) {
        set_speciality(speciality);
        set_group(group);
        set_rating(rating);
        set_attendance(attendance);
        cout << "SConstructor:\t" << this << endl;
    }
    Student(const Human& human, STUDENT_TAKE_PARAMETERS) : Human(human) {
        set_speciality(speciality);
        set_group(group);
        set_rating(rating);
        set_attendance(attendance);
        cout << "SConstructor:\t" << this << endl;
    }
    ~Student() {
        cout << "SDestructor:\t" << this << endl;
    }

    std::ostream& print(std::ostream& os) const override {
        return Human::print(os) << " " << speciality << " " << group << " " << rating << " " << attendance;
    }

    void save(std::ostream& os) const override {
        os << "Student" << std::endl;
        Human::save(os);
        os << speciality << std::endl;
        os << group << std::endl;
        os << rating << std::endl;
        os << attendance << std::endl;
    }

    void load(std::istream& is) override {
        Human::load(is);
        getline(is, speciality);
        getline(is, group);
        is >> rating;
        is >> attendance;
        is.ignore(); // Игнорируем остаток строки после посещаемости
    }
};

#define TEACHER_TAKE_PARAMETERS const std::string& speciality, int experience
#define TEACHER_GIVE_PARAMETERS speciality, experience

class Teacher : public Human {
    std::string speciality;
    int experience;

public:
    const std::string& get_speciality() const { return speciality; }
    int get_experience() const { return experience; }
    void set_speciality(const std::string& speciality) { this->speciality = speciality; }
    void set_experience(int experience) { this->experience = experience; }

    Teacher(HUMAN_TAKE_PARAMETERS, TEACHER_TAKE_PARAMETERS) : Human(HUMAN_GIVE_PARAMETERS) {
        set_speciality(speciality);
        set_experience(experience);
        cout << "TConstructor:\t" << this << endl;
    }
    ~Teacher() {
        cout << "TDestructor:\t" << this << endl;
    }

    std::ostream& print(std::ostream& os) const override {
        return Human::print(os) << " " << speciality << " " << experience << " years";
    }

    void save(std::ostream& os) const override {
        os << "Teacher" << std::endl;
        Human::save(os);
        os << speciality << std::endl;
        os << experience << std::endl;
    }

    void load(std::istream& is) override {
        Human::load(is);
        getline(is, speciality);
        is >> experience;
        is.ignore(); // Игнорируем остаток строки после опыта
    }
};

#define GRADUATE_TAKE_PARAMETERS const std::string& thesis_title, const std::string& advisor
#define GRADUATE_GIVE_PARAMETERS thesis_title, advisor

class Graduate : public Student {
    std::string thesis_title;
    std::string advisor;

public:
    const std::string& get_thesis_title() const { return thesis_title; }
    const std::string& get_advisor() const { return advisor; }
    void set_thesis_title(const std::string& thesis_title) { this->thesis_title = thesis_title; }
    void set_advisor(const std::string& advisor) { this->advisor = advisor; }

    Graduate(HUMAN_TAKE_PARAMETERS, STUDENT_TAKE_PARAMETERS, GRADUATE_TAKE_PARAMETERS)
        : Student(HUMAN_GIVE_PARAMETERS, STUDENT_GIVE_PARAMETERS) {
        set_thesis_title(thesis_title);
        set_advisor(advisor);
        cout << "GConstructor:\t" << this << endl;
    }
    Graduate(const Student& student, const std::string& thesis_title) : Student(student) {
        set_thesis_title(thesis_title);
        cout << "GConstructor:\t" << this << endl;
    }
    ~Graduate() {
        cout << "GDestructor:\t" << this << endl;
    }

    std::ostream& print(std::ostream& os) const override {
        return Student::print(os) << " " << thesis_title << " " << advisor;
    }

    void save(std::ostream& os) const override {
        os << "Graduate" << std::endl;
        Student::save(os);
        os << thesis_title << std::endl;
        os << advisor << std::endl;
    }

    void load(std::istream& is) override {
        Student::load(is);
        getline(is, thesis_title);
        getline(is, advisor);
    }
};

std::ostream& operator<<(std::ostream& os, const Human& obj) {
    return obj.print(os);
}

void Print(Human* group[], const int n) {
    cout << delimiter << endl;
    for (int i = 0; i < n; i++) {
        cout << *group[i] << endl;
        cout << delimiter << endl;
    }
}

void Clear(Human* group[], const int n) {
    for (int i = 0; i < n; i++) {
        delete group[i];
    }
}

void SaveGroup(Human* group[], const int n, const std::string& filename) {
    std::ofstream fout(filename);
    if (fout.is_open()) {
        for (int i = 0; i < n; ++i) {
            group[i]->save(fout);
        }
        fout.close();
    }
    else {
        std::cerr << "Error: Could not open file for writing." << std::endl;
    }
}

Human* LoadHuman(std::istream& is) {
    std::string type;
    is >> type;
    is.ignore(); // Игнорируем остаток строки после типа
    if (type == "Human") {
        Human* human = new Human("", "", 0);
        human->load(is);
        return human;
    }
    else if (type == "Student") {
        Student* student = new Student("", "", 0, "", "", 0.0, 0.0);
        student->load(is);
        return student;
    }
    else if (type == "Teacher") {
        Teacher* teacher = new Teacher("", "", 0, "", 0);
        teacher->load(is);
        return teacher;
    }
    else if (type == "Graduate") {
        Graduate* graduate = new Graduate("", "", 0, "", "", 0.0, 0.0, "", "");
        graduate->load(is);
        return graduate;
    }
    return nullptr;
}

void LoadGroup(Human* group[], const int n, const std::string& filename) {
    std::ifstream fin(filename);
    if (fin.is_open()) {
        for (int i = 0; i < n; ++i) {
            group[i] = LoadHuman(fin);
        }
        fin.close();
    }
    else {
        std::cerr << "Error: Could not open file for reading." << std::endl;
    }
}

int main() {
    setlocale(LC_ALL, "");

    Human* group[] = {
        new Student("Pinkman", "Jessi", 20, "Chemistry", "WW_220", 95, 90),
        new Teacher("White", "Walter", 50, "Chemistry", 25),
        new Graduate("Doe", "Johns", 24, "Chemistry", "WW_220", 88.5, 92.3, "Methods of nanocomposite synthesis", "Dr. White"),
        new Student("Vercetti", "Tommy", 30, "Theft", "Vice", 95, 90),
        new Teacher("Diaz", "Ricardo", 50, "Weapons distribution", 20)
    };

    // Сохранение группы в файл
    SaveGroup(group, sizeof(group) / sizeof(group[0]), "Group.txt");

    // Печать группы в консоль
    Print(group, sizeof(group) / sizeof(group[0]));
    
    cout << delimiter << endl;

    // Загрузка группы из файла
    LoadGroup(group, sizeof(group) / sizeof(group[0]), "Group.txt");

    // Печать загруженной группы в консоль
    Print(group, sizeof(group) / sizeof(group[0]));
    

    return 0;
}