#include <iostream>
#include <string>
#include "../include/lfu.hpp"

using namespace std;

void displayMenu() {
    cout << "\n=== Меню работы с LFU кэшем ===" << endl;
    cout << "1. Создать новый кэш" << endl;
    cout << "2. Добавить элемент (SET)" << endl;
    cout << "3. Получить элемент (GET)" << endl;
    cout << "4. Показать состояние кэша" << endl;
    cout << "5. Очистить кэш" << endl;
    cout << "0. Выход" << endl;
    cout << "Выберите опцию: ";
}

void printHumanReadableResult(int result, int key) {
    if (result == -1) {
        cout << "-1" << endl;
    } else {
        cout << "Ключ: " << key << ", Значение: " << result << endl;
    }
}

int main() {
    LFUCache* cache = nullptr;
    int choice;
    int capacity;
    
    do {
        displayMenu();
        cin >> choice;
        
        switch(choice) {
            case 1: {
                if (cache != nullptr) {
                    delete cache;
                    cout << "Старый кэш удален" << endl;
                }
                cout << "Введите емкость кэша: ";
                cin >> capacity;
                if (capacity <= 0) {
                    cout << "Ошибка: емкость должна быть положительным числом!" << endl;
                    break;
                }
                cache = new LFUCache(capacity);
                cout << "Кэш создан с емкостью " << capacity << endl;
                break;
            }
            
            case 2: {
                if (cache == nullptr) {
                    cout << "Ошибка: сначала создайте кэш!" << endl;
                    break;
                }
                int key, value;
                cout << "Введите ключ (целое число): ";
                cin >> key;
                cout << "Введите значение (целое число): ";
                cin >> value;
                cache->SET(key, value);
                cout << "Элемент добавлен: ключ=" << key << ", значение=" << value << endl;
                break;
            }
            
            case 3: {
                if (cache == nullptr) {
                    cout << "Ошибка: сначала создайте кэш!" << endl;
                    break;
                }
                int key;
                cout << "Введите ключ для поиска: ";
                cin >> key;
                int result = cache->GET(key);
                printHumanReadableResult(result, key);
                break;
            }
            
            case 4: {
                if (cache == nullptr) {
                    cout << "Ошибка: сначала создайте кэш!" << endl;
                    break;
                }
                cout << "\n--- Текущее состояние кэша ---" << endl;
                cache->printCache();
                break;
            }
            
            case 5: {
                if (cache != nullptr) {
                    delete cache;
                    cache = nullptr;
                    cout << "Кэш очищен" << endl;
                } else {
                    cout << "Кэш не создан!" << endl;
                }
                break;
            }
            
            case 0: {
                if (cache != nullptr) {
                    delete cache;
                    cout << "Кэш удален" << endl;
                }
                cout << "Выход из программы..." << endl;
                break;
            }
            
            default: {
                cout << "Неверный выбор! Попробуйте снова." << endl;
                break;
            }
        }
        
    } while (choice != 0);
    return 0;
}