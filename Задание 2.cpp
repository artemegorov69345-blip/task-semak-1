#include <iostream>
#include <cmath>

using namespace std;

/**
* @brief вычисляет площадь круга по длине окружности
* @param L - длина окружности
* @return - площадь круга
*/
float calculateS(const float d);

/**
* @brief точка входа в программу
* @return - 0, если программа выполнена корректно
*/
int main() {
    // длина окружности
    float d=0;
    
    // вводим
    cout << "Введите длину окружности: ";
    cin >> d;
    
    // выводим 
    cout << "Длина окружности: " << d << endl;
    
    // площадь круга
    // формула: S = L^2 / (4π)
    float S = calculateS(d);
    
    //результат
    cout << "Площадь круга: " << S << endl;
    
    return 0;
}
float calculateS(const float d) {
    return (L * L) / (4 * 3.14);
}
