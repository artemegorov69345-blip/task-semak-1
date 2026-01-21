#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <cmath>
#include <limits>
#include <algorithm>

using namespace std;

/**
 * @brief Перечисление для выбора способа заполнения двумерного массива
 * @details Определяет два возможных способа заполнения:
 *          - Ручной ввод пользователем
 *          - Автоматическое заполнение случайными числами
 */
enum FillMode {
    FILL_MANUALLY = 1,    // Ручное заполнение пользователем
    FILL_RANDOMLY = 2     // Автоматическое заполнение случайными числами
};

/**
 * @brief Проверяет корректность ввода целочисленного значения
 * @param value - ссылка на переменную для сохранения введенного значения
 * @return true - если ввод корректен, false - если введены некорректные данные
 * @details Функция проверяет успешность операции ввода.
 *          В случае ошибки очищает флаги состояния потока и буфер ввода.
 */
bool checkValue(int &value);

/**
 * @brief Проверяет, является ли значение положительным
 * @param value - проверяемое значение
 * @param paramName - название параметра для вывода в сообщении об ошибке
 * @return true - если значение положительное, false - в противном случае
 */
bool checkPositive(const int value, const string &paramName);

/**
 * @brief Создает двумерный массив заданного размера n x m
 * @param n - количество строк в массиве
 * @param m - количество столбцов в массиве
 * @return int** - указатель на созданный двумерный массив
 * @details Функция динамически выделяет память под массив.
 *          Проверяет корректность размеров перед выделением памяти.
 */
int** createArray(const int n, const int m);

/**
 * @brief Освобождает память, занятую двумерным массивом
 * @param array - указатель на массив для освобождения
 * @param n - количество строк в массиве
 */
void deleteArray(int** array, const int n);

/**
 * @brief Выводит двумерный массив на экран в табличном формате
 * @param array - указатель на массив для вывода
 * @param n - количество строк в массиве
 * @param m - количество столбцов в массиве
 * @details Форматирует вывод для удобного чтения с заголовками строк и столбцов
 */
void printArray(int* const* const array, const int n, const int m);

/**
 * @brief Заполняет массив значениями, введенными пользователем с клавиатуры
 * @param array - указатель на массив для заполнения
 * @param n - количество строк в массиве
 * @param m - количество столбцов в массиве
 */
void fillArrayManually(int** array, const int n, const int m);

/**
 * @brief Заполняет массив случайными числами в заданном диапазоне
 * @param array - указатель на массив для заполнения
 * @param n - количество строк в массиве
 * @param m - количество столбцов в массиве
 */
void fillArrayRandomly(int** array, const int n, const int m);

/**
 * @brief Находит максимальный по модулю элемент в указанном столбце массива
 * @param array - указатель на массив
 * @param n - количество строк в массиве
 * @param col - номер столбца (начинается с 0)
 * @return int - максимальное абсолютное значение элемента в столбце
 */
int findMaxAbsInColumn(int* const* const array, const int n, const int col);

/**
 * @brief Заменяет четные элементы каждого столбца максимальным по модулю элементом этого столбца
 * @param array - указатель на массив для модификации
 * @param n - количество строк в массиве
 * @param m - количество столбцов в массиве
 */
void replaceEvenWithMaxAbs(int** array, const int n, const int m);

/**
 * @brief Проверяет, является ли первый элемент указанного столбца четным числом
 * @param array - указатель на массив
 * @param col - номер столбца
 * @return true - если первый элемент четный, false - в противном случае
 */
bool isFirstElementEven(int* const* const array, const int col);

/**
 * @brief Удаляет все столбцы, в которых первый элемент является четным числом
 * @param array - ссылка на указатель массива для обработки
 * @param n - количество строк в массиве
 * @param m - ссылка на количество столбцов в массиве
 */
void deleteColumnsWithEvenFirst(int**& array, const int n, int& m);

/**
 * @brief Рекурсивно заполняет строку массива случайными числами
 * @param array - указатель на массив
 * @param row - номер строки для заполнения
 * @param col - текущий столбец для заполнения
 * @param cols - общее количество столбцов
 * @param min - минимальное значение случайного числа
 * @param max - максимальное значение случайного числа
 * @details Использует рекурсию для заполнения строки слева направо
 */
void fillRowRecursively(int** array, const int row, int col, const int cols, 
                        const int min, const int max);

int main() {
    cout << "=== РАБОТА С ДВУМЕРНЫМ МАССИВОМ n x m ===" << endl;
    
    // Ввод количества строк массива с инициализацией
    int n = 0;
    cout << "Введите количество строк массива (n > 0): ";
    
    while (!checkValue(n)) {
        cout << "Ошибка! Нужно ввести целое число. Попробуйте снова: ";
    }
    
    if (!checkPositive(n, "Количество строк")) {
        cout << "Программа завершена из-за ошибки ввода." << endl;
        return 1;
    }
    
    // Ввод количества столбцов массива с инициализацией
    int m = 0;
    cout << "Введите количество столбцов массива (m > 0): ";
    
    while (!checkValue(m)) {
        cout << "Ошибка! Нужно ввести целое число. Попробуйте снова: ";
    }
    
    if (!checkPositive(m, "Количество столбцов")) {
        cout << "Программа завершена из-за ошибки ввода." << endl;
        return 1;
    }
    
    // Создание массива с проверкой
    cout << "Создаем массив " << n << " x " << m << "..." << endl;
    int** originalArray = nullptr;
    
    try {
        originalArray = createArray(n, m);
        cout << "Память успешно выделена для массива размером " << n << " строк x " << m << " столбцов" << endl;
    } catch (const bad_alloc& e) {
        cout << "Ошибка! Не удалось выделить память для массива." << endl;
        cout << "Сообщение системы: " << e.what() << endl;
        return 1;
    }
    
    // Выбор способа заполнения
    cout << "\nВыберите способ заполнения массива:" << endl;
    cout << FILL_MANUALLY << " - Ввод вручную" << endl;
    cout << FILL_RANDOMLY << " - Заполнение случайными числами" << endl;
    cout << "Ваш выбор (" << FILL_MANUALLY << " или " << FILL_RANDOMLY << "): ";
    
    int choice = 0;
    while (!checkValue(choice) || (choice != FILL_MANUALLY && choice != FILL_RANDOMLY)) {
        cout << "Ошибка! Введите " << FILL_MANUALLY << " или " << FILL_RANDOMLY << ": ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
    // Заполнение массива в зависимости от выбора
    switch(choice) {
        case FILL_MANUALLY:
            fillArrayManually(originalArray, n, m);
            break;
        case FILL_RANDOMLY:
            // Инициализация генератора случайных чисел только при необходимости
            srand(static_cast<unsigned>(time(nullptr)));
            fillArrayRandomly(originalArray, n, m);
            break;
        default:
            cout << "Критическая ошибка: некорректный выбор заполнения!" << endl;
            deleteArray(originalArray, n);
            return 1;
    }
    
    // Вывод исходного массива
    cout << "\n=== ИСХОДНЫЙ МАССИВ ===" << endl;
    printArray(originalArray, n, m);
    
    // 1. Замена четных элементов каждого столбца максимальным по модулю элементом
    cout << "\n=== ЗАМЕНА ЧЕТНЫХ ЭЛЕМЕНТОВ ===" << endl;
    cout << "Заменяем четные элементы каждого столбца максимальным по модулю элементом этого столбца..." << endl;
    
    // Создаем копию для обработки
    int** arrayCopy1 = createArray(n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            arrayCopy1[i][j] = originalArray[i][j];
        }
    }
    
    replaceEvenWithMaxAbs(arrayCopy1, n, m);
    
    cout << "Результат преобразования:" << endl;
    printArray(arrayCopy1, n, m);
    
    // 2. Удаление столбцов с четным первым элементом
    cout << "\n=== УДАЛЕНИЕ СТОЛБЦОВ ===" << endl;
    cout << "Удаляем все столбцы, в которых первый элемент четный..." << endl;
    
    // Создаем еще одну копию для обработки
    int** arrayCopy2 = createArray(n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            arrayCopy2[i][j] = originalArray[i][j];
        }
    }
    
    int newM = m;
    deleteColumnsWithEvenFirst(arrayCopy2, n, newM);
    
    if (newM == 0) {
        cout << "Все столбцы были удалены! Массив стал пустым." << endl;
        deleteArray(arrayCopy2, n);
    } else {
        cout << "Результат (новый размер: " << n << " строк x " << newM << " столбцов):" << endl;
        printArray(arrayCopy2, n, newM);
        deleteArray(arrayCopy2, n);
    }
    
    // 3. Демонстрация рекуррентного метода заполнения
    cout << "\n=== ДЕМОНСТРАЦИЯ РЕКУРСИВНОГО МЕТОДА ===" << endl;
    cout << "Создаем массив 3x3 и заполняем его рекурсивно:" << endl;
    
    // Создаем отдельный массив для демонстрации
    int** recursiveArray = createArray(3, 3);
    if (recursiveArray != nullptr) {
        // Инициализируем генератор случайных чисел для рекурсивного заполнения
        srand(static_cast<unsigned>(time(nullptr)) + 1);
        
        for (int i = 0; i < 3; i++) {
            fillRowRecursively(recursiveArray, i, 0, 3, 1, 100);
        }
        
        cout << "Массив, заполненный рекурсивным методом:" << endl;
        printArray(recursiveArray, 3, 3);
        deleteArray(recursiveArray, 3);
    } else {
        cout << "Не удалось создать массив для демонстрации рекурсивного метода." << endl;
    }
    
    // Освобождение памяти исходного массива и копии
    deleteArray(originalArray, n);
    deleteArray(arrayCopy1, n);
    
    cout << "\n=== ПРОГРАММА УСПЕШНО ЗАВЕРШЕНА ===" << endl;
    return 0;
}

// Реализации функций

bool checkValue(int &value) {
    if (!(cin >> value)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }
    return true;
}

bool checkPositive(const int value, const string &paramName) {
    if (value <= 0) {
        cout << "Ошибка! " << paramName << " должен быть положительным целым числом!" << endl;
        return false;
    }
    return true;
}

int** createArray(const int n, const int m) {
    if (n <= 0) {
        throw invalid_argument("Количество строк должно быть положительным");
    }
    if (m <= 0) {
        throw invalid_argument("Количество столбцов должно быть положительным");
    }
    
    int** array = new int*[n];
    for (int i = 0; i < n; i++) {
        array[i] = new int[m];
    }
    
    return array;
}

void deleteArray(int** array, const int n) {
    if (array == nullptr) return;
    
    for (int i = 0; i < n; i++) {
        delete[] array[i];
    }
    delete[] array;
}

void printArray(int* const* const array, const int n, const int m) {
    if (array == nullptr) {
        cout << "Массив пуст!" << endl;
        return;
    }
    
    // Вывод заголовков столбцов
    cout << "       ";
    for (int j = 0; j < m; j++) {
        cout << setw(6) << "Стлб " << j + 1;
    }
    cout << endl;
    
    // Вывод разделительной линии
    cout << "      +";
    for (int j = 0; j < m; j++) {
        cout << "------+";
    }
    cout << endl;
    
    // Вывод строк массива
    for (int i = 0; i < n; i++) {
        cout << "Стр " << setw(2) << i + 1 << " |";
        for (int j = 0; j < m; j++) {
            cout << setw(6) << array[i][j] << "|";
        }
        cout << endl;
        
        // Вывод разделительной линии между строками
        if (i < n - 1) {
            cout << "      +";
            for (int j = 0; j < m; j++) {
                cout << "------+";
            }
            cout << endl;
        }
    }
    
    // Нижняя граница
    cout << "      +";
    for (int j = 0; j < m; j++) {
        cout << "------+";
    }
    cout << endl;
}

void fillArrayManually(int** array, const int n, const int m) {
    cout << "Введите элементы массива " << n << " x " << m << ":" << endl;
    
    for (int i = 0; i < n; i++) {
        cout << "Строка " << i + 1 << ":" << endl;
        for (int j = 0; j < m; j++) {
            cout << "  Элемент [" << i + 1 << "][" << j + 1 << "]: ";
            
            while (!checkValue(array[i][j])) {
                cout << "  Ошибка! Введите целое число: ";
            }
        }
    }
    cout << "Массив успешно заполнен вручную." << endl;
}

void fillArrayRandomly(int** array, const int n, const int m) {
    int minValue = 0;
    int maxValue = 0;
    
    cout << "Введите минимальное значение для случайных чисел: ";
    while (!checkValue(minValue)) {
        cout << "Ошибка! Введите целое число: ";
    }
    
    cout << "Введите максимальное значение для случайных чисел: ";
    while (!checkValue(maxValue)) {
        cout << "Ошибка! Введите целое число: ";
    }
    
    if (minValue > maxValue) {
        cout << "Предупреждение: Минимальное значение больше максимального." << endl;
        cout << "Меняю значения местами." << endl;
        swap(minValue, maxValue);
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            array[i][j] = rand() % (maxValue - minValue + 1) + minValue;
        }
    }
    
    cout << "Массив заполнен случайными числами в диапазоне [" 
         << minValue << ", " << maxValue << "]" << endl;
}

int findMaxAbsInColumn(int* const* const array, const int n, const int col) {
    if (array == nullptr) {
        return 0;
    }
    
    int maxAbs = abs(array[0][col]);
    
    for (int i = 1; i < n; i++) {
        int currentAbs = abs(array[i][col]);
        if (currentAbs > maxAbs) {
            maxAbs = currentAbs;
        }
    }
    
    return maxAbs;
}

void replaceEvenWithMaxAbs(int** array, const int n, const int m) {
    if (array == nullptr) return;
    
    // Находим максимальные по модулю значения для каждого столбца
    int* maxAbsValues = new int[m];
    for (int j = 0; j < m; j++) {
        maxAbsValues[j] = findMaxAbsInColumn(array, n, j);
    }
    
    // Заменяем четные элементы на максимальные значения их столбцов
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (array[i][j] % 2 == 0) {
                array[i][j] = maxAbsValues[j];
            }
        }
    }
    
    delete[] maxAbsValues;
}

bool isFirstElementEven(int* const* const array, const int col) {
    if (array == nullptr) {
        return false;
    }
    return (array[0][col] % 2 == 0);
}

void deleteColumnsWithEvenFirst(int**& array, const int n, int& m) {
    if (array == nullptr) return;
    
    // Определяем, какие столбцы нужно сохранить (где первый элемент нечетный)
    bool* keepColumn = new bool[m];
    int columnsToKeep = 0;
    
    for (int j = 0; j < m; j++) {
        if (!isFirstElementEven(array, j)) {
            keepColumn[j] = true;
            columnsToKeep++;
        } else {
            keepColumn[j] = false;
        }
    }
    
    // Если не осталось столбцов для сохранения
    if (columnsToKeep == 0) {
        deleteArray(array, n);
        array = nullptr;
        m = 0;
        delete[] keepColumn;
        return;
    }
    
    // Создаем новый массив с сохраненными столбцами
    int** newArray = createArray(n, columnsToKeep);
    
    for (int i = 0; i < n; i++) {
        int newColIndex = 0;
        for (int j = 0; j < m; j++) {
            if (keepColumn[j]) {
                newArray[i][newColIndex] = array[i][j];
                newColIndex++;
            }
        }
    }
    
    // Освобождаем старый массив и заменяем его новым
    deleteArray(array, n);
    array = newArray;
    m = columnsToKeep;
    
    delete[] keepColumn;
}

void fillRowRecursively(int** array, const int row, int col, const int cols, 
                        const int min, const int max) {
    // Базовый случай рекурсии: достигли конца строки
    if (col >= cols) {
        return;
    }
    
    // Заполняем текущий элемент случайным числом
    array[row][col] = rand() % (max - min + 1) + min;
    
    // Рекурсивный вызов для следующего элемента
    fillRowRecursively(array, row, col + 1, cols, min, max);
}
