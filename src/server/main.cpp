#include "chatserver.hpp"
#include "chatservice.hpp"
#include <iostream>
#include <signal.h>
using namespace std;

//处理服务器ctrl+c结束后，重置user的状态信息
void resetHandler(int){
    ChatService::instance()->reset();
    exit(0);
}
int main(){
    signal(SIGINT,resetHandler);
    signal(SIGTERM,resetHandler);
    /*signal 是一个在 UNIX-like 系统（如 Linux）中用于处理异步事件的函数。
    它允许你为特定的信号设置一个处理函数，当该信号发生时，该处理函数将被调用。
在给定的代码 signal(SIGINT, resetHandler); 中，signal 函数被用于设置一个处理 SIGINT 信号的函数。
具体来说：
SIGINT 是一个信号，通常由用户按下 Ctrl+C 产生。当一个进程收到 SIGINT 信号时，它通常表示用户想要中断该进程。
resetHandler 是当 SIGINT 信号发生时要调用的函数。具体这个函数做了什么取决于它的实现，但通常它可能会做一些清理工作，然后可能使进程终止或采取其他行动。*/
    EventLoop loop;
    InetAddress addr("127.0.0.1",6000);
    ChatServer server(&loop,addr,"ChatServer");

    server.start();
    loop.loop();
    return 0;
}
/*{"msgid":1,"id":25,"password":"wcf2002"}
{"msgid":1,"id":26,"password":"lisi2002"}
{"msgid":5,"id":25,"from":"zxhang san","to":26,"msg":"hello!"}
{"msgid":5,"id":26,"from":"li si","to":25,"msg":"I''m li si!"}
{"msgid":3,"name":"li si","password":"lisi2002"}
{"msgid":6,"id":26,"friendid":25}
insert into offlinemessage values(25,'{"from":"li si","id":26,"msg":"I''m li si!","msgid":5,"to":25}')*/
