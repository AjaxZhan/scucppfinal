#include "TextQuery.h"

using std::cin , std::cout ,std::endl;

int main(){

    ifstream ifs(filePath);

    TextQuery tq(ifs);
    while(true){
        cout << "enter the word to look for and q to quit : " << endl;
        string s; 
        if(!(cin >> s) || s=="q") break;
        print(cout,tq.query(s)) << endl;
    }
    return 0;
}