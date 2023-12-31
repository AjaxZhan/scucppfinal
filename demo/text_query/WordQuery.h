#ifndef WORDQUERY
#define WORDQUERY
#include "Query_base.h"
#include "TextQuery.h"
#include "Query.h"

class WordQuery : public Query_base{
    friend class Query;

    WordQuery(const string &s) : query_word(s) {}

    QueryResult eval(const TextQuery &t) const{
        return t.query(query_word);
    }
    string rep()const { return query_word;}
    string query_word;

};


#endif