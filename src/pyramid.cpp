#include <iostream>
#include <sstream>
#include <string>
#include "../include/arr.hpp"

using namespace std;

struct Block {
    int width;
    long long height;
};

// Функция сравнения для сортировки (по убыванию ширины)
void quickSort(Block* arr, int left, int right) {
    if (left >= right) return;
    
    int i = left, j = right;
    Block pivot = arr[(left + right) / 2];
    
    while (i <= j) {
        while (arr[i].width > pivot.width) i++;
        while (arr[j].width < pivot.width) j--;
        if (i <= j) {
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }
    
    quickSort(arr, left, j);
    quickSort(arr, i, right);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    cin >> N;
    
    // Временный массив для сбора пар (ширина -> максимальная высота)
    const int MAX_N = 100000;
    Block* tempBlocks = new Block[MAX_N];
    int uniqueCount = 0;
    
    // Читаем блоки и собираем максимальные высоты для каждой ширины
    for (int i = 0; i < N; ++i) {
        int w;
        long long h;
        cin >> w >> h;
        
        // Ищем ширину w в tempBlocks
        bool found = false;
        for (int j = 0; j < uniqueCount; ++j) {
            if (tempBlocks[j].width == w) {
                if (h > tempBlocks[j].height) {
                    tempBlocks[j].height = h;
                }
                found = true;
                break;
            }
        }
        
        if (!found) {
            tempBlocks[uniqueCount].width = w;
            tempBlocks[uniqueCount].height = h;
            uniqueCount++;
        }
    }
    
    // Сортируем по убыванию ширины
    quickSort(tempBlocks, 0, uniqueCount - 1);
    
    // Суммируем высоты
    long long totalHeight = 0;
    for (int i = 0; i < uniqueCount; ++i) {
        totalHeight += tempBlocks[i].height;
    }
    
    cout << totalHeight << "\n";
    
    delete[] tempBlocks;
    return 0;
}