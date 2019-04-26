#include <iostream>
#include "afx.h"
#include "table.h"
#include "wordItem.h"
#include <string.h>

int BorderProcessor(FILE *fp, WordTable *wt, WordItem *wd)
{
    Debug("begin BorderProcessor...\n");
    int ch = fgetc(fp);
    int result = IGNORE;
    // 设置初始容量为 3
    int cap = 3;
    char *token = new char[3];
    int index = 0;

    token[index++] = ch;
    switch ((char)ch)
    {
    case ',':
    case ';':
    case ')':
    case '(':
    case '{':
    case '}':
    case '[':
    case ']':
    case ':':
    case '#':
        token[index] = '\0';
        *wd = wt->search(DEFAULT, token, index+1);
        if (ISFINDWORDITEM(*wd))
        {
            result = SUCCESS;
        }
        else
        {
            wd->token = new char[index+1];
            strncpy(wd->token, token, index+1);
            result = ERROR;
        }
        delete[] token;
        token = nullptr;
        return result;
    }
    return IGNORE;
}


