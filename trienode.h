//Файл trienode.h
#pragma once

constexpr int sizeAlphabet = 26;//размер алфавита

//Структура для узла дерева
struct TrieNode {
	TrieNode* children[sizeAlphabet];//дочерние узлы
	bool isEnd; //переменная указывающая на то, что символ является концом слова

	//Конструктор по умолчанию
	TrieNode();
	//Конструктор копирования
	TrieNode(const TrieNode &other);
	//Оператор присвоения
	TrieNode& operator = (const TrieNode &other);

	//Узел не имеет детей
	bool isEmpty() const;

	//Количество детей у узла
	size_t amountChild() const;
};