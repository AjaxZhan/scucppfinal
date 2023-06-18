#ifndef QUERY
#define QUERY

#include "TextQuery.h"
#include "Query_base.h"
#include "WordQuery.h"

class Query{
    friend Query operator~(const Query &);
    friend Query operator&(const Query &, const Query &);
    friend Query operator|(const Query & , const Query &);

public:
    //构建WordQuery
    Query(const std::string &);
    //接口函数，调用Query_Base的操作,体现了多态——运行时动态绑定！
    //返回Query到的result
    QueryResult eval(const TextQuery &t )const{
        return q->eval(t);
    }
    //将result输出为string
    std::string rep() const{
        return q->rep();
    }
private:
    //构造函数，接收一个QueryBase。不希望用户能随意定义QueryBase对象
    Query(std::shared_ptr<Query_base>query) : q(query){}
    //底层指针指向Query_base
    std::shared_ptr<Query_base> q;
};

/**
 * @brief 输出运算符 由于是调用接口，接口是公共的，不需要声明友元。
 * 
 */
std::ostream& operator<<(std::ostream &os, const Query &query){
    //多态动态绑定
    return os << query.rep();
}
/**
 * @brief 构造一个WordQuery
 * 
 * @param s     
 */
inline Query::Query(const string &s) : q(new WordQuery(s)){}

#endif