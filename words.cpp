#include <iostream>
#include <string>
#include <vector>

class Word {
public:
    Word(const char* s)
    : word(s) {}
public:
    std::string& get_word()
    {
        return word;
    }
    void set_id(int i)
    {
        id = i;
    }
    int& get_id()
    {
        return id;
    }
private:
    std::string word;
    int id;
};

bool operator==(Word a, Word b)
{
    return a.get_word() == b.get_word();
}

bool operator==(Word a, const char* b)
{
    return a.get_word() == b;
}

class Wordshop {
public:
    Wordshop() = default;
    Wordshop(Word word) {
        word.set_id(0);
        words_in_shop.push_back(word);
    }
    Wordshop(const char* str) {
        words_in_shop.push_back(str);
        words_in_shop[words_in_shop.size() - 1].set_id(words_in_shop.size() - 1);
    }
    Wordshop(std::vector<Word> wordslist)
    : words_in_shop(wordslist) {}
public:
    void addWord(const char* str)
    {
        words_in_shop.push_back(str);
        words_in_shop[words_in_shop.size() - 1].set_id(words_in_shop.size() - 1);
    }
    void addWord(Word word)
    {
        words_in_shop.push_back(word);
        words_in_shop[words_in_shop.size() - 1].set_id(words_in_shop.size() - 1);

    }
    void removeWord(int i)
    {
        words_in_shop.erase(words_in_shop.begin() + i);
        for(int j = i; j < words_in_shop.size(); ++j)
        {
            words_in_shop[j].set_id(i - 1);
        }
    }
    std::vector<Word> get_words_of_shop()
    {
        return words_in_shop;
    }
    int size()
    {
        return words_in_shop.size();
    }
private:
    std::vector<Word> words_in_shop;
};

std::ostream& operator<<(std::ostream& os, Word w)
{
    os << w.get_word() << " " <<  w.get_id();
    return os;
}

std::ostream& operator<<(std::ostream& os, Wordshop sh)
{
    for(int i = 0; i < sh.size(); ++i)
    {
        os << sh.get_words_of_shop()[i] << std::endl;
    }
    return os;
}


class Wordbucket {
//id-n u indexy tarber en
public:
    Wordbucket() = default;
    Wordbucket(Wordshop sh, int i)
    {
        if(i <= sh.size() && i >= 0)
        {
            words_in_bucket.push_back(sh.get_words_of_shop()[i]);
        }
    }
    Wordbucket(Wordshop sh, Word w)
    {
        for(int i = 0; i < sh.size(); ++i)
        {
            if(sh.get_words_of_shop()[i] == w)
            {
                words_in_bucket.push_back(sh.get_words_of_shop()[i]);
                break;
            }
        }
    }
    Wordbucket(Wordshop sh, const char* ch)
    {
        for(int i = 0; i < sh.size(); ++i)
        {
            if(sh.get_words_of_shop()[i] == ch)
            {
                words_in_bucket.push_back(sh.get_words_of_shop()[i]);
                break;
            }
        }
    }
public:
    std::vector<Word>& get_bucket()
    {
        return words_in_bucket;
    }
    void addWord(Wordshop sh, int i)
    {
        if(i >= 0 && i < sh.get_words_of_shop().size())
        {
            words_in_bucket.push_back(sh.get_words_of_shop()[i]);
        }
    }
    void addWord(Wordshop sh, const char* ch)
    {
        for(int i = 0; i < sh.size(); ++i)
        {
            if(ch == sh.get_words_of_shop()[i])
            {
                words_in_bucket.push_back(sh.get_words_of_shop()[i]);
                break;
            }
        }
    }
    void remove(int id)
    {
        for(int i = 0; i < words_in_bucket.size(); ++i)
        {
            if(words_in_bucket[i].get_id() == id)
            {
                words_in_bucket.erase(words_in_bucket.begin() + i);
                break;
            }
        }
    }
    void clear()
    {
        words_in_bucket.clear();
    }
    void displayBucket()
    {
        for(int i = 0; i < words_in_bucket.size(); ++i)
        {
            std::cout << words_in_bucket[i] << std::endl;
        }
    }
    int size()
    {
        return words_in_bucket.size();
    }
private:
    std::vector<Word> words_in_bucket;
};

class User {
public:
    User(const char* s)
    : name(s) {}
public:
    Wordbucket& get_bucket()
    {
        return buck;
    }
    void print()
    {
        std::cout << name << ":" << std::endl;
        buck.displayBucket();
    }
    void printShop(Wordshop sh)
    {
        bool x;
        for(int i = 0; i < sh.size(); ++i)
        {
            x = 0;
            for(int j = 0; j < buck.size(); ++j)
            {
                if(sh.get_words_of_shop()[i].get_id() == buck.get_bucket()[j].get_id())
                {
                    x = 1;
                    break;
                }
            }
            if(!x)
            {
                std::cout << sh.get_words_of_shop()[i] << std::endl;
            }
        }
    }
private:
    std::string name;
    Wordbucket buck;
};



int main()
{
    Word w = "hello";
    Wordshop shop = "hi";
    shop.addWord("table");
    shop.addWord(w);
    shop.addWord("window");
    shop.addWord("water");

    User user1("John");
    user1.get_bucket().addWord(shop, "water");
    user1.get_bucket().addWord(shop, 0);
    user1.get_bucket().addWord(shop, 2);

    user1.print();
    std::cout << std::endl;
    std::cout << std::endl;

    user1.printShop(shop);
    std::cout << std::endl;

    //std::cout << shop << " " << w << std::endl;

    return 0;
}