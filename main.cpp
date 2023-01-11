//Файл main.cpp
#include <iostream>
#include <conio.h>
#include "console.h"

void consoleCode() {
	Console cons;//Объект для работы с консолью

	int c = 'a';
	bool bit = false;//логическая переменная для определения нажатия дважды Tab
	bool specialBit = false;//для определения нажатия F клавишь
	bool rightLeft = false; //нажатия права или лево
	cons.setColorToConsole(6);
	std::cout << "Добро пожаловать!" << std::endl << "Для справки нажмите F1" << std::endl << std::endl;
	std::cout << "<message>: ";
	cons.setColorToConsole(15);
	//Выход при нажатии Ctrl+C
	while (c != CTRL_C) {
		//Читаем символ
		c = _getch();
	
		//При нажатии F1 сначало в буфер помещается 0, а потом число 59,
		//поэтому для того, чтобы определить нажатие клавишь F будем отлавливать 0
		if (c == valueKeys::THIS_IS_NULL) {
			bit = false;
			specialBit = true;
		}
		else if (specialBit && c == valueKeys::F1) {
			//Если нажата F1
			specialBit = false;
			bit = false;
			rightLeft = false;
			//std::cout << std::endl << "Нажата F1" << std::endl;
			//cons.showCoord();
			cons.showHelp();
			cons.setColorToConsole(6);
			std::cout << "<message>: ";
			cons.setColorToConsole(15);
		}
		else if (specialBit && c == valueKeys::F2) {
			//Если нажата F2
			specialBit = false;
			bit = false;
			rightLeft = false;
			cons.showAllWords();
			cons.setColorToConsole(6);
			std::cout << "<message>: ";
			cons.setColorToConsole(15);
			std::cout << cons.getBuffer();//выводим буфер
		}
		else if (specialBit && c == valueKeys::F3) {
			//Если нажата F3
			specialBit = false;
			bit = false;
			rightLeft = false;
			cons.showInfo();
			cons.setColorToConsole(6);
			std::cout << "<message>: ";
			cons.setColorToConsole(15);
			std::cout << cons.getBuffer();//выводим буфер
		}
		else if (c == 224) {
			//Это является первым символом отправляемым при нажатии LEFT, RIGHT и DEL
			bit = false;
			specialBit = false;
			rightLeft = true;
		}
		else if (rightLeft && c == valueKeys::LEFT) {
			//Если нажата LEFT
			bit = false;
			specialBit = false;
			rightLeft = false;
			cons.pressedLeft();
		}
		else if (rightLeft && c == valueKeys::RIGHT) {
			//Если нажата RIGHT
			bit = false;
			specialBit = false;
			rightLeft = false;
			cons.pressedRight();
		}
		else if (c == valueKeys::BACKSPACE) {
			//Если нажата BACKSPACE
			bit = false;
			specialBit = false;
			rightLeft = false;
			cons.pressedBackspace();
		}
		else if (c == valueKeys::ENTER) {
			//Если нажата Enter
			bit = false;
			specialBit = false;
			rightLeft = false;
			cons.pressedEnter();
			cons.setColorToConsole(6);
			std::cout << "<message>: ";
			cons.setColorToConsole(15);
			std::cout << cons.getBuffer();//выводим буфер
		}
		else if (c == valueKeys::TAB) {
			//Если нажата Tabs
			specialBit = false;
			rightLeft = false;
			if (!bit) {
				//Tab нажата один раз
				bit = true;
				cons.pressedTab();
			}
			else {
				//Tab нажата два раза
				bit = false;
				if (cons.getAmountToVector() > 1) {
					cons.pressedDoubleTab();
					cons.setColorToConsole(6);
					std::cout << "<message>: ";
					cons.setColorToConsole(15);
					std::cout << cons.getBuffer();//выводим буфер
				}
			}
		}
		else if (c >= 32 && c <= 126 && !specialBit && !rightLeft) {
			//Нажата клавиша символа для ввода
			bit = false;
			specialBit = false;
			rightLeft = false;
			char symbol = static_cast<char>(c);
			cons.addToBuffer(symbol);
			cons.addSymbolToConsole(symbol);

		}
		else {
			//Нажата неизвестная клавиша
			bit = false;
			specialBit = false;
			rightLeft = false;
			cons.setColorToConsole(3);
			std::cout << std::endl << "Такого не знаю!!!" << std::endl;
			cons.setColorToConsole(6);
			std::cout << "<message>: ";
			cons.setColorToConsole(15);
			std::cout << cons.getBuffer();//выводим буфер
		}
	}
}

int main() {
	setlocale(LC_ALL, "");
	consoleCode();
	return 0;
}