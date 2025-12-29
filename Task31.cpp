#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

/**
* @brief Вычисляет значение функции y = 3x - 14 + e^x - e^(-x)
* @param x - входное значение
* @return значение функции y в точке x
*/
double vY(double x);

/**
* @brief Проверяет правильность ввода числового значения
* @param value - ссылка на переменную для сохранения значения
* @return true если ввод корректен, false если есть ошибка
*/
bool checkValue(double &value);

/**
* @brief Проверяет является ли значение положительным
* @param value - проверяемое значение
* @param paramName - название параметра для сообщения об ошибке
* @return true если значение положительное, false в противном случае
*/
bool checkPositive(double value, const string &paramName);

/**
* @brief Проверяет корректность интервала
* @param start - начало интервала
* @param end - конец интервала
* @return true если интервал корректен, false в противном случае
*/
bool checkInterval(double start, double end);

/**
* @brief Вычисляет значение функции рекуррентным методом
* @param x - начальное значение x
* @param h - шаг изменения
* @param n - количество итераций
* @return значение функции на n-ом шаге
*/
double getRecurent(double x, double h, int n);

/**
* @brief Основная функция программы
* @details Функция main является точкой входа в программу.
* Она выполняет следующие действия:
* Выводит приветственное сообщение
* Запрашивает у пользователя параметры табулирования
* Проверяет корректность введенных данных
* Выполняет табулирование функции
* Выводит результаты в виде таблицы
* Демонстрирует рекуррентный метод
* Показывает тестовый пример из задания
* 
* @return 0 при успешном выполнении, 1 при ошибке ввода
*/
int main() {
    double n, k, h;
    
    // Ввод параметров табулирования
    cout << "=== Табулирование функции y = 3x - 14 + e^x - e^(-x) ===" << endl;
    
    // Ввод начала интервала
    cout << "Введите начало интервала: ";
    while (!checkValue(n)) {
        cout << "Ошибка! Нужно вводить только числа! Попробуйте снова: ";
    }
    
    // Ввод конца интервала
    cout << "Введите конец интервала: ";
    while (!checkValue(k)) {
        cout << "Ошибка! Нужно вводить только числа! Попробуйте снова: ";
    }
    
    // Ввод шага табулирования
    cout << "Введите шаг табулирования: ";
    while (!checkValue(h)) {
        cout << "Ошибка! Нужно вводить только числа! Попробуйте снова: ";
    }
    
    // Проверка корректности введенных значений
    if (!checkPositive(h, "Шаг")) {
        return 1;
    }
    
    if (!checkInterval(n, k)) {
        return 1;
    }
    
    // Выводим заголовок таблицы
    cout << endl << "Таблица значений функции" << endl;
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
    
    // Демонстрация рекуррентного метода
    cout << endl << "Демонстрация рекуррентного метода:" << endl;
    cout << "Начальное x: " << n << ", шаг: " << h << endl;
    cout << "Значение функции через 3 шага: " << getRecurent(n, h, 3) << endl;
    
    // Тестовый пример из задания
    cout << endl << "=== Тестовый пример из задания ===" << endl;
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
* @brief Проверяет правильность ввода значения
* @param value - ссылка на переменную для сохранения значения
* @return true если ввод корректен, false если есть ошибка
*/
bool checkValue(double &value) {
    cin >> value;
    if (cin.fail()) {
        cin.clear(); // Сбрасываем флаг ошибки
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очищаем буфер
        return false;
    }
    return true;
}

/**
* @brief Проверяет положительное значение
* @param value - проверяемое значение
* @param paramName - название параметра для сообщения об ошибке
* @return true если значение положительное, false в противном случае
*/
bool checkPositive(double value, const string &paramName) {
    if (value <= 0) {
        cout << "Ошибка! " << paramName << " должен быть положительным числом!" << endl;
        return false;
    }
    return true;
}

/**
* @brief Проверяет корректность интервала
* @param start - начало интервала
* @param end - конец интервала
* @return true если интервал корректен, false в противном случае
*/
bool checkInterval(double start, double end) {
    if (start > end) {
        cout << "Ошибка! Начало интервала должно быть меньше или равно концу!" << endl;
        return false;
    }
    return true;
}

/**
* @brief Вычисляет значение функции рекуррентным методом
* @param x - начальное значение x
* @param h - шаг
* @param n - количество итераций
* @return значение функции на n-ом шаге
*/
double getRecurent(double x, double h, int n) {
    double currentX = x;
    for (int i = 0; i < n; i++) {
        currentX += h;
    }
    return vY(currentX);
}

/**
* @brief Вычисляет значение функции y = 3x - 14 + e^x - e^(-x)
* @param x - входное значение
* @return значение функции y в точке x
*/
double vY(double x) {
    return 3 * x - 14 + exp(x) - exp(-x);
}
