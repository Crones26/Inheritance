#define _USE_MATH_DEFINES
#include <Windows.h>
#include <iostream>
using namespace std;

namespace Geometry
{
    //enum (Enumeration - Перечисление) - это набор именованных констант типа 'int'
    enum Color
    {
        //Здесь используются 8-битные значения, которые могут интерпретироваться по-разному(что не есть хорошо)
        CONSOLE_RED = 0xCC, // старшая 'C' - цвет фона, младшая 'C' - цвет текста.
        CONSOLE_GREEN = 0xAA,
        CONSOLE_BLUE = 0x99,
        CONSOLE_DEFAULT = 0x07,
        RED = 0x000000FF,
        GREEN = 0x0000FF00,
        BLUE = 0x00FF0000,
        YELLOW = 0x0000FFFF,
    };

#define SHAPE_TAKE_PARAMETERS unsigned int start_x, unsigned int start_y, unsigned int line_width, Color color
#define SHAPE_GIVE_PARAMETERS start_x, start_y, line_width, color

    class Shape
    {
    protected:
        unsigned int start_x;
        unsigned int start_y;
        unsigned int line_width;
        Color color;

        // Определяем ограничения 
        static const int MIN_START_X = 100;
        static const int MAX_START_X = 1000;
        static const int MIN_START_Y = 100;
        static const int MAX_START_Y = 500;
        static const int MIN_LINE_WIDTH = 1;
        static const int MAX_LINE_WIDTH = 32;
        static const int MIN_SIZE = 50;
        static const int MAX_SIZE = 550;
        static int count;

    public:
        // Чисто-виртуальные функции (Pure virtual function)
        virtual double get_area() const = 0;
        virtual double get_perimeter() const = 0;
        virtual void draw() const = 0;
        /////////////////////////////////////////////
        Shape(SHAPE_TAKE_PARAMETERS) : start_x(start_x), start_y(start_y), line_width(line_width), color(color)
        {
            set_start_x(start_x);
            set_start_y(start_y);
            set_line_width(line_width);
            count++;
        }
        virtual ~Shape()
        {
            count--;
        }
        static int get_count()
        {
            return count;
        }
        //          Encapsulation
        unsigned int get_start_x() const
        {
            return start_x;
        }
        unsigned int get_start_y() const
        {
            return start_y;
        }
        unsigned int get_line_width() const
        {
            return line_width;
        }
        void set_start_x(unsigned int start_x)
        {
            if (start_x < MIN_START_X) start_x = MIN_START_X;
            if (start_x > MAX_START_X) start_x = MAX_START_X;
            this->start_x = start_x;
        }
        void set_start_y(unsigned int start_y)
        {
            if (start_y < MIN_START_Y) start_y = MIN_START_Y;
            if (start_y > MAX_START_Y) start_y = MAX_START_Y;
            this->start_y = start_y;
        }
        void set_line_width(unsigned int line_width)
        {
            if (line_width < MIN_LINE_WIDTH) line_width = MIN_LINE_WIDTH;
            if (line_width > MAX_LINE_WIDTH) line_width = MAX_LINE_WIDTH;
            this->line_width = line_width;
        }
        int filter_size(int size)const
        {
            return
                size < MIN_SIZE ? MIN_SIZE :
                size > MAX_SIZE ? MAX_SIZE :
                size;
        }
        //              Methods
        virtual void info() const
        {
            cout << "Площадь фигуры: " << get_area() << endl;
            cout << "Периметр фигуры: " << get_perimeter() << endl;
            draw();
        }
    };

    int Shape::count = 0;

    class Rectangle : public Shape
    {
        double width; // ширина прямоугольника
        double height; // высота прямоугольника
    public:
        Rectangle(double width, double height, SHAPE_TAKE_PARAMETERS) : Shape(SHAPE_GIVE_PARAMETERS)
        {
            set_width(width);
            set_height(height);
        }
        ~Rectangle() {}
        void set_width(double width)
        {
            this->width = filter_size(width);
        }
        void set_height(double height)
        {
            this->height = filter_size(height);
        }
        double get_width() const
        {
            return width;
        }
        double get_height() const
        {
            return height;
        }
        double get_area() const override
        {
            return width * height;
        }
        double get_perimeter() const override
        {
            return (width + height) * 2;
        }
        void draw() const override
        {
            //WinGDI - Windows Graphics Device Interface
            //1) Получаем окно консоли:
            //HWND hwnd = GetConsoleWindow();  //Функция GetConsoleWindow() получает окно консоли
            HWND hwnd = FindWindow(NULL, L"Inheritance - Microsoft Visual Studio");
            //2) Для того чтобы рисовать, нужен контекст устройства (Device Context), 
            //   который есть у каждого окна. Контекст устройства можно получить при помощи функции GetDC();
            HDC hdc = GetDC(hwnd);  //Получаем контекст окна консоли
            //Контекст устройства - это то, на чем мы будем рисовать.

            //3) Теперь нам нужно то, чем мы будем рисовать:
            HPEN hPen = CreatePen(PS_SOLID, line_width, color); //hPen - рисует контур фигуры;
            //PS_SOLID - сплошная линия
            //line_width - толщина линии в пикселах
            HBRUSH hBrush = CreateSolidBrush(color); //hBrush - рисует заливку фигуры (SolidBrush - сплошной цвет)

            //4) Выбираем чем, и на чем мы будем рисовать:
            SelectObject(hdc, hPen);
            SelectObject(hdc, hBrush);

            //5) Рисуем фигуру:
            ::Rectangle(hdc, start_x, start_y, start_x + width, start_y + height); //:: - Global Scope (Глобальное пространство имен)

            //6) hdc, hPen и hBrush занимают ресурсы, и после того, как мы ими воспользовались, ресурсы нужно освободить:
            DeleteObject(hBrush);
            DeleteObject(hPen);

            ReleaseDC(hwnd, hdc);
        }
        void info() const override
        {
            cout << typeid(*this).name() << endl;
            cout << "Ширина прямоугольника: " << get_width() << endl;
            cout << "Высота прямоугольника: " << get_height() << endl;
            Shape::info();
        }
    };

    //class Square : public Shape
    //{
    //    double side;
    //public:
    //    Square(double side, Color color) :Shape(color)
    //    {
    //        set_side(side);
    //    }
    //    ~Square() {}
    //    void set_side(double side)
    //    {
    //        this->side = side;
    //    }
    //    double get_side()const
    //    {
    //        return side;
    //    }
    //    double get_area()const override
    //    {
    //        return side * side;
    //    }
    //    double get_perimeter()const override
    //    {
    //        return side * 4;
    //    }
    //    void draw(int offsetX, int offsetY)const override
    //    {
    //        HWND hwnd = FindWindow(NULL, L"Inheritance - Microsoft Visual Studio"); //находит окно с заголовком "Inheritance - Microsoft Visual Studio".
    //        HDC hdc = GetDC(hwnd);// получает контекст устройства (HDC) для окна.
    //        HPEN hPen = CreatePen(PS_SOLID, 5, setRGB(color));// создает сплошное перо заданного цвета и толщины 5 пикселей
    //        HBRUSH hBrush = CreateSolidBrush(setRGB(color));//создает кисть заданного цвета.
    //        // выбирает созданные перо и кисть в контекст устройства.
    //        SelectObject(hdc, hPen);
    //        SelectObject(hdc, hBrush);
    //        // рисует квадрат с заданными смещениями offsetX и offsetY.
    //        ::Rectangle(hdc, offsetX, offsetY, offsetX + side, offsetY + side);
    //        // удаляет созданные кисть и перо, освобождая ресурсы.
    //        DeleteObject(hBrush);
    //        DeleteObject(hPen);
    //        ReleaseDC(hwnd, hdc);// освобождает контекст устройства.
    //    }
    //    void info(int offsetX, int offsetY)const override
    //    {
    //        cout << typeid(*this).name() << endl;
    //        cout << "Длина стороны: " << get_side() << endl;
    //        Shape::info(offsetX, offsetY);
    //    }
    //};

    /*class Square : public Shape
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

    class Square : public Rectangle
    {
    public:
        Square(double side, SHAPE_TAKE_PARAMETERS) : Rectangle(side, side, SHAPE_GIVE_PARAMETERS) {}
        ~Square() {}
    };

    class Circle : public Shape
    {
        double radius;
    public:
        Circle(double radius, SHAPE_TAKE_PARAMETERS) : Shape(SHAPE_GIVE_PARAMETERS)
        {
            set_radius(radius);
        }
        ~Circle() {}
        void set_radius(double radius)
        {
            this->radius = filter_size(radius);
        }
        double get_radius() const
        {
            return radius;
        }
        double get_diameter() const
        {
            return 2 * radius;
        }
        double get_area() const override
        {
            return M_PI * radius * radius;
        }
        double get_perimeter() const override
        {
            return 2 * M_PI * radius;
        }
        void draw() const override
        {
            HWND hwnd = FindWindow(NULL, L"Inheritance - Microsoft Visual Studio"); //находит окно с заголовком "Inheritance - Microsoft Visual Studio".
            HDC hdc = GetDC(hwnd);// получает контекст устройства (HDC) для окна.
            HPEN hPen = CreatePen(PS_SOLID, line_width, color);// создает сплошное перо заданного цвета и толщины 5 пикселей
            HBRUSH hBrush = CreateSolidBrush(color);//создает кисть заданного цвета.
            // выбирает созданные перо и кисть в контекст устройства.
            SelectObject(hdc, hPen);
            SelectObject(hdc, hBrush);
            // рисует окружность с заданными смещениями 
            ::Ellipse(hdc, start_x, start_y, start_x + get_diameter(), start_y + get_diameter());
            // удаляет созданные кисть и перо, освобождая ресурсы.
            DeleteObject(hBrush);
            DeleteObject(hPen);
            ReleaseDC(hwnd, hdc);// освобождает контекст устройства.
        }
        void info() const override
        {
            cout << typeid(*this).name() << endl;
            cout << "Радиус круга: " << get_radius() << endl;
            cout << "Диаметр круга: " << get_diameter() << endl;
            Shape::info();
        }
    };

    class Triangle : public Shape
    {
    public:
        virtual double get_height()const = 0;
        Triangle(SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS) {}
        ~Triangle() {}
        void info()const override
        {
            cout << "Высота треугольника: " << get_height() << endl;
            Shape::info();
        }
    };

    class EquilateralTriangle : public Triangle
    {
        double side;
    public:
        EquilateralTriangle(double side, SHAPE_TAKE_PARAMETERS) : Triangle(SHAPE_GIVE_PARAMETERS)
        {
            set_side(side);
        }
        ~EquilateralTriangle() {}
        void set_side(double side)
        {
            this->side = filter_size(side);
        }
        double get_side() const
        {
            return side;
        }
        double get_height() const override
        {
            return sqrt(3) / 2 * side;
        }
        double get_area() const override
        {
            return sqrt(3) / 4 * side * side;
        }
        double get_perimeter() const override
        {
            return 3 * side;
        }
        void draw() const override
        {
            HWND hwnd = FindWindow(NULL, L"Inheritance - Microsoft Visual Studio");
            HDC hdc = GetDC(hwnd);
            HPEN hPen = CreatePen(PS_SOLID, line_width, color);
            HBRUSH hBrush = CreateSolidBrush(color);

            SelectObject(hdc, hPen);
            SelectObject(hdc, hBrush);

            POINT points[] =
            {
                {start_x, start_y + side},
                {start_x + side, start_y + side},
                {start_x + side / 2, start_y + side - get_height()}
            };
            ::Polygon(hdc, points, 3);

            DeleteObject(hBrush);
            DeleteObject(hPen);
            ReleaseDC(hwnd, hdc);
        }
        void info() const override
        {
            cout << typeid(*this).name() << endl;
            cout << "Сторона равностороннего треугольника: " << get_side() << endl;
            Triangle::info();
        }
    };

    class IsoscelesTriangle : public Triangle
    {
        double base;
        double height;
    public:
        IsoscelesTriangle(double base, double height, SHAPE_TAKE_PARAMETERS) : Triangle(SHAPE_GIVE_PARAMETERS)
        {
            set_base(base);
            set_height(height);
        }
        ~IsoscelesTriangle() {}
        void set_base(double base)
        {
            this->base = filter_size(base);
        }
        void set_height(double height)
        {
            this->height = filter_size(height);
        }
        double get_base() const
        {
            return base;
        }
        double get_height() const override
        {
            return height;
        }
        double get_area() const override
        {
            return base * height / 2;
        }
        double get_perimeter() const override
        {
            return base + 2 * sqrt((base / 2) * (base / 2) + height * height);
        }
        void draw() const override
        {
            HWND hwnd = FindWindow(NULL, L"Inheritance - Microsoft Visual Studio");
            HDC hdc = GetDC(hwnd);
            HPEN hPen = CreatePen(PS_SOLID, line_width, color);
            HBRUSH hBrush = CreateSolidBrush(color);

            SelectObject(hdc, hPen);
            SelectObject(hdc, hBrush);

            POINT points[] = 
            {
                {start_x, start_y + height},
                {start_x + base, start_y + height},
                {start_x + base / 2, start_y}
            };
            ::Polygon(hdc, points, 3);

            DeleteObject(hBrush);
            DeleteObject(hPen);
            ReleaseDC(hwnd, hdc);
        }
        void info() const override
        {
            cout << typeid(*this).name() << endl;
            cout << "Основание равнобедренного треугольника: " << get_base() << endl;
            cout << "Высота равнобедренного треугольника: " << get_height() << endl;
            Triangle::info();
        }
    };

    class RightTriangle : public Triangle
    {
        double base;
        double height;
    public:
        RightTriangle(double base, double height, SHAPE_TAKE_PARAMETERS) : Triangle(SHAPE_GIVE_PARAMETERS)
        {
            set_base(base);
            set_height(height);
        }
        ~RightTriangle() {}
        void set_base(double base)
        {
            this->base = filter_size(base);
        }
        void set_height(double height)
        {
            this->height = filter_size(height);
        }
        double get_base() const
        {
            return base;
        }
        double get_height() const override
        {
            return height;
        }
        double get_area() const override
        {
            return base * height / 2;
        }
        double get_perimeter() const override
        {
            return base + height + sqrt(base * base + height * height);
        }
        void draw() const override
        {
            HWND hwnd = FindWindow(NULL, L"Inheritance - Microsoft Visual Studio");
            HDC hdc = GetDC(hwnd);
            HPEN hPen = CreatePen(PS_SOLID, line_width, color);
            HBRUSH hBrush = CreateSolidBrush(color);

            SelectObject(hdc, hPen);
            SelectObject(hdc, hBrush);

            POINT points[] = 
            {
                {start_x, start_y + height},
                {start_x + base, start_y + height},
                {start_x, start_y}
            };
            ::Polygon(hdc, points, 3);

            DeleteObject(hBrush);
            DeleteObject(hPen);
            ReleaseDC(hwnd, hdc);
        }
        void info() const override
        {
            cout << typeid(*this).name() << endl;
            cout << "Основание прямоугольного треугольника: " << get_base() << endl;
            cout << "Высота прямоугольного треугольника: " << get_height() << endl;
            Triangle::info();
        }
    };
}

void main()
{
    setlocale(LC_ALL, "");
    //Shape shape(Color::CONSOLE_RED);
    // Квадрат
    Geometry::Square square(50, 100, 100, 5, Geometry::Color::RED);
    /*cout << "Длина стороны:    " << square.get_side() << endl;
    cout << "Площадь квадрата: " << square.get_area() << endl;
    cout << "Периметр квадрата: " << square.get_perimeter() << endl;
    square.draw();*/
    square.info();
    // Прямоугольник
    Geometry::Rectangle rect(100, 50, 200, 100, 10, Geometry::Color::BLUE);
    rect.info();
    // Круг
    Geometry::Circle disk(40, 400, 100, 5, Geometry::Color::YELLOW); // Радиус круга изменен на 50
    disk.info();
    // Равносторонний треугольник
    Geometry::EquilateralTriangle equilateral_triangle(150, 400, 250, 5, Geometry::Color::YELLOW);
    equilateral_triangle.info();
    // Равнобедренный треугольник
    Geometry::IsoscelesTriangle isosceles_triangle(100, 150, 100, 250, 5, Geometry::Color::RED);
    isosceles_triangle.info();
    // Прямоугольный треугольник
    Geometry::RightTriangle right_triangle(100, 150, 250, 250, 5, Geometry::Color::BLUE);
    right_triangle.info();

    cout << "Количество фигур: " << Geometry::Shape::get_count() << endl;
}
