#include<Windows.h>
#include<iostream>
using namespace std;

namespace Geometry
{
	
	//enum (Enumeration - Перечисление) - это набор именованных констрант типа 'int'
	enum Color
	{
		//CONSOLE_RED = 0xCC,	//старшая 'C' - цвет фона, младшая 'C' - цвет текста.
		//CONSOLE_GREEN = 0xAA,
		//CONSOLE_BLUE = 0x99,
		//CONSOLE_DEFAULT = 0x07

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
	public:
		virtual double get_area() const = 0;
		virtual double get_perimeter()const = 0;
		virtual void draw()const = 0;
		Shape(Color color) :color(color) {}
		virtual ~Shape() {}
		virtual void info()const
		{
			cout << "Площадь фигуры: " << get_area() << endl;
			cout << "Периметр фигуры: " << get_perimeter() << endl;
			draw();
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
		void draw()const override // метод для рисования окружности с использованием GDI-функций Windows:
		{
			//HWND hwnd = GetConsoleWindow();
			HWND hwnd = FindWindow(NULL, L"Inheritance - Microsoft Visual Studio"); //находит окно с заголовком "Inheritance - Microsoft Visual Studio".
			HDC hdc = GetDC(hwnd);// получает контекст устройства (HDC) для окна.
			HPEN hPen = CreatePen(PS_SOLID, 5, color);// создает сплошное перо заданного цвета и толщины 5 пикселей
			HBRUSH hBrush = CreateSolidBrush(color);//создает кисть заданного цвета.
			// выбирает созданные перо и кисть в контекст устройства.
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			// рисует квадрат, который начинается в точке (500, 100) а нижний правый угол — в точке (500 + side, 100 + side).
			::Rectangle(hdc, 600, 200, 1000, 600);
			// удаляет созданные кисть и перо, освобождая ресурсы.
			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hwnd, hdc);// освобождает контекст устройства.
		}

		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Длина стороны: " << get_side() << endl;
			Shape::info();
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
		double width;	//ширина прямоугольника
		double height;	//высота прямоугольника
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
		void draw()const override
		{
			//WinGDI - Windows Grphics Device Interface
			//1. Получаем окно консоли:

			//HWND hwnd = GetConsoleWindow();	//Функция GetConsoleWindow() получает окно консоли
			HWND hwnd = FindWindow(NULL, L"Inheritance - Microsoft Visual Studio");
			
			//2. Для того чтобы рисовать, нужен контекст устройства (Device Context), 
			//	 который есть у каждого окна. Констекст устройства можно получить при помощи функции GetDC();
			HDC hdc = GetDC(hwnd);	//Получаем контекст окна консоли
			//Контекст устройства - это то, на чем мы будем рисовать.
			//3. Теперь нам нужно то, чем мы будем рисовать:
			HPEN hPen = CreatePen(PS_SOLID, 5, color);	//hPen		- рисует контур фигуры;
			//SP_SOLID	- сплошная линия
			//5			- толщина линии 5 пикселов
			HBRUSH hBrush = CreateSolidBrush(color);	//hBrush	- рисует заливку фигуры (SolidBrush - сплощной цвет)
			//4. Выбираем чем, и на чем мы будем рисовать:
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			//5. Рисуем фигуру:
			::Rectangle(hdc, 500, 100, 900, 300);	//:: - Global Scope (Глобальное пространство имен)
			//6. hdc, hPen и hBrush занимают ресурсы, и после того, как мы ими воспользовались, ресурсы нужно освободить:
			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hwnd, hdc);
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
		void draw()const override // метод для рисования окружности с использованием GDI-функций Windows:
		{
			//HWND hwnd = GetConsoleWindow();
			HWND hwnd = FindWindow(NULL, L"Inheritance - Microsoft Visual Studio"); //находит окно с заголовком "Inheritance - Microsoft Visual Studio".
			HDC hdc = GetDC(hwnd);// получает контекст устройства (HDC) для окна.
			HPEN hPen = CreatePen(PS_SOLID, 5, color);// создает сплошное перо заданного цвета и толщины 5 пикселей
			HBRUSH hBrush = CreateSolidBrush(color);//создает кисть заданного цвета.
			// выбирает созданные перо и кисть в контекст устройства.
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			// рисует окружность, который начинается в точке (500, 100) и имеет ширину и высоту, равные удвоенному радиусу.
			::Ellipse(hdc, 500, 100, 500 + (2 * radius), 100 + (2 * radius));
			// удаляет созданные кисть и перо, освобождая ресурсы.
			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hwnd, hdc);// освобождает контекст устройства.
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
		void draw()const override
		{
			//HWND hwnd = GetConsoleWindow();
			HWND hwnd = FindWindow(NULL, L"Inheritance - Microsoft Visual Studio"); // ищет окно с заголовком "Inheritance - Microsoft Visual Studio". Если такое окно не найдено, hwnd будет NULL.
			HDC hdc = GetDC(hwnd); // получает контекст устройства для окна, чтобы можно было рисовать.
			HPEN hPen = CreatePen(PS_SOLID, 5, color);// создает сплошное перо шириной 5 пикселей и заданного цвета (color).
			HBRUSH hBrush = CreateSolidBrush(color); // создает кисть заданного цвета.
			//выбирает созданные перо и кисть в контекст устройства.
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			POINT points[3] = { {500, 200}, {600, 300}, {700, 200} };// задает координаты вершин треугольника
			::Polygon(hdc, points, 3);// рисует треугольник по заданным координатам.
			//удаляет созданные кисть и перо, освобождая ресурсы
			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hwnd, hdc); //освобождает контекст устройства, чтобы другие процессы могли использовать его.
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Стороны треугольника: " << get_side_a() << ", " << get_side_b() << ", " << get_side_c() << endl;
			Shape::info();
		}
	};
}

void main()
{
	setlocale(LC_ALL, "");
	//Shape shape(Color::CONSOLE_RED);
	Geometry::Square square(500, Geometry::Color::CONSOLE_YELLOW);
	/*cout << "Длина стороны:    " << square.get_side() << endl;
	cout << "Площадь квадрата: " << square.get_area() << endl;
	cout << "Периметр квадрата: " << square.get_perimeter() << endl;
	square.draw();*/
	square.info();

	Geometry::Rectangle rect(100, 50, Geometry::Color::CONSOLE_BLUE);
	rect.info();

	Geometry::Circle circle(100, Geometry::Color::CONSOLE_GREEN);
	circle.info();

	Geometry::Triangle triangle(100, 100, 100, Geometry::Color::CONSOLE_RED);
	triangle.info();
}