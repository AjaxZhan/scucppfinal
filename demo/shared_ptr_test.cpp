#include "shared_ptr_test.h"
/**
 * @brief 无参构造，初始化内部维护的智能指针
 * @details make_shared在堆区分配一个对象并进行初始化，返回指向这个对象的shared_ptr。括号中传入构造函数参数。
 * 
 */
StrBlob::StrBlob() : data(std::make_shared<std::vector<std::string>>()) {}

/**
 * @brief Construct a new StrBlob using initializer_list
 */

StrBlob::StrBlob(std::initializer_list<std::string> il) : 
        data(std::make_shared<std::vector<std::string>>(il)) {}

/**
 * @brief 检查访问是否合法
 */
void StrBlob::check(size_type i, const std::string &msg) const {
    if(i >= data->size()){
        throw std::out_of_range(msg);
    }
}

/**
 * @brief 实现pop_back函数
 */
void StrBlob::pop_back(){
    //是否合法
    check(0,"pop_back on empty StrBlob");
    data->pop_back();
}

std::string& StrBlob::front(){
    check(0,"front on empty StrBlob");
    return data->front();
}   

std::string& StrBlob::back(){
    check(0,"back on empty StrBlob");
    return data->back();
}
/**
 * @brief const version of front and back 标准模板库也有const版本
 * 
 * @return const string& 
 */
const string& StrBlob::front() const{
    check(0," front on empty StrBlob");
    return data->front();
}
const string& StrBlob::back() const{
    check(0,"back on empty StrBlob");
    return data->back();
}



int main(){

    return 0;
}