#include "chatservice.hpp"
#include "public.hpp"
#include <muduo/base/Logging.h>
using namespace muduo;
using namespace std;
//获取单例对象的接口函数
ChatService* ChatService::instance(){
    static ChatService service;
    return &service;
}
//注册消息以及对应的Handler回调函数
ChatService::ChatService(){
    _msgHandlerMap.insert({LOGIN_MSG,std::bind(&ChatService::login,this,_1,_2,_3)});
    _msgHandlerMap.insert({REG_MSG, std::bind(&ChatService::reg,this,_1,_2,_3)});
}
//获取消息对应的处理器
MsgHandler ChatService::getHandler(int msgid)
{
    auto it = _msgHandlerMap.find(msgid);
    if(it==_msgHandlerMap.end()){
        //返回一个默认的处理器，空操作

        return [=](const TcpConnectionPtr &conn,json &js,Timestamp time){
            LOG_ERROR<<"msgid:"<<msgid<<"can not find handler!";
        };
    }
    else{
        return _msgHandlerMap[msgid];
    }
}
//处理登录业务
void ChatService::login(const TcpConnectionPtr &conn,json &js,Timestamp time){
    LOG_INFO<<"do login service!";
}
//处理注册业务 name password
void ChatService::reg(const TcpConnectionPtr &conn,json &js,Timestamp time){
    LOG_INFO<<"do register service!";
    string name=js["name"];
    string pwd=js["password"];
    User user;
    user.setName(name);
    user.setPwd(pwd);
    bool state=_userModel.insert(user);
    if(state){
        // 注册成功
        json response;
        response["msgid"]=REG_MSG_ACK;
        response["errno"]=0;
        response["id"]=user.getId();
        conn->send(response.dump());
    }
    else{
        //注册成功
        json response;
        response["msgid"]=REG_MSG_ACK;
        response["errno"]=1;
        conn->send(response.dump());
    }
}