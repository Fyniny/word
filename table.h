#include <list>
#include <map>

#ifndef TABLE
#define TABLE
class WordItem;

class SearchInterface
{
  public:
    // type 符号串类别，具体定义在afx.h中， token 单词符号串, count token的长度（含有 \0）
    virtual WordItem search(int type, char *token, int count) = 0;
    virtual ~SearchInterface();

  protected:
    std::list<WordItem *> word;
};

/*
 * 单词符号表
*/
class WordTable : public SearchInterface
{
  private:
    std::map<int, WordItem *> linkTables;

  public:
    bool addRelationTable(int typ, WordItem *linkTable);
    // 将单词符号保存进符号表中,并返回符号表项
    WordItem *addWordItem(const char *token, int code, int count);
    virtual WordItem search(int type, char *token, int count) override;
};

/*
 * 拓展符号表
*/
class ExWord : public SearchInterface
{
  private:
    int index;

  public:
    virtual WordItem search(int type, char *token, int count) override;
};

typedef ExWord IDWord;     // 标识符表
typedef ExWord IntWord;    // 常数表
typedef ExWord StringWord; // 字符串常量表
#endif