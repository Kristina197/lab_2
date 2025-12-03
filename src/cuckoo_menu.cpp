#include <iostream>
#include <string>
#include "../include/birdHash.hpp"

using namespace std;

void displayCuckooMenu() {
    cout << "\n=== МЕНЮ КУКУШКИНОЙ ХЕШ-ТАБЛИЦЫ (string -> string) ===" << endl;
    cout << "1. Создать новую таблицу" << endl;
    cout << "2. Добавить элемент" << endl;
    cout << "3. Найти элемент" << endl;
    cout << "4. Удалить элемент" << endl;
    cout << "5. Показать все таблицы" << endl;
    cout << "6. Показать статистику" << endl;
    cout << "7. Получить все ключи" << endl;
    cout << "0. Выход" << endl;
    cout << "Выберите действие: ";
}

void cuckooTableMenu() {
    CuckooHashTable cuckooTable;
    int choice;
    
    do {
        displayCuckooMenu();
        cin >> choice;
        
        switch (choice) {
            case 1: {
                size_t capacity;
                cout << "Введите емкость таблицы: ";
                cin >> capacity;
                
                cuckooTable = CuckooHashTable(capacity);
                cout << "Кукушкина хеш-таблица создана!" << endl;
                break;
            }
            
            case 2: {
                string key, value;
                cout << "Введите ключ: ";
                cin >> key;
                cout << "Введите значение: ";
                cin >> value;
                
                if (cuckooTable.insert(key, value)) {
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
                
                auto result = cuckooTable.search(key);
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
                
                if (cuckooTable.remove(key)) {
                    cout << "Элемент успешно удален!" << endl;
                } else {
                    cout << "Элемент с ключом '" << key << "' не найден!" << endl;
                }
                break;
            }
            
            case 5: {
                cuckooTable.display();
                break;
            }
            
            case 6: {
                cout << "\n=== СТАТИСТИКА КУКУШКИНОЙ ХЕШ-ТАБЛИЦЫ ===" << endl;
                cout << "Емкость каждой таблицы: " << cuckooTable.getCapacity() << endl;
                cout << "Размер: " << cuckooTable.getSize() << endl;
                cout << "Общая емкость (2 таблицы): " << cuckooTable.getCapacity() * 2 << endl;
                cout << "==========================================" << endl;
                break;
            }
            
            case 7: {
                auto keys = cuckooTable.keys();
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
                cout << "Выход из меню кукушкиной хеш-таблицы..." << endl;
                break;
            }
            
            default: {
                cout << "Неверный выбор! Попробуйте снова." << endl;
                break;
            }
        }
    } while (choice != 0);
}

void demoCuckooHashing() {
    cout << "\n=== ДЕМОНСТРАЦИЯ КУКУШКИНОГО ХЕШИРОВАНИЯ ===" << endl;
    
    CuckooHashTable demoTable(4);
    
    cout << "Добавляем элементы:" << endl;
    demoTable.insert("apple", "red");
    cout << "Добавлен: apple -> red" << endl;
    
    demoTable.insert("banana", "yellow");
    cout << "Добавлен: banana -> yellow" << endl;
    
    demoTable.insert("orange", "orange");
    cout << "Добавлен: orange -> orange" << endl;
    
    demoTable.insert("grape", "purple");
    cout << "Добавлен: grape -> purple" << endl;
    
    cout << "\nСостояние таблиц после добавления 4 элементов:" << endl;
    demoTable.display();
    
    cout << "Пытаемся добавить элемент, который вызовет перемещения:" << endl;
    if (demoTable.insert("kiwi", "green")) {
        cout << "Успешно добавлен: kiwi -> green" << endl;
    } else {
        cout << "Не удалось добавить kiwi (возможно, достигнут лимит итераций)" << endl;
    }
    
    cout << "\nИтоговое состояние таблиц:" << endl;
    demoTable.display();
    
    cout << "\nПоиск элементов:" << endl;
    auto result1 = demoTable.search("apple");
    if (result1.has_value()) {
        cout << "Найден apple: " << result1.value() << endl;
    }
    
    auto result2 = demoTable.search("kiwi");
    if (result2.has_value()) {
        cout << "Найден kiwi: " << result2.value() << endl;
    }
    
    auto result3 = demoTable.search("unknown");
    if (!result3.has_value()) {
        cout << "Не найден unknown" << endl;
    }
}

int main() {
    int choice;
    
    do {
        cout << "\n=== КУКУШКИНА ХЕШ-ТАБЛИЦА СО СТРОКАМИ ===" << endl;
        cout << "Тип: string -> string" << endl;
        cout << "Хеш-функция: (hash * 31 + abs(c)) % capacity" << endl;
        cout << "1. Работа с таблицей" << endl;
        cout << "2. Демонстрация работы" << endl;
        cout << "0. Выход" << endl;
        cout << "Выберите действие: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                cuckooTableMenu();
                break;
            case 2:
                demoCuckooHashing();
                break;
            case 0:
                cout << "Выход из программы..." << endl;
                break;
            default:
                cout << "Неверный выбор! Попробуйте снова." << endl;
                break;
        }
    } while (choice != 0);

    return 0;
}