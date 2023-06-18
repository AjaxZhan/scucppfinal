#ifndef NOTQUERY
#define NOTQUERY

#include "Query.h"
#include "Query_base.h"
#include "TextQuery.h"

class NotQuery : public Query_base{
    friend Query operator~(const Query &);
    NotQuery(const Query &q) : query(q) {}

    string rep() const { return "~(" + query.rep() + ")" ;}
    QueryResult eval(const TextQuery &t)const;
    Query query;

};
inline Query operator~(const Query &operand){
    return shared_ptr<Query_base>(new NotQuery(operand));
}

#endif