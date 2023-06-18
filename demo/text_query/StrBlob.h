#ifndef STRBLOB
#define STRBLOB
#include <iostream>
#include <vector>
#include <string>
#include <initializer_list>
#include <memory>
#include <exception>
#include <stdexcept>

using std::vector, std::string,std::shared_ptr;

/**
 * @brief 伴随指针类，保存一个weak_ptr指向data。
 *        不会影响vector的生命周期，但是可以组织用户访问一个不存在的vector。
 */
class StrBlobPtr;

/**
 * @brief Blob：binary Large Object 二进制大对象，是一种容器、集合
 *        这里先定义管理string的Blob类
 * 
 */
class StrBlob{
public: 
    // 和实际机器匹配， 是unsign类型
    typedef vector<string>::size_type size_type; 
    //友元类
    friend class StrBlobPtr;
    //指针
    StrBlobPtr begin();
    StrBlobPtr end();
    //构造函数
    StrBlob();
    StrBlob(std::initializer_list<string> il);
    //容器的常见操作
    size_t size()const { return data->size();}
    bool empty() const { return data->empty();}
    void push_back(string d){ data->push_back(d);}
    void pop_back();
    string& front();
    string& back();
    const string& front()const;
    const string& back() const;
    string& operator[](int i){

    }
private:
    //数据
    shared_ptr<vector<string>>data;
    /**
     * @brief 通过索引检查访问是否合法，不合法抛出异常
     * 
     * @param index 索引
     * @param msg  异常信息
     */
    void check(size_type index, const string &msg) const;
};

/**
 * @brief 构造函数，初始化智能指针
 */
StrBlob::StrBlob() : data(std::make_shared<vector<string>>()){}
StrBlob::StrBlob(std::initializer_list<string> il)
    : data(std::make_shared<vector<string>>(il)){} 

/**
 * @brief 元素访问、删除系列需要检查 
 */
void StrBlob::check(size_type index, const string &msg) const{
    if(index >= data->size()){
        throw std::out_of_range(msg);
    }
}
/**
 * @brief 删除尾部
 * 
 */
void StrBlob::pop_back(){
    data->erase(data->end()-1);
}
/**
 * @brief front
 * 
 */
string& StrBlob::front(){
    check(0,"try to get front on an empty Blob");
    return data->front();
}
/**
 * @brief back
 * 
 */
string& StrBlob::back(){
    check(0,"try to get back on an empty Blob");
    return data->back();
}
/**
 * @brief 重载const版本的front和back
 * 
 * @return const string& 
 */
const string& StrBlob::front()const{
    check(0,"try to get front on an empty Blob");
    return data->front();
}
/**
 * @brief back
 * 
 * @return const string& 
 */
const string& StrBlob::back() const{
    check(0,"try to get back on an empty Blob");
    return data->back();
}

StrBlobPtr StrBlob::begin(){
    return StrBlobPtr(*this);
}

StrBlobPtr StrBlob::end(){
    return StrBlobPtr(*this,this->data->size());
}

/**
 * @brief 伴随指针类
 * 
 */

class StrBlobPtr{
public:
    StrBlobPtr() : curr(0){}
    StrBlobPtr(StrBlob & sb , size_t s = 0)
        : wptr(sb.data),curr(s) {}
    bool operator!=(const StrBlobPtr&p) {
        return this->curr != p.curr;
    }
    /**
     * @brief 解引用
     * 
     * @return string& 
     */
    string& deref(){
        auto p = check(curr,"deference past end");
        return (*p)[curr];
    }
    /**
     * @brief ++运算符
     * 
     * @return StrBlobPtr& 
     */
    StrBlobPtr& incr(){
        check(curr,"increment end of StrBlobPtr");
        ++curr;
        return *this;
    }
private:
    //弱指针
    std::weak_ptr<vector<string>> wptr;
    //当前对象所表示的元素下标
    size_t curr;
    /**
     * @brief 检查访问是否有效
     * 
     * @param index 访问索引
     * @param msg  异常信息
     * @return  shared_ptr<vector<string>> 
     */
    shared_ptr<vector<string>> check(size_t index, const string &msg){
        // 如果与wptr共享对象的智能指针的数量为0，返回空sptr，否则返回指向其对象的sptr
        auto ret = wptr.lock();
        if(!ret) throw std::runtime_error("unbound StrBlobPtr");
        if(index>=ret->size()) throw std::out_of_range(msg);
        return ret;
    }


};

#endif