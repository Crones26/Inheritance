#include <Windows.h>
#include <iostream>
#include <fstream>
using namespace std;

namespace Geometry
{
    enum Color
    {
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
        virtual void draw(HDC hdc, int offsetX, int offsetY)const = 0;
        Shape(Color color) :color(color) {}
        virtual ~Shape() {}
        virtual void info()const
        {
            cout << "Площадь фигуры: " << get_area() << endl;
            cout << "Периметр фигуры: " << get_perimeter() << endl;
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
        void draw(HDC hdc, int offsetX, int offsetY)const override
        {
            HPEN hPen = CreatePen(PS_SOLID, 5, setRGB(color));// создает сплошное перо заданного цвета и толщины 5 пикселей
            HBRUSH hBrush = CreateSolidBrush(setRGB(color));// создает кисть заданного цвета.
            // выбирает созданные перо и кисть в контекст устройства.
            SelectObject(hdc, hPen);
            SelectObject(hdc, hBrush);
            // рисует квадрат с заданными смещениями offsetX и offsetY.
            ::Rectangle(hdc, offsetX, offsetY, offsetX + side, offsetY + side);
            // удаляет созданные кисть и перо, освобождая ресурсы.
            DeleteObject(hBrush);
            DeleteObject(hPen);
        }
        void info()const override
        {
            cout << typeid(*this).name() << endl;
            cout << "Длина стороны: " << get_side() << endl;
            Shape::info();
        }
    };

    class Rectangle :public Shape
    {
        double width;    //ширина прямоугольника
        double height;   //высота прямоугольника
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
        void draw(HDC hdc, int offsetX, int offsetY)const override
        {
            HPEN hPen = CreatePen(PS_SOLID, 5, setRGB(color));// создает сплошное перо заданного цвета и толщины 5 пикселей
            HBRUSH hBrush = CreateSolidBrush(setRGB(color));// создает кисть заданного цвета.
            // выбирает созданные перо и кисть в контекст устройства.
            SelectObject(hdc, hPen);
            SelectObject(hdc, hBrush);
            // рисует прямоугольник с заданными смещениями offsetX и offsetY.
            ::Rectangle(hdc, offsetX, offsetY, offsetX + width, offsetY + height);
            // удаляет созданные кисть и перо, освобождая ресурсы.
            DeleteObject(hBrush);
            DeleteObject(hPen);
        }
        void info()const override
        {
            cout << typeid(*this).name() << endl;
            cout << "Ширина прямоугольника: " << get_width() << endl;
            cout << "Высота прямоугольника: " << get_height() << endl;
            Shape::info();
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
        void draw(HDC hdc, int offsetX, int offsetY)const override
        {
            HPEN hPen = CreatePen(PS_SOLID, 5, setRGB(color));// создает сплошное перо заданного цвета и толщины 5 пикселей
            HBRUSH hBrush = CreateSolidBrush(setRGB(color));// создает кисть заданного цвета.
            // выбирает созданные перо и кисть в контекст устройства.
            SelectObject(hdc, hPen);
            SelectObject(hdc, hBrush);
            // рисует окружность с заданными смещениями offsetX и offsetY.
            ::Ellipse(hdc, offsetX, offsetY, offsetX + (2 * radius), offsetY + (2 * radius));
            // удаляет созданные кисть и перо, освобождая ресурсы.
            DeleteObject(hBrush);
            DeleteObject(hPen);
        }
        void info()const override
        {
            cout << typeid(*this).name() << endl;
            cout << "Радиус круга: " << get_radius() << endl;
            Shape::info();
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
        void draw(HDC hdc, int offsetX, int offsetY)const override
        {
            HPEN hPen = CreatePen(PS_SOLID, 5, setRGB(color));// создает сплошное перо заданного цвета и толщины 5 пикселей
            HBRUSH hBrush = CreateSolidBrush(setRGB(color));// создает кисть заданного цвета.
            // выбирает созданные перо и кисть в контекст устройства.
            SelectObject(hdc, hPen);
            SelectObject(hdc, hBrush);
            // задает координаты вершин треугольника с учетом смещений offsetX и offsetY.
            POINT points[3] = { {offsetX, offsetY + 100}, {offsetX + 100, offsetY}, {offsetX + 200, offsetY + 100} };
            // рисует треугольник по заданным координатам.
            ::Polygon(hdc, points, 3);
            // удаляет созданные кисть и перо, освобождая ресурсы.
            DeleteObject(hBrush);
            DeleteObject(hPen);
        }
        void info()const override
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
    Geometry::Square square(100, Geometry::Color::CONSOLE_YELLOW);
    Geometry::Rectangle rectShape(150, 80, Geometry::Color::CONSOLE_BLUE);
    Geometry::Circle circle(50, Geometry::Color::CONSOLE_GREEN);
    Geometry::Triangle triangle(100, 100, 100, Geometry::Color::CONSOLE_RED);

    square.draw(memDC, 100, 100);
    rectShape.draw(memDC, 300, 100);
    circle.draw(memDC, 500, 100);
    triangle.draw(memDC, 700, 100);

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