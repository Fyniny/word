#include <string.h>
#include <iostream>
#include "table.h"
#include "wordItem.h"
#include "afx.h"

SearchInterface::~SearchInterface()
{
    for (auto ite = this->word.begin(); ite != this->word.end(); ite++)
    {
        WordItem *tmp = *ite;
        ite = this->word.erase(ite);
        delete tmp;
    }
};

bool WordTable::addRelationTable(int typ, WordItem *linkTable)
{
    // 不能重复载入相同类型
    if (this->linkTables.find(typ) != this->linkTables.end())
    {
        return false;
    }
    this->linkTables[typ] = linkTable;
    return true;
}

// 将单词符号保存进符号表中,并返回符号表项
WordItem *WordTable::addWordItem(const char *token, int code, int count)
{
    for (auto v : this->word)
    {
        if (strlen(v->token) + 1 != count)
        {
            continue;
        }
        if (strncmp(v->token, token, count) == 0)
        {
            return v;
        }
    }
    auto tmp = new WordItem();
    tmp->token = new char[count];
    strncpy(tmp->token, token, count);
    tmp->sum = 0;
    tmp->syn = code;
    this->word.push_back(tmp);
    return tmp;
}

WordItem WordTable::search(int type, char *token, int count)
{
    Debug("begin WordTable::search...\n")
    // 查表
    if (type != DEFAULT)
    {
        auto ite = this->linkTables.find(type);
        if (ite != this->linkTables.end())
        {
            // 若表项内表不为空，代表有一张符号表，需要查询符号表
            // 若为空,代表查找出现错误
            if (ite->second->linkTable != nullptr)
            {
                return ite->second->linkTable->search(type, token, count);
            }
            Debug("[error] system error, returns a default value");
            return WordItem();
        }
    }
    // 查找表项中的单词符号
    for (auto ite = this->word.begin(); ite != this->word.end(); ite++)
    {
        int len = strlen((*ite)->token) + 1;
        Debug("tocken len = \"" << count << "\" table.token len = \"" << len << "\" token = \"" << token << "\" table.token = \"" << (*ite)->token << "\"\n");
        if (len != count)
        {
            continue;
        }
        if (strncmp((*ite)->token, token, count) == 0)
        {
            // 若是非关联单词符号表项（这项的linkTable属性非空），linkTable应为nullptr，这里与理论向反，说明token为关联表项中的项而不是该符号表的项，忽略
            if ((*ite)->linkTable != nullptr)
            {
                continue;
            }
            else
            {
                return *(*ite);
            }
        }
    }
    // 若始终没有查到，代表输入了错误的类型，或者发生了错误
    Debug("[ERROR] receive unsported type or token :: type = \"" << type << "\" token = \"" << token << "\" returns a default value" << std::endl);
    return WordItem();
}

WordItem ExWord::search(int type, char *token, int count)
{
    // 查表
    for (auto ite = this->word.begin(); ite != this->word.end(); ite++)
    {
        int len = strlen((*ite)->token) + 1;
        Debug("Exword::search token = \"" << token << "\" table.token = \"" << (*ite)->token << "\" Exword::search token len = \"" << count << "\" table.token = \"" << len << "\"\n");

        // 匹配相等，但此时可能是前面的单词相等
        if (len != count)
        {
            continue;
        }          
        if (strncmp(token, (*ite)->token, count) == 0)
        {
            return *(*ite);
        }
    }
    // 若没有查到，代表token是一个新的词，加入到表项中
    WordItem *tmp = new WordItem();
    tmp->token = new char[count];
    strncpy(tmp->token, token, count);
    tmp->syn = type;
    tmp->sum = this->index++;
    tmp->linkTable = nullptr;
    this->word.push_back(tmp);
    return *tmp;
}