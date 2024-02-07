#include "json.hpp"
using json = nlohmann::json;

#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;
 
 //json序列化示例1
 string func1(){
    json js;
    js["msg_type"]=2;
    js["from"]="zhang san";
    js["to"]="li si";
    js["msg"]="hello,what are you fucking doing now?";
    string sendBuf=js.dump();
    // cout<<sendBuf.c_str()<<endl;
    // cout<<js<<endl;
    return sendBuf;
 }
 //json序列化示例2
 string func2(){
    json js;
    js["id"]={1,2,3,4,5};
    js["name"]="zhang san";
    js["msg"]["zhang san"]="hello world";
    js["msg"]["liu shuo"]="hello china";
    
    return js.dump();
 }
 string func3(){
    json js;
    // 直接序列化一个vector容器
    vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(5);
    js["list"] = vec;
    // 直接序列化一个map容器
    map<int, string> m;
    m.insert({1, "黄山"});
    m.insert({2, "华山"});
    m.insert({3, "泰山"});
    js["path"] = m;
    return js.dump();
 }
 int main(){
    string recvBuf=func3();
    json jsbuf=json::parse(recvBuf);
    // func2();
    // func3();
    // cout<<jsbuf["msg_type"]<<endl;
    // cout<<jsbuf["from"]<<endl;
    // cout<<jsbuf["to"]<<endl;
    // cout<<jsbuf["msg"]<<endl;
    // cout<<jsbuf["id"]<<endl;
    // auto msgbuf=jsbuf["msg"];
    // cout<<msgbuf["zhang san"]<<endl;
    // cout<<msgbuf["liu shuo"]<<endl;
    auto vec = jsbuf["list"];
    for(auto &x:vec){
        cout<<x<<endl;
    }
    return 0;
 }
  