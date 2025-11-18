#include "User.h"
#include "Data_Manager.h"
#include <iostream>
#include <list>
#include "Useful_Tools.h"
using namespace std;

void UserLXY::showIfo()
{
	cout << "id = " << p.id << endl
		<< "name =" << p.Username << endl
		<< "phonenumber = " << p.phoneNumber << endl
		<< "email = " << p.email << endl;
	if (p.QQid != 0)
	{
		cout << "QQid" << p.QQid << endl;
	}
	if (p.WeChatid != 0)
	{
		cout << "WeChatid" << p.WeChatid << endl;
	}
	if (p.WeiBoid != 0)
	{
		cout << "WeiBoid" << p.WeiBoid << endl;
	}
}

int UserLXY::if_QQ_binded()
{
	if (p.QQid == 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
int UserLXY::if_WeChat_binded()
{
	if (p.WeChatid == 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
int UserLXY::if_WeiBo_binded()
{
	if (p.WeiBoid == 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
void UserLXY::attachQQ(int id)
{
	p.QQid = id;
}
void UserLXY::attachWeChat(int id)
{
	p.WeChatid = id;
}
void UserLXY::attachWeiBo(int id)
{
	p.WeiBoid = id;
}

std::list<std::unique_ptr<Platform_UserLXY>>
QQ_User_FactoryLXY::create_Userlist()
{
	datamanager.setQQFactory();
	auto valList = datamanager.readData<QQaccountIfoLXY>(); 

	std::list<std::unique_ptr<Platform_UserLXY>> ptrList;
	for (auto& v : valList)          
		ptrList.push_back(
			std::make_unique<QQ_UserLXY>(v)   // 只传账号信息
		);

	return ptrList;
}
std::list<std::unique_ptr<Platform_UserLXY>> WeChat_User_FactoryLXY::create_Userlist()
{
	datamanager.setWeChatFactory();
	auto valList = datamanager.readData<WeChataccountIfoLXY>();

	//这里把实体改成指针
	std::list<std::unique_ptr<Platform_UserLXY>> ptrList;
	for (auto& v : valList)                       
		ptrList.push_back(
			std::make_unique<WeChat_UserLXY>(v)
		);
	return ptrList;   
}
std::list<std::unique_ptr<Platform_UserLXY>> WeiBo_User_FactoryLXY::create_Userlist()
{	
	datamanager.setWeiBoFactory();
	auto valList = datamanager.readData<WeiBoaccountIfoLXY>();

	//这里把实体改成指针
	std::list<std::unique_ptr<Platform_UserLXY>> ptrList;
	for (auto& v : valList)                       
		ptrList.push_back(
			std::make_unique<WeiBo_UserLXY>(v)
		);
	return ptrList; 
}
int UserLXY::showid()
{
	return p.id;
}
int UserLXY::showQQid()
{
	return p.QQid;
}
int UserLXY::showWeChatid()
{
	return p.WeChatid;//下次从这里开始吧，其实不用再单独挑时间出来写课设了，只剩下了一点收尾阶段。就用剩下的几次课设课来写吧，现在发现这行报错了，再跨平台推荐好友的时候。应该是初始话是空指针，然后调用的时候没有注意
}
int UserLXY::showWeiBoid()
{
	return p.WeiBoid;
}
MainaccountIfoLXY& UserLXY::getIfo()
{
	return p;
}
void QQ_UserLXY::showIfo()
{
	cout << "QQ账号信息：" << endl
		<< "QQ号: " << p.QQid << endl
		<< "昵称: " << p.name << endl
		<< "密码: " << p.QQpassword << endl
		<< "是否绑定主账号: " << (p.ifconnect ? "是" : "否") << endl
		<< "是否在线: " << (p.ifonline ? "是" : "否") << endl;
}

void WeChat_UserLXY::showIfo()
{
	cout << "微信账号信息：" << endl
		<< "微信号: " << p.WeChatid << endl
		<< "昵称: " << p.name << endl
		<< "密码: " << p.WeChatpassword << endl
		<< "是否绑定主账号: " << (p.ifconnect ? "是" : "否") << endl
		<< "是否在线: " << (p.ifonline ? "是" : "否") << endl;
}

void WeiBo_UserLXY::showIfo()
{
	cout << "微博账号信息：" << endl
		<< "微博ID: " << p.WeiBoid << endl
		<< "昵称: " << p.name << endl
		<< "密码: " << p.WeiBopassword << endl
		<< "是否绑定主账号: " << (p.ifconnect ? "是" : "否") << endl
		<< "是否在线: " << (p.ifonline ? "是" : "否") << endl;
}
int QQ_UserLXY::showid()
{
	return p.QQid;
}
int WeChat_UserLXY::showid()
{
	return p.WeChatid;
}
int WeiBo_UserLXY::showid()
{
	return p.WeiBoid;
}
void UserLXY::changename()
{
	cout << "请输入新用户名" << endl;
	int newname;
	cin >> newname;
	p.Username = newname;
	cout << "修改成功" << endl;
}
void UserLXY::changepassword()
{
	delaycout("请输入旧密码");
	string oldpassword;
	cin >> oldpassword;
	if (oldpassword == p.password)
	{
		int newpassword;
		delaycout("请输入新的密码");
		cin >> newpassword;
		p.password = newpassword;
		delaycout("修改成功");
		return;
	}
	delaycout("密码错误");
	return;
}
void UserLXY::changephonenumber()
{
	delaycout("请输入新手机号");
	long long newphonenumber;
	cin >> newphonenumber;
	if (ifphonenumberlegal(newphonenumber) == true)
	{
		p.phoneNumber = newphonenumber;
		delaycout("修改成功");
		return;
	}
	delaycout("手机号格式错误");
}
void UserLXY::changeemail()
{
	delaycout("请输入新邮箱");
	string newemail;
	cin >> newemail;
	p.email = newemail;
	delaycout("修改成功");
}