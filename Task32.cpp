#include <iostream>
#include <cmath>
#include <iomanip>
#include <limits>

using namespace std;

/**
 * @brief Проверяет корректность ввода неотрицательного целого числа
 * @return Введенное пользователем неотрицательное целое число
 */
int checkIntValue();

/**
 * @brief Проверяет корректность ввода числа с плавающей точкой
 * @return Введенное пользователем число
 */
double checkDoubleValue();

/**
 * @brief Вычисляет сумму первых n членов ряда
 * @param n Количество членов ряда (должно быть >= 0)
 * @return Сумма первых n членов ряда
 */
double calculateSumN(const int n);

/**
 * @brief Вычисляет сумму членов ряда, модуль которых не меньше e
 * @param e Заданный порог для модуля члена ряда
 * @return Сумма членов ряда, удовлетворяющих условию
 */
double calculateSumE(const double e);

/**
 * @brief Главная функция программы
 * @return 0 в случае успешного выполнения, 1 в случае ошибки
 */
int main()
{
    int n = 0;
    double e = 0.0;
    double s_n = 0.0;
    double s_e = 0.0;
    
    cout << "==========================================" << endl;
    cout << "Вычисление суммы ряда" << endl;
    cout << "Ряд: sum(k=0 to n) [(-1)^k / (k! * (k+1)!)]" << endl;
    cout << "==========================================" << endl;
    
    // Часть a: сумма первых n членов
    cout << "--- Часть a: сумма первых n членов ---" << endl;
    cout << "Введите количество членов ряда (n >= 0): ";
    n = checkIntValue();
    
    if (n < 0)
    {
        cout << "Ошибка! n должно быть неотрицательным целым числом!" << endl;
        return 1;
    }
    
    s_n = calculateSumN(n);
    cout << fixed << setprecision(10);
    cout << "Сумма первых " << n << " членов ряда: " << s_n << endl;
    
    // Часть b: сумма элементов с |элемент| >= e
    cout << "--- Часть b: сумма элементов с |элемент| >= e ---" << endl;
    cout << "Введите точность e: ";
    e = checkDoubleValue();
    
    // Для e <= 0 выводим предупреждение, но продолжаем вычисления
    if (e <= 0)
    {
        cout << "Внимание: e <= 0. Будут суммироваться все члены ряда до достижения предела итераций." << endl;
    }
    
    s_e = calculateSumE(e);
    cout << fixed << setprecision(10);
    cout << "Сумма элементов с |элемент| >= " << e << ": " << s_e << endl;
    
    cout << "==========================================" << endl;
    cout << "Программа завершена успешно." << endl;
    
    return 0;
}

/**
 * @brief Проверяет корректность ввода неотрицательного целого числа
 * @return Введенное пользователем неотрицательное целое число
 */
int checkIntValue()
{
    int value = 0;
    cin >> value;
    
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Ошибка ввода! Введите целое число: ";
        return checkIntValue(); // Рекурсивный вызов для повторного ввода
    }
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return value;
}

/**
 * @brief Проверяет корректность ввода числа с плавающей точкой
 * @return Введенное пользователем число
 */
double checkDoubleValue()
{
    double value = 0.0;
    cin >> value;
    
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Ошибка ввода! Введите число: ";
        return checkDoubleValue(); 
    }
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return value;
}

/**
 * @brief Вычисляет сумму первых n членов ряда
 * @param n Количество членов ряда (должно быть >= 0)
 * @return Сумма первых n членов ряда
 */
double calculateSumN(const int n)
{
    if (n < 0)
    {
        return 0.0;
    }
    
    double sum = 0.0;
    double term = 1.0; // a_0 = 1 / (0! * 1!) = 1
    
    cout << "Процесс вычисления:" << endl;
    cout << "+-----+---------------------+---------------------+" << endl;
    cout << "|  k  |      Текущий        |   Текущая сумма     |" << endl;
    cout << "+-----+---------------------+---------------------+" << endl;
    
    for (int k = 0; k <= n; k++)
    {
        sum += term;
        
        cout << fixed << setprecision(10);
        cout << "| " << setw(3) << k << " | " 
             << setw(19) << term << " | "
             << setw(19) << sum << " |" << endl;
        
        // Рекуррентное вычисление следующего члена:
        // a_{k+1} = -a_k / ((k+1)*(k+2))
        if (k < n)
        {
            term = -term / ((k + 1.0) * (k + 2.0));
        }
    }
    
    cout << "+-----+---------------------+---------------------+" << endl;
    return sum;
}

/**
 * @brief Вычисляет сумму членов ряда, модуль которых не меньше e
 * @param e Заданный порог для модуля члена ряда
 * @return Сумма членов ряда, удовлетворяющих условию
 */
double calculateSumE(const double e)
{
    const int MAX_ITERATIONS = 1000; // Ограничение на количество итераций
    
    double sum = 0.0;
    double term = 1.0; // a_0 = 1
    int k = 0;
    int iterations = 0;
    
    cout << "Процесс вычисления (только члены с |элемент| >= " << e << "):" << endl;
    cout << "+-----+---------------------+---------------------+" << endl;
    cout << "|  k  |      Текущий        |   Текущая сумма     |" << endl;
    cout << "+-----+---------------------+---------------------+" << endl;
    
    // Если e <= 0, то условие |term| >= e выполняется всегда
    // Но мы ограничиваем количество итераций
    bool condition = true;
    
    while (condition && iterations < MAX_ITERATIONS)
    {
        sum += term;
        
        cout << fixed << setprecision(10);
        cout << "| " << setw(3) << k << " | " 
             << setw(19) << term << " | "
             << setw(19) << sum << " |" << endl;
        
        // Вычисляем следующий член рекуррентно:
        // a_{k+1} = -a_k / ((k+1)*(k+2))
        term = -term / ((k + 1.0) * (k + 2.0));
        k++;
        iterations++;
        
        // Обновляем условие для следующей итерации
        if (e > 0)
        {
            condition = (fabs(term) >= e);
        }
        // Если e <= 0, condition остается true, но ограничено MAX_ITERATIONS
    }
    
    cout << "+-----+---------------------+---------------------+" << endl;
    
    if (iterations >= MAX_ITERATIONS && e <= 0)
    {
        cout << "Внимание: достигнут предел итераций (" << MAX_ITERATIONS 
             << "). Сумма вычислена для первых " << MAX_ITERATIONS << " членов." << endl;
    }
    else if (iterations >= MAX_ITERATIONS)
    {
        cout << "Внимание: достигнут предел итераций (" << MAX_ITERATIONS 
             << "). Возможно, e слишком малое." << endl;
    }
    else
    {
        cout << "Количество учтенных элементов: " << k << endl;
    }
    
    return sum;
}
