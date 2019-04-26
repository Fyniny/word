#include <iostream>
#include "afx.h"
#include "table.h"
#include "wordItem.h"
#include <string.h>

int STRINGProcessor(FILE *fp, WordTable *wt, WordItem *wd)
{
    Debug("begin STRINGProcessor...\n");
    int ch = fgetc(fp);
    if(ch != '"') {
            Debug("exit STRINGProcessor...\n");
        return IGNORE;
    }
    // 设置初始容量为 20
    int cap = 20;
    char *token = new char[20];
    int index = 0;

    while('"' != (ch = fgetc(fp))) {
        Debug("STRINGProcessor() scanning... char = \"" << (char)ch << "\" ascii = \"" << ch << "\"" << "\n")
        // 字符串的引号不能跨行
        if('\n' == ch || '\r' == ch) {
            goto error;
        }
        token[index++] = ch;
        if(index >= cap) {
            cap = 2 * cap;
            auto tmp = new char[cap];
            strncpy(tmp, token, index);
            delete[] token;
            token = tmp;
        }
    }

    Debug("final STRING is \"" << token << "\"\n")
    token[index] = '\0';
    *wd = wt->search(STRING, token, index+1);
    delete[] token;
    token = nullptr;
    return SUCCESS;

error:
    wd->token = new char[index+1];
    strncpy(wd->token, token, index+1);
    delete[] token;
    token = nullptr;
    return ERROR;
}