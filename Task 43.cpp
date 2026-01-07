#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iomanip>
#include <cmath>
#include <limits>

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
bool checkPositive(int value, const string &paramName);

/**
 * @brief Создает двумерный массив заданного размера n x m
 * @param n - количество строк в массиве
 * @param m - количество столбцов в массиве
 * @return vector<vector<int>> - созданный двумерный массив
 * @details Функция динамически выделяет память под массив.
 *          Проверяет корректность размеров перед выделением памяти.
 */
vector<vector<int>> createArray(int n, int m);

/**
 * @brief Выводит двумерный массив на экран в табличном формате
 * @param array - константная ссылка на массив для вывода
 * @details Форматирует вывод для удобного чтения с заголовками строк и столбцов
 */
void printArray(const vector<vector<int>>& array);

/**
 * @brief Заполняет массив значениями, введенными пользователем с клавиатуры
 * @param array - ссылка на массив для заполнения
 */
void fillArrayManually(vector<vector<int>>& array);

/**
 * @brief Заполняет массив случайными числами в заданном диапазоне
 * @param array - ссылка на массив для заполнения
 */
void fillArrayRandomly(vector<vector<int>>& array);

/**
 * @brief Находит максимальный по модулю элемент в указанном столбце массива
 * @param array - константная ссылка на массив
 * @param col - номер столбца (начинается с 0)
 * @return int - максимальное абсолютное значение элемента в столбце
 */
int findMaxAbsInColumn(const vector<vector<int>>& array, int col);

/**
 * @brief Заменяет четные элементы каждого столбца максимальным по модулю элементом этого столбца
 * @param array - ссылка на массив для модификации
 * @details Создает копию исходного массива и работает с ней
 */
void replaceEvenWithMaxAbs(vector<vector<int>>& array);

/**
 * @brief Проверяет, является ли первый элемент указанного столбца четным числом
 * @param array - константная ссылка на массив
 * @param col - номер столбца
 * @return true - если первый элемент четный, false - в противном случае
 */
bool isFirstElementEven(const vector<vector<int>>& array, int col);

/**
 * @brief Удаляет все столбцы, в которых первый элемент является четным числом
 * @param array - ссылка на массив для обработки
 * @details Создает новый массив без указанных столбцов
 */
void deleteColumnsWithEvenFirst(vector<vector<int>>& array);

/**
 * @brief Рекурсивно заполняет строку массива случайными числами
 * @param array - ссылка на массив
 * @param row - номер строки для заполнения
 * @param col - текущий столбец для заполнения
 * @param min - минимальное значение случайного числа
 * @param max - максимальное значение случайного числа
 * @details Использует рекурсию для заполнения строки слева направо
 */
void fillRowRecursively(vector<vector<int>>& array, int row, int col, int min, int max);

int main() {
    cout << "=== РАБОТА С ДВУМЕРНЫМ МАССИВОМ n x m ===" << endl;
    
    // Ввод количества строк массива
    int n;
    cout << "Введите количество строк массива (n > 0): ";
    
    while (!checkValue(n)) {
        cout << "Ошибка! Нужно ввести целое число. Попробуйте снова: ";
    }
    
    if (!checkPositive(n, "Количество строк")) {
        cout << "Программа завершена из-за ошибки ввода." << endl;
        return 1;
    }
    
    // Ввод количества столбцов массива
    int m;
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
    vector<vector<int>> originalArray;
    
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
    
    int choice;
    while (!checkValue(choice) || (choice != FILL_MANUALLY && choice != FILL_RANDOMLY)) {
        cout << "Ошибка! Введите " << FILL_MANUALLY << " или " << FILL_RANDOMLY << ": ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
    // Заполнение массива в зависимости от выбора
    switch(choice) {
        case FILL_MANUALLY:
            fillArrayManually(originalArray);
            break;
        case FILL_RANDOMLY:
            // Инициализация генератора случайных чисел только при необходимости
            srand(static_cast<unsigned>(time(nullptr)));
            fillArrayRandomly(originalArray);
            break;
        default:
            cout << "Критическая ошибка: некорректный выбор заполнения!" << endl;
            return 1;
    }
    
    // Вывод исходного массива
    cout << "\n=== ИСХОДНЫЙ МАССИВ ===" << endl;
    printArray(originalArray);
    
    // 1. Замена четных элементов каждого столбца максимальным по модулю элементом
    cout << "\n=== ЗАМЕНА ЧЕТНЫХ ЭЛЕМЕНТОВ ===" << endl;
    cout << "Заменяем четные элементы каждого столбца максимальным по модулю элементом этого столбца..." << endl;
    
    // Создаем копию для обработки
    vector<vector<int>> arrayCopy1 = originalArray;
    replaceEvenWithMaxAbs(arrayCopy1);
    
    cout << "Результат преобразования:" << endl;
    printArray(arrayCopy1);
    
    // 2. Удаление столбцов с четным первым элементом
    cout << "\n=== УДАЛЕНИЕ СТОЛБЦОВ ===" << endl;
    cout << "Удаляем все столбцы, в которых первый элемент четный..." << endl;
    
    // Создаем еще одну копию для обработки
    vector<vector<int>> arrayCopy2 = originalArray;
    deleteColumnsWithEvenFirst(arrayCopy2);
    
    if (arrayCopy2.empty() || arrayCopy2[0].empty()) {
        cout << "Все столбцы были удалены! Массив стал пустым." << endl;
    } else {
        cout << "Результат (новый размер: " << arrayCopy2.size() 
             << " строк x " << arrayCopy2[0].size() << " столбцов):" << endl;
        printArray(arrayCopy2);
    }
    
    // 3. Демонстрация рекуррентного метода заполнения
    cout << "\n=== ДЕМОНСТРАЦИЯ РЕКУРСИВНОГО МЕТОДА ===" << endl;
    cout << "Создаем массив 3x3 и заполняем его рекурсивно:" << endl;
    
    // Создаем отдельный массив для демонстрации
    vector<vector<int>> recursiveArray;
    try {
        recursiveArray = createArray(3, 3);
        // Инициализируем генератор случайных чисел для рекурсивного заполнения
        srand(static_cast<unsigned>(time(nullptr)) + 1);
        
        for (int i = 0; i < 3; i++) {
            fillRowRecursively(recursiveArray, i, 0, 1, 100);
        }
        
        cout << "Массив, заполненный рекурсивным методом:" << endl;
        printArray(recursiveArray);
    } catch (const bad_alloc& e) {
        cout << "Не удалось создать массив для демонстрации рекурсивного метода." << endl;
    }
    
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

bool checkPositive(int value, const string &paramName) {
    if (value <= 0) {
        cout << "Ошибка! " << paramName << " должен быть положительным целым числом!" << endl;
        return false;
    }
    return true;
}

vector<vector<int>> createArray(int n, int m) {
    if (n <= 0) {
        throw invalid_argument("Количество строк должно быть положительным");
    }
    if (m <= 0) {
        throw invalid_argument("Количество столбцов должно быть положительным");
    }
    
    // Выделение памяти с проверкой
    vector<vector<int>> array;
    try {
        array.resize(n, vector<int>(m));
    } catch (const bad_alloc& e) {
        cerr << "Ошибка выделения памяти для массива размером " << n << "x" << m << endl;
        throw; // Пробрасываем исключение дальше
    }
    
    return array;
}

void printArray(const vector<vector<int>>& array) {
    if (array.empty()) {
        cout << "Массив пуст!" << endl;
        return;
    }
    
    int rows = array.size();
    int cols = array[0].size();
    
    // Вывод заголовков столбцов
    cout << "       ";
    for (int j = 0; j < cols; j++) {
        cout << setw(6) << "Стлб " << j + 1;
    }
    cout << endl;
    
    // Вывод разделительной линии
    cout << "      +";
    for (int j = 0; j < cols; j++) {
        cout << "------+";
    }
    cout << endl;
    
    // Вывод строк массива
    for (int i = 0; i < rows; i++) {
        cout << "Стр " << setw(2) << i + 1 << " |";
        for (int j = 0; j < cols; j++) {
            cout << setw(6) << array[i][j] << "|";
        }
        cout << endl;
        
        // Вывод разделительной линии между строками
        if (i < rows - 1) {
            cout << "      +";
            for (int j = 0; j < cols; j++) {
                cout << "------+";
            }
            cout << endl;
        }
    }
    
    // Нижняя граница
    cout << "      +";
    for (int j = 0; j < cols; j++) {
        cout << "------+";
    }
    cout << endl;
}

void fillArrayManually(vector<vector<int>>& array) {
    int rows = array.size();
    int cols = array[0].size();
    cout << "Введите элементы массива " << rows << " x " << cols << ":" << endl;
    
    for (int i = 0; i < rows; i++) {
        cout << "Строка " << i + 1 << ":" << endl;
        for (int j = 0; j < cols; j++) {
            cout << "  Элемент [" << i + 1 << "][" << j + 1 << "]: ";
            
            while (!checkValue(array[i][j])) {
                cout << "  Ошибка! Введите целое число: ";
            }
        }
    }
    cout << "Массив успешно заполнен вручную." << endl;
}

void fillArrayRandomly(vector<vector<int>>& array) {
    int minValue, maxValue;
    
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
    
    int rows = array.size();
    int cols = array[0].size();
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            array[i][j] = rand() % (maxValue - minValue + 1) + minValue;
        }
    }
    
    cout << "Массив заполнен случайными числами в диапазоне [" 
         << minValue << ", " << maxValue << "]" << endl;
}

int findMaxAbsInColumn(const vector<vector<int>>& array, int col) {
    if (array.empty() || col >= array[0].size()) {
        return 0;
    }
    
    int maxAbs = abs(array[0][col]);
    int rows = array.size();
    
    for (int i = 1; i < rows; i++) {
        int currentAbs = abs(array[i][col]);
        if (currentAbs > maxAbs) {
            maxAbs = currentAbs;
        }
    }
    
    return maxAbs;
}

void replaceEvenWithMaxAbs(vector<vector<int>>& array) {
    if (array.empty()) return;
    
    int rows = array.size();
    int cols = array[0].size();
    
    // Находим максимальные по модулю значения для каждого столбца
    vector<int> maxAbsValues(cols);
    for (int j = 0; j < cols; j++) {
        maxAbsValues[j] = findMaxAbsInColumn(array, j);
    }
    
    // Заменяем четные элементы на максимальные значения их столбцов
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (array[i][j] % 2 == 0) {
                array[i][j] = maxAbsValues[j];
            }
        }
    }
}

bool isFirstElementEven(const vector<vector<int>>& array, int col) {
    if (array.empty() || col >= array[0].size()) {
        return false;
    }
    return (array[0][col] % 2 == 0);
}

void deleteColumnsWithEvenFirst(vector<vector<int>>& array) {
    if (array.empty()) return;
    
    int rows = array.size();
    int cols = array[0].size();
    
    // Определяем, какие столбцы нужно сохранить (где первый элемент нечетный)
    vector<bool> keepColumn(cols, false);
    int columnsToKeep = 0;
    
    for (int j = 0; j < cols; j++) {
        if (!isFirstElementEven(array, j)) {
            keepColumn[j] = true;
            columnsToKeep++;
        }
    }
    
    // Если не осталось столбцов для сохранения
    if (columnsToKeep == 0) {
        array.clear();
        return;
    }
    
    // Создаем новый массив с сохраненными столбцами
    vector<vector<int>> newArray(rows, vector<int>(columnsToKeep));
    
    for (int i = 0; i < rows; i++) {
        int newColIndex = 0;
        for (int j = 0; j < cols; j++) {
            if (keepColumn[j]) {
                newArray[i][newColIndex] = array[i][j];
                newColIndex++;
            }
        }
    }
    
    // Заменяем старый массив новым
    array = newArray;
}

void fillRowRecursively(vector<vector<int>>& array, int row, int col, int min, int max) {
    int cols = array[0].size();
    
    // Базовый случай рекурсии: достигли конца строки
    if (col >= cols) {
        return;
    }
    
    // Заполняем текущий элемент случайным числом
    array[row][col] = rand() % (max - min + 1) + min;
    
    // Рекурсивный вызов для следующего элемента
    fillRowRecursively(array, row, col + 1, min, max);
}
