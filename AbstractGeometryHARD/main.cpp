#define _USE_MATH_DEFINES
#include <Windows.h>
#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

namespace Geometry
{
    // Определяем ограничения 
    const unsigned int MAX_X = 500;
    const unsigned int MAX_Y = 500;
    const unsigned int MIN_SIZE = 10;
    const unsigned int MAX_SIZE = 200;

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

    public:
        // Чисто-виртуальные функции (Pure virtual function)
        virtual double get_area() const = 0;
        virtual double get_perimeter() const = 0;
        virtual void draw(HDC hdc) const = 0;
        /////////////////////////////////////////////
        Shape(SHAPE_TAKE_PARAMETERS) : color(color)
        {
            set_start_x(start_x);
            set_start_y(start_y);
            set_line_width(line_width);
        }
        virtual ~Shape() {}

        // Encapsulation:
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
            if (start_x < MAX_X)
                this->start_x = start_x;
            else
                this->start_x = MAX_X - 1; // нужно убедится что не выходит за пределы
        }
        void set_start_y(unsigned int start_y)
        {
            if (start_y < MAX_Y)
                this->start_y = start_y;
            else
                this->start_y = MAX_Y - 1; // нужно убедится что не выходит за пределы
        }
        void set_line_width(unsigned int line_width)
        {
            this->line_width = line_width;
        }

        // Methods:

        virtual void info() const
        {
            cout << "Площадь фигуры: " << get_area() << endl;
            cout << "Периметр фигуры: " << get_perimeter() << endl;
        }
    };

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
            if (width >= MIN_SIZE && width <= MAX_SIZE)
                this->width = width;
            else
                this->width = (width < MIN_SIZE) ? MIN_SIZE : MAX_SIZE;
        }
        void set_height(double height)
        {
            if (height >= MIN_SIZE && height <= MAX_SIZE)
                this->height = height;
            else
                this->height = (height < MIN_SIZE) ? MIN_SIZE : MAX_SIZE;
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
        void draw(HDC hdc) const override
        {
            //WinGDI - Windows Graphics Device Interface
            //1) Получаем окно консоли:
            //HWND hwnd = GetConsoleWindow();  //Функция GetConsoleWindow() получает окно консоли
            //HWND hwnd = FindWindow(NULL, L"Inheritance - Microsoft Visual Studio");
            //2) Для того чтобы рисовать, нужен контекст устройства (Device Context), 
            //   который есть у каждого окна. Контекст устройства можно получить при помощи функции GetDC();
            //HDC hdc = GetDC(hwnd);  //Получаем контекст окна консоли
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

            //ReleaseDC(hwnd, hdc);
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
            if (radius >= MIN_SIZE && radius <= MAX_SIZE)
                this->radius = radius;
            else
                this->radius = (radius < MIN_SIZE) ? MIN_SIZE : MAX_SIZE;
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
            return M_PI * get_diameter();
        }
        void draw(HDC hdc) const override
        {
            //HWND hwnd = FindWindow(NULL, L"Inheritance - Microsoft Visual Studio"); //находит окно с заголовком "Inheritance - Microsoft Visual Studio".
            //HDC hdc = GetDC(hwnd);// получает контекст устройства (HDC) для окна.
            HPEN hPen = CreatePen(PS_SOLID, 5, color);// создает сплошное перо заданного цвета и толщины 5 пикселей
            HBRUSH hBrush = CreateSolidBrush(color);//создает кисть заданного цвета.
            // выбирает созданные перо и кисть в контекст устройства.
            SelectObject(hdc, hPen);
            SelectObject(hdc, hBrush);
            // рисует окружность с заданными смещениями 
            ::Ellipse(hdc, start_x, start_y, start_x + get_diameter(), start_y + get_diameter());
            // удаляет созданные кисть и перо, освобождая ресурсы.
            DeleteObject(hBrush);
            DeleteObject(hPen);
            //ReleaseDC(hwnd, hdc);// освобождает контекст устройства.
        }
        void info() const override
        {
            cout << typeid(*this).name() << endl;
            cout << "Радиус круга:  " << get_radius() << endl;
            cout << "Диаметр круга:" << get_diameter() << endl;
            Shape::info();
        }
    };

    class Triangle : public Shape
    {
        double a, b, c;
    public:
        Triangle(double a, double b, double c, SHAPE_TAKE_PARAMETERS)
            : Shape(SHAPE_GIVE_PARAMETERS), a(a), b(b), c(c) {}

        ~Triangle() {}
        void set_sides(double a, double b, double c)
        {
            this->a = a;
            this->b = b;
            this->c = c;
        }
        double get_side_a() const
        {
            return a;
        }
        double get_side_b() const
        {
            return b;
        }
        double get_side_c() const
        {
            return c;
        }
        double get_area() const override
        {
            double s = get_perimeter() / 2;
            return sqrt(s * (s - a) * (s - b) * (s - c));
        }
        double get_perimeter() const override
        {
            return a + b + c;
        }
        void draw(HDC hdc) const override
        {
            //HWND hwnd = FindWindow(NULL, L"Inheritance - Microsoft Visual Studio"); // ищет окно с заголовком "Inheritance - Microsoft Visual Studio". Если такое окно не найдено, hwnd будет NULL.
            //HDC hdc = GetDC(hwnd); // получает контекст устройства для окна, чтобы можно было рисовать.
            HPEN hPen = CreatePen(PS_SOLID, 5, color);// создает сплошное перо шириной 5 пикселей и заданного цвета (color).
            HBRUSH hBrush = CreateSolidBrush(color); // создает кисть заданного цвета.
            //выбирает созданные перо и кисть в контекст устройства.
            SelectObject(hdc, hPen);
            SelectObject(hdc, hBrush);
            // задает координаты вершин треугольника с учетом смещений 
            POINT points[3] = { {start_x + 300, start_y + 100}, {start_x + 400, start_y}, {start_x + 500, start_y + 100} };
            ::Polygon(hdc, points, 3);// рисует треугольник по заданным координатам.
            //удаляет созданные кисть и перо, освобождая ресурсы
            DeleteObject(hBrush);
            DeleteObject(hPen);
            //ReleaseDC(hwnd, hdc); //освобождает контекст устройства, чтобы другие процессы могли использовать его.
        }
        void info() const override
        {
            cout << typeid(*this).name() << endl;
            cout << "Стороны треугольника: " << get_side_a() << ", " << get_side_b() << ", " << get_side_c() << endl;
            Shape::info();
        }
    };
}

void DrawShapesToBitmap(const wchar_t* filename)
{
    // Размер изображения
    int width = 1080;
    int height = 900;

    // Создание устройства памяти и совместимого контекста устройства
    HDC hdc = GetDC(NULL);
    HDC memDC = CreateCompatibleDC(hdc);
    HBITMAP hBitmap = CreateCompatibleBitmap(hdc, width, height);
    SelectObject(memDC, hBitmap);

    // Заливка фона белым цветом
    HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));
    RECT rect = { 0, 0, width, height };
    FillRect(memDC, &rect, hBrush);
    DeleteObject(hBrush);

    // Рисование фигур
    Geometry::Square square(100, 100, 100, 5, Geometry::Color::RED);
    Geometry::Rectangle rectShape(150, 80, 300, 100, 5, Geometry::Color::BLUE);
    Geometry::Circle circle(50, 500, 100, 5, Geometry::Color::GREEN);
    Geometry::Triangle triangle(100, 100, 100, 350, 100, 5, Geometry::Color::YELLOW);

    square.draw(memDC);
    rectShape.draw(memDC);
    circle.draw(memDC);
    triangle.draw(memDC);

    // Сохранение изображения в файл BMP
    BITMAPFILEHEADER bfHeader;
    BITMAPINFOHEADER biHeader;
    BITMAPINFO bInfo;
    memset(&bfHeader, 0, sizeof(BITMAPFILEHEADER));
    memset(&biHeader, 0, sizeof(BITMAPINFOHEADER));
    memset(&bInfo, 0, sizeof(BITMAPINFO));

    

    GlobalUnlock(hDIB);
    GlobalFree(hDIB);

    // Освобождение ресурсов
    DeleteObject(hBitmap);
    DeleteDC(memDC);
    ReleaseDC(NULL, hdc);
}

void main()
{
    setlocale(LC_ALL, "");

    // Имя файла для сохранения BMP изображения
    const wchar_t* filename = L"shapes.bmp";

    // Рисование фигур в BMP файл
    DrawShapesToBitmap(filename);

    // Открытие BMP файла в Microsoft Paint
    ShellExecute(NULL, L"open", L"mspaint.exe", filename, NULL, SW_SHOW);

}
