#include "Utilities.h"

void Print(Human* group[], const int n)
{
    std::cout << delimiter << std::endl;
    for (int i = 0; i < n; i++)
    {
        std::cout << *group[i] << std::endl;
        std::cout << delimiter << std::endl;
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
        std::cout << "File cleared successfully.\n";
        fout.close();
    }
    else
    {
        std::cerr << "Error: File not found" << std::endl;
    }
}