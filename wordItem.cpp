#include "wordItem.h"
#include "table.h"
#include <string.h>

WordItem::WordItem()
{
    this->token = nullptr;
    this->sum = -1;
    this->syn = -1;
    this->linkTable = nullptr;
}

WordItem &WordItem::operator=(const WordItem &wd)
{
    if (this->token != nullptr)
    {
        delete[] this->token;
        this->token = nullptr;
    }

    if (wd.token != nullptr)
    {
        this->token = new char[strlen(wd.token) + 1];
        strncpy(this->token, wd.token, strlen(wd.token) + 1);
    }

    this->sum = wd.sum;
    this->syn = wd.syn;
    this->linkTable = nullptr;
}

WordItem::~WordItem()
{
    if (this->token != nullptr)
    {
        delete[] this->token;
        this->token = nullptr;
    }
    if (this->linkTable != nullptr)
    {
        delete this->linkTable;
        this->linkTable = nullptr;
    }
}

WordItem::WordItem(const WordItem &wd)
{
    this->token = nullptr;
    this->sum = -1;
    this->syn = -1;
    this->linkTable = nullptr;
    this->operator=(wd);
}