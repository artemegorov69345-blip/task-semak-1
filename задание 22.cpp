#include <iostream>
#include <cmath>
using namespace std;

/**
* @brief Вычисляет значение функции y в зависимости от x
* @param x - входное значение для функции
* @return результат вычисления функции y
*/
float vY(float x);

/**
* @brief Основная функция программы
* @return 0 при успешном выполнении
*/
int main() {
    float x = 0.0f;
    const float a = 1.6f; // Константа a = 1.6
    
    // Ввод значения x
    cout << "Введите значение x: ";
    cin >> x;
    
    // Проверка правильности ввода
    if (cin.fail()) {
        cout << "Ошибка! Нужно вводить только числа!" << endl;
        return 1;
    }
    
    // Выводим информацию о данных
    cout << "Информация о данных" << endl;
    cout << "x = " << x << endl;
    cout << "a = " << a << endl;
    
    // Вычисляем значение функции y
    float y = vY(x);
    
    // Выводим результат
    cout << "Результат вычислений" << endl;
    cout << "y = " << y << endl;
    
    return 0;
}

float vY(float x) {
    const float a = 1.6f; // Константа a = 1.6
    const float eps = 0.00001f; // точность значения
    
    // Выводим какую ветвь функции мы используем
    cout << "Выбор формулы" << endl;
    
    if (x > a) {
        // Первая ветвь: y = e^(ax) - 2.5, если x > a
        cout << "x > a (" << x << " > " << a << ")" << endl;
        cout << "Используется формула: y = e^(a*x) - 2.5" << endl;
        return exp(a * x) - 2.5f;
    } 
    else if (fabs(x) < eps) {
        // Вторая ветвь: y = 3, если x = 0
        cout << "x = 0 (" << x << " = 0)" << endl;
        cout << "Используется формула: y = 3" << endl;
        return 3.0f;
    }
    else if (x < a) {
        // Третья ветвь: y = a/x + sin(x), если x < a и x ≠ 0
        cout << "x < a (" << x << " < " << a << ")" << endl;
        cout << "Используется формула: y = a/x + sin(x)" << endl;
        return a / x + sin(x);
    }
    else {
        // x = a (но это уже обработано в первом условии как x > a)
        cout << "x = a (" << x << " = " << a << ")" << endl;
        cout << "Формула не определена для x = a" << endl;
        return 0;
    }
}
