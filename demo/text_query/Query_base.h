#ifndef QUERY_BASE
#define QUERY_BASE

#include "TextQuery.h"

using std::string;

/**
 * @brief Query系列的抽象基类
 * 
 */
class Query_base{
    friend class Query;
protected:
    using line_no  = TextQuery::line_no;
    virtual ~Query_base() = default;
private:
    /**
     * @brief 返回Query匹配的查询结果
     * 
     * @return QueryResult 
     */
    virtual QueryResult eval(const TextQuery&) const = 0;
    /**
     * @brief 返回查询结果的字符串输出
     * 
     * @return std::string 
     */
    virtual std::string rep() const = 0;


private:


};

#endif
