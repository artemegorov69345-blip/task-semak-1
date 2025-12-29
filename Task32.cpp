#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cmath>
#include <limits>

using namespace std;

enum Operation {
    FILL_MANUALLY = 0, 
    FILL_RANDOMLY = 1   
};

/**
* @brief Проверяет правильность ввода целого числа
* @return считанное число, если ввод правильный, иначе программа завершается
*/
int checkValue();

/**
* @brief Проверяет, положительное ли число
* @param value - число для проверки
* @param paramName - название параметра (для сообщения об ошибке)
* @return true если число положительное, false если нет
*/
bool checkPositive(const int value, const string &paramName);

/**
* @brief Проверяет правильность границ для случайных чисел
* @param min - минимальное значение
* @param max - максимальное значение
* @return true если min <= max, false если наоборот
*/
bool checkRandomBounds(const int min, const int max);

/**
* @brief Создает вектор (динамический массив) заданного размера
* @param n - размер массива
* @return готовый вектор нужного размера
*/
vector<int> createArray(const size_t n);

/**
* @brief Выводит массив на экран
* @param arr - массив для вывода
*/
void printArray(const vector<int>& arr);

/**
* @brief Заполняет массив числами, которые вводит пользователь
* @param arr - массив для заполнения
*/
void fillArrayManually(vector<int>& arr);

/**
* @brief Заполняет массив случайными числами в заданном диапазоне
* @param arr - массив для заполнения
*/
void fillArrayRandomly(vector<int>& arr);

/**
* @brief Заменяет последний элемент, который делится на 3, на 0
* @param arr - массив для изменения
*/
void replaceLastMultipleOfThree(vector<int>& arr);

/**
* @brief Подсчитывает, сколько в массиве четных чисел
* @param arr - массив для проверки
* @return количество четных чисел
*/
size_t countEvenNumbers(const vector<int>& arr);

/**
* @brief Создает новый массив, вставляя число K после каждого четного числа
* @param arr - исходный массив
* @param k - число, которое нужно вставлять
* @return новый массив с вставленными числами K
*/
vector<int> insertKAfterEven(const vector<int>& arr, const int k);

/**
* @brief Создает массив M из массива P по заданному правилу
* @param P - исходный массив
* @return новый массив M
*/
vector<int> createMfromP(const vector<int>& P);

/**
* @brief Заполняет массив случайными числами рекурсивно (демонстрация)
* @param arr - массив для заполнения
* @param index - текущий индекс
* @param min - минимальное значение
* @param max - максимальное значение
*/
void getRecurent(vector<int>& arr, const size_t index, const int min, const int max);


/**
 * @brief Главная функция программы
 * @return 0 если все успешно, 1 если ошибка
 */
int main() {
    // Инициализируем генератор случайных чисел текущим временем
    // Это нужно, чтобы при каждом запуске числа были разными
    srand(time(nullptr));
    
    cout << "=== ЛАБОРАТОРНАЯ РАБОТА: ОПЕРАЦИИ С МАССИВАМИ ===" << endl;
    
    int arraySize = 0;
    cout << "Введите размер массива (положительное число): ";
    arraySize = checkValue();
    
    // Проверяем, что размер положительный
    if (!checkPositive(arraySize, "Размер массива")) {
        return 1;
    }
    
    size_t n = static_cast<size_t>(arraySize);  // Преобразуем в size_t для использования с векторами
    
    int k = 0;
    cout << "Введите число K (будет вставляться после четных чисел): ";
    k = checkValue();
    
    cout << "Создаем массив размера " << n << "..." << endl;
    vector<int> P = createArray(n);  // P - исходный массив
    
    cout << "Выберите способ заполнения массива:" << endl;
    cout << FILL_MANUALLY << " - Ввести числа вручную" << endl;
    cout << FILL_RANDOMLY << " - Заполнить случайными числами" << endl;
    cout << "Ваш выбор: ";
    
    int choice = checkValue();
    
    // Обрабатываем выбор пользователя
    switch(choice) {
        case FILL_MANUALLY:
            cout << "Выбран ручной ввод чисел." << endl;
            fillArrayManually(P);
            break;
            
        case FILL_RANDOMLY:
            cout << "Выбран случайный ввод чисел." << endl;
            fillArrayRandomly(P);
            break;
            
        default:
            // Если ввели не 0 и не 1
            cout << "Ошибка! Нужно было ввести 0 или 1." << endl;
            return 1;
    }
    

    cout << "=== ВЫПОЛНЕНИЕ ОПЕРАЦИЙ ===" << endl;
    
    // Выводим исходный массив P
    cout << "Исходный массив P:" << endl;
    printArray(P);
    
    // Создаем копию массива и заменяем последний элемент, кратный 3, на 0
    cout << "Замена последнего элемента, делящегося на 3, на 0:" << endl;
    vector<int> P_copy(P);  // Создаем копию, чтобы не портить оригинал
    replaceLastMultipleOfThree(P_copy);
    cout << "Результат: ";
    printArray(P_copy);
    
    // Создаем новый массив с вставленными числами K после четных чисел
    cout << "Вставка числа K=" << k << " после каждого четного элемента:" << endl;
    vector<int> P_with_K = insertKAfterEven(P, k);
    cout << "Новый размер массива: " << P_with_K.size() << " элементов" << endl;
    cout << "Результат: ";
    printArray(P_with_K);
    
    // Создаем массив M из массива P по заданному правилу
    cout << "Создание массива M из массива P по правилу:" << endl;
    cout << "Правило создания M[i]:" << endl;
    cout << "M[0] = 0, M[n-1] = 0" << endl;
    cout << "Если (i+1) делится на 4: M[i] = 4 * |P[i]|" << endl;
    cout << "Иначе: M[i] = -P[i] * (i+1)" << endl;
    
    vector<int> M = createMfromP(P);
    cout << "Массив M: ";
    printArray(M);
    
    cout << "=== ДОПОЛНИТЕЛЬНО: РЕКУРРЕНТНЫЙ МЕТОД ===" << endl;
    cout << "Создаем маленький массив (6 элементов) и заполняем рекурсивно:" << endl;
    
    vector<int> recurentArray(6);
    // Заполняем числами от -50 до 50 рекурсивно
    getRecurent(recurentArray, 0, -50, 50);
    
    cout << "Массив, заполненный рекурсивно: ";
    printArray(recurentArray);
    
    cout << "=== ПРОГРАММА УСПЕШНО ЗАВЕРШЕНА ===" << endl;
    return 0;
}


/**
 * Функция checkValue проверяет, правильно ли пользователь ввел целое число.
 * Если ввод содержит ошибку, программа завершается.
 * @return считанное целое число
 */
int checkValue() {
    int value;
    cin >> value;  // Пытаемся считать число из потока ввода
    
    // Проверяем, не произошла ли ошибка
    if (cin.fail()) {
        cout << "Ошибка ввода! Программа завершена." << endl;
        exit(1);
    }
    
    // Очищаем буфер ввода
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return value;
}

/**
 * Функция checkPositive проверяет, является ли число положительным.
 * Используется для проверки размера массива (размер не может быть 0 или отрицательным).
 * @return true если число положительное, false если нет
 */
bool checkPositive(const int value, const string &paramName) {
    if (value <= 0) {
        cout << "Ошибка! Параметр '" << paramName << "' должен быть положительным числом!" << endl;
        return false;
    }
    return true;
}

/**
 * Функция checkRandomBounds проверяет корректность границ для случайных чисел.
 * Минимальное значение не должно быть больше максимального.
 * @return true если границы корректны, false если нет
 */
bool checkRandomBounds(const int min, const int max) {
    if (min > max) {
        cout << "Ошибка! Минимальное значение (" << min << ") не может быть больше максимального (" << max << ")!" << endl;
        return false;
    }
    return true;
}

/**
 * Функция createArray создает вектор (динамический массив в C++) заданного размера.
 * Вектор сам управляет памятью, не нужно вызывать malloc/free.
 * @return вектор заданного размера
 */
vector<int> createArray(const size_t n) {
    return vector<int>(n);  // Создаем вектор из n элементов
}

/**
 * Функция printArray выводит все элементы массива через запятую.
 * Если массив пустой, выводит соответствующее сообщение.
 */
void printArray(const vector<int>& arr) {
    // Проверяем, не пустой ли массив
    if (arr.empty()) {
        cout << "Массив пуст" << endl;
        return;
    }
    
    // Проходим по всем элементам массива
    for (size_t i = 0; i < arr.size(); i++) {
        cout << arr[i];  // Выводим текущий элемент
        
        // Если это не последний элемент, добавляем запятую
        if (i < arr.size() - 1) {
            cout << ", ";
        }
    }
    cout << endl;  // Переход на новую строку в конце
}

/**
 * Функция fillArrayManually позволяет пользователю вручную ввести
 * все элементы массива.
 */
void fillArrayManually(vector<int>& arr) {
    cout << "Вам нужно ввести " << arr.size() << " чисел:" << endl;
    
    // Проходим по всем позициям массива
    for (size_t i = 0; i < arr.size(); i++) {
        cout << "Элемент " << i + 1 << " из " << arr.size() << ": ";
        arr[i] = checkValue();
    }
}

/**
 * Функция fillArrayRandomly заполняет массив случайными числами.
 * Сначала запрашивает у пользователя диапазон значений.
 */
void fillArrayRandomly(vector<int>& arr) {
    int minValue, maxValue;
    
    // Запрашиваем минимальное значение
    cout << "Введите минимальное значение для случайных чисел: ";
    minValue = checkValue();
    
    // Запрашиваем максимальное значение
    cout << "Введите максимальное значение для случайных чисел: ";
    maxValue = checkValue();
    
    // Проверяем корректность диапазона
    if (!checkRandomBounds(minValue, maxValue)) {
        return;  // Если ошибка, выходим из функции
    }
    
    // Заполняем массив случайными числами
    for (size_t i = 0; i < arr.size(); i++) {
        // Генерируем случайное число в диапазоне [minValue, maxValue]
        arr[i] = rand() % (maxValue - minValue + 1) + minValue;
    }
    
    cout << "Массив заполнен случайными числами от " << minValue << " до " << maxValue << endl;
}

/**
 * Функция replaceLastMultipleOfThree ищет в массиве последний элемент,
 * который делится на 3 без остатка, и заменяет его на 0.
 * Поиск идет с конца массива к началу.
 */
void replaceLastMultipleOfThree(vector<int>& arr) {
    // Если массив пустой, нечего заменять
    if (arr.empty()) {
        cout << "Массив пуст, заменять нечего." << endl;
        return;
    }
    
    // Идем с конца массива к началу (от последнего элемента к первому)
    for (size_t i = arr.size(); i > 0; i--) {
        size_t index = i - 1;  // Преобразуем в правильный индекс
        
        // Проверяем, делится ли текущий элемент на 3 без остатка
        if (arr[index] % 3 == 0) {
            cout << "Найден элемент arr[" << index << "] = " << arr[index] << ", который делится на 3." << endl;
            arr[index] = 0;  // Заменяем на 0
            return;  
        }
    }
    
    // Если дошли до сюда, значит не нашли ни одного элемента, кратного 3
    cout << "В массиве нет элементов, которые делятся на 3." << endl;
}

/**
 * Функция countEvenNumbers подсчитывает количество четных чисел в массиве.
 * Четное число - это число, которое делится на 2 без остатка.
 * @return количество четных чисел
 */
size_t countEvenNumbers(const vector<int>& arr) {
    size_t count = 0;  // Счетчик четных чисел
    
    // Проходим по всем элементам массива
    for (int num : arr) {
        // Проверяем четность (остаток от деления на 2 равен 0)
        if (num % 2 == 0) {
            count++;  // Увеличиваем счетчик
        }
    }
    
    return count;  
}

/**
 * Функция insertKAfterEven создает новый массив, в который копирует
 * все элементы исходного массива, а после каждого четного числа вставляет число K.
 * @return новый массив с вставленными числами K
 */
vector<int> insertKAfterEven(const vector<int>& arr, const int k) {
    // Считаем, сколько будет четных чисел (столько раз вставим K)
    size_t evenCount = countEvenNumbers(arr);
    
    // Новый размер = старый размер + количество вставок K
    size_t newSize = arr.size() + evenCount;
    
    // Создаем новый массив нужного размера
    vector<int> newArray(newSize);
    
    // Индекс для заполнения нового массива
    size_t newIndex = 0;
    
    // Проходим по всем элементам исходного массива
    for (size_t i = 0; i < arr.size(); i++) {
        // Копируем текущий элемент из старого массива в новый
        newArray[newIndex++] = arr[i];
        
        // Если элемент четный, добавляем после него число K
        if (arr[i] % 2 == 0) {
            newArray[newIndex++] = k;  // Вставляем K
        }
    }
    
    return newArray; 
}

/**
 * Функция createMfromP создает массив M из массива P по правилу:
 * - M[0] = 0, M[n-1] = 0
 * - Если (i+1) делится на 4: M[i] = 4 * |P[i]|
 * - Иначе: M[i] = -P[i] * (i+1)
 * @return новый массив M
 */
vector<int> createMfromP(const vector<int>& P) {
    // Создаем массив M такого же размера, как P
    vector<int> M(P.size());
    
    // Устанавливаем первый и последний элементы в 0
    if (!M.empty()) {
        M[0] = 0;
        M[M.size() - 1] = 0;
    }
    
    // Заполняем остальные элементы по правилу
    for (size_t i = 1; i + 1 < M.size(); i++) {
        // Проверяем, делится ли (i+1) на 4
        if ((i + 1) % 4 == 0) {
            // Если делится: M[i] = 4 * модуль(P[i])
            M[i] = 4 * abs(P[i]);
        } else {
            // Иначе: M[i] = -P[i] * (i+1)
            M[i] = -P[i] * static_cast<int>(i + 1);
        }
    }
    
    return M;  
}

/**
 * Функция getRecurent демонстрирует рекуррентный метод заполнения массива.
 * Она заполняет массив рекурсивно, вызывая саму себя для каждого следующего элемента.
 * Это пример рекурсии - функции, которая вызывает сама себя.
 */
void getRecurent(vector<int>& arr, const size_t index, const int min, const int max) {
    // Базовый случай рекурсии: если дошли до конца массива
    if (index >= arr.size()) {
        return;  // Завершаем рекурсию
    }
    
    // Рекуррентный шаг: заполняем текущий элемент случайным числом
    arr[index] = rand() % (max - min + 1) + min;
    
    // Рекурсивный вызов для следующего элемента
    getRecurent(arr, index + 1, min, max);
}
