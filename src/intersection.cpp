#include <iostream>
#include <initializer_list>

struct MyArr {
    int* data;
    int size;
    int capacity;
};

//инициализация массива
void initArray(MyArr &arr) {
    arr.data = nullptr;
    arr.size = 0;
    arr.capacity = 0;
}

//освобождение памяти
void freeArr(MyArr &arr) {
    delete[] arr.data;
    arr.data = nullptr;
    arr.size = 0;
    arr.capacity = 0;
}

//проверка и расширение памяти при необходимости
static void ensureCapacity(MyArr &arr, int newSize) {
    if (newSize <= arr.capacity) return;

    int newCapacity = arr.capacity == 0 ? 1 : arr.capacity;
    while (newCapacity < newSize)
        newCapacity *= 2;

    int* newData = new int[newCapacity];
    for (int i = 0; i < arr.size; ++i)
        newData[i] = arr.data[i];

    delete[] arr.data;
    arr.data = newData;
    arr.capacity = newCapacity;
}

// добавление в конец
void addEnd(MyArr &arr, int val) {
    ensureCapacity(arr, arr.size + 1);
    arr.data[arr.size++] = val;
}

// чтение всех элементов
void readArray(const MyArr &arr) {
    if (arr.size == 0) {
        std::cout << "Массив пуст." << std::endl;
        return;
    }
    std::cout << "Содержимое массива (" << arr.size << "/" << arr.capacity << "): ";
    for (int i = 0; i < arr.size; ++i)
        std::cout << arr.data[i] << " ";
    std::cout << std::endl;
}

//получение элемента по индексу
int getAt(const MyArr &arr, int idx) {
    if (idx >= 0 && idx < arr.size)
        return arr.data[idx];
    else {
        std::cout << "Неверный индекс" << std::endl;
        return -1;
    }
}

//логическая длина массива
int lenArr(const MyArr &arr) {
    return arr.size;
}

// Проверка наличия элемента в массиве
bool contains(const MyArr &arr, int value) {
    for (int i = 0; i < arr.size; i++) {
        if (arr.data[i] == value) {
            return true;
        }
    }
    return false;
}

// Сортировка массива (пузырьковая)
void sortArray(MyArr &arr) {
    for (int i = 0; i < arr.size; i++) {
        for (int j = 0; j < arr.size - i - 1; j++) {
            if (arr.data[j] > arr.data[j + 1]) {
                int temp = arr.data[j];
                arr.data[j] = arr.data[j + 1];
                arr.data[j + 1] = temp;
            }
        }
    }
}

// Копирование массива (исправленная версия)
void copyArray(MyArr &dest, const MyArr &src) {
    // Освобождаем старые данные
    if (dest.data) {
        delete[] dest.data;
    }
    
    // Копируем размер и емкость
    dest.size = src.size;
    dest.capacity = src.capacity;
    
    // Выделяем новую память и копируем данные
    if (src.capacity > 0) {
        dest.data = new int[src.capacity];
        for (int i = 0; i < src.size; i++) {
            dest.data[i] = src.data[i];
        }
    } else {
        dest.data = nullptr;
    }
}

// Структура Множество
struct Set {
    MyArr elements;
};

// Инициализация множества
void initSet(Set &set) {
    initArray(set.elements);
}

// Проверка наличия элемента в множестве
bool containsSet(const Set &set, int value) {
    return contains(set.elements, value);
}

// Инициализация множества
void initSetFromList(Set &set, std::initializer_list<int> init_list) {
    initSet(set);
    for (int value : init_list) {
        if (!containsSet(set, value)) {
            addEnd(set.elements, value);
        }
    }
    sortArray(set.elements);
}

// Добавление элемента в множество
void addToSet(Set &set, int value) {
    if (!containsSet(set, value)) {
        addEnd(set.elements, value);
        sortArray(set.elements);
    }
}

// Получение размера множества
int sizeSet(const Set &set) {
    return lenArr(set.elements);
}

// Получение элемента множества по индексу
int getSetElement(const Set &set, int index) {
    return getAt(set.elements, index);
}

// Проверка пустоты множества
bool isEmptySet(const Set &set) {
    return lenArr(set.elements) == 0;
}

// Нахождение пересечения двух множеств
void intersectionSet(const Set &set1, const Set &set2, Set &result) {
    initSet(result);
    for (int i = 0; i < sizeSet(set1); i++) {
        int value = getSetElement(set1, i);
        if (containsSet(set2, value)) {
            addToSet(result, value);
        }
    }
}

// Вычисление размера пересечения двух множеств
int intersectionSizeSet(const Set &set1, const Set &set2) {
    int count = 0;
    for (int i = 0; i < sizeSet(set1); i++) {
        if (containsSet(set2, getSetElement(set1, i))) {
            count++;
        }
    }
    return count;
}

// Вывод множества
void printSet(const Set &set) {
    std::cout << "{";
    for (int i = 0; i < sizeSet(set); i++) {
        std::cout << getSetElement(set, i);
        if (i < sizeSet(set) - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "}";
}

// Копирование множества (исправленная версия)
void copySet(Set &dest, const Set &src) {
    copyArray(dest.elements, src.elements);
}

// Освобождение памяти множества
void freeSet(Set &set) {
    freeArr(set.elements);
}

// Упрощенный подход без сложных структур коллекций
int main() {
    std::cout << "=== Пример из задания ===" << std::endl;
    
    // Создаем массивы для хранения множеств
    const int MAX_SETS = 10;
    Set sets[MAX_SETS];
    
    // Инициализируем множества из примера
    initSetFromList(sets[0], {1, 2, 3});
    initSetFromList(sets[1], {2, 3, 4});
    initSetFromList(sets[2], {5, 6});
    initSetFromList(sets[3], {3, 4, 5});
    
    int num_sets = 4;
    
    // Выводим все множества
    std::cout << "Ввод: {";
    for (int i = 0; i < num_sets; i++) {
        printSet(sets[i]);
        if (i < num_sets - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "}" << std::endl;
    
    // Находим пару с максимальным пересечением
    int max_intersection = 0;
    int best_i = 0, best_j = 0;
    
    for (int i = 0; i < num_sets; i++) {
        for (int j = i + 1; j < num_sets; j++) {
            int current_intersection = intersectionSizeSet(sets[i], sets[j]);
            if (current_intersection > max_intersection) {
                max_intersection = current_intersection;
                best_i = i;
                best_j = j;
            }
        }
    }
    
    // Выводим результат
    std::cout << "Вывод: ";
    printSet(sets[best_i]);
    std::cout << ", ";
    printSet(sets[best_j]);
    std::cout << ", количество общих элементов: " << max_intersection << std::endl;
    
    // Показываем общие элементы
    if (max_intersection > 0) {
        Set common;
        initSet(common);
        intersectionSet(sets[best_i], sets[best_j], common);
        std::cout << "Общие элементы: ";
        printSet(common);
        std::cout << std::endl;
        freeSet(common);
    }
    
    // Дополнительный пример: можно добавлять новые множества
    std::cout << "\n=== Дополнительный пример ===" << std::endl;
    
    // Добавляем еще одно множество
    initSetFromList(sets[4], {4, 5, 6, 7});
    num_sets = 5;
    
    std::cout << "Ввод: {";
    for (int i = 0; i < num_sets; i++) {
        printSet(sets[i]);
        if (i < num_sets - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "}" << std::endl;
    
    // Находим новую пару с максимальным пересечением
    max_intersection = 0;
    best_i = 0; best_j = 0;
    
    for (int i = 0; i < num_sets; i++) {
        for (int j = i + 1; j < num_sets; j++) {
            int current_intersection = intersectionSizeSet(sets[i], sets[j]);
            if (current_intersection > max_intersection) {
                max_intersection = current_intersection;
                best_i = i;
                best_j = j;
            }
        }
    }
    
    std::cout << "Вывод: ";
    printSet(sets[best_i]);
    std::cout << ", ";
    printSet(sets[best_j]);
    std::cout << ", количество общих элементов: " << max_intersection << std::endl;
    
    // Тестирование с пустыми множествами
    std::cout << "\n=== Тест с пустыми множествами ===" << std::endl;
    
    Set test_sets[3];
    initSetFromList(test_sets[0], {1, 2, 3});
    initSetFromList(test_sets[1], {});
    initSetFromList(test_sets[2], {2, 3});
    
    std::cout << "Ввод: {";
    for (int i = 0; i < 3; i++) {
        printSet(test_sets[i]);
        if (i < 2) {
            std::cout << ", ";
        }
    }
    std::cout << "}" << std::endl;
    
    max_intersection = 0;
    best_i = 0; best_j = 0;
    
    for (int i = 0; i < 3; i++) {
        for (int j = i + 1; j < 3; j++) {
            int current_intersection = intersectionSizeSet(test_sets[i], test_sets[j]);
            if (current_intersection > max_intersection) {
                max_intersection = current_intersection;
                best_i = i;
                best_j = j;
            }
        }
    }
    
    std::cout << "Вывод: ";
    printSet(test_sets[best_i]);
    std::cout << ", ";
    printSet(test_sets[best_j]);
    std::cout << ", количество общих элементов: " << max_intersection << std::endl;
    
    // Пример с большим количеством множеств
    std::cout << "\n=== Пример с 6 множествами ===" << std::endl;
    
    Set many_sets[6];
    initSetFromList(many_sets[0], {1, 3, 5, 7, 9});
    initSetFromList(many_sets[1], {2, 4, 6, 8, 10});
    initSetFromList(many_sets[2], {1, 2, 3, 4, 5});
    initSetFromList(many_sets[3], {3, 4, 5, 6, 7});
    initSetFromList(many_sets[4], {5, 6, 7, 8, 9});
    initSetFromList(many_sets[5], {1, 5, 10});
    
    std::cout << "Ввод: {";
    for (int i = 0; i < 6; i++) {
        printSet(many_sets[i]);
        if (i < 5) {
            std::cout << ", ";
        }
    }
    std::cout << "}" << std::endl;
    
    max_intersection = 0;
    best_i = 0; best_j = 0;
    
    for (int i = 0; i < 6; i++) {
        for (int j = i + 1; j < 6; j++) {
            int current_intersection = intersectionSizeSet(many_sets[i], many_sets[j]);
            if (current_intersection > max_intersection) {
                max_intersection = current_intersection;
                best_i = i;
                best_j = j;
            }
        }
    }
    
    std::cout << "Вывод: ";
    printSet(many_sets[best_i]);
    std::cout << ", ";
    printSet(many_sets[best_j]);
    std::cout << ", количество общих элементов: " << max_intersection << std::endl;
    
    if (max_intersection > 0) {
        Set common;
        initSet(common);
        intersectionSet(many_sets[best_i], many_sets[best_j], common);
        std::cout << "Общие элементы: ";
        printSet(common);
        std::cout << std::endl;
        freeSet(common);
    }
    
    // Освобождаем память
    for (int i = 0; i < num_sets; i++) {
        freeSet(sets[i]);
    }
    for (int i = 0; i < 3; i++) {
        freeSet(test_sets[i]);
    }
    for (int i = 0; i < 6; i++) {
        freeSet(many_sets[i]);
    }
    
    return 0;
}