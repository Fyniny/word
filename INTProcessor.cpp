#include <iostream>
#include "afx.h"
#include "table.h"
#include "wordItem.h"
#include <string.h>

#define digit(ch) ((ch) >= '0' && (ch) <= '9')

int INTProcessor(FILE* fp, WordTable* wt,WordItem* wd) {
    Debug("begin INTProcessor...\n");
    int ch = fgetc(fp);
    
    if (!digit(ch)) {
        return IGNORE;
    }
    int result = IGNORE;
    // 设置初始容量为 20
    int cap = 20;
    char* token = new char[20];
    int index = 0;
    token[index++] = ch;

    while(EOF != (ch = fgetc(fp)) && digit(ch)) {
        token[index++] = ch;
        if (index >= cap) {
            cap = 2 * cap;
            char* tmp = new char[cap];
            strncpy(tmp, token, index - 1);
            delete[] token;
            token = tmp;
            tmp = nullptr;
        }
    }

    token[index] = '\0';
    // 检查是否是关键字
    *wd = wt->search(INT, token, index+1);
    result = SUCCESS;
    
    delete[] token;
    token = nullptr;

    if(!feof(fp)) {
        retract(fp);
    }
    return result;
}