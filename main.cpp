#include <iostream>
#include "table.h"
#include <list>
#include "afx.h"
#include "wordItem.h"
#include <string.h>

int DEFAULT;
int ID;
int STRING;
int INT;

class ScanProcess
{
private:
    std::list<processorFunc> processor;

public:
    void addProcess(processorFunc processor)
    {
        if (processor == nullptr)
        {
            return;
        }
        this->processor.push_back(processor);
    }

    // 需要再每一个处理函数中做好错误处理逻辑
    int Scan(FILE *fp, WordTable *wt, WordItem *wordItem)
    {
        int result = IGNORE;
        // 初始化
        if (wordItem->token != nullptr)
        {
            delete[] wordItem->token;
            wordItem->token = nullptr;
        }
        wordItem->sum = 0;
        wordItem->syn = -1;
        if (wordItem->linkTable != nullptr)
        {
            delete wordItem->linkTable;
            wordItem->token = nullptr;
        }

        for (auto handler = this->processor.begin(); handler != this->processor.end(); handler++)
        {
            result = (*handler)(fp, wt, wordItem);
            if (result == IGNORE)
            {
                retract(fp);
                continue;
            }
            return result;
        }
    }
};

struct kv
{
    const char *word;
    int syn;
};

void initTable(WordTable *w)
{
    kv keyword[] = {
        {"if", 1},
        {"else", 2},
        {"while", 3},
        {"for", 4},
        {"switch", 5},
        {"case", 6},
        {"continue", 7},
        {"break", 8},
        {"return", 9},
        {"const", 10},
        {"goto", 11},
        {"int", 12},
        {"double", 13},
        {"float", 14},
        {"void", 15},
        {"struct", 16}};

    kv operators[] = {
        {"+", 17},
        {"-", 18},
        {"*", 19},
        {"/", 20},
        {">", 21},
        {"<", 22},
        {"=", 23},
        {">=", 24},
        {"<=", 25},
        {"==", 26},
        {"!=", 27},
        {">>", 28},
        {"<<", 29},
        {"!", 30},
        {"^", 31},
        {"|", 32},
        {"&", 33},
        {"~", 34},
        {"%", 35},
        {"&&", 36},
        {"||", 37},
        {".",38}};

    kv border[] = {
        {",", 39},
        {";", 40},
        {":", 41},
        {"(", 42},
        {")", 43},
        {"{", 44},
        {"}", 45},
        {"[", 46},
        {"]", 47},
        {"#", 48}};

    DEFAULT = -1;
    INT = 100;
    STRING = 101;
    ID = 102;

    for (auto k : keyword)
    {
        w->addWordItem(k.word, k.syn, strlen(k.word) + 1);
    }
    for (auto k : operators)
    {
        w->addWordItem(k.word, k.syn, strlen(k.word) + 1);
    }
    for (auto k : border)
    {
        w->addWordItem(k.word, k.syn, strlen(k.word) + 1);
    }

    // 字符串符号表
    auto stringsItem = w->addWordItem("STRING", STRING, strlen("STRING") + 1);
    stringsItem->linkTable = new StringWord();
    if (!w->addRelationTable(STRING, stringsItem))
    {
        std::cout << "[error] addRelationTable failed:: multi-relation of stringTable\n";
        exit(1);
    }

    // 标识符符号表
    auto idItem = w->addWordItem("ID", ID, strlen("ID") + 1);
    idItem->linkTable = new IDWord();
    if (!w->addRelationTable(ID, idItem))
    {
        std::cout << "[error] addRelationTable failed:: multi-relations of idTable\n";
        exit(1);
    }

    // 整型符号表
    auto intItem = w->addWordItem("INT", INT, strlen("INT") + 1);
    intItem->linkTable = new IntWord();
    if (!w->addRelationTable(INT, intItem))
    {
        std::cout << "[error] addRelationTable failed:: multi-relations of intIable\n";
        exit(1);
    }
}

int main()
{
    const char *file = "test.txt";
    auto fp = fopen(file, "r");
    if (fp == nullptr)
    {
        std::cout << "[error] file open failed\n";
        exit(1);
    }
    ScanProcess scanner;
    // 初始化表
    Debug("init table...\n");
    WordTable wt;
    initTable(&wt);
    Debug("...done\n");
    // 添加scanner处理函数
    scanner.addProcess(IDProcessor);
    scanner.addProcess(INTProcessor);
    scanner.addProcess(OperatorProcessor);
    scanner.addProcess(BorderProcessor);
    scanner.addProcess(STRINGProcessor);

    // 调用扫描子程序
    WordItem wd;
    int result = IGNORE;
    while (getbe(fp) != EOF)
    {
        Debug("scanning sub program of process...\n");
        result = scanner.Scan(fp, &wt, &wd);
        switch (result)
        {
        case SUCCESS:
            std::cout << "(" << wd.syn << " , " << wd.sum << ") " << wd.token << std::endl;
            break;
        case ERROR:
            if (wd.token == nullptr)
            {
                std::cout << "[INFO] token is nullptr, that's invalid, though get an error syntax,you should reserve the syntax-token\n";
            }
            std::cout << "[ERROR] token = \"" << (wd.token == nullptr ? "a nullptr variable" : wd.token) << "\" is error syntax\n";
            break;
        default:
        {
            int ch = fgetc(fp);
            std::cout << "[FATAL] unexpected error: token = \"" << (char)ch << "\" ascii = \"" << ch << "\" \n";
        }
        }
    }
}
