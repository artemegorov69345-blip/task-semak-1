#include <iostream>
#include <cmath>
#include <iomanip>
#include <limits>

using namespace std;

// Объявления функций
/**
* @brief Считывает числовое значение, при ошибке ввода завершает программу
* @return считанное значение
*/
double checkValue();

/**
* @brief Считывает целое числовое значение, при ошибке ввода завершает программу
* @return считанное целое значение
*/
int checkIntValue();

/**
* @brief Проверяет положительное значение
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
* @brief Вычисляет функцию y = (e^a - e^(-a)) / 2 (гиперболический синус)
* @param a значение переменной a
* @return Возвращает значение функции
*/
double getFunc(const double a);

/**
* @brief Рассчитывает значение следующего элемента ряда
* @param previous предыдущий элемент ряда
* @param a значение переменной a
* @param n индекс элемента последовательности
* @return Возвращает значение следующего элемента ряда
*/
double nextElement(const double previous, const double a, const int n);

/**
* @brief Рассчитывает значение суммы ряда с точностью до epsilon
* @param a значение переменной a
* @param eps значение величины точности
* @return Возвращает значение суммы ряда
*/
double getSum(const double a, const double eps);

/**
* @brief Рекуррентное вычисление суммы ряда
* @param a значение переменной a
* @param eps точность вычислений
* @param maxIterations максимальное количество итераций
* @return значение суммы ряда
*/
double getRecurent(const double a, const double eps, const int maxIterations = 1000);

/**
 * @brief Точка входа в программу
 * @return Возвращает 0 в случае успеха
 */
int main()
{
    cout << "=== Вычисление гиперболического синуса sh(x) и его разложения в ряд ===" << endl;
    
    // Ввод точности вычислений пользователем
    cout << "Введите точность вычислений (например, 0.0001): ";
    double eps = checkValue();
    
    // Проверка, что точность положительная
    if (!checkPositive(eps, "Точность вычислений")) {
        return 1;
    }
    
    // Ввод параметров для табулирования функции
    cout << "Введите начало интервала табулирования: ";
    double iStart = checkValue();
    
    cout << "Введите конец интервала табулирования: ";
    double iEnd = checkValue();
    
    // Проверка корректности интервала: конец должен быть больше начала
    if (!checkInterval(iStart, iEnd)) {
        cout << "Ошибка! Конец интервала должен быть больше начала!" << endl;
        return 1;
    }
    
    // Ввод шага табулирования - количество точек между значениями
    cout << "Введите количество шагов (целое число): ";
    int stepCount = checkIntValue();
    
    // Проверка, что количество шагов положительное
    if (!checkPositive(stepCount, "Количество шагов")) {
        return 1;
    }
    
    // Вычисляем фактический шаг как расстояние между точками
    double actualStep = (iEnd - iStart) / stepCount;
    
    // Выводим заголовок таблицы
    cout << endl;
    cout << "Таблица значений функции sh(x) = (e^x - e^(-x))/2 и ее разложения в ряд Тейлора:" << endl;
    cout << "Интервал: [" << iStart << ", " << iEnd << "], шагов: " << stepCount << ", точность: " << eps << endl;
    cout << "+----------+---------------+---------------+---------------+" << endl;
    cout << "|     x    |    sh(x)      |    S(x)       |    |f-S|     |" << endl;
    cout << "+----------+---------------+---------------+---------------+" << endl;
    
    // Табулирование функции - вычисление значений для каждого x в интервале
    cout << fixed << setprecision(6);
    int pointsCalculated = 0;
    
    for (int i = 0; i <= stepCount; i++) {
        // Вычисляем текущее значение x
        double a = iStart + i * actualStep;
        double funcValue = getFunc(a);       // Точное значение функции
        double sumValue = getSum(a, eps);    // Приближенное значение через ряд
        double diff = fabs(funcValue - sumValue);  // Разность между точным и приближенным
        
        // Вывод строки таблицы с форматированием
        cout << "| " << setw(8) << a << " | "
             << setw(13) << funcValue << " | "
             << setw(13) << sumValue << " | "
             << setw(13) << diff << " |" << endl;
        
        pointsCalculated++;
    }
    
    cout << "+----------+---------------+---------------+---------------+" << endl;
    cout << "Всего вычислено точек: " << pointsCalculated << endl;
    
    // Демонстрация рекуррентного метода вычисления
    cout << endl << "Демонстрация рекуррентного метода вычисления суммы ряда:" << endl;
    double testValue = (iStart + iEnd) / 2.0;  // Среднее значение интервала для теста
    cout << "Тестовое значение x = " << testValue << endl;
    cout << "Точное значение sh(" << testValue << ") = " << getFunc(testValue) << endl;
    cout << "Сумма ряда с точностью " << eps << " = " << getSum(testValue, eps) << endl;
    cout << "Рекуррентное вычисление = " << getRecurent(testValue, eps) << endl;
    
    return 0;
}

/**
* @brief Считывает числовое значение, при ошибке ввода завершает программу
* @return считанное значение
*/
double checkValue() {
    double value = 0.0;  // Инициализация по умолчанию
    cin >> value;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max());
        cout << "Ошибка ввода! Программа завершена." << endl;
        exit(1);  // Завершение программы при ошибке ввода
    }
    return value;
}

/**
* @brief Считывает целое числовое значение, при ошибке ввода завершает программу
* @return считанное целое значение
*/
int checkIntValue() {
    int value = 0;  // Инициализация по умолчанию
    cin >> value;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Ошибка ввода! Программа завершена." << endl;
        exit(1);  // Завершение программы при ошибке ввода
    }
    return value;
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

bool checkInterval(const double start, const double end) {
    if (end <= start) {
        return false;
    }
    return true;
}

double getFunc(const double a) {
    return (exp(a) - exp(-a)) / 2.0;
}

double nextElement(const double previous, const double a, const int n) {
    // Исправленная рекуррентная формула
    return previous * (a * a) / ((2.0 * n - 1.0) * (2.0 * n));
}

double getSum(const double a, const double eps) {
    // Проверка для a = 0 с использованием константы из cmath
    if (fabs(a) < numeric_limits<double>::epsilon()) {
        return 0.0;
    }
    
    // Первый элемент ряда для гиперболического синуса: a
    double element = a;
    double sum = element;
    int k = 1;  // номер текущего элемента (начиная с 1 для второго элемента)
    
    while (fabs(element) > eps && k < 1000) {
        // Исправленная рекуррентная формула
        element = element * (a * a) / ((2.0 * k - 1.0) * (2.0 * k));
        sum += element;
        k++;
    }
    
    return sum;
}

double getRecurent(const double a, const double eps, const int maxIterations) {
    // Проверка для a = 0 с использованием константы из cmath
    if (fabs(a) < numeric_limits<double>::epsilon()) {
        return 0.0;
    }
    
    double sum = a;  // Первый элемент
    double element = a;
    
    for (int k = 1; k < maxIterations && fabs(element) > eps; k++) {
        // Исправленная рекуррентная формула
        element = element * (a * a) / ((2.0 * k - 1.0) * (2.0 * k));
        sum += element;
    }
    
    return sum;
}
