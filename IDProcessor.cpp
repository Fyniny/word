#include <iostream>
#include "afx.h"
#include "table.h"
#include "wordItem.h"
#include <string.h>


#define letter(ch) ((ch) >= 'a' && (ch) <= 'z' || (ch) >= 'A' && (ch) <= 'Z')
#define underline(ch) ((ch) == '_')
#define digit(ch) ((ch)>= '0'&&(ch)<= '9')
    
int IDProcessor(FILE* fp, WordTable* wt,WordItem* wd) {
    int ch = fgetc(fp);
    if (!(letter(ch) || underline(ch))) {
        return IGNORE;
    }
    int result = IGNORE;
    // 设置初始容量为 20
    int cap = 20;
    char* token = new char[20];
    int index = 0;
    token[index++] = ch;

    while(EOF != (ch = fgetc(fp)) && letter(ch) || underline(ch) || digit(ch)) {
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
    auto wordItem = wt->search(DEFAULT, token, index+1);

    if(ISFINDWORDITEM(wordItem)) {
        *wd = wordItem;
        result = SUCCESS;
    } else {
        auto tmp = wt->search(ID, token, index+1);
        *wd = tmp;
        result = SUCCESS;
    }

    delete[] token;
    token = nullptr;
    // 疑问? 是不是文件指针在执行fgetc(fp)时,若文件到了eof,文件指针不再前移,而非eof时总是前移
    if(!feof(fp)) {
        retract(fp);
    }
    return result;
}