#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

/**
* @brief Основная функция программы
* @return 0 при успешном выполнении
*/
int main() {
    // Инициализация генератора случайных чисел
    srand(time(0));
    
    const int N = 10; // размер массива
    int arr[N];       // массив
    int A;           // заданное число для второй задачи
    int B;           // заданное число для третьей задачи
    
    // Заполнение массива случайными числами в диапазоне [-10, 10]
    cout << "=== Работа с массивом ===" << endl;
    cout << "Массив из " << N << " элементов в диапазоне [-10, 10]:" << endl;
    
    for (int i = 0; i < N; i++) {
        arr[i] = rand() % 21 - 10; // числа от -10 до 10
    }
    
    // Вывод исходного массива
    cout << "Исходный массив: ";
    for (int i = 0; i < N; i++) {
        cout << setw(4) << arr[i] << " ";
    }
    cout << endl;
    
    // Задача 1: Заменить второй элемент на максимальный среди отрицательных
    cout << "=== Задача 1 ===" << endl;
    cout << "Заменить второй элемент массива на максимальный среди отрицательных" << endl;
    
    int max_neg = -11; // начальное значение (меньше минимального возможного)
    bool found_neg = false;
    
    // Поиск максимального отрицательного элемента
    for (int i = 0; i < N; i++) {
        if (arr[i] < 0 && arr[i] > max_neg) {
            max_neg = arr[i];
            found_neg = true;
        }
    }
    
    if (found_neg) {
        cout << "Максимальный отрицательный элемент: " << max_neg << endl;
        cout << "Второй элемент (индекс 1) был: " << arr[1] << endl;
        arr[1] = max_neg;
        cout << "Теперь второй элемент: " << arr[1] << endl;
    } else {
        cout << "В массиве нет отрицательных элементов" << endl;
    }
    
    // Вывод массива после первой задачи
    cout << "Массив после задачи 1: ";
    for (int i = 0; i < N; i++) {
        cout << setw(4) << arr[i] << " ";
    }
    cout << endl;
    
    // Задача 2: Найти количество положительных элементов, по модулю <= A
    cout << "=== Задача 2 ===" << endl;
    cout << "Найти количество положительных элементов, |элемент| <= A" << endl;
    cout << "Введите число A: ";
    cin >> A;
    
    // Проверка ввода
    if (cin.fail()) {
        cout << "Ошибка! Нужно ввести число!" << endl;
        return 1;
    }
    
    int count_pos = 0;
    cout << "Положительные элементы, |элемент| <= " << A << ":" << endl;
    
    for (int i = 0; i < N; i++) {
        if (arr[i] > 0 && abs(arr[i]) <= A) {
            count_pos++;
            cout << "arr[" << i << "] = " << arr[i] << endl;
        }
    }
    
    cout << "Количество таких элементов: " << count_pos << endl;
    
    // Задача 3: Найти номер первой пары соседних элементов, сумма < B
    cout << "=== Задача 3 ===" << endl;
    cout << "Найти номер первой пары соседних элементов, сумма < B" << endl;
    cout << "Введите число B: ";
    cin >> B;
    
    // Проверка ввода
    if (cin.fail()) {
        cout << "Ошибка! Нужно ввести число!" << endl;
        return 1;
    }
    
    int pair_index = -1; // -1 означает, что пара не найдена
    
    for (int i = 0; i < N - 1; i++) {
        if (arr[i] + arr[i + 1] < B) {
            pair_index = i;
            break; // нашли первую пару - выходим из цикла
        }
    }
    
    if (pair_index != -1) {
        cout << "Первая пара найдена на индексе " << pair_index << endl;
        cout << "arr[" << pair_index << "] = " << arr[pair_index] << endl;
        cout << "arr[" << pair_index + 1 << "] = " << arr[pair_index + 1] << endl;
        cout << "Сумма: " << arr[pair_index] + arr[pair_index + 1] << " < " << B << endl;
    } else {
        cout << "Таких пар не найдено" << endl;
    }
    
    // Вывод итогового массива
    cout << "=== Итоговый массив ===" << endl;
    cout << "Индекс:  ";
    for (int i = 0; i < N; i++) {
        cout << setw(4) << i << " ";
    }
    cout << "Значение: ";
    for (int i = 0; i < N; i++) {
        cout << setw(4) << arr[i] << " ";
    }
    cout << endl;
    
    return 0;
}