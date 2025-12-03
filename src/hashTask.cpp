#include <iostream>
#include <string>
#include "../include/doubleHash.hpp"
#include "../include/array.hpp"

using namespace std;

struct Pair {
    string employee;
    string manager;
};

int countDirectSubordinates(MyArray<Pair>& pairs, const string& manager) {
    int count = 0;
    for (int i = 0; i < arraySize(pairs); i++) {
        Pair p = indexKey(pairs, i);
        if (p.manager == manager && p.employee != manager) {
            count++;
        }
    }
    return count;
}

int countAllSubordinates(MyArray<Pair>& pairs, const string& manager, DoubleHashingHashTable<string, int>& cache) {
    // Проверяем кэш
    auto cached = cache.search(manager);
    if (cached.has_value()) {
        return cached.value();
    }
    
    int total = 0;

    for (int i = 0; i < arraySize(pairs); i++) {
        Pair p = indexKey(pairs, i);
        if (p.manager == manager && p.employee != manager) {
            total += 1 + countAllSubordinates(pairs, p.employee, cache);
        }
    }

    cache.directInsert(manager, total);
    return total;
}

int main() {
    MyArray<Pair> pairs;
    
    cout << "Введите пары (сотрудник менеджер), для завершения введите 'end':" << endl;

    string emp, mgr;
    while (true) {
        cin >> emp;
        if (emp == "end") break;
        cin >> mgr;
        
        Pair newPair;
        newPair.employee = emp;
        newPair.manager = mgr;
        addTail(pairs, newPair);
    }

    DoubleHashingHashTable<string, int> cache;

    DoubleHashingHashTable<string, bool> allEmployees;
    for (int i = 0; i < arraySize(pairs); i++) {
        Pair p = indexKey(pairs, i);
        allEmployees.directInsert(p.employee, true);
        allEmployees.directInsert(p.manager, true);
    }

    cout << "Результат: ";
    bool first = true;

    MyArray<string> printed;
    
    for (int i = 0; i < arraySize(pairs); i++) {
        Pair p = indexKey(pairs, i);

        bool employeePrinted = false;
        bool managerPrinted = false;
        
        for (int j = 0; j < arraySize(printed); j++) {
            if (indexKey(printed, j) == p.employee) {
                employeePrinted = true;
            }
            if (indexKey(printed, j) == p.manager) {
                managerPrinted = true;
            }
        }

        if (!employeePrinted) {
            int count = countAllSubordinates(pairs, p.employee, cache);
            if (!first) cout << ", ";
            cout << p.employee << "-" << count;
            first = false;
            addTail(printed, p.employee);
        }

        if (!managerPrinted) {
            int count = countAllSubordinates(pairs, p.manager, cache);
            if (!first) cout << ", ";
            cout << p.manager << "-" << count;
            first = false;
            addTail(printed, p.manager);
        }
    }
    cout << endl;
    
    return 0;
}