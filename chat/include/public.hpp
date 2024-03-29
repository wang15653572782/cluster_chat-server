#ifndef PUBLIC_H
#define PUBLILC_H

//server和client的公共文件
enum EnMsgType{
    LOGIN_MSG = 1,//登录消息
    REG_MSG,//注册消息
    REG_MSG_ACK,//注册响应
};
/*注意：第一个枚举成员的默认值为整型的 0，后续枚举成员的值在前一个成员上加 1。我们在这个实例中把第一个枚举成员的值定义为 1，第二个就为 2，以此类推。

可以在定义枚举类型时改变枚举元素的值：

enum season {spring, summer=3, autumn, winter};
没有指定值的枚举元素，其值为前一元素加 1。也就说 spring 的值为 0，summer 的值为 3，autumn 的值为 4，winter 的值为 5
*/
#endif