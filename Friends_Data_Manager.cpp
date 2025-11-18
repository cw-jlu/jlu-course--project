#include "Friends_Data_Manager.h"
#include <iostream>
#include <memory>
#include <algorithm>
using namespace std;
// 设置工厂
void Friends_Data_ManagerLXY::setFactory(std::unique_ptr<Friends_Factory> factory)
{
    friendsfactory = std::move(factory);
}

// 切换 QQ 平台
void Friends_Data_ManagerLXY::setQQPlatform()
{
    setFactory(std::make_unique<QQ_Friends_Factory>());
    friendstools = friendsfactory->GetTools();
    friendslist = friendstools->get_friend_list();
}

// 切换 WeChat 平台
void Friends_Data_ManagerLXY::setWeChatPlatform()
{
    setFactory(std::make_unique<WeChat_Friends_Factory>());
    friendstools = friendsfactory->GetTools();
    friendslist = friendstools->get_friend_list();
}

// 切换 WeiBo 平台
void Friends_Data_ManagerLXY::setWeiBoPlatform()
{
    setFactory(std::make_unique<WeiBo_Friends_Factory>());
    friendstools = friendsfactory->GetTools();
    friendslist = friendstools->get_friend_list();
}

// 切换 Main 平台
void Friends_Data_ManagerLXY::setMainPlatform()
{
    setFactory(std::make_unique<Main_Friends_Factory>());
    friendstools = friendsfactory->GetTools();
    friendslist = friendstools->get_friend_list();
}

// 写回磁盘
void Friends_Data_ManagerLXY::write_back()
{
    if (friendstools)
        friendstools->write_friend_list(friendslist);
}

// 判重：存在返回 1，否则 0
int Friends_Data_ManagerLXY::search_same(int id1, int id2)
{
    for (const auto& item : friendslist)
    {
        int a = item->id1;
        int b = item->id2;
        if ((id1 == a && id2 == b) || (id1 == b && id2 == a))
            return 1;
    }
    return 0;
}

// 添加好友
void Friends_Data_ManagerLXY::addfriends(int id1, int id2)
{
    if (id1 == id2)
    {
        std::cout << "不能加自己为好友" << std::endl;
        return;
    }
    if (!friendsfactory)
    {
        std::cout << "请先选择好友工厂" << std::endl;
        return;
    }

    int a = std::min(id1, id2);
    int b = std::max(id1, id2);

    if (search_same(a, b) == 0)
    {
        friendslist.push_back(std::make_shared<Friend_ShipLXY>(a, b));
        std::cout << "好友添加成功" << std::endl;
        write_back();
    }
    else
    {
        std::cout << b << " 已经是您的好友了" << std::endl;
    }
}

// 删除好友
void Friends_Data_ManagerLXY::deletefriends(int id1, int id2)
{
    if (!friendsfactory)
    {
        std::cout << "请先选择好友工厂" << std::endl;
        return;
    }

    for (auto it = friendslist.begin(); it != friendslist.end(); ++it)
    {
        if (((*it)->id1 == id1 && (*it)->id2 == id2) ||
            ((*it)->id1 == id2 && (*it)->id2 == id1))
        {
            friendslist.erase(it);
            std::cout << "好友删除成功" << std::endl;
            write_back();
            return;
        }
    }
    std::cout << "未找到好友" << std::endl;
}
void Friends_Data_ManagerLXY::showfriends(int id)
{
    if (friendsfactory == nullptr)
    {
        cout << "请先选择好友工厂" << endl;
    }
    else
    {
		cout << id << "的好友有：" << endl;//把好友都打印出来，不保存链表
        for(const auto& item : friendslist)
        {
            if (item->id1 == id)
            {
                cout << item->id2 << " ";
            }
            else if (item->id2 == id)
            {
                cout << item->id1 << " ";
            }
		}
    }
}
list<Friend_ShipLXY>& Friends_Data_ManagerLXY::showandgetfriends(int id)//还没写好，先不用，这个暂定是给上层调用用的，上面要是逻辑改了就可以删掉这个函数
{
    static list<Friend_ShipLXY> result; // 静态变量，函数结束后仍然存在
    result.clear(); // 每次调用前清空
    if (friendsfactory == nullptr)
    {
        cout << "请先选择好友工厂" << endl;
        return result;
    }
    for (const auto& item : friendslist)
    {
        if (item->id1 == id)
        {
            cout << item->id2 << " ";
			result.push_back(*item);
        }
        else if (item->id2 == id)
        {
            cout << item->id1 << " ";
			result.push_back(*item);
        }
    }
    return result;
}
list<shared_ptr<Friend_ShipLXY>> Friends_Data_ManagerLXY::getfriends(int id)//这里不应该参杂到各个平台的id，因为这个是底层函数，各自管好自己就好了
{
    list<shared_ptr<Friend_ShipLXY>> temp;
    for (const auto& item : friendslist)
    {
        if (item->id1 == id || item->id2 == id)
        {
            temp.push_back(item);
        }
    }
    return temp;
}
bool Friends_Data_ManagerLXY::isfriend(int id1, int id2)
{
    for (const auto& item : friendslist)
    {
        if ((item->id1 == id1 && item->id2 == id2) || (item->id1 == id2 && item->id2 == id1))
            return true;
    }
    return false;
}