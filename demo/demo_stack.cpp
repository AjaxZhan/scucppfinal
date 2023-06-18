#include <iostream>
using namespace std;

#define SIZE 100
template<class T>
class Stack{
public:
    Stack(int size = SIZE){};

    void push(T);
    T pop();
    T& top();
    int size();
    bool empty();
    bool full();

    bool check();    

    ~Stack(){
        delete[] this->elem;
    }

private:
    T* elem;
    int sp;
    int capacity;   

};

template<class T>
Stack<T>::Stack(int size){
    elem = new T[size];
    capacity = size;
    sp = -1;
}

template<class T>
void Stack<T>::push(T t){
    check();
    elem[++sp] = t;
}

template<class T>
T Stack<T>::pop(){
    check();
    return elem[sp--];
}

template<class T>
T& Stack<T>::top(){
    if(empty()){
        throw out_of_range("数组为空");
    }
    return elem[sp];
}
template<class T>
int Stack<T>::size(){
    return sp+1;
}
template<class T>
bool Stack<T>::empty(){
    return sp == -1;
}
template<class T>
bool Stack<T>::full(){
    return sp == capacity+1;
}
template<class T>
bool Stack<T>::check(){
    if(full()) throw out_of_range("数组为满啦");

}

int main(){


}