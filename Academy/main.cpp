#include "Academy.h"
#include "Human.h"
#include "Student.h"
#include "Teacher.h"
#include "Graduate.h"
#include "Utilities.h"

void main()
{
    setlocale(LC_ALL, "");

    Human* group[] =
    {
        new Student("Pinkman", "Jessi", 20, "Chemistry", "WW_220", 95, 90),
        new Teacher("White", "Walter", 50, "Chemistry", 25),
        new Graduate("Doe", "Johns", 24, "Chemistry", "WW_220", 88.5, 92.3, "Methods of nanocomposite synthesis", "Dr. White"),
        new Student("Vercetti", "Tommy", 30, "Theft", "Vice", 95, 90),
        new Teacher("Diaz", "Ricardo", 50, "Weapons distribution", 20)
    };

    char clearFile;
    std::cout << "Do you want to clear the file? (y/n): ";
    std::cin >> clearFile;
    if (clearFile == 'y' || clearFile == 'Y')
    {
        ClearFile("File.txt");
    }

    std::ofstream fout;
    fout.open("File.txt", std::ios_base::app);
    for (int i = 0; i < sizeof(group) / sizeof(group[0]); i++)
    {
        fout << *group[i] << std::endl;
    }
    fout.close();

    Print(group, sizeof(group) / sizeof(group[0]));
    Clear(group, sizeof(group) / sizeof(group[0]));

    std::cout << delimiter << std::endl;
    std::ifstream fin("File.txt");
    if (fin.is_open())
    {
        while (!fin.eof())
        {
            const int SIZE = 1024;
            char buffer[SIZE]{};
            fin.getline(buffer, SIZE);
            std::cout << buffer << std::endl;
        }
        fin.close();
    }
    else
    {
        std::cerr << "Error: File not found" << std::endl;
    }
    system("notepad File.txt");
}