#include <iostream>  
#include <cstdlib>   
#include <ctime>     
#include <limits>    

using namespace std;  

/**
 * @brief Перечисление для выбора способа заполнения массива
 */
enum Operation {
    FILL_MANUALLY = 0,  ///< Ручной ввод элементов массива
    FILL_RANDOMLY = 1   ///< Заполнение массива случайными числами
};

// Прототипы функций

/**
 * @brief Проверяет корректность ввода целого числа
 * @return Введенное пользователем целое число
 * @note При ошибке ввода завершает программу с кодом 1
 */
int checkValue();

/**
 * @brief Проверяет, является ли число положительным
 * @param value Проверяемое значение
 * @param paramName Название параметра для вывода в сообщении об ошибке
 * @return true если значение положительное, иначе false
 */
bool checkPositive(const int value, const string &paramName);

/**
 * @brief Проверяет корректность интервала (min <= max)
 * @param min Минимальное значение интервала
 * @param max Максимальное значение интервала
 * @return true если интервал корректен, иначе false
 */
bool checkInterval(const int min, const int max);

/**
 * @brief Создает динамический массив целых чисел
 * @param n Размер массива
 * @return Указатель на созданный массив
 */
int* createArray(const size_t n);

/**
 * @brief Освобождает память, занятую динамическим массивом
 * @param arr Указатель на массив для удаления
 */
void deleteArray(int* arr);

/**
 * @brief Выводит элементы массива в консоль
 * @param arr Массив для вывода
 * @param n Размер массива
 */
void printArray(const int* arr, const size_t n);

/**
 * @brief Заполняет массив значениями, введенными пользователем
 * @param arr Массив для заполнения
 * @param n Размер массива
 */
void fillArrayManually(int* arr, const size_t n);

/**
 * @brief Заполняет массив случайными числами в заданном диапазоне
 * @param arr Массив для заполнения
 * @param n Размер массива
 * @note Запрашивает у пользователя минимальное и максимальное значения
 */
void fillArrayRandomly(int* arr, const size_t n);

/**
 * @brief Вычисляет сумму однозначных чисел в массиве (от 0 до 9)
 * @param arr Массив для анализа
 * @param n Размер массива
 * @return Сумма однозначных чисел
 */
int sumOneDigitNumbers(const int* arr, const size_t n);

/**
 * @brief Переворачивает элементы массива между минимальным и максимальным элементами
 * @param arr Массив для обработки
 * @param n Размер массива
 * @note Изменяет исходный массив
 */
void reverseBetweenMinMax(int* arr, const size_t n);

/**
 * @brief Находит последнюю пару соседних элементов с одинаковыми знаками и произведением меньше X
 * @param arr Массив для поиска
 * @param n Размер массива
 * @param x Пороговое значение для произведения
 * @return Индекс первого элемента пары или -1 если пара не найдена
 */
int findLastPair(const int* arr, const size_t n, const int x);

/**
 * @brief Рекурсивно заполняет массив случайными числами
 * @param arr Массив для заполнения
 * @param index Текущий индекс для заполнения (начинается с 0)
 * @param n Размер массива
 * @param min Минимальное значение случайных чисел
 * @param max Максимальное значение случайных чисел
 */
void getRecurent(int* arr, const size_t index, const size_t n, const int min, const int max);

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    
    cout << "=== ЛАБОРАТОРНАЯ РАБОТА: РАБОТА С МАССИВАМИ ===" << endl;
    cout << "Программа выполняет различные операции с массивом целых чисел." << endl;
    
    int arraySize = 0;
    cout << "Шаг 1: Введите размер массива (положительное число): ";
    arraySize = checkValue();
    
    if (!checkPositive(arraySize, "Размер массива")) {
        return 1;  
    }
    
    int numberX = 0;
    cout << "Шаг 2: Введите число X (для поиска пар): ";
    numberX = checkValue();
    
    cout << "Шаг 3: Создаем массив размера " << arraySize << "..." << endl;
    int* myArray = createArray(static_cast<size_t>(arraySize));
    
    cout << "Выберите способ заполнения массива:" << endl;
    cout << FILL_MANUALLY << " - Ввести числа вручную" << endl;
    cout << FILL_RANDOMLY << " - Заполнить случайными числами" << endl;
    cout << "Ваш выбор: ";
    
    int choice = checkValue();
    
    switch(choice) {
        case FILL_MANUALLY:
            cout << "Выбран ручной ввод." << endl;
            fillArrayManually(myArray, static_cast<size_t>(arraySize));
            break;
            
        case FILL_RANDOMLY:
            cout << "Выбран случайный ввод." << endl;
            fillArrayRandomly(myArray, static_cast<size_t>(arraySize));
            break;
            
        default:
            cout << "Ошибка! Нужно было ввести 0 или 1." << endl;
            deleteArray(myArray);
            return 1;
    }
    
    cout << "=== РЕЗУЛЬТАТЫ ===" << endl;
    
    cout << "1. Исходный массив:" << endl;
    printArray(myArray, static_cast<size_t>(arraySize));
    
    cout << "2. Сумма однозначных чисел (от 0 до 9):" << endl;
    int oneDigitSum = sumOneDigitNumbers(myArray, static_cast<size_t>(arraySize));
    cout << "   Результат: " << oneDigitSum << endl;
    
    cout << "3. Переворачиваем элементы между минимальным и максимальным:" << endl;
    int* copiedArray = new int[static_cast<size_t>(arraySize)];
    for (size_t i = 0; i < static_cast<size_t>(arraySize); i++) {
        copiedArray[i] = myArray[i];
    }
    reverseBetweenMinMax(copiedArray, static_cast<size_t>(arraySize));
    cout << "   Результат: ";
    printArray(copiedArray, static_cast<size_t>(arraySize));
    delete[] copiedArray;
    
    cout << "4. Поиск последней пары соседних элементов:" << endl;
    cout << "   Условие: одинаковые знаки И произведение < " << numberX << endl;
    int pairIndex = findLastPair(myArray, static_cast<size_t>(arraySize), numberX);
    
    if (pairIndex != -1) {
        cout << "   Найдена пара на позициях " << pairIndex + 1 
             << " и " << pairIndex + 2 << endl;
        cout << "   Элементы: " << myArray[pairIndex] 
             << " и " << myArray[pairIndex + 1] << endl;
        cout << "   Произведение: " << myArray[pairIndex] * myArray[pairIndex + 1] << endl;
    } else {
        cout << "   Такая пара не найдена." << endl;
    }
    
    cout << "=== ДОПОЛНИТЕЛЬНО: РЕКУРРЕНТНЫЙ МЕТОД ===" << endl;
    cout << "Создаем маленький массив (5 элементов) и заполняем рекурсивно:" << endl;
    
    const size_t recurentSize = 5;
    int* recurentArray = createArray(recurentSize);
    getRecurent(recurentArray, 0, recurentSize, 1, 100);
    
    cout << "Массив, заполненный рекурсивно: ";
    printArray(recurentArray, recurentSize);
    deleteArray(recurentArray);
    
    deleteArray(myArray);
    
    cout << "=== РАБОТА ПРОГРАММЫ ЗАВЕРШЕНА ===" << endl;
    return 0;  
}

/**
 * @brief Проверяет корректность ввода целого числа
 * @return Введенное пользователем целое число
 * @note При ошибке ввода завершает программу с кодом 1
 */
int checkValue() {
    int value = 0;
    cin >> value;
    
    if (cin.fail()) {
        cout << "Ошибка ввода! Программа завершена." << endl;
        exit(1);
    }
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return value;
}

/**
 * @brief Проверяет, является ли число положительным
 * @param value Проверяемое значение
 * @param paramName Название параметра для вывода в сообщении об ошибке
 * @return true если значение положительное, иначе false
 */
bool checkPositive(const int value, const string &paramName) {
    if (value <= 0) {
        cout << "Ошибка! Параметр '" << paramName 
             << "' должен быть положительным числом!" << endl;
        return false;
    }
    return true;
}

/**
 * @brief Проверяет корректность интервала (min <= max)
 * @param min Минимальное значение интервала
 * @param max Максимальное значение интервала
 * @return true если интервал корректен, иначе false
 */
bool checkInterval(const int min, const int max) {
    if (min > max) {
        cout << "Ошибка! Минимальное значение (" << min 
             << ") не может быть больше максимального (" << max << ")!" << endl;
        return false;
    }
    return true;
}

/**
 * @brief Создает динамический массив целых чисел
 * @param n Размер массива
 * @return Указатель на созданный массив
 */
int* createArray(const size_t n) {
    return new int[n];
}

/**
 * @brief Освобождает память, занятую динамическим массивом
 * @param arr Указатель на массив для удаления
 */
void deleteArray(int* arr) {
    delete[] arr;
}

/**
 * @brief Выводит элементы массива в консоль
 * @param arr Массив для вывода
 * @param n Размер массива
 */
void printArray(const int* arr, const size_t n) {
    if (n <= 0) {
        cout << "Массив пуст" << endl;
        return;
    }
    
    for (size_t i = 0; i < n; i++) {
        cout << arr[i];
        if (i < n - 1) {
            cout << ", ";
        }
    }
    cout << endl;  
}

/**
 * @brief Заполняет массив значениями, введенными пользователем
 * @param arr Массив для заполнения
 * @param n Размер массива
 */
void fillArrayManually(int* arr, const size_t n) {
    cout << "Введите " << n << " чисел:" << endl;
    
    for (size_t i = 0; i < n; i++) {
        cout << "Элемент " << i + 1 << ": ";
        arr[i] = checkValue();
    }
}

/**
 * @brief Заполняет массив случайными числами в заданном диапазоне
 * @param arr Массив для заполнения
 * @param n Размер массива
 * @note Запрашивает у пользователя минимальное и максимальное значения
 */
void fillArrayRandomly(int* arr, const size_t n) {
    int minValue = 0;
    int maxValue = 0;
    
    cout << "Введите минимальное значение: ";
    minValue = checkValue();
    
    cout << "Введите максимальное значение: ";
    maxValue = checkValue();
    
    if (!checkInterval(minValue, maxValue)) {
        return; 
    }
    
    for (size_t i = 0; i < n; i++) {
        arr[i] = rand() % (maxValue - minValue + 1) + minValue;
    }
    
    cout << "Массив успешно заполнен случайными числами от " 
         << minValue << " до " << maxValue << endl;
}

/**
 * @brief Вычисляет сумму однозначных чисел в массиве (от 0 до 9)
 * @param arr Массив для анализа
 * @param n Размер массива
 * @return Сумма однозначных чисел
 */
int sumOneDigitNumbers(const int* arr, const size_t n) {
    int sum = 0;
    
    for (size_t i = 0; i < n; i++) {
        if (arr[i] >= 0 && arr[i] < 10) {
            sum += arr[i];
        }
    }
    
    return sum;  
}

/**
 * @brief Переворачивает элементы массива между минимальным и максимальным элементами
 * @param arr Массив для обработки
 * @param n Размер массива
 * @note Изменяет исходный массив
 */
void reverseBetweenMinMax(int* arr, const size_t n) {
    if (n < 2) {
        cout << "Массив слишком маленький для этой операции." << endl;
        return;
    }
    
    size_t minIndex = 0;
    size_t maxIndex = 0;
    
    for (size_t i = 1; i < n; i++) {
        if (arr[i] < arr[minIndex]) {
            minIndex = i;
        }
        if (arr[i] > arr[maxIndex]) {
            maxIndex = i;
        }
    }
    
    if (minIndex == maxIndex) {
        cout << "Минимальный и максимальный элементы совпадают." << endl;
        return;
    }
    
    if (minIndex > maxIndex) {
        swap(minIndex, maxIndex);
    }
    
    size_t left = minIndex + 1;
    size_t right = maxIndex - 1;
    
    while (left < right) {
        swap(arr[left], arr[right]);
        left++;
        right--;
    }
    
    cout << "Перевернуты элементы между позициями " 
         << minIndex + 1 << " и " << maxIndex + 1 << endl;
}

/**
 * @brief Находит последнюю пару соседних элементов с одинаковыми знаками и произведением меньше X
 * @param arr Массив для поиска
 * @param n Размер массива
 * @param x Пороговое значение для произведения
 * @return Индекс первого элемента пары или -1 если пара не найдена
 */
int findLastPair(const int* arr, const size_t n, const int x) {
    int lastFoundIndex = -1;
    
    for (size_t i = 0; i < n - 1; i++) {
        bool sameSign = (arr[i] >= 0 && arr[i + 1] >= 0) || 
                       (arr[i] < 0 && arr[i + 1] < 0);
        
        if (sameSign && arr[i] * arr[i + 1] < x) {
            lastFoundIndex = static_cast<int>(i);
        }
    }
    
    return lastFoundIndex;
}

/**
 * @brief Рекурсивно заполняет массив случайными числами
 * @param arr Массив для заполнения
 * @param index Текущий индекс для заполнения (начинается с 0)
 * @param n Размер массива
 * @param min Минимальное значение случайных чисел
 * @param max Максимальное значение случайных чисел
 */
void getRecurent(int* arr, const size_t index, const size_t n, const int min, const int max) {
    if (index >= n) {
        return;  
    }
    
    arr[index] = rand() % (max - min + 1) + min;
    getRecurent(arr, index + 1, n, min, max);
}
