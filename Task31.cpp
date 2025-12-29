#include <iostream>
#include <cmath>
#include <iomanip>
#include <limits>
using namespace std;

/**
* @brief Сравнивает два числа с плавающей точкой с учетом погрешности
* @param a - первое число
* @param b - второе число
* @return true если a <= b с учетом погрешности, false в противном случае
*/
bool isLessOrEqualWithEpsilon(const double a, const double b);

/**
* @brief Вычисляет значение функции y = 3x - 14 + e^x - e^(-x)
* @param x - входное значение
* @return значение функции y в точке x
*/
double vY(const double x);

/**
* @brief Проверяет правильность ввода числового значения
* @param value - ссылка на переменную для сохранения значения
* @return true если ввод корректен, false если есть ошибка
*/
bool checkValue(const double &value);

/**
* @brief Проверяет является ли значение положительным
* @param value - проверяемое значение
* @param paramName - название параметра для сообщения об ошибке
* @return true если значение положительное, false в противном случае
*/
bool checkPositive(const double value, const string &paramName);

/**
* @brief Проверяет корректность интервала
* @param start - начало интервала
* @param end - конец интервала
* @return true если интервал корректен, false в противном случае
*/
bool checkInterval(const double start, const double end);

/**
* @brief Вычисляет значение функции рекуррентным методом
* @param x - начальное значение x
* @param h - шаг изменения
* @param n - количество итераций
* @return значение функции на n-ом шаге
*/
double getRecurent(const double x, const double h, const int n);

/**
* @brief Выводит таблицу значений функции на заданном интервале
* @param start - начало интервала
* @param end - конец интервала
* @param step - шаг табулирования
*/
void printTable(const double start, const double end, const double step);

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
    double n = 0.0, k = 0.0, h = 0.0;
    
    // Ввод параметров табулирования
    cout << "=== Табулирование функции y = 3x - 14 + e^x - e^(-x) ===" << endl;
    
    // Ввод начала интервала
    cout << "Введите начало интервала: ";
    if (!checkValue(n)) {
        cout << "Ошибка! Нужно вводить только числа!" << endl;
        return 1;
    }
    
    // Ввод конца интервала
    cout << "Введите конец интервала: ";
    if (!checkValue(k)) {
        cout << "Ошибка! Нужно вводить только числа!" << endl;
        return 1;
    }
    
    // Ввод шага табулирования
    cout << "Введите шаг табулирования: ";
    if (!checkValue(h)) {
        cout << "Ошибка! Нужно вводить только числа!" << endl;
        return 1;
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
    
    // Табулирование функции
    printTable(n, k, h);
    
    // Демонстрация рекуррентного метода
    cout << endl << "Демонстрация рекуррентного метода:" << endl;
    cout << "Начальное x: " << n << ", шаг: " << h << endl;
    cout << "Значение функции через 3 шага: " << getRecurent(n, h, 3) << endl;
    
    // Тестовый пример из задания
    cout << endl << "=== Тестовый пример из задания ===" << endl;
    cout << "Интервал: [1, 3], шаг: 0.2" << endl;
    printTable(1.0, 3.0, 0.2);
    
    return 0;
}

/**
* @brief Сравнивает два числа с плавающей точкой с учетом погрешности
* @param a - первое число
* @param b - второе число
* @return true если a <= b с учетом погрешности, false в противном случае
*/
bool isLessOrEqualWithEpsilon(const double a, const double b) {
    // Используем машинный эпсилон для double
    const double epsilon = numeric_limits<double>::epsilon();
    
    // Для сравнения с учетом погрешности используем относительную ошибку
    // Масштабируем epsilon в зависимости от величины чисел
    const double absA = fabs(a);
    const double absB = fabs(b);
    const double maxAbs = max(absA, absB);
    
    // Если оба числа близки к нулю, используем абсолютную погрешность
    if (maxAbs < 1.0) {
        return a <= b + 10.0 * epsilon;
    }
    
    // Иначе используем относительную погрешность
    return a <= b + maxAbs * 10.0 * epsilon;
}

/**
* @brief Проверяет правильность ввода значения
* @param value - ссылка на переменную для сохранения значения
* @return true если ввод корректен, false если есть ошибка
*/
bool checkValue(const double &value) {
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
bool checkPositive(const double value, const string &paramName) {
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
bool checkInterval(const double start, const double end) {
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
double getRecurent(const double x, const double h, const int n) {
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
double vY(const double x) {
    return 3 * x - 14 + exp(x) - exp(-x);
}

/**
* @brief Выводит таблицу значений функции на заданном интервале
* @param start - начало интервала
* @param end - конец интервала
* @param step - шаг табулирования
*/
void printTable(const double start, const double end, const double step) {
    cout << "+-------------+-------------+" << endl;
    cout << "|     x       |     y       |" << endl;
    cout << "+-------------+-------------+" << endl;
    
    double x = start;
    int t = 0;
    
    cout << fixed << setprecision(4);
    
    while (isLessOrEqualWithEpsilon(x, end)) {
        t++;
        double y = vY(x);
        
        cout << "| " << setw(11) << x << " | ";
        
        if (!isfinite(y)) {
            cout << setw(11) << "Нет решения" << " |" << endl;
        } else {
            cout << setw(11) << y << " |" << endl;
        }
        
        x += step;
    }
    
    cout << "+-------------+-------------+" << endl;
    cout << "Всего вычислено точек: " << t << endl;
}
