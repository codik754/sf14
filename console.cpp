//Файл console.cpp
#include "console.h"
#include <iostream>

//Конструктор по умолчанию
Console::Console() : dict_(), buffer_(), length_(0), pos_(0) {
	//Заполняем словарь словами
	dict_.fillDictionary();
	hConsole_ = GetStdHandle(STD_OUTPUT_HANDLE);
}


//Показать все слова
void Console::showAllWords(){
	setColorToConsole(15);
	std::cout << std::endl << "Общее количество слов в словаре: " << dict_.getCount() << std::endl;
	dict_.showAllWords();
}

//Установить цвет в консоле
void Console::setColorToConsole(WORD n) {
	SetConsoleTextAttribute(hConsole_, n);
}

//Добавить символ в буфер
void Console::addToBuffer(char c) {
    //Если в конце строки
	if (pos_ == length_) {
		buffer_.push_back(c);
	}
	else {
		//Иначе
		buffer_.insert(pos_, 1, c);
	}
	++length_;
	++pos_;
}

//Получить буфер
std::string& Console::getBuffer(){
	return buffer_;
}

//Отобразить помощь
void Console::showHelp() {
	setColorToConsole(6);
	std::cout << std::endl << "Помощь" << std::endl << std::endl;
	std::cout << "Нажмите: " << std::endl;
	setColorToConsole(3);
	std::cout << "F1 - ";
	setColorToConsole(6);
	std::cout << "для справки" << std::endl;
	setColorToConsole(3);
	std::cout << "F2 - ";
	setColorToConsole(6);
	std::cout << "для вывода всех слов в словаре" << std::endl;
	setColorToConsole(3);
	std::cout << "F3 - ";
	setColorToConsole(6);
	std::cout << "для вывода информации о программе" << std::endl;
	setColorToConsole(3);
	std::cout << "Left(стрелка влево) - ";
	setColorToConsole(6);
	std::cout << "перемещение влево" << std::endl;
	setColorToConsole(3);
	std::cout << "Right(стрелка вправо) - ";
	setColorToConsole(6);
	std::cout << "перемещение вправо" << std::endl;
	setColorToConsole(3);
	std::cout << "Backspace - ";
	setColorToConsole(6);
	std::cout << "удалить символ. Реализована возможность удаления только с конца" << std::endl;
	setColorToConsole(3);
	std::cout << "Tab - ";
	setColorToConsole(6);
	std::cout << "автодополнение. Если есть совпадение с одним словом в словаре, то это слово добавиться в текст." <<
	    " Если совпадений несколько, при повторном нажатие Tab выведится весь список слов." << std::endl;
	setColorToConsole(3);
	std::cout << " - ";
	setColorToConsole(6);
	std::cout << "отправка сообщения" << std::endl;
	setColorToConsole(3);
	std::cout << "Ctrl + c - ";
	setColorToConsole(6);
	std::cout << "выход из программы" << std::endl;
	setColorToConsole(15);

	std::cout << std::endl;
}

//Отобразить информацию о программе
void Console::showInfo() {
	setColorToConsole(3);
	std::cout << std::endl << "Программа с автодополнением текста v 1.0.0" << std::endl;
	setColorToConsole(6);
	std::cout << "Автор: ";
	setColorToConsole(3);
	std::cout << "Беспалов Иван" << std::endl;
	setColorToConsole(15);
}


//Метод, запускаемый при нажатии клавиши влево
void Console::pressedLeft(){
	//Если длина равна нулю
	if (length_ == 0) {
		return;
	}

	//Если курсор находится на нулевой позиции
	if (pos_ == 0) {
		return;
	}

	//Высчитываем координаты
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(hConsole_, &info);

	COORD xy{ info.dwCursorPosition.X, info.dwCursorPosition.Y };

	//Если курсор находится вначале строки в консоле
	if (xy.X > 0) {
		--xy.X;
		SetConsoleCursorPosition(hConsole_, xy);
	}
	else {
		--xy.Y;
		xy.X = info.dwSize.X - 1;
		SetConsoleCursorPosition(hConsole_, xy);
	}

	--pos_;//перемещаем позицию
}


//Метод, запускаемый при нажатии клавиши вправо
void Console::pressedRight() {
	//Если длина равна 0
	if (length_ == 0) {
		return;
	}

	//Если курсор находится в конце строки
	if (pos_ == length_) {
		return;
	}

	//Высчитываем координаты
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(hConsole_, &info);

	COORD xy{ info.dwCursorPosition.X, info.dwCursorPosition.Y };

	//Если курсор находится в конце строки консоли
	if (xy.X < info.dwSize.X - 1) {
		++xy.X;
		SetConsoleCursorPosition(hConsole_, xy);
	}
	else {
		++xy.Y;
		xy.X = 0;
		SetConsoleCursorPosition(hConsole_, xy);
	}

	++pos_;//перемещаем позицию
}


//Добавления символа в консоль
void Console::addSymbolToConsole(char symbol) {

	//Позиция совпадает с длиной. Курсос находится в конце
	if (pos_ == length_) {
		std::cout << symbol;
		return;
	}

	//Очищаем экран от позиции до конца строки
	//Запоминнаем позицию
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(hConsole_, &info);

	COORD here{ info.dwCursorPosition.X, info.dwCursorPosition.Y };

	//Высчитываем разницу между длиной буфера и текущей позиции
	size_t l = length_ - pos_;
	//Печатаем сиволы пробела
	for (size_t i = 0; i < l; ++i) {
		std::cout << ' ';
	}

	//Возвращаем курсор на прежнее место
	SetConsoleCursorPosition(hConsole_, here);

	//Печатаем оставщуюся строку
	std::string str = buffer_.substr(pos_ - 1, l + 1);
	std::cout << str;

	//Устанавливаем курсор на нужную позицию
	++here.X;
	if (here.X > info.dwSize.X - 1) {
		here.X = 0;
		++here.Y;
	}
	//Возвращаем курсор на прежнее место
	SetConsoleCursorPosition(hConsole_, here);
}


//Нажата клавиша Enter
void Console::pressedEnter() {
	setColorToConsole(3);
	std::cout << std::endl << "Поздравляю! Сообщение отправлено." << std::endl;
	buffer_.clear();
	length_ = 0;
	pos_ = 0;
}


//Нажата клавиша Backspace
void Console::pressedBackspace() {
	//Если длина равна 0
	if (length_ == 0) {
		return;
	}

	//Если курсор находится в начале строки
	if (pos_ == 0) {
		return;
	}

	//Запоминнаем позицию
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(hConsole_, &info);

	COORD here{ info.dwCursorPosition.X, info.dwCursorPosition.Y };

	//Если указатель находится в конце строки
	if (pos_ == length_) {
		//Возвращаем курсор назад и печатаем пробел. Потом опять возвращаем назад
		if (here.X == 0) {
			--here.Y;
			here.X = info.dwSize.X - 1;
			//Устанавливаем указатель
			SetConsoleCursorPosition(hConsole_, here);
			std::cout << " \b";
			SetConsoleCursorPosition(hConsole_, here);
		}
		else {
			std::cout << "\b \b";
		}
		buffer_.pop_back();
		--length_;
		--pos_;
		return;
	}
}

//Нажата клавиша Tab один раз
void Console::pressedTab() {
	//Проверяем длину строки
	if (length_ == 0) {
		return;
	}

	//Проверяем позицию
	if (pos_ == 0) {
		return;
	}

	//Если в текущей позиции пробел
	if (buffer_[pos_] == ' ') {
		return;
	}

	size_t posSpace = 0;
	int n = 0;
	//Ищеи ближайший пробел или конец строки идя по буферу в обратном направлении
	for (posSpace = pos_; posSpace != 0 && buffer_[posSpace] != ' '; --posSpace) {
		++n;//подсчитываем количество шагов
	}

	//Если стоим на пробеле
	if (buffer_[posSpace] == ' ' && posSpace != 0) {
		++posSpace;//Надо увеличить позицию
	}
	
	//Выделяем слово
	std::string str = buffer_.substr(posSpace, n);

	//Ищем совпадения в словаре
	dict_.findWords(str, v_);

	//Если количество совпадений равно 1, то будем вставлять слово
	if (v_.size() == 1) {
		pos_ = pos_ - n;//перемещаем позицию
		buffer_.resize(pos_);//уменьшаем строку
		//Если позиция не равна 0(не начало строки)
		if (pos_ != 0) {
			//Нужно добавить пробел
			buffer_.push_back(' ');
		}
		//Вставляем слово в буфер
		buffer_ += v_[0];

		//Запоминнаем позицию
		CONSOLE_SCREEN_BUFFER_INFO info;
		GetConsoleScreenBufferInfo(hConsole_, &info);

		COORD here{ info.dwCursorPosition.X, info.dwCursorPosition.Y };
		
		here.X -= n;//перемещаем координату

		//Если по X получилось меньше 0, то нужно уменьшить Y и X отсчитывать от конца строки
		if (here.X < 0) {
			--here.Y;
			here.X = info.dwSize.X + here.X;
		}

		//Перемещаем курсор
		SetConsoleCursorPosition(hConsole_, here);

		//Печатаем пробелы
		for (size_t i = 0; i < length_ - pos_; ++i) {
			std::cout << ' ';
		}

		//Перемещаем курсос
		SetConsoleCursorPosition(hConsole_, here);

		//Если не конец строки нужно добавить пробел
		if (pos_ != 0) {
			std::cout << ' ';
		}

		//Печатаем слово
		std::cout << v_[0];

		//Изменяем длину и позицию
		length_ = buffer_.size();
		pos_ = length_;
	}
}

//Нажата клавиша Tab два раза раз
void Console::pressedDoubleTab() {
	//Если количество записей больше 1, то
	if (v_.size() > 1) {
		//Выводим все слова
		std::cout << std::endl;
		for (size_t i = 0; i < v_.size(); ++i) {
			std::cout << v_[i] << std::endl;
		}
	}
}

//Получить количество записей в векторе
size_t Console::getAmountToVector() const {
	return v_.size();
}