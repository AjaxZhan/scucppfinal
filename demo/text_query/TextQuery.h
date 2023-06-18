#ifndef TEXT_QUERY
#define TEXT_QUERY

#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <set>
#include <map>

//c++17
using std::vector,std::map,std::set,std::string,std::ifstream,std::ostream;
using std::shared_ptr;

//filePath
static string filePath = "./text.dat";

//VO类，保存查询结果。与TextQuery共享数据。
class QueryResult;

/**
 * @brief 负责执行查询的业务类，从文件读取数据并进行处理保存
 */
class TextQuery{
public:
    using line_no = vector<string>::size_type;

    TextQuery(ifstream&);
    /**
     * @brief 对外提供的查询接口
     * 
     * @param word  要查询的单词
     * @return QueryResult  查询结果
     */
    QueryResult query(const string & word) const;
private:
    //共享数据：智能指针。保存每一行数据。
    shared_ptr<vector<string>> file;
    //注意这里map不需要为指针，因为map不负责保存数据，只负责保存关系。
    map<string,shared_ptr<set<line_no>>> table; 

};


/**
 * @brief 保存查询结果，相当于一个VO类
 * 
 */
class QueryResult{
public:
    //将打印函数定义为友元
    friend ostream& print(ostream& , const QueryResult&);
    using Iter = set<TextQuery::line_no>::iterator;
    
    Iter begin() const { return lines->begin();}
    Iter end() const {return lines->end();}
    shared_ptr<vector<string>> getFile()const {
        //返回一个指针指向我们的file
        return std::make_shared<vector<string>>(file);
    }
    QueryResult(string s , shared_ptr<vector<string>> f, shared_ptr<set<TextQuery::line_no>> l)
        : sought(s) , file(f), lines(l){}

private:
    //查询文本
    string sought;
    //每行文本
    shared_ptr<vector<string>> file;
    //行号
    shared_ptr<set<TextQuery::line_no>> lines;
};

/**
 * @brief 打印查询结果
 * 
 * @return ostream& 
 */
ostream& print(ostream & , const QueryResult&);

#endif