#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

// Перечислимый тип для операций
enum Operation {
    P = 1,
    S = 2
};

/**
* @brief Вычисляет периметр треугольника по координатам вершин
* @param x1, y1 - координаты первой вершины
* @param x2, y2 - координаты второй вершины  
* @param x3, y3 - координаты третьей вершины
* @return периметр треугольника
*/
float Pv(float x1, float y1, float x2, float y2, float x3, float y3);

/**
* @brief Вычисляет площадь треугольника по координатам вершин
* @param x1, y1 - координаты первой вершины
* @param x2, y2 - координаты второй вершины
* @param x3, y3 - координаты третьей вершины
* @return площадь треугольника
*/
float Sv(float x1, float y1, float x2, float y2, float x3, float y3);

/**
* @brief Основная функция программы
* @return 0 при успешном выполнении
*/
int main() {
    float x1 = 0;
    float y1 = 0;
    float y2 = 0;
    float x2 = 0;
    float y3 = 0;
    float x3 = 0;
    int w;
    
    // Ввод координат треугольника
    cout << "Введите координаты первой вершины (x1 y1): ";
    cin >> x1 >> y1;
    
    cout << "Введите координаты второй вершины (x2 y2): ";
    cin >> x2 >> y2;
    
    cout << "Введите координаты третьей вершины (x3 y3): ";
    cin >> x3 >> y3;
    
    // Правильно или нет
    if (cin.fail()) {
        cout << "Ошибка! Нужно вводить только числа!" << endl;
        return 1; // Завершаем программу с ошибкой
    }
    
    // Выбор 
    cout << "Что вы хотите вычислить?" << endl;
    cout << "1 - Периметр треугольника" << endl;
    cout << "2 - Площадь треугольника" << endl;
    cout << "Ваш выбор (1 или 2): ";
    cin >> w;
    
    // Правильно или нет
    if (w != 1 && w != 2) {
        cout << "Ошибка! Нужно выбрать 1 или 2!" << endl;
        return 1; // Завершаем программу с ошибкой
    }
    
    //Информация о треугольнике
    cout << "Информация о треугольнике" << endl;
    cout << "Вершина A: (" << x1 << ", " << y1 << ")" << endl;
    cout << "Вершина B: (" << x2 << ", " << y2 << ")" << endl;
    cout << "Вершина C: (" << x3 << ", " << y3 << ")" << endl;
    
    // Выполняем операцию
    if (w == 1) {
        float P = Pv(x1, y1, x2, y2, x3, y3);
        cout << "Периметр треугольника: " << P << endl;
    } 
    else if (w == 2) {
        float S = Sv(x1, y1, x2, y2, x3, y3);
        cout << "Площадь треугольника: " << S << endl;
    }
    
    return 0;
}

float Pv(float x1, float y1, float x2, float y2, float x3, float y3) {
    // Длины сторон
    float a = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    float b = sqrt(pow(x3 - x2, 2) + pow(y3 - y2, 2));
    float c = sqrt(pow(x1 - x3, 2) + pow(y1 - y3, 2));
    
    cout << "Длина стороны AB: " << a << endl;
    cout << "Длина стороны BC: " << b << endl;
    cout << "Длина стороны CA: " << c << endl;
    
    // Периметр = сумма длин всех сторон
    return a + b + c;
}

float Sv(float x1, float y1, float x2, float y2, float x3, float y3) {
    // Вычисляем длины сторон
    float a = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    float b = sqrt(pow(x3 - x2, 2) + pow(y3 - y2, 2));
    float c = sqrt(pow(x1 - x3, 2) + pow(y1 - y3, 2));
    
    cout << "Длина стороны AB: " << a << endl;
    cout << "Длина стороны BC: " << b << endl;
    cout << "Длина стороны CA: " << c << endl;
    
    // Формулу Герона для площади
    float p = (a + b + c) / 2; // Полупериметр
    float S = sqrt(p * (p - a) * (p - b) * (p - c));
    
    return S;
}
