#include "Friends_Data_Tools.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

/*Main*/
list<shared_ptr<Friend_ShipLXY>> Main_Friends_ToolsLXY::get_friend_list()
{
    list<shared_ptr<Friend_ShipLXY>> typedData;
    ifstream file("MainFriendsLXY.txt");
    if (!file.is_open())
    {
        cerr << "MainFriendsLXY.txt打开失败或文件不存在\n";
        return typedData;
    }

    string line;
    while (getline(file, line))
    {
        if (line.empty()) continue;

        istringstream iss(line);
        int id1{}, id2{};
        if (iss >> id1 >> id2)
        {
            typedData.push_back(std::make_shared<Friend_ShipLXY>(id1, id2));
        }
        else
        {
            cerr << "行格式错误: " << line << '\n';
        }
    }
    file.close();
    return typedData;
}
void Main_Friends_ToolsLXY::write_friend_list(list<shared_ptr<Friend_ShipLXY>>& lst)
{
    ofstream file("MainFriendsLXY.txt");

    if (!file.is_open())
    {
        cerr << "MainFriendsLXY.txt打开失败" << endl;
        return;
    }

    for (const auto& account : lst)
    {
        file << account->id1 << " "
            << account->id2
            << "\n";
    }
    file.close();
}

/* ---------- QQ_Friends_ManagerLXY ---------- */
list<shared_ptr<Friend_ShipLXY>> QQ_Friends_ToolsLXY::get_friend_list()
{
    list<shared_ptr<Friend_ShipLXY>> typedData;
    ifstream file("QQFriendsLXY.txt");
    if (!file.is_open())
    {
        cerr << "QQFriendsLXY.txt打开失败或文件不存在\n";
        return typedData;          // 返回空列表
    }

    string line;
    while (getline(file, line))          // 一行一行读
    {
        if (line.empty()) continue;

        istringstream iss(line);
        int id1{}, id2{};
        if (iss >> id1 >> id2)                
        {
            // 用 make_unique 构造对象，再把指针塞进 list
            typedData.push_back(std::make_shared<Friend_ShipLXY>(Friend_ShipLXY{ id1, id2 }));
        }
        else
        {
            cerr << "行格式错误: " << line << '\n';
        }
    }
    file.close();
    return typedData;                        
}
void QQ_Friends_ToolsLXY::write_friend_list(list<shared_ptr<Friend_ShipLXY>>& lst)
{
    ofstream file("QQFriendsLXY.txt");

    if (!file.is_open())
    {
        cerr << "QQFriendsLXY.txt打开失败" << endl;
        return;
    }

    for (const auto& account : lst)
    {
        file << account->id1 << " "
            << account->id2
            << "\n";
    }
    file.close();
}

/* ---------- WeChat_Friends_ManagerLXY ---------- */
list<shared_ptr<Friend_ShipLXY>>
WeChat_Friends_ToolsLXY::get_friend_list()
{
    list<shared_ptr<Friend_ShipLXY>> typedData;
    ifstream file("WeChatFriendsLXY.txt");
    if (!file.is_open())
    {
        cerr << "WeChatFriendsLXY.txt打开失败或文件不存在\n";
        return typedData;
    }

    string line;
    while (getline(file, line))
    {
        if (line.empty()) continue;

        istringstream iss(line);
        int id1{}, id2{};
        if (iss >> id1 >> id2)
        {
            typedData.push_back(make_shared<Friend_ShipLXY>(Friend_ShipLXY{ id1, id2 }));
        }
        else
        {
            cerr << "行格式错误: " << line << '\n';
        }
    }
    file.close();
    return typedData;
}

void WeChat_Friends_ToolsLXY::write_friend_list(list<shared_ptr<Friend_ShipLXY>>& lst)
{
    ofstream file("WeChatFriendsLXY.txt", ios::trunc);
    if (!file.is_open())
    {
        cerr << "WeChatFriendsLXY.txt打开失败\n";
        return;
    }

    for (const auto& account : lst)
    {
        file << account->id1 << ' ' << account->id2 << '\n';
    }
    file.close();
}
/* ---------- WeiBo_Friends_ManagerLXY ---------- */
list<shared_ptr<Friend_ShipLXY>>
WeiBo_Friends_ToolsLXY::get_friend_list()
{
    list<shared_ptr<Friend_ShipLXY>> typedData;
    ifstream file("WeiBoFriendsLXY.txt");
    if (!file.is_open())
    {
        cerr << "WeiBoFriendsLXY.txt打开失败或文件不存在\n";
        return typedData;
    }

    string line;
    while (getline(file, line))
    {
        if (line.empty()) continue;

        istringstream iss(line);
        int id1{}, id2{};
        if (iss >> id1 >> id2)
        {
            typedData.push_back(make_shared<Friend_ShipLXY>(Friend_ShipLXY(id1, id2)));
        }
        else
        {
            cerr << "行格式错误: " << line << '\n';
        }
    }
    file.close();
    return typedData;
}

void WeiBo_Friends_ToolsLXY::write_friend_list(list<shared_ptr<Friend_ShipLXY>>& lst)
{
    ofstream file("WeiBoFriendsLXY.txt", ios::trunc);
    if (!file.is_open())
    {
        cerr << "WeiBoFriendsLXY.txt打开失败\n";
        return;
    }

    for (const auto& account : lst)
    {
        file << account->id1 << ' ' << account->id2 << '\n';
    }
    file.close();
}

/* ---------- 工厂类 ---------- */
std::unique_ptr<Friends_Data_ToolsLXY> Main_Friends_Factory::GetTools() { return std::make_unique<Main_Friends_ToolsLXY>(); }
std::unique_ptr<Friends_Data_ToolsLXY> QQ_Friends_Factory::GetTools() { return std::make_unique<QQ_Friends_ToolsLXY>(); }
std::unique_ptr<Friends_Data_ToolsLXY> WeChat_Friends_Factory::GetTools() { return std::make_unique<WeChat_Friends_ToolsLXY>(); }
std::unique_ptr<Friends_Data_ToolsLXY> WeiBo_Friends_Factory::GetTools() { return std::make_unique<WeiBo_Friends_ToolsLXY>(); }