
#include <iostream>
#include <memory>
#include<string>
#include<vector>
#include<algorithm>
#include "Graph.h"
using namespace std;

class A{

    public:
    string id;
    A(string a){
        this->id = a;
    }

};

class test{

    public:
        A* a;
        vector<A*> va ;


    public:
        string name;
        test(string name):a(){
           // a = new A(name);
            this->name = name;
            va.push_back(new A("ppp"));
            
        };
        void begin(){
            this->a = va.at(0);
        };

};

int main(){
    vector<shared_ptr<test>> T;

    T.push_back(make_shared<test>("u"));

    shared_ptr<test> pt = make_shared<test>("a");
    shared_ptr<test> pt1 = nullptr;
    pt1 =  pt;
        cout << pt1.get()->name << endl;
     pt1 = *(T.begin());


    cout << pt1.get()->name << endl;




    test ts("---");

    cout << ts.a->id << endl;
    ts.begin();
    cout << ts.a->id << endl;





}