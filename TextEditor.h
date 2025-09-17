#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <stack>
#include <string>

class TextEditor {
private:
    std::stack<char> leftStack;  // Символы слева от курсора
    std::stack<char> rightStack; // Символы справа от курсора
    
    // Вспомогательная функция для получения последних 10 символов слева от курсора
    std::string getLeftText();

public:
    // Конструктор - инициализирует объект без текста
    TextEditor();

    // Добавляет текст в позицию курсора
    void addText(const std::string& text);

    // Удаляет k символов слева от курсора
    // Возвращает количество символов, которое было удалено
    int deleteText(int k);

    // Смещает курсор на k символов влево
    // Возвращает символы которые находятся левее курсора (последние 10)
    std::string cursorLeft(int k);

    // Смещает курсор на k символов вправо
    // Возвращает символы которые находятся левее курсора (последние 10)
    std::string cursorRight(int k);

    // Вспомогательная функция для отображения всего текста (для отладки)
    std::string getAllText();
};

#endif
