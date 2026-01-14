#include <iostream>  
#include <cstdlib>   
#include <ctime>     
#include <limits>    

using namespace std;  

/**
 * @brief Перечисление для выбора способа заполнения массива
 */
enum Operation {
    FILL_MANUALLY = 0,  
    FILL_RANDOMLY = 1   
};

// Прототипы функций
int checkValue();
bool checkPositive(const int value, const string &paramName);
bool checkInterval(const int min, const int max);
int* createArray(const int n);
void deleteArray(int* arr);
void printArray(const int* arr, const int n);
void fillArrayManually(int* arr, const int n);
void fillArrayRandomly(int* arr, const int n);
int sumOneDigitNumbers(const int* arr, const int n);
void reverseBetweenMinMax(int* arr, const int n);
int findLastPair(const int* arr, const int n, const int x);
void getRecurent(int* arr, const int index, const int n, const int min, const int max);


int main() {
    srand(time(nullptr));
    
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
    int* myArray = createArray(arraySize);
    
    cout << "Выберите способ заполнения массива:" << endl;
    cout << FILL_MANUALLY << " - Ввести числа вручную" << endl;
    cout << FILL_RANDOMLY << " - Заполнить случайными числами" << endl;
    cout << "Ваш выбор: ";
    
    int choice = checkValue();
    
    switch(choice) {
        case FILL_MANUALLY:
            cout << "Выбран ручной ввод." << endl;
            fillArrayManually(myArray, arraySize);
            break;
            
        case FILL_RANDOMLY:
            cout << "Выбран случайный ввод." << endl;
            fillArrayRandomly(myArray, arraySize);
            break;
            
        default:
            cout << "Ошибка! Нужно было ввести 0 или 1." << endl;
            deleteArray(myArray);
            return 1;
    }
    
    cout << "=== РЕЗУЛЬТАТЫ ===" << endl;
    
    cout << "1. Исходный массив:" << endl;
    printArray(myArray, arraySize);
    
    cout << "2. Сумма однозначных чисел (от 0 до 9):" << endl;
    int oneDigitSum = sumOneDigitNumbers(myArray, arraySize);
    cout << "   Результат: " << oneDigitSum << endl;
    
    cout << "3. Переворачиваем элементы между минимальным и максимальным:" << endl;
    int* copiedArray = new int[arraySize];
    for (int i = 0; i < arraySize; i++) {
        copiedArray[i] = myArray[i];
    }
    reverseBetweenMinMax(copiedArray, arraySize);
    cout << "   Результат: ";
    printArray(copiedArray, arraySize);
    delete[] copiedArray;
    
    cout << "4. Поиск последней пары соседних элементов:" << endl;
    cout << "   Условие: одинаковые знаки И произведение < " << numberX << endl;
    int pairIndex = findLastPair(myArray, arraySize, numberX);
    
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
    
    int recurentSize = 5;
    int* recurentArray = createArray(recurentSize);
    getRecurent(recurentArray, 0, recurentSize, 1, 100);
    
    cout << "Массив, заполненный рекурсивно: ";
    printArray(recurentArray, recurentSize);
    deleteArray(recurentArray);
    
    deleteArray(myArray);
    
    cout << "=== РАБОТА ПРОГРАММЫ ЗАВЕРШЕНА ===" << endl;
    return 0;  
}

int checkValue() {
    int value;
    cin >> value;
    
    if (cin.fail()) {
        cout << "Ошибка ввода! Программа завершена." << endl;
        exit(1);
    }
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return value;
}

bool checkPositive(const int value, const string &paramName) {
    if (value <= 0) {
        cout << "Ошибка! Параметр '" << paramName 
             << "' должен быть положительным числом!" << endl;
        return false;
    }
    return true;
}

bool checkInterval(const int min, const int max) {
    if (min > max) {
        cout << "Ошибка! Минимальное значение (" << min 
             << ") не может быть больше максимального (" << max << ")!" << endl;
        return false;
    }
    return true;
}

int* createArray(const int n) {
    return new int[n];
}

void deleteArray(int* arr) {
    delete[] arr;
}

void printArray(const int* arr, const int n) {
    if (n <= 0) {
        cout << "Массив пуст" << endl;
        return;
    }
    
    for (int i = 0; i < n; i++) {
        cout << arr[i];
        if (i < n - 1) {
            cout << ", ";
        }
    }
    cout << endl;  
}

void fillArrayManually(int* arr, const int n) {
    cout << "Введите " << n << " чисел:" << endl;
    
    for (int i = 0; i < n; i++) {
        cout << "Элемент " << i + 1 << ": ";
        arr[i] = checkValue();
    }
}

void fillArrayRandomly(int* arr, const int n) {
    int minValue = 0;
    int maxValue = 0;
    
    cout << "Введите минимальное значение: ";
    minValue = checkValue();
    
    cout << "Введите максимальное значение: ";
    maxValue = checkValue();
    
    if (!checkInterval(minValue, maxValue)) {
        return; 
    }
    
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % (maxValue - minValue + 1) + minValue;
    }
    
    cout << "Массив успешно заполнен случайными числами от " 
         << minValue << " до " << maxValue << endl;
}

int sumOneDigitNumbers(const int* arr, const int n) {
    int sum = 0;
    
    for (int i = 0; i < n; i++) {
        if (arr[i] >= 0 && arr[i] < 10) {
            sum += arr[i];
        }
    }
    
    return sum;  
}

void reverseBetweenMinMax(int* arr, const int n) {
    if (n < 2) {
        cout << "Массив слишком маленький для этой операции." << endl;
        return;
    }
    
    int minIndex = 0;
    int maxIndex = 0;
    
    for (int i = 1; i < n; i++) {
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
    
    int left = minIndex + 1;
    int right = maxIndex - 1;
    
    while (left < right) {
        swap(arr[left], arr[right]);
        left++;
        right--;
    }
    
    cout << "Перевернуты элементы между позициями " 
         << minIndex + 1 << " и " << maxIndex + 1 << endl;
}

int findLastPair(const int* arr, const int n, const int x) {
    int lastFoundIndex = -1;
    
    for (int i = 0; i < n - 1; i++) {
        bool sameSign = (arr[i] >= 0 && arr[i + 1] >= 0) || 
                       (arr[i] < 0 && arr[i + 1] < 0);
        
        if (sameSign && arr[i] * arr[i + 1] < x) {
            lastFoundIndex = i;
        }
    }
    
    return lastFoundIndex;
}

void getRecurent(int* arr, const int index, const int n, const int min, const int max) {
    if (index >= n) {
        return;  
    }
    
    arr[index] = rand() % (max - min + 1) + min;
    getRecurent(arr, index + 1, n, min, max);
}
