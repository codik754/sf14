//Файл dictionary.cpp
#include "dictionary.h"
#include <algorithm>
#include <iostream>

//Конструктор по умолчанию
Dictionary::Dictionary() :  count_(0) {
    root_ = new TrieNode;
}

//Удаление всего дерева и освобождение памяти
void Dictionary::deleteAll(TrieNode* r) {
    if (r) {
        for (size_t i = 0; i < sizeAlphabet; i++) {
            if (r->children[i]) {
                deleteAll(r->children[i]);
            }
        }
        delete r;
    }
}

//Деструктор
Dictionary::~Dictionary() {
   deleteAll(root_);
}

//Конструктор копирования
Dictionary::Dictionary(const Dictionary& other) : root_(other.root_), count_(other.count_) { }

//Оператор присвоения
Dictionary& Dictionary::operator =(const Dictionary& other) {
    //Проверка на самоприсвоение
    if (&other == this) {
        return *this;
    }

    root_ = other.root_;
    count_ = other.count_;

    return *this;
}

//Добавление слова в словарь
void Dictionary::addWord(const std::string &word) {
    //Копируем строку
    std::string tempStr = word;
    
    //Делаем все символы в строке маленькими
    std::transform(tempStr.begin(), tempStr.end(), tempStr.begin(), tolower);

    //Сначала указатель указывает на корень
    TrieNode* node = root_;
    //Проходим по всем символам слова
    for (size_t i = 0; i < tempStr.length(); ++i) {
        //Вычисляем индекс символа
        int index = tempStr[i] - 'a';
        //Если у узла нет ребенка с таким индексом
        if (!node->children[index]) {
            //Создаем новый узел
            node->children[index] = new TrieNode;
        }
        //Теперь node указывает на следующий узел
        node = node->children[index];

       
    }
    node->isEnd = true;//устанавливаем конец слова
    ++count_;//Увеличиваем количество слов
}

//Получить количество слов в словаре
size_t Dictionary::getCount() const {
    return count_;
}

//Заполнить словарь
void Dictionary::fillDictionary() {
    addWord("a");
    addWord("the");
    addWord("win");
    addWord("all");
    addWord("hi");
    addWord("hello");
    addWord("how");
    addWord("are");
    addWord("you");
    addWord("they");
    addWord("we");
    addWord("are");
    addWord("he");
    addWord("she");
    addWord("it");
    addWord("is");
    addWord("and");
    addWord("what");
    addWord("when");
    addWord("where");
    addWord("do");
    addWord("did");
    addWord("done");
    addWord("go");
    addWord("will");
    addWord("be");
    addWord("home");
    addWord("game");
    addWord("phone");
    addWord("good");
    addWord("can");
    addWord("word");
    addWord("world");
    addWord("book");
    addWord("laptop");
    addWord("programming");
    addWord("cool");
    addWord("day");
    addWord("month");
    addWord("week");
    addWord("year");
    addWord("for");
    addWord("to");
    addWord("winter");
    addWord("spring");
    addWord("summer");
    addWord("autumn");
    addWord("night");
    addWord("evening");
    addWord("morning");
    addWord("tomorrow");
    addWord("weather");
    addWord("rest");
    addWord("play");
    addWord("sleep");
    addWord("swim");
    addWord("take");
    addWord("have");
    addWord("took");
    addWord("has");
    addWord("simple");
    addWord("hard");
    addWord("want");
    addWord("know");
    addWord("new");
    addWord("old");
    addWord("my");
    addWord("your");
    addWord("our");
    addWord("them");
    addWord("code");
    addWord("computer");
    addWord("key");
    addWord("keypad");
    addWord("monitor");
    addWord("work");
    addWord("tomorrow");
    addWord("snow");
    addWord("low");
    addWord("high");
    addWord("bit");
    addWord("byte");
    addWord("write");
    addWord("wrote");
    addWord("read");
    addWord("send");
    addWord("sent");
    addWord("slept");
    addWord("build");
    addWord("think");
    addWord("thought");
    addWord("this");
    addWord("there");
    addWord("here");
    addWord("sit");
    addWord("sat");
    addWord("pay");
    addWord("paid");
    addWord("buy");
    addWord("bought");
}


//Функция для рекурсивного обхода дерева и вывода всех слов
void Dictionary::showAll_(TrieNode* r, char buf[], int ind) const {
    //Если узел пустой
    if (!r) {
        return;
    }

    //Обходим по всем детям узла
    for (size_t i = 0; i < sizeAlphabet; i++) {
        //Если узел есть
        if (r->children[i]) {
            //Добавляем символ в буфер
            buf[ind] = (char)(i + 'a');
            //Увеличиваем индекс на 1
            ind++;
            //Если символ является концом слова и у узла есть дети
            if (r->children[i]->isEnd && (!r->children[i]->isEmpty())) {
                buf[ind] = '\0';//Добавляем символ конца строки
                std::cout << buf << std::endl;//Печатаем слово
                showAll_(r->children[i], buf, ind);//рекурсивно вызываем функцию
            }
            else if (!r->children[i]->isEnd) {
                //Если не конец слова
                showAll_(r->children[i], buf, ind);//рекурсивно вызываем функцию
            }
            else {
                //В остальных случаях. Печатаем слово
                buf[ind] = '\0';
                std::cout << buf << std::endl;
            }
            ind--;//Уменьшаем индекс на 1
        }
    }
}


//Показать все слова
void Dictionary::showAllWords() const {
    char buf[100];//буфер для слов
    int i = 0;//индес элемента
    showAll_(root_, buf, i);//Вызываем функцию для вывода всех слов
}


// Рекурсивная функция удаления слова из дерева
TrieNode * Dictionary::remove(TrieNode * r, const std::string& word, int depth)
{
    // Если дерево пустое
    if (!r)
        return nullptr;
    // Если дошли до конца ключа
    if (depth == word.size()) {
        // Этот узел больше не конец слова
        // поэтому снимаем метку
        if (r->isEnd)
            r->isEnd = false;
        // Если ключ не является префиксом, удаляем его
        if (r->isEmpty()) {
            delete (r);
            r = nullptr;
        }
        return r;
    }

    // Пока не дошли до конца ключа или определили, 
    // что его нет в дереве, рекурсивно вызываем для ребенка
    int index = word[depth] - 'a';
    r->children[index] = remove(r->children[index], word, depth + 1);
    // Если у корня нет дочернего слова
    // (удален только один его дочерний элемент),
    // и он не заканчивается другим словом.
    if (r->isEmpty() && r->isEnd == false) {
        delete (r);
        r = nullptr;
    }
    // возвращаем новый корень
    return r;
}


//Функция для удаления слова
void Dictionary::removeWord(const std::string& word) {
    //Копируем строку
    std::string tempStr = word;

    //Делаем все символы в строке маленькими
    std::transform(tempStr.begin(), tempStr.end(), tempStr.begin(), tolower);

    //Удаляем слово
    remove(root_, tempStr);

    --count_;//Уменьшаем количество слов
}

//Рекурсивная функция для поиска
void Dictionary::findW(TrieNode* r, char buf[], int ind, const std::string &word ,std::vector<std::string>& v) const {
    //Если узел пустой
    if (!r) {
        return;
    }

    //Пробегаем по всем детям узла
    for (size_t i = 0; i < sizeAlphabet; i++) {
        //Если узел существует
        if (r->children[i]) {
            //Добавляем символ в буфер
            buf[ind] = (char)(i + 'a');
            //Увеличиваем индекс
            ind++;
            //Если символ является концом слова и у узла есть дети
            if (r->children[i]->isEnd && (!r->children[i]->isEmpty())) {
                buf[ind] = '\0';//Добавляем символ конца строки
                v.emplace_back(word + buf);//Добавляем слово в вектор
                findW(r->children[i], buf, ind, word, v);//Рекурсивно вызываем функцию
            }
            else if (!r->children[i]->isEnd) {
                //Если не конец слова
                findW(r->children[i], buf, ind, word, v);//Рекурсивно вызываем функцию
            }
            else {
                //В остальных случаях
                buf[ind] = '\0';//Добавляем символ конца строки
                v.emplace_back(word + buf);//Добавляем слово в вектор
            }
            ind--;//уменьшаем индекс на 1
        }
    }
}

//Найти совпадения
void Dictionary::findWords(const std::string& str, std::vector<std::string>& v) const {
    //Очищаем вектор 
    v.clear();
    
    //Копируем строку
    std::string tempStr = str;

    //Делаем все символы в строке маленькими
    std::transform(tempStr.begin(), tempStr.end(), tempStr.begin(), tolower);

   // std::cout << std::endl << "tempStr: " << tempStr << std::endl;

    //Сначала указатель указывает на корень
    TrieNode* node = root_;
    size_t m = 0;
    //Проходим по всем символам слова
    for (size_t i = 0; i < tempStr.length(); ++i) {
        //Вычисляем индекс символа
        int index = tempStr[i] - 'a';
        //Если у узла нет ребенка с таким индексом
        if (node->children[index]) {
            //Теперь node указывает на следующий символ
            node = node->children[index];
            ++m;
        }
        
    }

    //Если глубина разная
    if (m != tempStr.length()) {
        return;
    }

    //Если это конец слова и нет детей, то выходим
    if (node->isEnd && node->amountChild() == 0) {
        return;
    }
    else if (node->amountChild() == 1 && !node->isEnd) {
        //Если один ребенок
        std::string temp;

        //Идем до момента, когда будет один ребенок или конец слова
        while (!node->isEnd && node->amountChild() == 1) {
            for (size_t i = 0; i < sizeAlphabet; ++i) {
                if (node->children[i]) {
                    char c = static_cast<char>(i) + 'a';
                    temp.push_back(c);
                    node = node->children[i];
                }
            }
        }
        

        std::string temp2 = tempStr + temp;//формируем конечное слово

        v.push_back(temp2);//Добавляем в вектор

        return;
    }
    else {

        char buff[100];//Буфер для слова
        int ind = 0;//индекс в буфере
        //Если конец слова
        if (node->isEnd) {
            v.push_back(tempStr);//добавляем в вектор это слово
        }
        
        findW(node, buff, ind, tempStr,v);//Вызываем рекурсивно функцию
        return;
    }
}
