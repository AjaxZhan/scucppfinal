/*
Author：Cagur
Content：包含const版本的front和back的StrBlob类
    Blob类的功能：不同拷贝之间共享相同的元素，即拷贝一个Blob对象的时候，src和dest底层引用的是相同的元素
    这是version1，使用vector维护字符串
*/

#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <initializer_list>

using std::vector; using std::string;
typedef std::vector<std::string>::size_type size_type;

class StrBlob{
public:
    StrBlob();
    //接收列表初始化
    StrBlob(std::initializer_list<std::string> il);

    size_type size() const{ return data->size();}
    bool empty() const {return data->empty();}
    //添加元素
    void push_back(const std::string &t){data->push_back(t);}
    //删除元素
    void pop_back();
    //元素访问
    std::string& front();
    std::string& back();
    //const重载版本
    const string& front() const ;
    const string& back() const ;

private:
    //使用智能指针维护 动态分配的vector
    std::shared_ptr<std::vector<std::string>> data;

    void check(size_type i, const std::string &msg) const;
};