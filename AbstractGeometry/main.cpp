#include <Windows.h>
#include <iostream>
using namespace std;

namespace Geometry
{
    //enum (Enumeration - Перечисление) - это набор именованных констрант типа 'int'
    enum Color
    {	//Здесь используются 8-битные значения, которые могут интерпретироваться по-разному(что не есть хорошо)
        //CONSOLE_RED = 0xCC,	//старшая 'C' - цвет фона, младшая 'C' - цвет текста.
        //CONSOLE_GREEN = 0xAA,
        //CONSOLE_BLUE = 0x99,
        //CONSOLE_DEFAULT = 0x07

        // Здесь используются 32-битные значения(0xAARRGGBB)
        CONSOLE_RED = 0x000000FF,
        CONSOLE_GREEN = 0x0000FF00,
        CONSOLE_BLUE = 0x00FF0000,
        CONSOLE_YELLOW = 0x00FFFF00,
        CONSOLE_DEFAULT = 0x00000007
    };

    class Shape
    {
    protected:
        Color color;
        COLORREF setRGB(Color color)const
        {
            switch (color)
            {
            case CONSOLE_BLUE: return 0xFF0000; break;
            case CONSOLE_RED: return 0x0000FF; break;
            case CONSOLE_GREEN: return 0x00FF00; break;
            case CONSOLE_YELLOW: return 0x00FFFF; break;
            }
            return 0x000000; 
        }
    public:
        virtual double get_area() const = 0;
        virtual double get_perimeter()const = 0;
        virtual void draw(int offsetX, int offsetY)const = 0;
        Shape(Color color) :color(color) {}
        virtual ~Shape() {}
        virtual void info(int offsetX, int offsetY)const
        {
            cout << "Площадь фигуры: " << get_area() << endl;
            cout << "Периметр фигуры: " << get_perimeter() << endl;
            draw(offsetX, offsetY);
        }
    };

    class Square :public Shape
    {
        double side;
    public:
        Square(double side, Color color) :Shape(color)
        {
            set_side(side);
        }
        ~Square() {}
        void set_side(double side)
        {
            this->side = side;
        }
        double get_side()const
        {
            return side;
        }
        double get_area()const override
        {
            return side * side;
        }
        double get_perimeter()const override
        {
            return side * 4;
        }
        void draw(int offsetX, int offsetY)const override
        {
            HWND hwnd = FindWindow(NULL, L"Inheritance - Microsoft Visual Studio"); //находит окно с заголовком "Inheritance - Microsoft Visual Studio".
            HDC hdc = GetDC(hwnd);// получает контекст устройства (HDC) для окна.
            HPEN hPen = CreatePen(PS_SOLID, 5, setRGB(color));// создает сплошное перо заданного цвета и толщины 5 пикселей
            HBRUSH hBrush = CreateSolidBrush(setRGB(color));//создает кисть заданного цвета.
            // выбирает созданные перо и кисть в контекст устройства.
            SelectObject(hdc, hPen);
            SelectObject(hdc, hBrush);
            // рисует квадрат с заданными смещениями offsetX и offsetY.
            ::Rectangle(hdc, offsetX, offsetY, offsetX + side, offsetY + side);
            // удаляет созданные кисть и перо, освобождая ресурсы.
            DeleteObject(hBrush);
            DeleteObject(hPen);
            ReleaseDC(hwnd, hdc);// освобождает контекст устройства.
        }
        void info(int offsetX, int offsetY)const override
        {
            cout << typeid(*this).name() << endl;
            cout << "Длина стороны: " << get_side() << endl;
            Shape::info(offsetX, offsetY);
        }
    };

    /*class Square :public Shape
    {
        double side;
    public:
        Square(double side, Color color) :Shape(color)
        {
            set_side(side);
        }
        ~Square() {}
        void set_side(double side)
        {
            this->side = side;
        }
        double get_side()const
        {
            return side;
        }
        double get_area()const override
        {
            return side * side;
        }
        double get_perimeter()const override
        {
            return side * 4;
        }
        void draw()const override
        {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, color);
            for (int i = 0; i < side; i++)
            {
                for (int i = 0; i < side; i++)
                {
                    cout << "* ";
                }
                cout << endl;
            }
            SetConsoleTextAttribute(hConsole, Color::CONSOLE_DEFAULT);
        }

        void info()const override
        {
            cout << typeid(*this).name() << endl;
            cout << "Длина стороны: " << get_side() << endl;
            Shape::info();
        }
    };*/

    class Rectangle :public Shape
    {
        double width;    //ширина прямоугольника
        double height;    //высота прямоугольника
    public:
        Rectangle(double width, double height, Color color) :Shape(color)
        {
            set_width(width);
            set_height(height);
        }
        ~Rectangle() {}
        void set_width(double width)
        {
            this->width = width;
        }
        void set_height(double height)
        {
            this->height = height;
        }
        double get_width()const
        {
            return width;
        }
        double get_height()const
        {
            return height;
        }
        double get_area()const override
        {
            return width * height;
        }
        double get_perimeter()const override
        {
            return (width + height) * 2;
        }
        void draw(int offsetX, int offsetY)const override
        {
            HWND hwnd = FindWindow(NULL, L"Inheritance - Microsoft Visual Studio");
            HDC hdc = GetDC(hwnd);
            HPEN hPen = CreatePen(PS_SOLID, 5, setRGB(color));
            HBRUSH hBrush = CreateSolidBrush(setRGB(color));
            SelectObject(hdc, hPen);
            SelectObject(hdc, hBrush);
            ::Rectangle(hdc, offsetX, offsetY, offsetX + width, offsetY + height);
            DeleteObject(hBrush);
            DeleteObject(hPen);
            ReleaseDC(hwnd, hdc);
        }
        void info(int offsetX, int offsetY)const override
        {
            cout << typeid(*this).name() << endl;
            cout << "Ширина прямоугольника: " << get_width() << endl;
            cout << "Высота прямоугольника: " << get_height() << endl;
            Shape::info(offsetX, offsetY);
        }
    };

    class Circle : public Shape
    {
        double radius;
    public:
        Circle(double radius, Color color) : Shape(color)
        {
            set_radius(radius);
        }
        ~Circle() {}
        void set_radius(double radius)
        {
            this->radius = radius;
        }
        double get_radius()const
        {
            return radius;
        }
        double get_area()const override
        {
            return 3.14 * radius * radius;
        }
        double get_perimeter()const override
        {
            return 2 * 3.14 * radius;
        }
        void draw(int offsetX, int offsetY)const override
        {
            HWND hwnd = FindWindow(NULL, L"Inheritance - Microsoft Visual Studio"); //находит окно с заголовком "Inheritance - Microsoft Visual Studio".
            HDC hdc = GetDC(hwnd);// получает контекст устройства (HDC) для окна.
            HPEN hPen = CreatePen(PS_SOLID, 5, setRGB(color));// создает сплошное перо заданного цвета и толщины 5 пикселей
            HBRUSH hBrush = CreateSolidBrush(setRGB(color));//создает кисть заданного цвета.
            // выбирает созданные перо и кисть в контекст устройства.
            SelectObject(hdc, hPen);
            SelectObject(hdc, hBrush);
            // рисует окружность с заданными смещениями offsetX и offsetY.
            ::Ellipse(hdc, offsetX, offsetY, offsetX + (2 * radius), offsetY + (2 * radius));
            // удаляет созданные кисть и перо, освобождая ресурсы.
            DeleteObject(hBrush);
            DeleteObject(hPen);
            ReleaseDC(hwnd, hdc);// освобождает контекст устройства.
        }
        void info(int offsetX, int offsetY)const override
        {
            cout << typeid(*this).name() << endl;
            cout << "Радиус круга: " << get_radius() << endl;
            Shape::info(offsetX, offsetY);
        }
    };

    class Triangle : public Shape
    {
        double a, b, c;
    public:
        Triangle(double a, double b, double c, Color color) : Shape(color)
        {
            set_sides(a, b, c);
        }
        ~Triangle() {}
        void set_sides(double a, double b, double c)
        {
            this->a = a;
            this->b = b;
            this->c = c;
        }
        double get_side_a()const
        {
            return a;
        }
        double get_side_b()const
        {
            return b;
        }
        double get_side_c()const
        {
            return c;
        }
        double get_area()const override
        {
            double s = get_perimeter() / 2;
            return sqrt(s * (s - a) * (s - b) * (s - c));
        }
        double get_perimeter()const override
        {
            return a + b + c;
        }
        void draw(int offsetX, int offsetY)const override
        {
            HWND hwnd = FindWindow(NULL, L"Inheritance - Microsoft Visual Studio"); // ищет окно с заголовком "Inheritance - Microsoft Visual Studio". Если такое окно не найдено, hwnd будет NULL.
            HDC hdc = GetDC(hwnd); // получает контекст устройства для окна, чтобы можно было рисовать.
            HPEN hPen = CreatePen(PS_SOLID, 5, setRGB(color));// создает сплошное перо шириной 5 пикселей и заданного цвета (color).
            HBRUSH hBrush = CreateSolidBrush(setRGB(color)); // создает кисть заданного цвета.
            //выбирает созданные перо и кисть в контекст устройства.
            SelectObject(hdc, hPen);
            SelectObject(hdc, hBrush);
            // задает координаты вершин треугольника с учетом смещений offsetX и offsetY
            POINT points[3] = { {offsetX, offsetY + 100}, {offsetX + 100, offsetY}, {offsetX + 200, offsetY + 100} };
            ::Polygon(hdc, points, 3);// рисует треугольник по заданным координатам.
            //удаляет созданные кисть и перо, освобождая ресурсы
            DeleteObject(hBrush);
            DeleteObject(hPen);
            ReleaseDC(hwnd, hdc); //освобождает контекст устройства, чтобы другие процессы могли использовать его.
        }
        void info(int offsetX, int offsetY)const override
        {
            cout << typeid(*this).name() << endl;
            cout << "Стороны треугольника: " << get_side_a() << ", " << get_side_b() << ", " << get_side_c() << endl;
            Shape::info(offsetX, offsetY);
        }
    };
}

void main()
{
    setlocale(LC_ALL, "");
    Geometry::Square square(100, Geometry::Color::CONSOLE_RED);
    square.info(100, 100);

    Geometry::Rectangle rect(150, 80, Geometry::Color::CONSOLE_BLUE);
    rect.info(300, 100);

    Geometry::Circle circle(50, Geometry::Color::CONSOLE_GREEN);
    circle.info(500, 100);

    Geometry::Triangle triangle(100, 100, 100, Geometry::Color::CONSOLE_YELLOW);
    triangle.info(700, 100);

}