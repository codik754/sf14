//Файл dictionary.h
#pragma once
#include "trienode.h"
#include <string>
#include <vector>

//Класс для словаря и работы с ним
class Dictionary{
	TrieNode* root_;//корень дерева
	size_t count_; //количество слов в словаре

	//Удаление всего дерева и освобождение памяти
	void deleteAll(TrieNode* r);

	// Функция для рекурсивного обхода дерева и вывода всех слов
	void showAll_(TrieNode* r, char buf[], int ind) const;

	// Рекурсивная функция удаления слова из дерева
	TrieNode* remove(TrieNode* r, const std::string& word, int depth = 0);

	//Рекурсивная функция для поиска
	void findW(TrieNode* r, char buf[], int ind, const std::string& word, std::vector<std::string>& v) const;
public:
	//Конструктор по умолчанию
	Dictionary();
	//Деструктор
	~Dictionary();
	//Конструктор копирования
	Dictionary(const Dictionary& other);
	//Оператор присвоения
	Dictionary& operator =(const Dictionary& other);

	//Добавление слова в словарь
	void addWord(const std::string& word);

	//Заполнить словарь
	void fillDictionary();

	//Получить количество слов в словаре
	size_t getCount() const;

	//Функция для удаления слова
	void removeWord(const std::string& word);
	
	//Показать все слова
	void showAllWords() const;

	//Найти совпадения
	void findWords(const std::string& str, std::vector<std::string>& v) const;
};

