#include "TextEditor.h"
#include <algorithm>

// Конструктор
TextEditor::TextEditor() {
    // Стеки уже пустые по умолчанию
}

// Добавляет текст в позицию курсора
void TextEditor::addText(const std::string& text) {
    for (char c : text) {
        leftStack.push(c);
    }
}

// Удаляет k символов слева от курсора
int TextEditor::deleteText(int k) {
    int deleted = 0;
    while (deleted < k && !leftStack.empty()) {
        leftStack.pop();
        deleted++;
    }
    return deleted;
}

// Смещает курсор на k символов влево
std::string TextEditor::cursorLeft(int k) {
    int moved = 0;
    while (moved < k && !leftStack.empty()) {
        rightStack.push(leftStack.top());
        leftStack.pop();
        moved++;
    }
    
    return getLeftText();
}

// Смещает курсор на k символов вправо
std::string TextEditor::cursorRight(int k) {
    int moved = 0;
    while (moved < k && !rightStack.empty()) {
        leftStack.push(rightStack.top());
        rightStack.pop();
        moved++;
    }
    
    return getLeftText();
}

// Вспомогательная функция для получения последних 10 символов слева от курсора
std::string TextEditor::getLeftText() {
    std::string result;
    std::stack<char> temp;
    
    // Извлекаем символы из leftStack во временный стек
    int count = 0;
    while (!leftStack.empty() && count < 10) {
        temp.push(leftStack.top());
        leftStack.pop();
        count++;
    }
    
    // Формируем результат и возвращаем символы обратно в leftStack
    while (!temp.empty()) {
        result += temp.top();
        leftStack.push(temp.top());
        temp.pop();
    }
    
    return result;
}

// Вспомогательная функция для отображения всего текста
std::string TextEditor::getAllText() {
    std::string result;
    std::stack<char> temp;
    
    // Получаем левую часть
    while (!leftStack.empty()) {
        temp.push(leftStack.top());
        leftStack.pop();
    }
    
    while (!temp.empty()) {
        result += temp.top();
        leftStack.push(temp.top());
        temp.pop();
    }
    
    // Добавляем курсор для визуализации
    result += "|";
    
    // Получаем правую часть
    while (!rightStack.empty()) {
        temp.push(rightStack.top());
        rightStack.pop();
    }
    
    std::string rightPart;
    while (!temp.empty()) {
        rightPart += temp.top();
        rightStack.push(temp.top());
        temp.pop();
    }
    
    std::reverse(rightPart.begin(), rightPart.end());
    result += rightPart;
    
    return result;
}
