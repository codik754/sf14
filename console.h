//Файл console.h
#pragma once

#include "dictionary.h"
#include <windows.h>
#include <iostream>
#include <vector>

//Определяем коды кнопок
enum valueKeys {
	THIS_IS_NULL = 0,
	CTRL_C = 3,
	BACKSPACE = 8,
	TAB = 9,
	ENTER = 13,
	SPACE = 32,
	F1 = 59,
	F2 = 60,
	F3 = 61,
	LEFT = 75,
	RIGHT = 77
};

//Класс для работы с консолью
class Console{
	Dictionary dict_;//словарь
	std::string buffer_; //буффер для сохранения строки
	HANDLE hConsole_;//поле нужно для работы с цветом в консоле Windows и для другого еще
	size_t length_;//длина строки в буфере
	size_t pos_; //позиция курсора в сообщении
	std::vector<std::string> v_; //вектор для сохранения результатов поиска в словаре
public:
	//Конструктор по умолчанию
	Console();

	//Показать все слова
	void showAllWords();

	//Установить цвет в консоле
	void setColorToConsole(WORD n);

	//Добавить символ в буфер
	void addToBuffer(char c);

	//Получить буфер
	std::string& getBuffer();

	//Отобразить помощь
	void showHelp();

	//Отобразить информацию о программе
	void showInfo();

	//Добавления символа в консоль
	void addSymbolToConsole(char symbol);

	//Получить количество записей в векторе
	size_t getAmountToVector() const;

	//Метод, запускаемый при нажатии клавиши влево
	void pressedLeft();
	//Метод, запускаемый при нажатии клавиши вправо
	void pressedRight();

	//Нажата клавиша Enter
	void pressedEnter();

	//Нажата клавиша Backspace
	void pressedBackspace();

	//Нажата клавиша Tab один раз
	void pressedTab();

	//Нажата клавиша Tab два раза раз
	void pressedDoubleTab();
	
};

