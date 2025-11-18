#include "User_Manager.h"
#include <string>
#include <list>
#include <memory>
#include "Useful_Tools.h"
using namespace std;

User_ManagerLXY::User_ManagerLXY()
{
    datamanager.setMainFactory();
    auto accounts = datamanager.readData<MainaccountIfoLXY>();
    for (auto& account : accounts)
    {
        Userlist.emplace_back(std::make_unique<UserLXY>(account));
    }
    signingmanager.setMainPlatform();
}
void User_ManagerLXY::addUser(std::unique_ptr<UserLXY> user)
{
    Userlist.emplace_back(std::move(user));   // 转移所有权
}
void User_ManagerLXY::show_all_user()
{
    for (const auto& p : Userlist)   // p 是 const unique_ptr<UserLXY>&
    {
        p->showIfo();                // 指针语法
    }
}
BindingStatus User_ManagerLXY::attach_QQ(UserLXY& user)
{
    if (user.if_QQ_binded() == 1)
    {
        cout << "该用户已经绑定QQ，无法多次绑定" << endl;
        return BindingStatus::PLATFORM_ALREADY_BOUND;
    }
    cout << "正在进行QQ绑定" << endl;
    int id = readIntOnly("请输入QQid");
    signingmanager.setQQPlatform();
    LoginStatus status;
    status = signingmanager.signIn_for_binding(id);//引导用户的文字信息包含在signIn里面
    if (status == LoginStatus::SUCCESS)
    {
        user.attachQQ(id);//调用下层User中的attachQQ直接绑定
		save_all_user();//绑定成功后立刻保存
        cout << "绑定成功" << endl;
        return BindingStatus::SUCCESS;
    }
    else
    {
        cout << "绑定失败" << endl;
        return BindingStatus::FAILED;
    } 
}
// 微信绑定
BindingStatus User_ManagerLXY::attach_WeChat(UserLXY& user)
{
    if (user.if_WeChat_binded())                 
    {
        cout << "该用户已经绑定微信，无法多次绑定" << endl;
        return BindingStatus::PLATFORM_ALREADY_BOUND;
    }
    cout << "正在进行微信绑定" << endl;
    int id = readIntOnly("请输入微信id");
    signingmanager.setWeChatPlatform();
    LoginStatus status = signingmanager.signIn_for_binding(id);   // 引导文字内置在 signIn 里
    if (status == LoginStatus::SUCCESS)
    {
        user.attachWeChat(id);
		save_all_user();//绑定成功后立刻保存
        cout << "绑定成功" << endl;
        return BindingStatus::SUCCESS;
    }
    else
    {
        cout << "绑定失败" << endl;
        return BindingStatus::FAILED;         // 注意拼写修正
    }
}
// 微博绑定
BindingStatus User_ManagerLXY::attach_WeiBo(UserLXY& user)
{
    if (user.if_WeiBo_binded())                  
    {
        cout << "该用户已经绑定微博，无法多次绑定" << endl;
        return BindingStatus::PLATFORM_ALREADY_BOUND;
    }
    cout << "正在进行微博绑定" << endl;
    int id = readIntOnly("请输入微博id");
    signingmanager.setWeiBoPlatform();
    LoginStatus status = signingmanager.signIn_for_binding(id);
    if (status == LoginStatus::SUCCESS)
    {
        user.attachWeiBo(id);
        cout << "绑定成功" << endl;
		save_all_user();//绑定成功后立刻保存
        return BindingStatus::SUCCESS;
    }
    else
    {
        cout << "绑定失败" << endl;
        return BindingStatus::FAILED;
    }
}
std::shared_ptr<UserLXY> User_ManagerLXY::get_main_user_ifo(int id)
{
    for (auto& p : Userlist)          // p 是 unique_ptr<UserLXY>
    {
        if (p->showid() == id)
            return p;                 // 自动从 unique_ptr 提升为 shared_ptr
    }
    std::cout << "该用户不存在" << std::endl;
    return nullptr;                   // 空 shared_ptr
}
std::shared_ptr<UserLXY> User_ManagerLXY::get_main_user_ifo_by_QQ(int id)
{
    for (auto& p : Userlist)
    {
        if (p->showQQid() == id)
        {
            return p;
        }
    }
    std::cout << "该用户不存在或未绑定" << std::endl;
    return nullptr;
}
std::shared_ptr<UserLXY> User_ManagerLXY::get_main_user_ifo_by_WeChat(int id)
{
    for (auto& p : Userlist)
        if (p->showWeChatid() == id) return p;
    std::cout << "该用户不存在或未绑定" << std::endl;
    return nullptr;
}
std::shared_ptr<UserLXY> User_ManagerLXY::get_main_user_ifo_by_WeiBo(int id)
{
    for (auto& p : Userlist)
        if (p->showWeiBoid() == id) return p;
    std::cout << "该用户不存在或未绑定" << std::endl;
    return nullptr;
}
void User_ManagerLXY::showoneuserbyid(int id)
{
    shared_ptr<UserLXY> user = get_main_user_ifo(id);
    user->showIfo();
}
void Platform_User_ManagerLXY::show_all_user()
{
    for (auto& it : Platform_Userlist)
    {
        it->showIfo();
    }
}
void User_ManagerLXY::save_all_user()
{
    datamanager.setMainFactory();
    list<MainaccountIfoLXY> temp;
    for (const auto& user : Userlist)
    {
		temp.push_back(user->getIfo());
    }
    datamanager.writeData<MainaccountIfoLXY>(temp);
}