#ifndef User_h
#define User_h
#include <iostream>
#include <list>
#include <memory>
#include "Data_Manager.h"
#include <string>
struct MainaccountIfoLXY;//向前声明
struct QQaccountIfoLXY;
struct WeChataccountIfoLXY;
struct WeiBoaccountIfoLXY;

class UserLXY 
{
private:
    //这个用户的信息就是主账号信息，把Main和QQ微信微博区分开，前者是要我写的，后者只提供账号登录验证和好友信息
    MainaccountIfoLXY p;//这里是最最最根源的用户信息，所以用拷贝构造而不是引用，我决定放弃用Datamanager来作为原始数据存储点
public:
    UserLXY(MainaccountIfoLXY &a):p(a){}//直接结构体赋值
    ~UserLXY() = default;

    //登陆注册注销账号
    void showIfo();

    void attachQQ(int id);//直接修改p中内容,辅助上层的绑定程序进行绑定账号
    void attachWeChat(int id);
    void attachWeiBo(int id);
    int if_QQ_binded();
    int if_WeChat_binded();
    int if_WeiBo_binded();
    int showid();
    int showQQid();
    int showWeChatid();
    int showWeiBoid();

    void changename();
    void changepassword();
    void changephonenumber();
    void changeemail();
    MainaccountIfoLXY& getIfo();
};
class Platform_UserLXY
{
public:
    virtual void addfriend() {}
    virtual void deletefriend() {}
    virtual void showIfo(){}
    virtual void addgroup(){}
    virtual void deletegroup(){}
    virtual void showgroup(){}
    virtual ~Platform_UserLXY() = default;
    virtual int showid() = 0;
};
/*工厂方法模式来写其他平台*/
class QQ_UserLXY : public Platform_UserLXY
{
public:
    QQ_UserLXY(QQaccountIfoLXY& ifo) :p(ifo){}
    void showIfo();
	int showid();
private:
    QQaccountIfoLXY p;
};
class WeChat_UserLXY : public Platform_UserLXY
{
public:
    WeChat_UserLXY(WeChataccountIfoLXY& ifo):p(ifo){}
    void showIfo();
	int showid();
private:
    WeChataccountIfoLXY p;
};
class WeiBo_UserLXY :public Platform_UserLXY
{
public:
    WeiBo_UserLXY(WeiBoaccountIfoLXY& ifo):p(ifo){}
    void showIfo();
	int showid();
private:
    WeiBoaccountIfoLXY p;
};
class User_FactoryLXY
{
protected:
    Data_ManagerLXY datamanager;
    
public:
    virtual std::list<std::unique_ptr<Platform_UserLXY>> create_Userlist() = 0;
};
class QQ_User_FactoryLXY : public User_FactoryLXY
{
public:
    std::list<std::unique_ptr<Platform_UserLXY>> create_Userlist();
};
class WeChat_User_FactoryLXY : public User_FactoryLXY
{
public:
    std::list<std::unique_ptr<Platform_UserLXY>> create_Userlist();
};
class WeiBo_User_FactoryLXY : public User_FactoryLXY
{
public:
    std::list<std::unique_ptr<Platform_UserLXY>> create_Userlist();
};

#endif