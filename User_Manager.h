#ifndef User_Manager_h
#define User_Manager_h

#include "User.h"
#include "Data_Manager.h"
#include "Signing_Manager.h"
#include <memory>
#include <iostream>

enum class BindingStatus {
	SUCCESS,                    // 绑定成功
	PLATFORM_ALREADY_BOUND,     // 该平台已绑定
	ACCOUNT_NOT_EXIST,          // 要绑定的账号不存在
	USER_NOT_FOUND,             // 用户不存在
	FAILED,
};//绑定操作使用的枚举

class User_ManagerLXY
{
private:
	std::list<std::shared_ptr<UserLXY>> Userlist;//这个是所有用户的链表(只包括main)
	Data_ManagerLXY datamanager;//数据工具
	Signing_ManagerLXY signingmanager;//用户登录工具

public:
	User_ManagerLXY();//把所有用户编制成链表

	void addUser(std::unique_ptr<UserLXY> user);
	void show_all_user();
	void save_all_user();//把所有用户信息写回文件
	//绑定工具
	BindingStatus attach_QQ(UserLXY& user);
	BindingStatus attach_WeChat(UserLXY& user);
	BindingStatus attach_WeiBo(UserLXY& user);
	//搜索工具
	std::shared_ptr<UserLXY> get_main_user_ifo(int id);
	std::shared_ptr<UserLXY> get_main_user_ifo_by_QQ(int id);
	std::shared_ptr<UserLXY> get_main_user_ifo_by_WeChat(int id);
	std::shared_ptr<UserLXY> get_main_user_ifo_by_WeiBo(int id);
	void showoneuserbyid(int id);
	LoginStatus Signin(int id)
	{
		return signingmanager.signIn(id);
	}
	LoginStatus Signup()
	{
		return signingmanager.signUp();
	}
	bool searchifidlegal(int id)
	{
		for (const auto& item : Userlist)
		{
			if (item->showid() == id)
			{
				return true;
			}
		}
		return false;
	}
};

class Platform_User_ManagerLXY//这个类使用多态工厂来生成三种平台的用户链表
{
private:
	std::list<std::unique_ptr<Platform_UserLXY>> Platform_Userlist;//用户链表
    Data_ManagerLXY datamanager;//数据工具
	std::unique_ptr<User_FactoryLXY> currentfactory;//当前工厂
	Signing_ManagerLXY signingmanager;//登录工具
public:
	void setfactory(std::unique_ptr<User_FactoryLXY> factory)
	{
        currentfactory = std::move(factory);
	}
	void setQQfactory()//指定工厂
	{
		setfactory(std::make_unique<QQ_User_FactoryLXY>());
		Platform_Userlist = currentfactory->create_Userlist();
		signingmanager.setQQPlatform();
	}
	void setWeChatfactory()
	{
        setfactory(std::make_unique<WeChat_User_FactoryLXY>());
        Platform_Userlist = currentfactory->create_Userlist();
		signingmanager.setWeChatPlatform();
	}
	void setWeiBofactory()
	{
		setfactory(std::make_unique<WeiBo_User_FactoryLXY>());
        Platform_Userlist = currentfactory->create_Userlist();
		signingmanager.setWeiBoPlatform();
	}
	bool searchifidlegal(int id)
	{
		for (const auto& item : Platform_Userlist)
		{
			if (item->showid() == id)
			{
				return true;
			}
		}
		return false;
	}
	LoginStatus Signin(int id)
	{
		return signingmanager.signIn(id);
	}
	LoginStatus Signup()
	{
		return signingmanager.signUp();
	}
	void show_all_user();
};
#endif