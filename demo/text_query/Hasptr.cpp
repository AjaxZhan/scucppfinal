#include <string>
/**
 * @brief 实现“值”版本的拷贝构造和赋值运算符重载
 */
class Hasptr{

public:
    Hasptr(std::string &s, int j) : ps(new std::string(s)),i(j){}
    Hasptr(const Hasptr & hp)
        : ps(new std::string(*hp.ps)),i(hp.i){}   //注意这里需要解引用
    Hasptr& operator=(const Hasptr &hs){
        auto newstr = new std::string(*hs.ps);
        delete[] ps;
        ps = newstr;
        i = hs.i;
        return *this;
    }

    ~Hasptr(){
        delete[] ps;
    }

private:
    std::string *ps;
    int i;
};