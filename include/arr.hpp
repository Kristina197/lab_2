#ifndef LIB_H
#define LIB_H

using namespace std;
#include <string>

// Структура для массива
struct MyArr {
    string* data;   //указатель на динамический массив
    int size;    //текущий размер массива
    int capacity;
};
void initArray(MyArr &arr);
void freeArr(MyArr &arr);

void addEnd(MyArr &arr, const string& val);
void getAt(const MyArr &arr, int idx);
void delAt(MyArr &arr, int idx);
void readArray(const MyArr &arr);
void addAt(MyArr &arr, int idx, const string& val);
void repArr(MyArr &arr, int idx, const string& val);
int lenArr(const MyArr &arr);


#endif
