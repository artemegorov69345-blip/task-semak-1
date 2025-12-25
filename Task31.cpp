#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

// Объявление функции 
double vY(double x);

/**
* @brief Основная функция программы
* @return 0 при успешном выполнении
*/
int main() {
    double n, k, h;
    
    // Ввод параметров табулирования
    cout << "=== Табулирование функции y = 3x - 14 + e^x - e^(-x) ===" << endl;
    cout << "Введите начало интервала: ";
    cin >> n;
    
    // Проверка правильности ввода
    if (cin.fail()) {
        cout << "Ошибка! Нужно вводить только числа!" << endl;
        return 1;
    }
    
    cout << "Введите конец интервала: ";
    cin >> k;
    
    // Проверка правильности ввода
    if (cin.fail()) {
        cout << "Ошибка! Нужно вводить только числа!" << endl;
        return 1;
    }
    
    cout << "Введите шаг табулирования: ";
    cin >> h;
    
    // Проверка правильности ввода
    if (cin.fail()) {
        cout << "Ошибка! Нужно вводить только числа!" << endl;
        return 1;
    }
    
    if (h <= 0) {
        cout << "Ошибка! Шаг должен быть положительным числом!" << endl;
        return 1;
    }
    
    if (n > k) {
        cout << "Ошибка! Начало интервала должно быть меньше или равно концу!" << endl;
        return 1;
    }
    
    // Выводим заголовок таблицы
    cout << "Таблица значений функции" << endl;
    cout << "+-------------+-------------+" << endl;
    cout << "|     x       |     y       |" << endl;
    cout << "+-------------+-------------+" << endl;
    
    // Табулирование функции
    double x = n;
    int t = 0;
    
    cout << fixed << setprecision(4);
    
    while (x <= k + h/1000) {
        t++;
        double y = vY(x);
        
        cout << "| " << setw(11) << x << " | ";
        
        if (!isfinite(y)) {
            cout << setw(11) << "Нет решения" << " |" << endl;
        } else {
            cout << setw(11) << y << " |" << endl;
        }
        
        x += h;
    }
    
    cout << "+-------------+-------------+" << endl;
    cout << "Всего вычислено точек: " << t << endl;
    
    // Тестовый пример из задания
    cout << "Тестовый пример из задания" << endl;
    cout << "Интервал: [1, 3], шаг: 0.2" << endl;
    
    double test_n = 1.0;
    double test_k = 3.0;
    double test_h = 0.2;
    
    cout << "+-------------+-------------+" << endl;
    cout << "|     x       |     y       |" << endl;
    cout << "+-------------+-------------+" << endl;
    
    x = test_n;
    while (x <= test_k + test_h/1000) {
        double y = vY(x);
        cout << "| " << setw(11) << x << " | ";
        
        if (!isfinite(y)) {
            cout << setw(11) << "Нет решения" << " |" << endl;
        } else {
            cout << setw(11) << y << " |" << endl;
        }
        
        x += test_h;
    }
    
    cout << "+-------------+-------------+" << endl;
    
    return 0;
}

/**
* @brief Вычисляет значение функции y = 3x - 14 + e^x - e^(-x)
* @param x - входное значение
* @return значение функции y в точке x
*/
double vY(double x) {
    return 3 * x - 14 + exp(x) - exp(-x);
}
