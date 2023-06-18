#include "TextQuery.h"
#include <sstream>


/**
 * @brief 从文件中读取数据
 */
TextQuery::TextQuery(ifstream& ifs) : file(new vector<string>){ // 初始化智能指针
    string text;
    while(std::getline(ifs,text)){
        file->push_back(text);
        //切割单词
        int now_line = file->size()- 1;
        std::istringstream  line(text);
        string word;
        while(line >> word){
            auto &lines = table[word];
            if(!lines){
                lines.reset(new set<line_no>);
            }
            lines->insert(now_line); 
        }
    }
}
/**
 * @brief 对外提供的查询接口
 * 
 * @param word 
 * @return QueryResult 
 */
QueryResult TextQuery::query(const string &word)const{
    static shared_ptr<set<line_no>> nodata(new set<line_no>);
    auto loc = table.find(word);
    if(loc == table.end()) return QueryResult(word,file,nodata);
    else return QueryResult(word,file,loc->second);
}


/**
 * @brief 打印查询结果
 * 
 * @param os 
 * @param result 
 * @return ostream& 
 */
ostream& print(ostream& os , const QueryResult& result){
    os << "The word : " << result.sought
     << " occurs " << result.lines->size() << " "
      " time" << (result.lines->size() > 1 ? "s" : "") << std::endl;
    for(auto num : *result.lines){
        os << "\t (line " << num+1 << ")" 
            << *(result.file->begin()+num) << std::endl;
    }
    return os;
}

