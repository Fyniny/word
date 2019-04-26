#ifndef WORDITEM 
#define WORDITEM
/*
 * 单词符号表项，若linkTable非空，象征着该项具有内建表项，如(数字符号):
 * 12 syn=7,sum=1
 * 13,syn=7,sum=2
 * 14 syn=7,sum=3
 * 在表中关系为
 * Word {
 *  WordItem: {
 *     num, 7,-1, NumWord::WordItem {
 *                                          {12,7,1,nullptr}
 *                                          {13,7,2,nullptr}
 *                                          {14,7,3,nullptr}
 *                                   }
 *   }
 * }
*/

class SearchInterface;

struct WordItem
{
    char* token; // 字符串本身
    int syn;     // 种别码
    int sum;     // 内码
    SearchInterface* linkTable; // 关联的符号表，该项不为nullpter时，sum无效
public:
    WordItem();
    // linkTable 默认为nullptr
    WordItem& operator=(const WordItem& wd);
    WordItem(const WordItem& wd);
    ~WordItem();
};
#endif