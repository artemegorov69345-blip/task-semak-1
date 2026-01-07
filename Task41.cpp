#include <iostream>  
#include <cstdlib>   
#include <ctime>     
#include <limits>    
#include <vector>    

using namespace std;  

/**
 * @brief Перечисление для выбора способа заполнения матрицы
 * 
 * Определяет возможные способы заполнения матрицы, которые пользователь
 * может выбрать при запуске программы.
 */
enum Operation {
    FILL_MANUALLY = 0,  
    FILL_RANDOMLY = 1   
};

/**
* @brief Проверяет, правильно ли введено целое число
* @return считанное число или программа завершается при ошибке
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
bool checkInterval(const int min, const int max);

/**
* @brief Создает массив (вектор) заданного размера
* @param n - размер массива
* @return готовый вектор нужного размера
*/
vector<int> createArray(const size_t n);

/**
* @brief Показывает массив на экране
* @param arr - массив для вывода
*/
void printArray(const vector<int>& arr);

/**
* @brief Заполняет массив числами, которые вводит пользователь
* @param arr - массив для заполнения
*/
void fillArrayManually(vector<int>& arr);

/**
* @brief Заполняет массив случайными числами
* @param arr - массив для заполнения
*/
void fillArrayRandomly(vector<int>& arr);

/**
* @brief Считает сумму всех однозначных чисел в массиве
* @param arr - массив для обработки
* @return сумму однозначных чисел
*/
int sumOneDigitNumbers(const vector<int>& arr);

/**
* @brief Переворачивает часть массива между минимальным и максимальным элементами
* @param arr - массив для изменения
*/
void reverseBetweenMinMax(vector<int>& arr);

/**
* @brief Ищет последнюю пару соседних чисел с одинаковыми знаками, чье произведение меньше x
* @param arr - массив для поиска
* @param x - число для сравнения
* @return индекс первого элемента пары или -1 если пара не найдена
*/
int findLastPair(const vector<int>& arr, const int x);

/**
* @brief Заполняет массив случайными числами рекурсивно (демонстрация рекуррентного метода)
* @param arr - массив для заполнения
* @param index - текущий индекс (начинается с 0)
* @param min - минимальное значение
* @param max - максимальное значение
*/
void getRecurent(vector<int>& arr, const int index, const int min, const int max);


/**
 * @brief Главная функция программы
 * @return 0 если все успешно, 1 если ошибка
 */
int main() {
    // Инициализируем генератор случайных чисел текущим временем
    srand(time(nullptr));
    
    cout << "=== ЛАБОРАТОРНАЯ РАБОТА: РАБОТА С МАССИВАМИ ===" << endl;
    cout << "Программа выполняет различные операции с массивом целых чисел." << endl;
    
    int arraySize = 0;
    cout << "Шаг 1: Введите размер массива (положительное число): ";
    arraySize = checkValue();
    
    // Проверяем, что размер положительный с помощью checkPositive
    if (!checkPositive(arraySize, "Размер массива")) {
        return 1;  
    }
    
    int numberX = 0;
    cout << "Шаг 2: Введите число X (для поиска пар): ";
    numberX = checkValue();
    
    cout << "Шаг 3: Создаем массив размера " << arraySize << "..." << endl;
    vector<int> myArray = createArray(arraySize);
    
    cout << "Выберите способ заполнения массива:" << endl;
    cout << FILL_MANUALLY << " - Ввести числа вручную" << endl;
    cout << FILL_RANDOMLY << " - Заполнить случайными числами" << endl;
    cout << "Ваш выбор: ";
    
    int choice = checkValue();
    
    // Обрабатываем выбор пользователя
    switch(choice) {
        case FILL_MANUALLY:
            cout << "Выбран ручной ввод." << endl;
            fillArrayManually(myArray);
            break;
            
        case FILL_RANDOMLY:
            cout << "Выбран случайный ввод." << endl;
            fillArrayRandomly(myArray);
            break;
            
        default:
            // Если ввели не 0 и не 1
            cout << "Ошибка! Нужно было ввести 0 или 1." << endl;
            return 1;
    }
    
    cout << "=== РЕЗУЛЬТАТЫ ===" << endl;
    
    // Выводим исходный массив
    cout << "1. Исходный массив:" << endl;
    printArray(myArray);
    
    // Считаем и выводим сумму однозначных чисел
    cout << "2. Сумма однозначных чисел (от 0 до 9):" << endl;
    int oneDigitSum = sumOneDigitNumbers(myArray);
    cout << "   Результат: " << oneDigitSum << endl;
    
    // Переворачиваем часть между min и max
    cout << "3. Переворачиваем элементы между минимальным и максимальным:" << endl;
    vector<int> copiedArray(myArray);  // Создаем копию, чтобы не испортить оригинал
    reverseBetweenMinMax(copiedArray);
    cout << "   Результат: ";
    printArray(copiedArray);
    
    // Ищем последнюю пару
    cout << "4. Поиск последней пары соседних элементов:" << endl;
    cout << "   Условие: одинаковые знаки И произведение < " << numberX << endl;
    int pairIndex = findLastPair(myArray, numberX);
    
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
    
    vector<int> recurentArray(5);
    getRecurent(recurentArray, 0, 1, 100);  // Заполняем числами от 1 до 100
    
    cout << "Массив, заполненный рекурсивно: ";
    printArray(recurentArray);
    
    cout << "=== РАБОТА ПРОГРАММЫ ЗАВЕРШЕНА ===" << endl;
    return 0;  
}

/**
 * Функция checkValue проверяет, правильно ли пользователь ввел целое число.
 * @return считанное целое число
 */
int checkValue() {
    int value;
    cin >> value;  // Пытаемся считать число
    
    // Если произошла ошибка (например, ввели буквы вместо цифр)
    if (cin.fail()) {
        cout << "Ошибка ввода! Программа завершена." << endl;
        exit(1);
    }
    
    // Очищаем буфер ввода
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return value;  // Возвращаем считанное значение
}

/**
 * Функция checkPositive проверяет, является ли число положительным.
 * Используется для проверки размера массива.
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
 * Функция checkInterval проверяет, что минимум не больше максимума.
 * Нужна для задания границ случайных чисел.
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
 * Функция createArray создает вектор (динамический массив) заданного размера.
 * В C++ vector сам управляет памятью, поэтому не нужно malloc/free.
 */
vector<int> createArray(const size_t n) {
    return vector<int>(n);  // Создаем вектор из n элементов
}

/**
 * Функция printArray выводит все элементы массива через запятую.
 */
void printArray(const vector<int>& arr) {
    // Если массив пустой, выводим сообщение
    if (arr.empty()) {
        cout << "Массив пуст" << endl;
        return;
    }
    
    // Проходим по всем элементам массива
    for (size_t i = 0; i < arr.size(); i++) {
        cout << arr[i];  // Выводим элемент
        
        // Если это не последний элемент, добавляем запятую
        if (i < arr.size() - 1) {
            cout << ", ";
        }
    }
    cout << endl;  
}

/**
 * Функция fillArrayManually позволяет пользователю ввести все числа массива вручную.
 */
void fillArrayManually(vector<int>& arr) {
    cout << "Введите " << arr.size() << " чисел:" << endl;
    
    for (size_t i = 0; i < arr.size(); i++) {
        cout << "Элемент " << i + 1 << ": ";
        arr[i] = checkValue();
    }
}

/**
 * Функция fillArrayRandomly заполняет массив случайными числами в заданном диапазоне.
 * Сначала запрашиваем у пользователя границы диапазона.
 */
void fillArrayRandomly(vector<int>& arr) {
    int minValue = 0;
    int maxValue = 0;
    
    // Запрашиваем минимальное значение
    cout << "Введите минимальное значение: ";
    minValue = checkValue();
    
    // Запрашиваем максимальное значение
    cout << "Введите максимальное значение: ";
    maxValue = checkValue();
    
    // Проверяем, что диапазон корректен
    if (!checkInterval(minValue, maxValue)) {
        return; 
    }
    
    // Заполняем массив случайными числами
    for (size_t i = 0; i < arr.size(); i++) {
        // Генерируем случайное число в диапазоне [minValue, maxValue]
        arr[i] = rand() % (maxValue - minValue + 1) + minValue;
    }
    
    cout << "Массив успешно заполнен случайными числами от " 
         << minValue << " до " << maxValue << endl;
}

/**
 * Функция sumOneDigitNumbers считает сумму всех чисел от 0 до 9 включительно.
 * Такие числа называются однозначными.
 */
int sumOneDigitNumbers(const vector<int>& arr) {
    int sum = 0;  // Начинаем с нуля
    
    // Проходим по всем элементам массива
    for (int num : arr) {
        // Проверяем, что число в диапазоне от 0 до 9
        if (num >= 0 && num < 10) {
            sum += num;  // Добавляем к сумме
        }
    }
    
    return sum;  
}

/**
 * Функция reverseBetweenMinMax находит минимальный и максимальный элементы,
 * а затем переворачивает часть массива между ними.
 */
void reverseBetweenMinMax(vector<int>& arr) {
    // Если массив слишком маленький, ничего не делаем
    if (arr.size() < 2) {
        cout << "Массив слишком маленький для этой операции." << endl;
        return;
    }
    
    // Ищем индексы минимального и максимального элементов
    size_t minIndex = 0;  // Начинаем с первого элемента
    size_t maxIndex = 0;
    
    // Проходим по массиву и ищем минимум и максимум
    for (size_t i = 1; i < arr.size(); i++) {
        if (arr[i] < arr[minIndex]) {
            minIndex = i;  // Нашли новый минимум
        }
        if (arr[i] > arr[maxIndex]) {
            maxIndex = i;  // Нашли новый максимум
        }
    }
    
    // Если минимум и максимум на одной позиции, нечего переворачивать
    if (minIndex == maxIndex) {
        cout << "Минимальный и максимальный элементы совпадают." << endl;
        return;
    }
    
    // Убеждаемся, что minIndex меньше maxIndex
    if (minIndex > maxIndex) {
        swap(minIndex, maxIndex);  // Меняем местами
    }
    
    // Переворачиваем элементы между minIndex и maxIndex
    // Используем два указателя: один идет слева, другой справа
    size_t left = minIndex + 1;
    size_t right = maxIndex - 1;
    
    while (left < right) {
        // Меняем местами элементы на позициях left и right
        swap(arr[left], arr[right]);
        
        // Двигаем указатели к центру
        left++;
        right--;
    }
    
    cout << "Перевернуты элементы между позициями " 
         << minIndex + 1 << " и " << maxIndex + 1 << endl;
}

/**
 * Функция findLastPair ищет последнюю пару соседних элементов,
 * у которых одинаковые знаки и произведение меньше заданного числа X.
 */
int findLastPair(const vector<int>& arr, const int x) {
    int lastFoundIndex = -1;  // -1 значит "не найдено"
    
    // Проходим по массиву, останавливаясь на предпоследнем элементе
    for (size_t i = 0; i < arr.size() - 1; i++) {
        // Проверяем, что знаки одинаковые (оба положительные или оба отрицательные)
        bool sameSign = (arr[i] >= 0 && arr[i + 1] >= 0) || 
                       (arr[i] < 0 && arr[i + 1] < 0);
        
        // Если знаки одинаковые И произведение меньше X
        if (sameSign && arr[i] * arr[i + 1] < x) {
            lastFoundIndex = static_cast<int>(i);  // Запоминаем индекс
            // Не прерываем цикл, ищем последнюю такую пару
        }
    }
    
    return lastFoundIndex;
}

/**
 * Функция getRecurent демонстрирует рекуррентный метод заполнения массива.
 * Она заполняет массив рекурсивно, вызывая саму себя для каждого следующего элемента.
 */
void getRecurent(vector<int>& arr, const int index, const int min, const int max) {
    // Базовый случай рекурсии: если дошли до конца массива
    if (index >= static_cast<int>(arr.size())) {
        return;  
    }
    
    // Рекуррентный шаг: заполняем текущий элемент
    arr[index] = rand() % (max - min + 1) + min;
    
    // Рекурсивный вызов для следующего элемента
    // Это и есть рекуррентный метод: текущее состояние зависит от предыдущего
    getRecurent(arr, index + 1, min, max);
}
