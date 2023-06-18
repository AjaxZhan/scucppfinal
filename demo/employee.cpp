/*
Author：Cagur
Content：
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#define FILE_PATH "./employee.dat"
using namespace std;

class Employee{

private:
    string name;
    double sal;
public:
    Employee() = default;
    Employee(string ename, double esal) : name(ename),sal(esal) {}
    void Show()const{
        cout  << "employee's name is " << name <<" , the sal is " << sal << endl;
    }
    string getName()const { return name; }
    double getSal() const { return sal; }
};

class EmployeeManager{

private:
    vector<Employee> data;
    bool inputFlag;

public:
    //构造函数，读取文件
    EmployeeManager();
    //展示菜单
    void showMenu();
    //获取用户键盘输入，调用写文件接口
    void getInput();
    //遍历数组，写入文件。覆盖
    void WriteData();
    //遍历数据
    void ShowAll()const ;
};


int main(){

    EmployeeManager manager;
    manager.showMenu();


    
    return 0;
}

/**
 * @brief 构造函数，读取文件
 * 
 */
EmployeeManager::EmployeeManager(){

    ifstream ifs(FILE_PATH,ios::in);
    if(!ifs.is_open()){
        cout << "cannot open the file" << endl;
        ifs.close();
        exit(1);
    }
    string tname;
    double tsal;
    string line;
    while(getline(ifs,line)){
        istringstream iss(line);
        iss >> tname >> tsal;
        Employee temp(tname,tsal);
        data.push_back(temp);
    }
    cout << "init successfully." <<endl;
}

/**
 * @brief 展示菜单
 * 
 */
void EmployeeManager::showMenu(){
        cout << "1: insertEmployeeData " << endl;
        cout << "2: showEmployeeData " <<endl; 
        cout << "0 : exit " << endl;
        string op;
        cin >> op;
        if(op == "1"){
            getInput();
            this->showMenu();
        }else if(op == "2"){
            this->ShowAll();
            cout << " continue to use? q to quit , c to continue ";
            string iop ;
            cin >> iop;
            if(iop != "q"){
                this->showMenu();
            } 
        }else if(op == "0") {
            cout << "See you next time " << endl;
            exit(0);
        }else{
            system("cls");
            showMenu();
        }
}
/**
 * @brief 获取用户键盘输入，调用写文件接口
 * 
 */
void EmployeeManager::getInput(){
        inputFlag = true;
        while(inputFlag){
            string tname;
            double tsal;
            cout  << "Please input the information of Employee . " << endl;
            cout << "name : ";
            cin >> tname;
            cout << "sal : ";
            cin >> tsal;
            Employee emp(tname,tsal);
            data.push_back(emp);
            cout << " q to quit  , c to continue :  ";
            string f;
            cin >> f;
            if(f == "q") inputFlag = false; 
        }
        this->WriteData();
        cout << "data insert successfully." << endl;
}

/**
 * @brief 遍历数组，展示数据
 * 
 */
void EmployeeManager::ShowAll()const{
    for(auto x : data){
        x.Show();
    }
}

/**
 * @brief 遍历数组，写入文件。用户选择是否覆盖
 * 
 */
void EmployeeManager::WriteData(){
    ofstream ofs(FILE_PATH,ios::out);
    for(auto x : data){
        string tname = x.getName();
        double tsal = x.getSal();
        ofs << tname << " " << tsal << " " << endl;
    }
}