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
* @brief Проверяет правильность ввода целого числового значения
* @param value - ссылка на переменную для сохранения значения
* @return true если ввод корректен, false если есть ошибка
*/
bool checkIntValue(int &value);

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
    const double eps = 1e-4;  // Точность 10^-4 для вычисления суммы ряда
    
    cout << "=== Вычисление гиперболического синуса sh(x) и его разложения в ряд ===" << endl;
    
    // Ввод параметров для табулирования функции
    // iStart - переменная для хранения начала интервала табулирования
    double iStart;
    cout << "Введите начало интервала табулирования: ";
    while (!checkValue(iStart)) {
        cout << "Ошибка! Нужно вводить только числа! Попробуйте снова: ";
    }
    
    // iEnd - переменная для хранения конца интервала табулирования
    double iEnd;
    cout << "Введите конец интервала табулирования: ";
    while (!checkValue(iEnd)) {
        cout << "Ошибка! Нужно вводить только числа! Попробуйте снова: ";
    }
    
    // Проверка корректности интервала: конец должен быть больше начала
    if (!checkInterval(iStart, iEnd)) {
        cout << "Ошибка! Конец интервала должен быть больше начала!" << endl;
        return 1;
    }
    
    // Ввод шага табулирования - количество точек между значениями
    // Шаг должен быть целым числом согласно требованию преподавателя
    int stepCount;
    cout << "Введите количество шагов (целое число): ";
    while (!checkIntValue(stepCount)) {
        cout << "Ошибка! Нужно вводить только целые числа! Попробуйте снова: ";
    }
    
    // Проверка, что количество шагов положительное
    if (!checkPositive(stepCount, "Количество шагов")) {
        return 1;
    }
    
    // Вычисляем фактический шаг как расстояние между точками
    double actualStep = (iEnd - iStart) / stepCount;
    
    // Выводим заголовок таблицы
    cout << endl;
    cout << "Таблица значений функции sh(x) = (e^x - e^(-x))/2 и ее разложения в ряд Тейлора:" << endl;
    cout << "Интервал: [" << iStart << ", " << iEnd << "], шагов: " << stepCount << endl;
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

// Реализации функций (должны быть после main)

/**
* @brief Проверяет правильность ввода числового значения
* @param value - ссылка на переменную для сохранения значения
* @return true если ввод корректен, false если есть ошибка
* @details Функция пытается считать значение из потока ввода.
*          Если ввод успешен, возвращает true.
*          Если возникает ошибка (например, введены не числа),
*          очищает флаги ошибок и буфер ввода, возвращает false.
*/
bool checkValue(double &value) {
    cin >> value;
    if (cin.fail()) {
        cin.clear();  // Сбрасываем флаги ошибок
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Очищаем буфер ввода
        return false;  // Возвращаем false - ввод некорректен
    }
    return true;  // Возвращаем true - ввод корректен
}

/**
* @brief Проверяет правильность ввода целого числового значения
* @param value - ссылка на переменную для сохранения значения
* @return true если ввод корректен, false если есть ошибка
*/
bool checkIntValue(int &value) {
    cin >> value;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
