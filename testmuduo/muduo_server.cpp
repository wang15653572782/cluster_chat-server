/*muduo网络库给用户提供了两个主要的类
TcpServer：用于编写服务器程序的
TcpClient：用于编写客户端程序的

epoll+线程池
好处：能够把网络IO的代码和业务代码区分开
        用户的连接和断开  用户的可读写事件
*/
#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <iostream>
#include <string>
#include <functional>
using namespace std;
using namespace muduo;
using namespace muduo::net;
using namespace placeholders;
/*基于muduo网络库开发服务器程序
1.组合TcpServer对象
2.创建EventLoop事件循环对象的指针
3.明确TcpServer构造函数需要什么参数，输出ChatServer的构造函数
4.在当前服务器类的构造函数当中，注册处理连接的回调函数和处理读写事件的回调函数
5.设置合适的服务器端线程数量，muduo库会自己分配IO线程和worker线程*/
class ChatServer{
    public:
    ChatServer(EventLoop* loop,//事件循环
            const InetAddress& listenAddr,//IP+PORT
            const string& nameArg)//服务器的名字
        :_server(loop,listenAddr,nameArg),_loop(loop)
{
    //给服务器注册用户连接的创建和断开回调
    _server.setConnectionCallback(std::bind(&ChatServer::onConnection,this,_1));

    //给服务器注册用户读写事件回调
    _server.setMessageCallback(std::bind(&ChatServer::onMessage,this,_1,_2,_3));
    //设置服务器端的线程数量 1个IO线程 3个worker进程
    _server.setThreadNum(4);

}
    void start(){
        _server.start();
    }
            
    private:
    //专门处理用户的连接创建和断开
    void onConnection(const TcpConnectionPtr& conn){
        if(conn->connected()){
            cout<<conn->peerAddress().toIpPort()
            <<" -> "<<conn->localAddress().toIpPort()<<"state::online"<<endl;

        }else{
              cout<<conn->peerAddress().toIpPort()
            <<" -> "<<conn->localAddress().toIpPort()<<"state::offline"<<endl;
            conn->shutdown();//close(fd)

        }
    }
    //专门处理用户的读写事件
    void onMessage(const TcpConnectionPtr& conn,//连接 
                Buffer* buf,//缓冲区
                Timestamp time)//接受到数据的时间信息
                {
                    string buffer = buf->retrieveAllAsString();
                    cout<<"recv data:"<<buffer<<"time:"<<time.toString()<<endl;
                    conn->send(buffer);
                }
    TcpServer _server;
    EventLoop *_loop;

};

int main(){
    EventLoop loop;
    InetAddress addr("127.0.0.1",6000);
    ChatServer server(&loop,addr,"ChatServer");
    server.start();
    loop.loop();//epoll_wait以阻塞方式等待新用户连接，已连接用户的读写事件等
    return 0;
}