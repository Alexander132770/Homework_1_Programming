#include <iostream>
#include "TextEditor.h"

int main() {
    TextEditor editor;
    
    std::cout << "=== Демонстрация работы текстового редактора ===\n\n";
    
    // Добавляем текст
    editor.addText("Hello");
    std::cout << "После addText('Hello'): " << editor.getAllText() << std::endl;
    
    editor.addText(" World");
    std::cout << "После addText(' World'): " << editor.getAllText() << std::endl;
    
    // Перемещаем курсор влево
    std::string left = editor.cursorLeft(6);
    std::cout << "После cursorLeft(6): " << editor.getAllText() << std::endl;
    std::cout << "Символы слева: '" << left << "'" << std::endl;
    
    // Добавляем текст в текущую позицию
    std::cout << "После addText('Beautiful '): " << editor.getAllText() << std::endl;
    
    // Перемещаем курсор вправо
    std::string right = editor.cursorRight(3);
    std::cout << "После cursorRight(3): " << editor.getAllText() << std::endl;
    std::cout << "Символы слева: '" << right << "'" << std::endl;
    
    // Удаляем текст
    int deleted = editor.deleteText(2);
    std::cout << "После deleteText(2): " << editor.getAllText() << std::endl;
    std::cout << "Удалено символов: " << deleted << std::endl;
    
    // Еще несколько операций
    editor.cursorLeft(5);
    std::cout << "После cursorLeft(5): " << editor.getAllText() << std::endl;
    
    editor.addText("Amazing ");
    std::cout << "После addText('Amazing '): " << editor.getAllText() << std::endl;
    
    // Пытаемся удалить больше символов чем есть
    deleted = editor.deleteText(100);
    std::cout << "После deleteText(100): " << editor.getAllText() << std::endl;
    std::cout << "Фактически удалено: " << deleted << " символов" << std::endl;
    
    return 0;
}
