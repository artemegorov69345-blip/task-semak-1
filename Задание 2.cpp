#include <iostream>
#include <cmath>

using namespace std;

int main() {
    // длина окружности
    float d;
    
    // вводим
    cout << "Введите длину окружности: ";
    cin >> d;
    
    // выводим 
    cout << "Длина окружности: " << d << endl;
    
    // площадь круга
    // формула: S = L^2 / (4π)
    float S = (d * d) / (4 * 3.14159);
    
    //результат
    cout << "Площадь круга: " << S << endl;
    
    return 0;
}