#include <iostream>
#include "afx.h"

// 跳过前导空白
int getbe(FILE* fp) {
    int ch; 
    while((ch = fgetc(fp)) == ' ' || ch == '\r' || ch == '\n' && ch != EOF) Debug("getbe() scanning(out of while)... char = \"" << (char)ch << "\" ascii = \"" << ch << "\"" << "\n");
    Debug("getbe() scanning(out of while)... char = \"" << (char)ch << "\" ascii = \"" << ch << "\"" << "\n")
    if(feof(fp)) {
        return EOF;
    }
    retract(fp);
    return 0;
}

