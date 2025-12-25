#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

// Объявления функций (прототипы)
double vY(double x);
double vS(double x, double eps);

/**
* @brief Основная функция программы
* @return 0 при успешном выполнении
*/
int main() {
    // Константы из задания
    const double a = 0.1;      // начало интервала
    const double b = 0.8;      // конец интервала  
    const double h = 0.1;      // шаг табулирования
    const double eps = 0.00004; // точность 40×10^-5 = 0.00004
    
    cout << "Табулирование функции и суммы ряда" << endl;
    cout << "Функция: y = ln(1/(2 + 2x + x^2))" << endl;
    cout << "Ряд: S = -(1+x)^2 + (1+x)^4/2 - (1+x)^6/3 + ..." << endl;
    cout << "Интервал: [" << a << ", " << b << "]" << endl;
    cout << "Шаг: " << h << endl;
    cout << "Точность: " << eps << endl;
    
    // Выводим заголовок таблицы
    cout << "+-------------+---------------------+---------------------+-----------------+" << endl;
    cout << "|     x       |    Функция y(x)     |   Сумма ряда S(x)   |   Разность      |" << endl;
    cout << "+-------------+---------------------+---------------------+-----------------+" << endl;
    
    // Табулирование
    cout << fixed << setprecision(6);
    for (double x = a; x <= b + h/1000; x += h) {
        double y = vY(x);
        double s = vS(x, eps);
        double r = fabs(y - s);
        
        cout << "| " << setw(11) << x << " | ";
        cout << setw(19) << y << " | ";
        cout << setw(19) << s << " | ";
        cout << setw(15) << r << " |" << endl;
    }
    
    cout << "+-------------+---------------------+---------------------+-----------------+" << endl;
    
    // Проверка точности
    cout << "Проверка точности" << endl;
    cout << "Максимальная допустимая погрешность: " << eps << endl;
    
    double max_r = 0;
    double x_max = a;
    
    for (double x = a; x <= b + h/1000; x += h) {
        double y = vY(x);
        double s = vS(x, eps);
        double r = fabs(y - s);
        
        if (r > max_r) {
            max_r = r;
            x_max = x;
        }
    }
    
    cout << "Максимальная разность: " << max_r << " при x = " << x_max << endl;
    
    if (max_r <= eps) {
        cout << "Точность достигнута!" << endl;
    } else {
        cout << "Точность не достигнута!" << endl;
    }
    
    return 0;
}

/**
* @brief Вычисляет значение функции y = ln(1/(2 + 2x + x^2))
* @param x - входное значение
* @return значение функции в точке x
*/
double vY(double x) {
    return log(1.0 / (2.0 + 2.0*x + x*x));
}

/**
* @brief Вычисляет сумму ряда для функции ln(1/(2 + 2x + x^2))
* @param x - входное значение
* @param eps - точность вычисления
* @return сумму ряда с заданной точностью
*/
double vS(double x, double eps) {
    double s = 0.0;          // сумма ряда
    double a = 0.0;          // текущий элемент ряда
    int n = 1;               // номер элемента
    double t = 1.0 + x;      // (1+x)
    double t2 = t * t;       // (1+x)^2
    
    // Первый элемент ряда: -(1+x)^2
    a = -t2;
    s = a;
    n = 2;
    
    // Вычисляем остальные элементы пока |a| >= eps
    do {
        // Рекуррентная формула: следующий элемент = предыдущий * (-(1+x)^2) * (n-1)/n
        a = a * (-t2) * (n-1) / n;
        s += a;
        n++;
    } while (fabs(a) >= eps);
    
    return s;
}
