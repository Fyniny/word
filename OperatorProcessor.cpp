#include <iostream>
#include "afx.h"
#include "table.h"
#include "wordItem.h"
#include <string.h>

int OperatorProcessor(FILE *fp, WordTable *wt, WordItem *wd)
{
    Debug("begin OperatorProcessor...\n");
    int ch = fgetc(fp);
    int result = IGNORE;
    // 设置初始容量为 3
    int cap = 3;
    char *token = new char[3];
    int index = 0;

readCh:
    token[index++] = ch;
    switch ((char)ch)
    {
    case '+':
    case '-':
    case '*':
    case '/':
    case '^':
    case '~':
    case '%':
    case '.':
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

    int status = 0;
selection:
    switch (ch)
    {
    case '|':
        if (status == 1)
        {
            goto end;
        }
        status = 1;
        break;
    case '&':
        if (status == 2)
        {
            goto end;
        }
        status = 2;
        break;
    case '>':
        if (status == 3 || status == 5)
        {
            goto end;
        }
        status = 3;
        break;
    case '<':
        if (status == 4 || status == 5)
        {
            goto end;
        }
        status = 4;
        break;
    case '=':
        if (status == 5)
        {
            goto end;
        }
        status = 5;
        break;
    case '!':
        if (status == 5)
        {
            goto end;
        }
        status = 6;
        break;
    default:
        if (status == 0)
        {
            return IGNORE;
        }
        // 经过这里的都只是一个符合的运算符
        // 回退
        if (!feof(fp))
        {
            retract(fp);
        }
        index--;
        goto end;
    }
    ch = fgetc(fp);
    token[index++] = ch;
    goto selection;

end:
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