#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
using namespace std;

struct SNode {
    string value;
    SNode* next;
};

struct Stack {
    SNode* top;
};

// Инициализация стека
void initStack(Stack &stack) {
    stack.top = nullptr;
}

// Добавление элемента в стек
void push(Stack &stack, const string& val) {
    SNode* node = new SNode;
    node->value = val;
    node->next = stack.top;
    stack.top = node;
}

// Извлечение элемента из стека
string pop(Stack &stack) {
    if (!stack.top) {
        return "";
    }
    SNode* tmp = stack.top;
    string val = tmp->value;
    stack.top = stack.top->next;
    delete tmp;
    return val;
}

// Просмотр верхнего элемента без удаления
string peek(const Stack& stack) {
    if (!stack.top) {
        return "";
    }
    return stack.top->value;
}

// Вывод содержимого стека
void readStack(const Stack &stack) {
    if (!stack.top) {
        cout << "Стек пуст" << endl;
        return;
    }
    cout << "Содержимое стека: " << endl;
    for (SNode* curr = stack.top; curr; curr = curr->next) {
        cout << curr->value << endl;
    }
}

// Очистка памяти
void clearStack(Stack &stack) {
    while (stack.top) {
        SNode* tmp = stack.top;
        stack.top = stack.top->next;
        delete tmp;
    }
    cout << "память очищена" << endl;
}

// Проверка, является ли токен оператором
bool isOperator(const string& token) {
    return token == "+" 
            || token == "-" 
            || token == "*" 
            || token == "/";
}

// Выполнение арифметической операции
double performOperation(const string& operation, double a, double b) {
    if (operation == "+") return a + b;
    if (operation == "-") return a - b;
    if (operation == "*") return a * b;
    if (operation == "/") {
        if (b == 0) {
            throw runtime_error("Деление на ноль!");
        }
        return a / b;
    }
    throw invalid_argument("Неизвестная операция: " + operation);
}

// Основная функция вычисления RPN выражения
double evaluateRPN(const string& expression) {
    Stack operands;
    initStack(operands);
    
    istringstream iss(expression);
    string token;
    
    cout << "Вычисление выражения: " << expression << endl;
    cout << "==================================" << endl;
    
    while (iss >> token) {
        
        if (isOperator(token)) {
            // Проверяем, что в стеке достаточно операндов
            if (!operands.top || !operands.top->next) {
                clearStack(operands);
                throw runtime_error("Недостаточно операндов для операции " + token);
            }
            
            // Извлекаем два операнда
            string b_str = pop(operands);
            string a_str = pop(operands);
            
            // Преобразуем в числа
            double b = stod(b_str);
            double a = stod(a_str);
            
            // Выполняем операцию
            double result = performOperation(token, a, b);
            
            // Помещаем результат обратно в стек
            push(operands, to_string(result));
            
        } else {
            // Проверяем, что токен - число
            try {
                stod(token);
                // Если успешно - добавляем в стек
                push(operands, token);
            } catch (const invalid_argument&) {
                clearStack(operands);
                throw invalid_argument("Некорректный токен: " + token);
            }
        }
        
    }
    
    // Проверяем, что в стеке остался ровно один элемент
    if (!operands.top || operands.top->next) {
        clearStack(operands);
        throw runtime_error("Некорректное выражение");
    }
    
    // Извлекаем и возвращаем результат
    string result_str = pop(operands);
    double result = stod(result_str);
    
    cout << "==================================" << endl;
    cout << "Финальный результат: " << result << endl;
    
    return result;
}

// Функция для демонстрации вычислений
void demonstrateCalculation(const string& expression) {
    cout << "\n" << string(50, '=') << endl;
    cout << "ВЫЧИСЛЕНИЕ: " << expression << endl;
    cout << string(50, '=') << endl;
    
    try {
        double result = evaluateRPN(expression);
        cout << "УСПЕХ: " << expression << " = " << result << endl;
    } catch (const exception& e) {
        cout << "ОШИБКА: " << e.what() << endl;
    }
}

// Интерактивный режим
void interactiveMode() {
    cout << "\nИНТЕРАКТИВНЫЙ РЕЖИМ КАЛЬКУЛЯТОРА RPN" << endl;
    cout << "Введите выражения в обратной польской записи" << endl;
    cout << "Пример: 3 1 4 * +" << endl;
    cout << "Для выхода введите 'exit'" << endl;
    
    string input;
    while (true) {
        cout << "\n> ";
        getline(cin, input);
        
        if (input == "exit" || input == "quit") {
            break;
        }
        
        if (input.empty()) {
            continue;
        }
        
        try {
            double result = evaluateRPN(input);
            cout << "Результат: " << result << endl;
        } catch (const exception& e) {
            cout << "Ошибка: " << e.what() << endl;
        }
    }
}

// Демонстрация работы стека
void demonstrateStack() {
    cout << "=== Демонстрация работы стека ===" << endl;
    
    Stack stack;
    initStack(stack);
    
    cout << "Добавляем элементы: 10, 20, 30" << endl;
    push(stack, "10");
    push(stack, "20");
    push(stack, "30");
    
    readStack(stack);
    
    cout << "Верхний элемент: " << peek(stack) << endl;
    
    cout << "Извлекаем элементы: ";
    while (stack.top) {
        cout << pop(stack) << " ";
    }
    cout << endl;
    
    clearStack(stack);
}

// Главная функция
int main() {
    // Демонстрация работы стека
    demonstrateStack();
    
    cout << "\nКАЛЬКУЛЯТОР ОБРАТНОЙ ПОЛЬСКОЙ ЗАПИСИ" << endl;
    cout << "=====================================" << endl;
    
    // Демонстрационные примеры
    demonstrateCalculation("3 1 4 * +");        // 3 + 1 * 4 = 7
    demonstrateCalculation("5 1 2 + 4 * + 3 -"); // 5 + ((1 + 2) * 4) - 3 = 14
    demonstrateCalculation("2 3 + 4 *");         // (2 + 3) * 4 = 20
    demonstrateCalculation("4 2 /");             // 4 / 2 = 2
    
    // Примеры с ошибками
    demonstrateCalculation("3 +");               // Недостаточно операндов
    demonstrateCalculation("3 0 /");             // Деление на ноль
    demonstrateCalculation("3 abc +");           // Некорректный токен
    
    // Запуск интерактивного режима
    interactiveMode();
    
    return 0;
}