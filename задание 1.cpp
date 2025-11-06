#include <iostream>
#include <cmath>

using namespace std;
/**
* @brief рассчитывает значение функции A по заданной формуле
* @param x - значение константы x
* @param y - значение константы y
* @param z - значение константы z
* @return - рассчитанное значение
*/
float getA(const float x, const float y, const float z);

/**
* @brief рассчитывает значение функции B по заданной формуле
* @param x - значение константы x
* @param y - значение константы y
* @param z - значение константы z
* @return - рассчитанное значение
*/
float getB(const float x, const float y, const float z);

/**
* @brief точка входа в программу
* @return - 0, если программа выполнена корректно
*/
int main() {
    //константы
    const float x = 2.2;
    const float y = 9.2;
    const float z = 10.2;
    
    //данных
    cout << "Исходные данные:" << endl;
    cout << "x = " << x << endl;
    cout << "y = " << y << endl;
    cout << "z = " << z << endl;
    cout << endl;
 
    //результаты
    cout << "Результаты вычислений:" << endl;
    cout << "a = " << getA(x,y,z) << endl;
    cout << "b = " << getB(x,y,z) << endl;
    
    return 0;
}

float getA(const float x, const float y, const float z)
{
    return log(z + x*x) + pow(sin(x / y), 2);
}

float getB(const float x, const float y, const float z)
{
    return exp(-z) * (x + sqrt(x + z))/(x - sqrt(fabs(x - y)));
}
