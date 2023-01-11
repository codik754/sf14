//Файл trienode.cpp
#include "trienode.h"

//Конструктор по умолчанию
TrieNode::TrieNode() : isEnd(false) {
	for (size_t i = 0; i < sizeAlphabet; ++i) {
		children[i] = nullptr;
	}
}

//Конструктор копирования
TrieNode::TrieNode(const TrieNode& other) : isEnd(other.isEnd) {
	for (size_t i = 0; i < sizeAlphabet; ++i) {
		children[i] = other.children[i];
	}
}

//Оператор присвоения
TrieNode& TrieNode::operator = (const TrieNode& other) {
	//Проверка на самоприсвоение
	if (&other == this) {
		return *this;
	}

	isEnd = other.isEnd;
	for (size_t i = 0; i < sizeAlphabet; ++i) {
		children[i] = other.children[i];
	}

	return *this;
}

//Узел не имеет детей
bool TrieNode::isEmpty() const {
	for (size_t i = 0; i < sizeAlphabet; ++i) {
		if (children[i]) {
			return false;
		}
	}
	return true;
}


//Количество детей у узла
size_t TrieNode::amountChild() const{
	size_t n = 0;
	
	for (size_t i = 0; i < sizeAlphabet; ++i) {
		if (children[i]) {
			++n;
		}
	}

	return n;
}