#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int HASH_TABLE_SIZE = 1009;

struct Node {
    string val;
    Node* next;
};

struct CustomHash {
    Node** buckets;
    int tableSize;
};

long hashFunc(const string& str) {
    long hash = 5381;
    for (char chr : str) {
        hash = ((hash << 5) + hash) + chr;
    }
    return hash;
}

void initializeSet(CustomHash& set) {
    set.tableSize = HASH_TABLE_SIZE;
    set.buckets = new Node*[set.tableSize];
    for (int i = 0; i < set.tableSize; i++) {
        set.buckets[i] = NULL;
    }
}

void freeSet(CustomHash& set) {
    for (int i = 0; i < set.tableSize; i++) {
        Node* currNode = set.buckets[i];
        while (currNode != NULL) {
            Node* toDel = currNode;
            currNode = currNode->next;
            delete toDel;
        }
    }
    delete[] set.buckets;
}

bool checkElem(const CustomHash& set, const string& elem) {
    unsigned long hash = hashFunc(elem);
    int idx = hash % set.tableSize;

    Node* currNode = set.buckets[idx];
    while (currNode != NULL) {
        if (currNode->val == elem) {
            return true;
        }
        currNode = currNode->next;
    }
    return false;
}

void addElem(CustomHash& set, const string& elem) {
    if (checkElem(set, elem)) {
        cout << "Элемент " << elem << " уже существует в множестве" << endl;
        return;
    }

    unsigned long hash = hashFunc(elem);
    int idx = hash % set.tableSize;

    Node* newNode = new Node;
    newNode->val = elem;
    newNode->next = set.buckets[idx];
    set.buckets[idx] = newNode;

    cout << "Элемент " << elem << " успешно добавлен" << endl;
}

void removeElem(CustomHash& set, const string& elem) {
    unsigned long hash = hashFunc(elem);
    int idx = hash % set.tableSize;

    Node* currNode = set.buckets[idx];
    Node* prevNode = NULL;

    while (currNode != NULL) {
        if (currNode->val == elem) {
            if (prevNode == NULL) {
                set.buckets[idx] = currNode->next;
            } else {
                prevNode->next = currNode->next;
            }

            delete currNode;
            cout << "Элемент " << elem << " успешно удален" << endl;
            return;
        }
        prevNode = currNode;
        currNode = currNode->next;
    }
    
    cout << "Элемент " << elem << " не найден в множестве" << endl;
}

bool loadFromFile(CustomHash& set, const string& fPath) {
    ifstream inFile(fPath);
    if (!inFile.is_open()) {
        cout << "Ошибка: не удалось открыть файл " << fPath << endl;
        return false;
    }
    
    cout << "Загрузка данных из файла..." << endl;
    string currLine;

    while (getline(inFile, currLine)) {
        if (!currLine.empty()) {
            addElem(set, currLine);
        }
    }

    cout << "Данные успешно загружены" << endl;
    return true;
}

void printSet(const CustomHash& set) {
    cout << "Текущее состояние множества:" << endl;
    bool isEmpty = true;
    
    for (int i = 0; i < set.tableSize; i++) {
        Node* currNode = set.buckets[i];
        while (currNode != NULL) {
            isEmpty = false;
            cout << currNode->val << endl;
            currNode = currNode->next;
        }
    }
    
    if (isEmpty) {
        cout << "Множество пусто" << endl;
    }
}

// Тестирование функций хеш-таблицы
void testHashTableFunctions() {
    cout << "\n=== ТЕСТИРОВАНИЕ ФУНКЦИЙ ХЕШ-ТАБЛИЦЫ ===" << endl;
    
    CustomHash testSet;
    
    // Тест 1: Инициализация
    cout << "\n1. Тест инициализации..." << endl;
    initializeSet(testSet);
    cout << "Размер таблицы: " << testSet.tableSize << endl;
    cout << "Хеш-таблица успешно инициализирована!" << endl;
    
    // Тест 2: Добавление элементов
    cout << "\n2. Тест добавления элементов..." << endl;
    addElem(testSet, "apple");
    addElem(testSet, "banana");
    addElem(testSet, "orange");
    addElem(testSet, "apple"); // Попытка добавить дубликат
    cout << "Статус после добавления:" << endl;
    printSet(testSet);
    
    // Тест 3: Проверка наличия элементов
    cout << "\n3. Тест проверки наличия элементов..." << endl;
    cout << "Проверка 'apple': " << (checkElem(testSet, "apple") ? "найден" : "не найден") << endl;
    cout << "Проверка 'grape': " << (checkElem(testSet, "grape") ? "найден" : "не найден") << endl;
    
    // Тест 4: Удаление элементов
    cout << "\n4. Тест удаления элементов..." << endl;
    removeElem(testSet, "banana");
    removeElem(testSet, "grape"); // Попытка удалить несуществующий элемент
    cout << "Статус после удаления:" << endl;
    printSet(testSet);
    
    // Тест 5: Добавление коллизий
    cout << "\n5. Тест хеш-функции и коллизий..." << endl;
    cout << "Хеш 'test1': " << hashFunc("test1") << endl;
    cout << "Хеш 'test2': " << hashFunc("test2") << endl;
    cout << "Хеш 'apple': " << hashFunc("apple") << endl;
    
    // Тест 6: Работа с пустой таблицей
    cout << "\n6. Тест работы с пустой таблицей..." << endl;
    CustomHash emptySet;
    initializeSet(emptySet);
    cout << "Проверка 'something' в пустой таблице: " 
         << (checkElem(emptySet, "something") ? "найден" : "не найден") << endl;
    printSet(emptySet);
    freeSet(emptySet);
    
    // Тест 7: Очистка памяти
    cout << "\n7. Тест освобождения памяти..." << endl;
    freeSet(testSet);
    cout << "Память успешно освобождена!" << endl;
}

// Тест загрузки из файла
void testFileOperations() {
    cout << "\n=== ТЕСТИРОВАНИЕ РАБОТЫ С ФАЙЛАМИ ===" << endl;
    
    CustomHash fileSet;
    initializeSet(fileSet);
    
    // Создание тестового файла
    ofstream testFile("test_data.txt");
    if (testFile.is_open()) {
        testFile << "первая строка\nвторая строка\nтретья строка\nпервая строка\n"; // Дубликат
        testFile.close();
        cout << "Тестовый файл создан" << endl;
    }
    
    // Тест загрузки из файла
    cout << "\n1. Тест загрузки из файла..." << endl;
    bool loaded = loadFromFile(fileSet, "test_data.txt");
    cout << "Результат загрузки: " << (loaded ? "успешно" : "ошибка") << endl;
    printSet(fileSet);
    
    // Тест загрузки из несуществующего файла
    cout << "\n2. Тест загрузки из несуществующего файла..." << endl;
    loadFromFile(fileSet, "несуществующий_файл.txt");
    
    freeSet(fileSet);
}

// Тест пользовательского интерфейса
void testUserInterface() {
    cout << "\n=== ТЕСТИРОВАНИЕ ПОЛЬЗОВАТЕЛЬСКОГО ИНТЕРФЕЙСА ===" << endl;
    
    CustomHash uiSet;
    initializeSet(uiSet);
    
    cout << "\n1. Тест команды SETADD..." << endl;
    addElem(uiSet, "element1");
    addElem(uiSet, "element2");
    addElem(uiSet, "element1"); // Дубликат
    
    cout << "\n2. Тест команды SET_AT..." << endl;
    cout << "Поиск 'element1': " << (checkElem(uiSet, "element1") ? "найден" : "не найден") << endl;
    cout << "Поиск 'element3': " << (checkElem(uiSet, "element3") ? "найден" : "не найден") << endl;
    
    cout << "\n3. Тест команды SETDEL..." << endl;
    removeElem(uiSet, "element2");
    removeElem(uiSet, "element2"); // Повторное удаление
    
    cout << "\n4. Итоговое состояние:" << endl;
    printSet(uiSet);
    
    freeSet(uiSet);
};

int main() {
    cout << "=== ПРОГРАММА РАБОТЫ С ХЕШ-ТАБЛИЦЕЙ ===" << endl;
    
    // Запуск всех тестов
    testHashTableFunctions();
    testFileOperations();
    testUserInterface();
    
    // Основной интерфейс программы
    cout << "\n=== ОСНОВНОЙ РЕЖИМ РАБОТЫ ===" << endl;
    
    string fPath;
    string cmd;
    string arg;

    cout << "\nВведите путь к файлу с данными (или 'test' для использования тестового файла): ";
    getline(cin, fPath);

    if (fPath.empty()) {
        cout << "Ошибка: путь к файлу не может быть пустым" << endl;
        return 1;
    }

    // Создание тестового файла, если указано 'test'
    if (fPath == "test") {
        fPath = "input_data.txt";
        ofstream testInput(fPath);
        if (testInput.is_open()) {
            testInput << "начальный элемент 1\n";
            testInput << "начальный элемент 2\n";
            testInput << "начальный элемент 3\n";
            testInput.close();
            cout << "Используется тестовый файл: " << fPath << endl;
        }
    }

    CustomHash mainSet;
    initializeSet(mainSet);

    if (!loadFromFile(mainSet, fPath)) {
        cout << "\nСоздание пустой хеш-таблицы для работы..." << endl;
    }
    
    printSet(mainSet);

    while (true) {
        cout << "\nВведите команду (SETADD, SETDEL, SET_AT) или EXIT для выхода: ";
        cin >> cmd;

        for (char &c : cmd) {
            c = toupper(c);
        }

        if (cmd == "EXIT") {
            break;
        }

        if (cmd == "SETADD" || cmd == "SETDEL" || cmd == "SET_AT") {
            cout << "Введите элемент: ";
            cin >> arg;

            if (cmd == "SETADD") {
                if (checkElem(mainSet, arg)) {
                    cout << "Элемент " << arg << " уже существует в множестве." << endl;
                } else {
                    addElem(mainSet, arg);
                }
            } else if (cmd == "SETDEL") {
                removeElem(mainSet, arg);
            } else if (cmd == "SET_AT") {
                if (checkElem(mainSet, arg)) {
                    cout << "Элемент " << arg << " найден в множестве." << endl;
                } else {
                    cout << "Элемент " << arg << " не найден в множестве." << endl;
                }
            }
            
            printSet(mainSet);
        } else {
            cout << "Ошибка: неизвестная команда в запросе: " << cmd << endl;
            cout << "Доступные команды: SETADD, SETDEL, SET_AT, EXIT" << endl;
        }
    }

    freeSet(mainSet);
    
    cout << "\n=== ПРОГРАММА ЗАВЕРШЕНА ===" << endl;
    return 0;
}