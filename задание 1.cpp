#include <iostream>
#include <cmath>

using namespace std;

int main() {
    //константы
    float x = 2.2;
    float y = 9.2;
    float z = 10.2;
    
    //данных
    cout << "Исходные данные:" << endl;
    cout << "x = " << x << endl;
    cout << "y = " << y << endl;
    cout << "z = " << z << endl;
    cout << endl;
    
    //значение a
    float a = log(z + x*x) + pow(sin(x / y), 2);
    
    //значение b
    float n = exp(-z) * (x + sqrt(x + z));
    float d = x - sqrt(fabs(x - y));
    float b = n / d;
    
    //результаты
    cout << "Результаты вычислений:" << endl;
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    
    return 0;
}