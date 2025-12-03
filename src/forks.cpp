#include "../include/tree.hpp"
#include <iostream>
#include <vector>

int main() {
    using namespace BinaryTree;
    using namespace std;
    
    FullBinaryTree* tree = createFBT();
    int value;
    
    // Чтение последовательности
    cin >> value;
    while (value != 0) {
        insertFBT(tree, value);
        cin >> value;
    }
    
    // Получение вершин с двумя детьми
    vector<int> forks = getNodesWithTwoChildren(tree);
    
    // Вывод результата
    for (size_t i = 0; i < forks.size(); ++i) {
        cout << forks[i];
        if (i != forks.size() - 1) {
            cout << " ";
        }
    }
    cout << endl;
    
    // Очистка памяти
    deleteFBT(tree);
    
    return 0;
}