#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

/**
* @brief Вычисляет член ряда для заданного k
* @param k - номер члена ряда
* @param fact_k - факториал k (k!)
* @param fact_k1 - факториал k+1 ((k+1)!)
* @return значение члена ряда для заданного k
*/
double calculateTerm(int k, double fact_k, double fact_k1);

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
* @brief Проверяет является ли значение неотрицательным
* @param value - проверяемое значение
* @param paramName - название параметра для сообщения об ошибке
* @return true если значение >= 0, false в противном случае
*/
bool checkNonNegative(int value, const string &paramName);

/**
* @brief Вычисляет сумму ряда рекуррентным методом
* @param n - количество членов ряда
* @param fact_k - начальный факториал для k
* @param fact_k1 - начальный факториал для k+1
* @return сумма n членов ряда, вычисленная рекуррентно
*/
double getRecurentSum(int n, double fact_k, double fact_k1);

/**
* @brief Основная функция программы
* @details Программа вычисляет сумму ряда: sum(k=0 to n) [(-1)^k / (k! * (k+1)!)]
*          Часть a: сумма первых n членов
*          Часть b: сумма элементов с |элемент| >= e
* @return 0 при успешном выполнении
*/
int main() {
    int n = 0;
    double e = 0.0;
    
    cout << "Вычисление суммы ряда" << endl;
    cout << "Ряд: sum(k=0 to n) [(-1)^k / (k! * (k+1)!)]" << endl;
    
    // Часть a: сумма первых n членов
    cout << "Часть a: сумма первых n членов" << endl;
    cout << "Введите количество членов ряда (n): ";
    
    while (!checkIntValue(n)) {
        cout << "Ошибка! Нужно вводить только целые числа! Попробуйте снова: ";
    }
    
    if (!checkNonNegative(n, "n")) {
        return 1;
    }
    
    // Вычисление суммы первых n членов
    double s_n = 0;
    double f_k = 1;      // для k!
    double f_k1 = 1;     // для (k+1)!
    
    cout << "Процесс вычисления:" << endl;
    cout << "+-----+---------------------+---------------------+" << endl;
    cout << "|  k  |      Текущий        |   Текущая сумма     |" << endl;
    cout << "+-----+---------------------+---------------------+" << endl;
    
    for (int k = 0; k <= n; k++) {
        double a = calculateTerm(k, f_k, f_k1);
        s_n += a;
        
        // Выводим шаг вычисления
        cout << fixed << setprecision(10);
        cout << "| " << setw(3) << k << " | " 
             << setw(19) << a << " | "
             << setw(19) << s_n << " |" << endl;
        
        // Подготавливаем факториалы для следующего k
        if (k < n) {
            f_k *= (k + 1);
            f_k1 *= (k + 2);
        }
    }
    
    cout << "+-----+---------------------+---------------------+" << endl;
    cout << "Сумма первых " << n << " членов ряда: " 
         << fixed << setprecision(10) << s_n << endl;
    
    // Проверка с помощью рекуррентного метода
    cout << "Проверка рекуррентным методом: " 
         << getRecurentSum(n, 1.0, 1.0) << endl;
    
    // Часть b: сумма элементов с |элемент| >= e
    cout << endl << "Часть b: сумма элементов с |элемент| >= e" << endl;
    cout << "Введите точность e (например, 0.0001): ";
    
    while (!checkValue(e)) {
        cout << "Ошибка! Нужно вводить только числа! Попробуйте снова: ";
    }
    
    // Вычисление суммы элементов с |элемент| >= e
    double s_e = 0;
    int k = 0;
    double a;
    
    // Сброс факториалов
    f_k = 1;
    f_k1 = 1;
    
    cout << "Вычисление суммы для e = " << e << ":" << endl;
    cout << "+-----+---------------------+---------------------+" << endl;
    cout << "|  k  |      Текущий        |   Текущая сумма     |" << endl;
    cout << "+-----+---------------------+---------------------+" << endl;
    
    do {
        a = calculateTerm(k, f_k, f_k1);
        
        // Если |элемент| >= |e|, добавляем к сумме
        if (fabs(a) >= fabs(e)) {
            s_e += a;
            
            cout << fixed << setprecision(10);
            cout << "| " << setw(3) << k << " | " 
                 << setw(19) << a << " | "
                 << setw(19) << s_e << " |" << endl;
        }
        
        // Подготавливаем факториалы для следующего k
        k++;
        f_k *= k;
        f_k1 *= (k + 1);
        
    } while (fabs(a) >= fabs(e));
    
    cout << "+-----+---------------------+---------------------+" << endl;
    cout << "Итоговая сумма элементов с |элемент| >= " << e << ": " 
         << fixed << setprecision(10) << s_e << endl;
    cout << "Количество учтенных элементов: " << k << endl;
    
    return 0;
}

/**
* @brief Вычисляет член ряда для заданного k
* @param k - номер члена ряда
* @param fact_k - факториал k (k!)
* @param fact_k1 - факториал k+1 ((k+1)!)
* @return значение члена ряда для заданного k
*/
double calculateTerm(int k, double fact_k, double fact_k1) {
    double denominator = fact_k * fact_k1;
    if (k % 2 == 0) {
        return 1.0 / denominator;
    } else {
        return -1.0 / denominator;
    }
}

/**
* @brief Проверяет правильность ввода числового значения
* @param value - ссылка на переменную для сохранения значения
* @return true если ввод корректен, false если есть ошибка
*/
bool checkValue(double &value) {
    cin >> value;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }
    return true;
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
* @brief Проверяет является ли значение неотрицательным
* @param value - проверяемое значение
* @param paramName - название параметра для сообщения об ошибке
* @return true если значение >= 0, false в противном случае
*/
bool checkNonNegative(int value, const string &paramName) {
    if (value < 0) {
        cout << "Ошибка! " << paramName << " должно быть неотрицательным целым числом!" << endl;
        return false;
    }
    return true;
}

/**
* @brief Вычисляет сумму ряда рекуррентным методом
* @param n - количество членов ряда
* @param fact_k - начальный факториал для k
* @param fact_k1 - начальный факториал для k+1
* @return сумма n членов ряда, вычисленная рекуррентно
*/
double getRecurentSum(int n, double fact_k, double fact_k1) {
    double sum = 0.0;
    double current_fact_k = fact_k;
    double current_fact_k1 = fact_k1;
    
    for (int k = 0; k <= n; k++) {
        double term = calculateTerm(k, current_fact_k, current_fact_k1);
        sum += term;
        
        if (k < n) {
            current_fact_k *= (k + 1);
            current_fact_k1 *= (k + 2);
        }
    }
    
    return sum;
}
