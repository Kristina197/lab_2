#include <iostream>
#include <string>
#include "../include/doubleHash.hpp"

using namespace std;

void displayHashMenu() {
    cout << "\n=== МЕНЮ ХЕШ-ТАБЛИЦЫ ===" << endl;
    cout << "1. Создать новую хеш-таблицу" << endl;
    cout << "2. Добавить элемент" << endl;
    cout << "3. Найти элемент" << endl;
    cout << "4. Удалить элемент" << endl;
    cout << "5. Показать все элементы" << endl;
    cout << "6. Показать статистику" << endl;
    cout << "7. Получить все ключи" << endl;
    cout << "0. Выход" << endl;
    cout << "Выберите действие: ";
}

void intHashTableMenu() {
    DoubleHashingHashTable<int, int> hashTable;
    int choice;
    
    do {
        displayHashMenu();
        cin >> choice;
        
        switch (choice) {
            case 1: {
                size_t capacity;
                double loadFactor;
                cout << "Введите емкость таблицы: ";
                cin >> capacity;
                cout << "Введите коэффициент заполнения (0.1-0.9): ";
                cin >> loadFactor;
                
                hashTable = DoubleHashingHashTable<int, int>(capacity, loadFactor);
                cout << "Хеш-таблица создана!" << endl;
                break;
            }
            
            case 2: {
                int key, value;
                cout << "Введите ключ: ";
                cin >> key;
                cout << "Введите значение: ";
                cin >> value;
                
                if (hashTable.directInsert(key, value)) {
                    cout << "Элемент успешно добавлен!" << endl;
                } else {
                    cout << "Ошибка при добавлении элемента!" << endl;
                }
                break;
            }
            
            case 3: {
                int key;
                cout << "Введите ключ для поиска: ";
                cin >> key;
                
                auto result = hashTable.search(key);
                if (result.has_value()) {
                    cout << "Найдено: ключ " << key << " -> значение " << result.value() << endl;
                } else {
                    cout << "Элемент с ключом " << key << " не найден!" << endl;
                }
                break;
            }
            
            case 4: {
                int key;
                cout << "Введите ключ для удаления: ";
                cin >> key;
                
                if (hashTable.remove(key)) {
                    cout << "Элемент успешно удален!" << endl;
                } else {
                    cout << "Элемент с ключом " << key << " не найден!" << endl;
                }
                break;
            }
            
            case 5: {
                hashTable.display();
                break;
            }
            
            case 6: {
                cout << "\n=== СТАТИСТИКА ХЕШ-ТАБЛИЦЫ ===" << endl;
                cout << "Емкость: " << hashTable.getCapacity() << endl;
                cout << "Размер: " << hashTable.getSize() << endl;
                cout << "Коэффициент заполнения: " << hashTable.getLoadFactor() << endl;
                cout << "===============================" << endl;
                break;
            }
            
            case 7: {
                auto keys = hashTable.keys();
                cout << "Ключи в таблице: ";
                for (int i = 0; i < arraySize(keys); i++) {
                    cout << indexKey(keys, i);
                    if (i < arraySize(keys) - 1) {
                        cout << ", ";
                    }
                }
                cout << endl;
                break;
            }
            
            case 0: {
                cout << "Выход из меню хеш-таблицы..." << endl;
                break;
            }
            
            default: {
                cout << "Неверный выбор! Попробуйте снова." << endl;
                break;
            }
        }
    } while (choice != 0);
}

void stringHashTableMenu() {
    DoubleHashingHashTable<string, string> hashTable;
    int choice;
    
    do {
        displayHashMenu();
        cin >> choice;
        
        switch (choice) {
            case 1: {
                size_t capacity;
                double loadFactor;
                cout << "Введите емкость таблицы: ";
                cin >> capacity;
                cout << "Введите коэффициент заполнения (0.1-0.9): ";
                cin >> loadFactor;
                
                hashTable = DoubleHashingHashTable<string, string>(capacity, loadFactor);
                cout << "Хеш-таблица создана!" << endl;
                break;
            }
            
            case 2: {
                string key, value;
                cout << "Введите ключ: ";
                cin >> key;
                cout << "Введите значение: ";
                cin >> value;
                
                if (hashTable.directInsert(key, value)) {
                    cout << "Элемент успешно добавлен!" << endl;
                } else {
                    cout << "Ошибка при добавлении элемента!" << endl;
                }
                break;
            }
            
            case 3: {
                string key;
                cout << "Введите ключ для поиска: ";
                cin >> key;
                
                auto result = hashTable.search(key);
                if (result.has_value()) {
                    cout << "Найдено: ключ '" << key << "' -> значение '" << result.value() << "'" << endl;
                } else {
                    cout << "Элемент с ключом '" << key << "' не найден!" << endl;
                }
                break;
            }
            
            case 4: {
                string key;
                cout << "Введите ключ для удаления: ";
                cin >> key;
                
                if (hashTable.remove(key)) {
                    cout << "Элемент успешно удален!" << endl;
                } else {
                    cout << "Элемент с ключом '" << key << "' не найден!" << endl;
                }
                break;
            }
            
            case 5: {
                hashTable.display();
                break;
            }
            
            case 6: {
                cout << "\n=== СТАТИСТИКА ХЕШ-ТАБЛИЦЫ ===" << endl;
                cout << "Емкость: " << hashTable.getCapacity() << endl;
                cout << "Размер: " << hashTable.getSize() << endl;
                cout << "Коэффициент заполнения: " << hashTable.getLoadFactor() << endl;
                cout << "===============================" << endl;
                break;
            }
            
            case 7: {
                auto keys = hashTable.keys();
                cout << "Ключи в таблице: ";
                for (int i = 0; i < arraySize(keys); i++) {
                    cout << "'" << indexKey(keys, i) << "'";
                    if (i < arraySize(keys) - 1) {
                        cout << ", ";
                    }
                }
                cout << endl;
                break;
            }
            
            case 0: {
                cout << "Выход из меню хеш-таблицы..." << endl;
                break;
            }
            
            default: {
                cout << "Неверный выбор! Попробуйте снова." << endl;
                break;
            }
        }
    } while (choice != 0);
}

int main() {
    int typeChoice;
    
    do {
        cout << "\n=== ВЫБОР ТИПА ХЕШ-ТАБЛИЦЫ ===" << endl;
        cout << "1. Хеш-таблица с целыми числами (int -> int)" << endl;
        cout << "2. Хеш-таблица со строками (string -> string)" << endl;
        cout << "0. Выход" << endl;
        cout << "Выберите тип: ";
        cin >> typeChoice;
        
        switch (typeChoice) {
            case 1:
                intHashTableMenu();
                break;
            case 2:
                stringHashTableMenu();
                break;
            case 0:
                cout << "Выход из программы..." << endl;
                break;
            default:
                cout << "Неверный выбор! Попробуйте снова." << endl;
                break;
        }
    } while (typeChoice != 0);

    return 0;
}
