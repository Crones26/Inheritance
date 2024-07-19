#include <iostream>

using namespace std;
using std::cin;
using std::cout;
using std::endl;

class Vehicle
{
public:
    virtual void move() = 0;
};
class GroundVehicle :public Vehicle{};

class Bike : public GroundVehicle
{
public:
    void move()override
    {
        cout << "Harley Davison едет на двух колесах" << endl;
    }
};

void main()
{
    setlocale(LC_ALL, "");
    //Vehicle vehicle;
    //GroundVehicle gv;
    Bike harley_davidson;
    harley_davidson.move();


}