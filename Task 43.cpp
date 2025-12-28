#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iomanip>
#include <cmath>
#include <limits>

using namespace std;

// Перечисление для выбора способа заполнения
enum FillMode {
    FILL_MANUALLY = 0,
    FILL_RANDOMLY = 1
};

/**
 * @brief Проверяет правильность ввода целого числа
 * @param value - переменная для сохранения значения
 * @return true если ввод корректен, false если ошибка
 */
bool checkValue(int &value);

/**
 * @brief Проверяет положительное значение
 * @param value - проверяемое значение
 * @param paramName - название параметра
 * @return true если значение положительное, false в противном случае
 */
bool checkPositive(int value, const string &paramName);

/**
 * @brief Создает квадратную матрицу n x n
 * @param n - размер матрицы
 * @return созданная матрица
 */
vector<vector<int>> createMatrix(int n);

/**
 * @brief Выводит матрицу на экран
 * @param matrix - матрица для вывода
 */
void printMatrix(const vector<vector<int>>& matrix);

/**
 * @brief Заполняет матрицу вручную
 * @param matrix - матрица для заполнения
 */
void fillMatrixManually(vector<vector<int>>& matrix);

/**
 * @brief Заполняет матрицу случайными числами
 * @param matrix - матрица для заполнения
 */
void fillMatrixRandomly(vector<vector<int>>& matrix);

/**
 * @brief Находит максимальный по модулю элемент в столбце
 * @param matrix - матрица
 * @param col - номер столбца
 * @return максимальный по модулю элемент
 */
int findMaxAbsInColumn(const vector<vector<int>>& matrix, int col);

/**
 * @brief Заменяет четные элементы каждого столбца максимальным по модулю элементом этого столбца
 * @param matrix - матрица для изменения
 */
void replaceEvenWithMaxAbs(vector<vector<int>>& matrix);

/**
 * @brief Проверяет, является ли первый элемент столбца четным
 * @param matrix - матрица
 * @param col - номер столбца
 * @return true если первый элемент четный, false в противном случае
 */
bool isFirstElementEven(const vector<vector<int>>& matrix, int col);

/**
 * @brief Удаляет все столбцы, в которых первый элемент четный
 * @param matrix - матрица для обработки
 */
void deleteColumnsWithEvenFirst(vector<vector<int>>& matrix);

/**
 * @brief Рекурсивное заполнение строки матрицы
 * @param matrix - матрица
 * @param row - текущая строка
 * @param col - текущий столбец
 * @param min - минимальное значение
 * @param max - максимальное значение
 */
void getRecurentRow(vector<vector<int>>& matrix, int row, int col, int min, int max);

int main() {
    srand(time(nullptr)); // Инициализация генератора случайных чисел
    
    cout << "=== РАБОТА С КВАДРАТНОЙ МАТРИЦЕЙ n x n ===" << endl;
    
    // Ввод размера матрицы
    int n;
    cout << "\nВведите размер матрицы n (n > 0): ";
    
    while (!checkValue(n)) {
        cout << "Ошибка! Нужно ввести целое число. Попробуйте снова: ";
    }
    
    if (!checkPositive(n, "Размер матрицы")) {
        return 1;
    }
    
    // Создание матрицы
    cout << "Создаем матрицу " << n << " x " << n << "..." << endl;
    vector<vector<int>> matrix = createMatrix(n);
    
    // Выбор способа заполнения
    cout << "Выберите способ заполнения матрицы:" << endl;
    cout << FILL_MANUALLY << " - Вручную" << endl;
    cout << FILL_RANDOMLY << " - Случайными числами" << endl;
    cout << "Ваш выбор: ";
    
    int choice;
    while (!checkValue(choice)) {
        cout << "Ошибка! Введите 0 или 1: ";
    }
    
    switch(choice) {
        case FILL_MANUALLY:
            fillMatrixManually(matrix);
            break;
        case FILL_RANDOMLY:
            fillMatrixRandomly(matrix);
            break;
        default:
            cout << "Ошибка! Неверный выбор." << endl;
            return 1;
    }
    
    // Вывод исходной матрицы
    cout << "=== ИСХОДНАЯ МАТРИЦА ===" << endl;
    printMatrix(matrix);
    
    // Замена четных элементов каждого столбца максимальным по модулю элементом
    cout << "=== ЗАМЕНА ЧЕТНЫХ ЭЛЕМЕНТОВ ===" << endl;
    cout << "Заменяем четные элементы каждого столбца максимальным по модулю элементом этого столбца..." << endl;
    
    // Создаем копию для демонстрации
    vector<vector<int>> matrixCopy = matrix;
    replaceEvenWithMaxAbs(matrixCopy);
    
    cout << "Результат:" << endl;
    printMatrix(matrixCopy);
    
    // Удаление столбцов с четным первым элементом
    cout << "=== УДАЛЕНИЕ СТОЛБЦОВ ===" << endl;
    cout << "Удаляем все столбцы, в которых первый элемент четный..." << endl;
    
    // Создаем еще одну копию
    vector<vector<int>> matrixCopy2 = matrix;
    deleteColumnsWithEvenFirst(matrixCopy2);
    
    if (matrixCopy2.empty() || matrixCopy2[0].empty()) {
        cout << "Все столбцы были удалены!" << endl;
    } else {
        cout << "Результат (новая размерность: " << matrixCopy2.size() 
             << " x " << matrixCopy2[0].size() << "):" << endl;
        printMatrix(matrixCopy2);
    }
    
    // Демонстрация рекуррентного метода
    cout << "=== ДЕМОНСТРАЦИЯ РЕКУРРЕНТНОГО МЕТОДА ===" << endl;
    cout << "Создаем матрицу 3x3 и заполняем рекурсивно:" << endl;
    
    vector<vector<int>> recurentMatrix = createMatrix(3);
    for (int i = 0; i < 3; i++) {
        getRecurentRow(recurentMatrix, i, 0, 1, 100);
    }
    
    printMatrix(recurentMatrix);
    
    cout << "=== ПРОГРАММА ЗАВЕРШЕНА ===" << endl;
    return 0;
}


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
        cout << "Ошибка! " << paramName << " должен быть положительным числом!" << endl;
        return false;
    }
    return true;
}

vector<vector<int>> createMatrix(int n) {
    return vector<vector<int>>(n, vector<int>(n));
}

void printMatrix(const vector<vector<int>>& matrix) {
    if (matrix.empty()) {
        cout << "Матрица пуста!" << endl;
        return;
    }
    
    int n = matrix.size();
    cout << "   ";
    for (int j = 0; j < n; j++) {
        cout << setw(6) << "Столб " << j + 1;
    }
    cout << endl;
    
    for (int i = 0; i < n; i++) {
        cout << "Ряд " << setw(2) << i + 1 << ": ";
        for (int j = 0; j < matrix[i].size(); j++) {
            cout << setw(6) << matrix[i][j];
        }
        cout << endl;
    }
}

void fillMatrixManually(vector<vector<int>>& matrix) {
    int n = matrix.size();
    cout << "Введите элементы матрицы " << n << " x " << n << ":" << endl;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << "Элемент [" << i + 1 << "][" << j + 1 << "]: ";
            
            while (!checkValue(matrix[i][j])) {
                cout << "Ошибка! Введите целое число: ";
            }
        }
    }
    cout << "Матрица успешно заполнена." << endl;
}

void fillMatrixRandomly(vector<vector<int>>& matrix) {
    int minValue, maxValue;
    
    cout << "Введите минимальное значение: ";
    while (!checkValue(minValue)) {
        cout << "Ошибка! Введите целое число: ";
    }
    
    cout << "Введите максимальное значение: ";
    while (!checkValue(maxValue)) {
        cout << "Ошибка! Введите целое число: ";
    }
    
    if (minValue > maxValue) {
        cout << "Ошибка! Минимальное значение больше максимального. Использую значения по умолчанию (1-100)." << endl;
        minValue = 1;
        maxValue = 100;
    }
    
    int n = matrix.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = rand() % (maxValue - minValue + 1) + minValue;
        }
    }
    
    cout << "Матрица заполнена случайными числами от " 
         << minValue << " до " << maxValue << endl;
}

int findMaxAbsInColumn(const vector<vector<int>>& matrix, int col) {
    int maxAbs = 0;
    int n = matrix.size();
    
    // Проверяем, что столбец существует
    if (col < matrix[0].size()) {
        maxAbs = abs(matrix[0][col]);
        
        for (int i = 1; i < n; i++) {
            int currentAbs = abs(matrix[i][col]);
            if (currentAbs > maxAbs) {
                maxAbs = currentAbs;
            }
        }
    }
    
    return maxAbs;
}

void replaceEvenWithMaxAbs(vector<vector<int>>& matrix) {
    int n = matrix.size();
    if (n == 0) return;
    
    int m = matrix[0].size();
    
    // Для каждого столбца находим максимальный по модулю элемент
    vector<int> maxAbsValues(m);
    for (int j = 0; j < m; j++) {
        maxAbsValues[j] = findMaxAbsInColumn(matrix, j);
    }
    
    // Заменяем четные элементы
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (matrix[i][j] % 2 == 0) {
                matrix[i][j] = maxAbsValues[j];
            }
        }
    }
}

bool isFirstElementEven(const vector<vector<int>>& matrix, int col) {
    if (matrix.empty() || col >= matrix[0].size()) {
        return false;
    }
    return matrix[0][col] % 2 == 0;
}

void deleteColumnsWithEvenFirst(vector<vector<int>>& matrix) {
    if (matrix.empty()) return;
    
    int n = matrix.size();
    int m = matrix[0].size();
    
    // Определяем, какие столбцы нужно удалить
    vector<bool> keepColumn(m, true);
    int columnsToKeep = 0;
    
    for (int j = 0; j < m; j++) {
        if (isFirstElementEven(matrix, j)) {
            keepColumn[j] = false;
        } else {
            columnsToKeep++;
        }
    }
    
    // Если все столбцы удаляются, очищаем матрицу
    if (columnsToKeep == 0) {
        matrix.clear();
        return;
    }
    
    // Создаем новую матрицу с оставшимися столбцами
    vector<vector<int>> newMatrix(n, vector<int>(columnsToKeep));
    
    for (int i = 0; i < n; i++) {
        int newCol = 0;
        for (int j = 0; j < m; j++) {
            if (keepColumn[j]) {
                newMatrix[i][newCol] = matrix[i][j];
                newCol++;
            }
        }
    }
    
    // Заменяем старую матрицу новой
    matrix = newMatrix;
}

void getRecurentRow(vector<vector<int>>& matrix, int row, int col, int min, int max) {
    int m = matrix[0].size();
    
    // Базовый случай: если дошли до конца строки
    if (col >= m) {
        return;
    }
    
    // Рекуррентный шаг: заполняем текущий элемент
    matrix[row][col] = rand() % (max - min + 1) + min;
    
    // Рекурсивный вызов для следующего элемента строки
    getRecurentRow(matrix, row, col + 1, min, max);
}