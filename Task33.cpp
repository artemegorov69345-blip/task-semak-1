#include <iostream>
#include <cmath>
#include <iomanip>
#include <limits>

using namespace std;

// Объявления функций
/**
* @brief Проверяет правильность ввода числового значения
* @param value - ссылка на переменную для сохранения значения
* @return true если ввод корректен, false если есть ошибка
*/
bool checkValue(double &value);

/**
* @brief Проверяет положительное значение
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
* @brief Вычисляет функцию y = (e^a - e^(-a)) / 2 (гиперболический синус)
* @param a значение переменной a
* @return Возвращает значение функции
*/
double getFunc(double a);

/**
* @brief Рассчитывает значение следующего элемента ряда
* @param previous предыдущий элемент ряда
* @param a значение переменной a
* @param n индекс элемента последовательности
* @return Возвращает значение следующего элемента ряда
*/
double nextElement(double previous, double a, int n);

/**
* @brief Рассчитывает значение суммы ряда с точностью до epsilon
* @param a значение переменной a
* @param eps значение величины точности
* @return Возвращает значение суммы ряда
*/
double getSum(double a, double eps);

/**
* @brief Рекуррентное вычисление суммы ряда
* @param a значение переменной a
* @param eps точность вычислений
* @param maxIterations максимальное количество итераций
* @return значение суммы ряда
*/
double getRecurent(double a, double eps, int maxIterations = 1000);

/**
 * @brief Точка входа в программу
 * @return Возвращает 0 в случае успеха
 */
int main()
{
    const double eps = 1e-4;  // Точность 10^-4
    
    cout << "=== Вычисление гиперболического синуса sh(x) и его разложения в ряд ===" << endl;
    
    // Ввод начала интервала
    double iStart;
    cout << "Введите начало интервала: ";
    while (!checkValue(iStart)) {
        cout << "Ошибка! Нужно вводить только числа! Попробуйте снова: ";
    }
    
    // Ввод конца интервала
    double iEnd;
    cout << "Введите конец интервала: ";
    while (!checkValue(iEnd)) {
        cout << "Ошибка! Нужно вводить только числа! Попробуйте снова: ";
    }
    
    // Проверка интервала
    if (!checkInterval(iStart, iEnd)) {
        cout << "Ошибка! Конец интервала должен быть больше начала!" << endl;
        return 1;
    }
    
    // Ввод шага
    double step;
    cout << "Введите значение шага: ";
    while (!checkValue(step)) {
        cout << "Ошибка! Нужно вводить только числа! Попробуйте снова: ";
    }
    
    // Проверка шага
    if (!checkPositive(step, "Шаг")) {
        return 1;
    }
    
    // Выводим заголовок таблицы
    cout << endl;
    cout << "Таблица значений:" << endl;
    cout << "+----------+---------------+---------------+---------------+" << endl;
    cout << "|    a     |     f(a)      |     S(a)      |   Разность    |" << endl;
    cout << "+----------+---------------+---------------+---------------+" << endl;
    
    // Табулирование функции
    cout << fixed << setprecision(6);
    for (double a = iStart; a <= iEnd + numeric_limits<double>::epsilon(); a += step) {
        double funcValue = getFunc(a);
        double sumValue = getSum(a, eps);
        double diff = fabs(funcValue - sumValue);
        
        cout << "| " << setw(8) << setprecision(2) << a << " | "
             << setw(13) << funcValue << " | "
             << setw(13) << sumValue << " | "
             << setw(13) << diff << " |" << endl;
    }
    
    cout << "+----------+---------------+---------------+---------------+" << endl;
    
    // Демонстрация рекуррентного метода
    cout << endl << "Демонстрация рекуррентного метода:" << endl;
    double testValue = (iStart + iEnd) / 2.0;
    cout << "Значение a = " << testValue << endl;
    cout << "Точное значение f(a) = " << getFunc(testValue) << endl;
    cout << "Сумма ряда S(a) = " << getSum(testValue, eps) << endl;
    cout << "Рекуррентное вычисление = " << getRecurent(testValue, eps) << endl;
    
    return 0;
}

bool checkValue(double &value) {
    cin >> value;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }
    return true;
}

bool checkPositive(double value, const string &paramName) {
    if (value <= 0) {
        cout << "Ошибка! " << paramName << " должен быть положительным числом!" << endl;
        return false;
    }
    return true;
}

bool checkInterval(double start, double end) {
    if (end <= start) {
        return false;
    }
    return true;
}

double getFunc(double a) {
    return (exp(a) - exp(-a)) / 2.0;
}

double nextElement(double previous, double a, int n) {
    return previous * (a * a) / ((2.0 * n) * (2.0 * n + 1.0));
}

double getSum(double a, double eps) {
    // Первый элемент ряда для гиперболического синуса: a
    double element = a;
    double sum = element;
    int n = 1;
    
    while (fabs(element) > eps && n < 1000) {
        element = nextElement(element, a, n);
        sum += element;
        n++;
    }
    
    return sum;
}

double getRecurent(double a, double eps, int maxIterations) {
    double sum = a;  // Первый элемент
    double element = a;
    
    for (int n = 1; n < maxIterations && fabs(element) > eps; n++) {
        element = element * (a * a) / ((2.0 * n) * (2.0 * n + 1.0));
        sum += element;
    }
    
    return sum;
}
