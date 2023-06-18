#include <iostream>
using std::string;

/**
 * @brief 定义使用自己设计的引用计数版本的Hasptr
 * 
 */
class Hasptr{
public:
    Hasptr(const Hasptr& hp)
        : ps(new string(*hp.ps)),i(hp.i),use(hp.use) {++*use;}
    Hasptr(const string & s)
        : ps(new string(s)),i(0), use(new size_t(1)){}
    Hasptr & operator=(const Hasptr & hp){
        //右侧 ++ ，左侧 -- 
        ++*hp.use;
        if(--*this->use == 0){
            delete ps;
            delete use;
        }
        this->ps = hp.ps;
        this->i = hp.i;
        use = hp.use;
        return *this;
    }
    ~Hasptr(){
        if(--*use == 0){
            delete ps;
            delete use;
        }
    }
private:
    string *ps;
    int i;
    std::size_t *use; // 堆区的引用计数
};