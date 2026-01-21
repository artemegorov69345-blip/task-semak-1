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
 * @brief Создает двумерный массив заданного размера n x m
 * @param n - количество строк в массиве
 * @param m - количество столбцов в массиве
 * @return int** - указатель на созданный двумерный массив
 * @details Функция динамически выделяет память под массив.
 *          Проверяет корректность размеров перед выделением памяти.
 */
int** createArray(const size_t n, const size_t m);

/**
 * @brief Освобождает память, занятую двумерным массивом
 * @param array - указатель на массив для освобождения
 * @param n - количество строк в массиве
 */
void deleteArray(int** array, const size_t n);

/**
 * @brief Выводит двумерный массив на экран в табличном формате
 * @param array - указатель на массив для вывода
 * @param n - количество строк в массиве
 * @param m - количество столбцов в массиве
 * @details Форматирует вывод для удобного чтения с заголовками строк и столбцов
 */
void printArray(int* const* const array, const size_t n, const size_t m);

/**
 * @brief Заполняет массив значениями, введенными пользователем с клавиатуры
 * @param array - указатель на массив для заполнения
 * @param n - количество строк в массиве
 * @param m - количество столбцов в массиве
 */
void fillArrayManually(int** array, const size_t n, const size_t m);

/**
 * @brief Заполняет массив случайными числами в заданном диапазоне
 * @param array - указатель на массив для заполнения
 * @param n - количество строк в массиве
 * @param m - количество столбцов в массиве
 */
void fillArrayRandomly(int** array, const size_t n, const size_t m);

/**
 * @brief Находит максимальный по модулю элемент в указанном столбце массива
 * @param array - указатель на массив
 * @param n - количество строк в массиве
 * @param col - номер столбца (начинается с 0)
 * @return int - максимальное абсолютное значение элемента в столбце
 */
int findMaxAbsInColumn(int* const* const array, const size_t n, const size_t col);

/**
 * @brief Заменяет четные элементы каждого столбца максимальным по модулю элементом этого столбца
 * @param array - указатель на массив для модификации
 * @param n - количество строк в массиве
 * @param m - количество столбцов в массиве
 */
void replaceEvenWithMaxAbs(int** array, const size_t n, const size_t m);

/**
 * @brief Создает новый массив без столбцов, в которых первый элемент четный
 * @param array - указатель на исходный массив
 * @param n - количество строк в массиве
 * @param m - количество столбцов в исходном массиве
 * @param newM - ссылка на переменную для сохранения нового количества столбцов
 * @return int** - новый массив без удаленных столбцов
 */
int** createArrayWithoutEvenFirstColumns(int* const* const array, const size_t n, const size_t m, size_t& newM);

int main() {
    cout << "=== РАБОТА С ДВУМЕРНЫМ МАССИВОМ n x m ===" << endl;
    
    // Ввод количества строк массива с инициализацией (без цикла проверки)
    size_t n = 0;
    cout << "Введите количество строк массива (n > 0): ";
    cin >> n;
    
    // Ввод количества столбцов массива с инициализацией (без цикла проверки)
    size_t m = 0;
    cout << "Введите количество столбцов массива (m > 0): ";
    cin >> m;
    
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
    
    // Выбор способа заполнения (без цикла проверки)
    cout << "\nВыберите способ заполнения массива:" << endl;
    cout << FILL_MANUALLY << " - Ввод вручную" << endl;
    cout << FILL_RANDOMLY << " - Заполнение случайными числами" << endl;
    cout << "Ваш выбор (" << FILL_MANUALLY << " или " << FILL_RANDOMLY << "): ";
    
    int choice = 0;
    cin >> choice;
    
    // Заполнение массива в зависимости от выбора
    if (choice == FILL_MANUALLY) {
        fillArrayManually(originalArray, n, m);
    } else if (choice == FILL_RANDOMLY) {
        // Инициализация генератора случайных чисел только при необходимости
        srand(static_cast<unsigned>(time(nullptr)));
        fillArrayRandomly(originalArray, n, m);
    } else {
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
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < m; j++) {
            arrayCopy1[i][j] = originalArray[i][j];
        }
    }
    
    replaceEvenWithMaxAbs(arrayCopy1, n, m);
    
    cout << "Результат преобразования:" << endl;
    printArray(arrayCopy1, n, m);
    
    // 2. Удаление столбцов с четным первым элементом
    cout << "\n=== УДАЛЕНИЕ СТОЛБЦОВ ===" << endl;
    cout << "Удаляем все столбцы, в которых первый элемент четный..." << endl;
    
    // Создаем массив без столбцов с четным первым элементом
    size_t newM = m;
    int** arrayCopy2 = createArrayWithoutEvenFirstColumns(originalArray, n, m, newM);
    
    if (newM == 0) {
        cout << "Все столбцы были удалены! Массив стал пустым." << endl;
    } else {
        cout << "Результат (новый размер: " << n << " строк x " << newM << " столбцов):" << endl;
        printArray(arrayCopy2, n, newM);
        deleteArray(arrayCopy2, n);
    }
    
    // Освобождение памяти исходного массива и копии
    deleteArray(originalArray, n);
    deleteArray(arrayCopy1, n);
    
    cout << "\n=== ПРОГРАММА УСПЕШНО ЗАВЕРШЕНА ===" << endl;
    return 0;
}

// Реализации функций

int** createArray(const size_t n, const size_t m) {
    if (n == 0) {
        throw invalid_argument("Количество строк должно быть положительным");
    }
    if (m == 0) {
        throw invalid_argument("Количество столбцов должно быть положительным");
    }
    
    int** array = new int*[n];
    for (size_t i = 0; i < n; i++) {
        array[i] = new int[m];
    }
    
    return array;
}

void deleteArray(int** array, const size_t n) {
    if (array == nullptr) return;
    
    for (size_t i = 0; i < n; i++) {
        delete[] array[i];
    }
    delete[] array;
}

void printArray(int* const* const array, const size_t n, const size_t m) {
    if (array == nullptr) {
        cout << "Массив пуст!" << endl;
        return;
    }
    
    // Вывод заголовков столбцов
    cout << "       ";
    for (size_t j = 0; j < m; j++) {
        cout << setw(6) << "Стлб " << j + 1;
    }
    cout << endl;
    
    // Вывод разделительной линии
    cout << "      +";
    for (size_t j = 0; j < m; j++) {
        cout << "------+";
    }
    cout << endl;
    
    // Вывод строк массива
    for (size_t i = 0; i < n; i++) {
        cout << "Стр " << setw(2) << i + 1 << " |";
        for (size_t j = 0; j < m; j++) {
            cout << setw(6) << array[i][j] << "|";
        }
        cout << endl;
        
        // Вывод разделительной линии между строками
        if (i < n - 1) {
            cout << "      +";
            for (size_t j = 0; j < m; j++) {
                cout << "------+";
            }
            cout << endl;
        }
    }
    
    // Нижняя граница
    cout << "      +";
    for (size_t j = 0; j < m; j++) {
        cout << "------+";
    }
    cout << endl;
}

void fillArrayManually(int** array, const size_t n, const size_t m) {
    cout << "Введите элементы массива " << n << " x " << m << ":" << endl;
    
    for (size_t i = 0; i < n; i++) {
        cout << "Строка " << i + 1 << ":" << endl;
        for (size_t j = 0; j < m; j++) {
            cout << "  Элемент [" << i + 1 << "][" << j + 1 << "]: ";
            cin >> array[i][j];
        }
    }
    cout << "Массив успешно заполнен вручную." << endl;
}

void fillArrayRandomly(int** array, const size_t n, const size_t m) {
    int minValue = 0;
    int maxValue = 0;
    
    cout << "Введите минимальное значение для случайных чисел: ";
    cin >> minValue;
    
    cout << "Введите максимальное значение для случайных чисел: ";
    cin >> maxValue;
    
    if (minValue > maxValue) {
        cout << "Предупреждение: Минимальное значение больше максимального." << endl;
        cout << "Меняю значения местами." << endl;
        swap(minValue, maxValue);
    }
    
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < m; j++) {
            array[i][j] = rand() % (maxValue - minValue + 1) + minValue;
        }
    }
    
    cout << "Массив заполнен случайными числами в диапазоне [" 
         << minValue << ", " << maxValue << "]" << endl;
}

int findMaxAbsInColumn(int* const* const array, const size_t n, const size_t col) {
    if (array == nullptr) {
        return 0;
    }
    
    int maxAbs = abs(array[0][col]);
    
    for (size_t i = 1; i < n; i++) {
        int currentAbs = abs(array[i][col]);
        if (currentAbs > maxAbs) {
            maxAbs = currentAbs;
        }
    }
    
    return maxAbs;
}

void replaceEvenWithMaxAbs(int** array, const size_t n, const size_t m) {
    if (array == nullptr) return;
    
    // Находим максимальные по модулю значения для каждого столбца
    int* maxAbsValues = new int[m];
    for (size_t j = 0; j < m; j++) {
        maxAbsValues[j] = findMaxAbsInColumn(array, n, j);
    }
    
    // Заменяем четные элементы на максимальные значения их столбцов
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < m; j++) {
            if (array[i][j] % 2 == 0) {
                array[i][j] = maxAbsValues[j];
            }
        }
    }
    
    delete[] maxAbsValues;
}

int** createArrayWithoutEvenFirstColumns(int* const* const array, const size_t n, const size_t m, size_t& newM) {
    if (array == nullptr || n == 0 || m == 0) {
        newM = 0;
        return nullptr;
    }
    
    // Считаем, сколько столбцов нужно оставить
    size_t columnsToKeep = 0;
    for (size_t j = 0; j < m; j++) {
        if (array[0][j] % 2 != 0) {
            columnsToKeep++;
        }
    }
    
    // Если не осталось столбцов для сохранения
    if (columnsToKeep == 0) {
        newM = 0;
        return nullptr;
    }
    
    // Создаем новый массив с сохраненными столбцами
    int** newArray = createArray(n, columnsToKeep);
    
    for (size_t i = 0; i < n; i++) {
        size_t newColIndex = 0;
        for (size_t j = 0; j < m; j++) {
            if (array[0][j] % 2 != 0) {
                newArray[i][newColIndex] = array[i][j];
                newColIndex++;
            }
        }
    }
    
    newM = columnsToKeep;
    return newArray;
}
