#ifndef Signing_Tools
#define Signing_Tools

#include <list>
#include <iostream>
#include <string>
#include <memory>
#include "Data_Manager.h"
/*各种登录注册工具*/
/*使用工厂方法模式*/

enum class LoginStatus {
	SUCCESS,
	ACCOUNT_NOT_EXIST,
	PASSWORD_ERROR,
	ALREADY_ONLINE,
	ALREADY_CONNECT,
	NO_ACCOUNTS_REGISTERED,
	DATABASE_ERROR,
	INVALID_INPUT,
	REGISTER_SUCCESS,       
	REGISTER_FAILED,        
	ID_ALREADY_EXISTS,
	NOT_BOUND
};//这个是登录注册返回值的枚举
class Signing_PlatformLXY
{
public:
	virtual LoginStatus sign_in() = 0;//引导登录
	virtual LoginStatus sign_in(int id) = 0;//引导有id登录
	virtual LoginStatus sign_in_for_binding(int id) = 0;//引导绑定
	virtual LoginStatus sign_up() = 0;/*注册完了一定要马上写回文件！！！！*/
    Data_ManagerLXY datamanager;
};
class Main_SigningLXY : public Signing_PlatformLXY
{
public:
	LoginStatus sign_in();
	LoginStatus sign_in(int id);
	LoginStatus sign_in_for_binding(int id);
	LoginStatus sign_up();/*注册完了一定要马上写回文件！！！！！*/
};
class QQ_SigningLXY : public Signing_PlatformLXY
{
public:
	LoginStatus sign_in();
	LoginStatus sign_in(int id);
	LoginStatus sign_in_for_binding(int id);
	LoginStatus sign_up();/*注册完了一定要马上写回文件！！！！！*/
};
class WeChat_SigningLXY :public Signing_PlatformLXY
{
public:
	LoginStatus sign_in();
	LoginStatus sign_in(int id);
	LoginStatus sign_in_for_binding(int id);
	LoginStatus sign_up();/*注册完了一定要马上写回文件！！！！！*/
};
class WeiBo_SigningLXY : public Signing_PlatformLXY
{
public:
	LoginStatus sign_in();
	LoginStatus sign_in(int id);
	LoginStatus sign_in_for_binding(int id);
	LoginStatus sign_up();/*注册完了一定要马上写回文件！！！！！*/
};
class Signing_FactoryLXY
{
public:
	virtual std::unique_ptr<Signing_PlatformLXY> set_signing_platform() = 0;
};
class Main_FactoryLXY:public Signing_FactoryLXY 
{
public:
	std::unique_ptr<Signing_PlatformLXY> set_signing_platform() { return std::make_unique<Main_SigningLXY>(); }
};
class QQ_FactoryLXY :public Signing_FactoryLXY
{
public:
	std::unique_ptr<Signing_PlatformLXY> set_signing_platform() { return std::make_unique<QQ_SigningLXY>(); }
};
class WeChat_FactoryLXY :public Signing_FactoryLXY
{
public:
	std::unique_ptr<Signing_PlatformLXY> set_signing_platform() { return std::make_unique<WeChat_SigningLXY>(); }
};
class WeiBo_FactoryLXY :public Signing_FactoryLXY
{
public:
	std::unique_ptr<Signing_PlatformLXY> set_signing_platform() { return std::make_unique<WeiBo_SigningLXY>(); }
};
/*一个登录管理类*/
#endif