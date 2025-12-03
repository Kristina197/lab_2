#include "stack.hpp"
#include <iostream>

void initStack(Stack &stack) {
    stack.top = nullptr;
}

void push(Stack &stack, const std::string& val) {
    SNode* node = new SNode;
    node->value = val;
    node->next = stack.top;
    stack.top = node;
}

std::string pop(Stack &stack) {
    if (!stack.top) {
        return "";
    }
    SNode* tmp = stack.top;
    std::string val = tmp->value;
    stack.top = stack.top->next;
    delete tmp;
    return val;
}

std::string peek(const Stack& stack) {
    if (!stack.top) {
        return "";
    }
    return stack.top->value;
}

void readStack(const Stack &stack) {
    if (!stack.top) {
        std::cout << "Стек пуст" << std::endl;
        return;
    }
    std::cout << "Содержимое стека: " << std::endl;
    for (SNode* curr = stack.top; curr; curr = curr->next) {
        std::cout << curr->value << std::endl;
    }
}

void clearStack(Stack &stack) {
    while (stack.top) {
        SNode* tmp = stack.top;
        stack.top = stack.top->next;
        delete tmp;
    }
    std::cout << "память очищена" << std::endl;
}