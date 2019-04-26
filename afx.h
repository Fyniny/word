/*
 * 存放一些全局参数或定义
*/
#include "table.h"
// #define DEBUG

#ifdef DEBUG
#include <iostream>
#define Debug(text) \
        std::cout << text;
#else
#define Debug(text)
#endif

#ifndef PROCESSFUNC
#define PROCESSFUNC
typedef int (*processorFunc) (FILE*,WordTable*,WordItem*);

// processorFunc 返回值
#define SUCCESS 1
#define IGNORE  0
#define ERROR  -1

#endif

// 标识符
#define TYPE_ID     1
// 字符串
#define TYPE_STRING 2
// 整型符号
#define TYPE_INT    3

// 回退
#define retract(file) \
        if (!feof(file)) \
        {                  \
            fseek(file, -1, SEEK_CUR); \
        }   


        
// type
extern int DEFAULT;
extern int ID;
extern int STRING;
extern int INT;

extern int getbe(FILE* fp);
extern int IDProcessor(FILE*,WordTable*,WordItem*);
extern int INTProcessor(FILE* fp, WordTable* wt,WordItem* wd);
extern int OperatorProcessor(FILE *fp, WordTable *wt, WordItem *wd);
extern int BorderProcessor(FILE *fp, WordTable *wt, WordItem *wd);
extern int STRINGProcessor(FILE *fp, WordTable *wt, WordItem *wd);

#define ISFINDWORDITEM(wordItem) ((wordItem).token != nullptr && (wordItem).syn != -1)