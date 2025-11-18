#include <fstream>
#include <sstream>
#include <iostream>
#include "Data_Tools.h"
using namespace std;

//Main
std::list<MainaccountIfoLXY> MainReaderLXY::readTyped()
{
    std::list<MainaccountIfoLXY> typedData;
    std::ifstream file("MainaccountIfoLXY.txt");

    if (!file.is_open())
    {
        std::cerr << "MainaccountIfoLXY.txt打开失败或文件不存在\n";
        return typedData;
    }

    std::string line;
    while (std::getline(file, line))                 // 一行一行读
    {
        if (line.empty()) continue;                  // 跳过空行

        // ===== 调试：打印原始行和十六进制 =====
        //std::cout << "原始行: '" << line << "'\n";
        //std::cout << "行长度: " << line.size()
          //  << "  字段数: "
           // << std::count(line.begin(), line.end(), ' ') + 1 << '\n';
        //for (unsigned char c : line) std::printf(" %02x", c);
        //std::cout << '\n';
        // ===== 调试结束 =====

        std::istringstream iss(line);
        MainaccountIfoLXY account;
        std::string phoneStr, onlineStr;

        // 只读 11 个字段，后面多余内容直接忽略
        if (!(iss >> account.id >> phoneStr >> account.email
            >> account.Username >> account.password
            >> account.date >> account.address
            >> account.QQid >> account.WeChatid
            >> account.WeiBoid >> onlineStr))
        {
            std::cerr << "字段不足或格式错误，跳过整行: " << line << '\n';
            continue;
        }

        // 电话号码转换
        try {
            account.phoneNumber = std::stoll(phoneStr);
        }
        catch (const std::invalid_argument&) {
            std::cerr << "手机号非数字，跳过整行: " << phoneStr << '\n';
            continue;
        }
        catch (const std::out_of_range&) {
            std::cerr << "手机号超出范围，跳过整行: " << phoneStr << '\n';
            continue;
        }

        // 布尔值转换
        account.ifonline = (onlineStr == "1" || onlineStr == "true" || onlineStr == "yes");

        typedData.push_back(account);
    }

    file.close();
    return typedData;
}
void MainWriterLXY::writeTyped(const list<MainaccountIfoLXY>& data)
{
    ofstream file("MainaccountIfoLXY.txt");

    if (!file.is_open())
    {
        cerr << "MainaccountIfoLXY.txt打开失败" << endl;
        return;
    }

    for (const auto& account : data)
    {
        file << account.id << " "
            << account.phoneNumber << " "
            << account.email << " "
            << account.Username << " "
            << account.password << " "
            << account.date << " "
            << account.address << " "
            << account.QQid << " "
            << account.WeChatid << " "
            << account.WeiBoid << " "
            << (account.ifonline ? 1 : 0)  // 布尔值存为1/0
            << "\n";
    }

    file.close();
}
void MainViewerLXY::showTyped(const list<MainaccountIfoLXY>& data)
{
    if (data.empty()) {
        cout << "没有Main账号数据" << endl;
        return;
    }

    int count = 1;
    for (const auto& account : data)
    {
        cout << "=== Main账号 #" << count++ << " ===" << endl;
        cout << "ID: " << account.id << endl;
        cout << "电话号码: " << account.phoneNumber << endl;
        cout << "邮箱: " << account.email << endl;
        cout << "用户名: " << account.Username << endl;
        cout << "密码: " << account.password << endl;
        cout << "日期: " << account.date << endl;
        cout << "地址: " << account.address << endl;
        cout << "QQ ID: " << account.QQid << endl;
        cout << "微信 ID: " << account.WeChatid << endl;
        cout << "微博 ID: " << account.WeiBoid << endl;
        cout << "在线状态: " << (account.ifonline ? "在线" : "离线") << endl;
        cout << "--------------------------" << endl;
    }
}
//QQ
list<QQaccountIfoLXY> QQReaderLXY::readTyped()
{
    list<QQaccountIfoLXY> typedData;
    ifstream file("QQaccountIfoLXY.txt");
    if (!file.is_open())
    {
        cerr << "QQaccountIfoLXY.txt打开失败或文件不存在" << endl;
        return typedData;  // 返回空列表
    }
    string line;
    while (getline(file, line))//一行一行读
    {
        if (line.empty()) continue;  // 跳过空行
        istringstream iss(line);
        QQaccountIfoLXY account;
        string onlineStr;//先用字符串接收布尔值，后面再转换
        string connectStr;//先用字符串接收布尔值，后面再转换
        if (iss >> account.QQid >> account.QQpassword >> account.name >> connectStr >> onlineStr)
        {
            // 转换布尔值
            account.ifconnect = (connectStr == "1" || connectStr == "true" || connectStr == "yes");
            account.ifonline = (onlineStr == "1" || onlineStr == "true" || onlineStr == "yes");
            typedData.push_back(account);
        }
        else
        {
            cerr << "行格式错误: " << line << endl;
        }
    }
    file.close();
    return typedData;
}
void QQWriterLXY::writeTyped(const list<QQaccountIfoLXY>& data)
{
    ofstream file("QQaccountIfoLXY.txt");
    if (!file.is_open())
    {
        cerr << "QQaccountIfoLXY.txt打开失败" << endl;
        return;
    }
    for (const auto& account : data)
    {
        file << account.QQid << " "
            << account.QQpassword << " "
            << account.name << " "
            << (account.ifconnect ? 1 : 0) << " "  // 布尔值存为1/0
            << (account.ifonline ? 1 : 0)           // 布尔值存为1/0
            << "\n";
    }
    file.close();
}
void QQViewerLXY::showTyped(const list<QQaccountIfoLXY>& data)
{
    if (data.empty()) {
        cout << "没有QQ账号数据" << endl;
        return;
    }
    int count = 1;
    for (const auto& account : data)
    {
        cout << "=== QQ账号 #" << count++ << " ===" << endl;
        cout << "QQ ID: " << account.QQid << endl;
        cout << "密码: " << account.QQpassword << endl;
        cout << "昵称: " << account.name << endl;
        cout << "连接状态: " << (account.ifconnect ? "已连接" : "未连接") << endl;
        cout << "在线状态: " << (account.ifonline ? "在线" : "离线") << endl;
        cout << "--------------------------" << endl;
    }
}
//微信
list<WeChataccountIfoLXY> WeChatReaderLXY::readTyped()
{
    list<WeChataccountIfoLXY> typedData;
    ifstream file("WeChataccountIfoLXY.txt");
    if (!file.is_open())
    {
        cerr << "WeChataccountIfoLXY.txt打开失败或文件不存在" << endl;
        return typedData;  // 返回空列表
    }
    string line;
    while (getline(file, line))//一行一行读
    {
        if (line.empty()) continue;  // 跳过空行
        istringstream iss(line);
        WeChataccountIfoLXY account;
        string onlineStr;//先用字符串接收布尔值，后面再转换
        string connectStr;//先用字符串接收布尔值，后面再转换
        if (iss >> account.WeChatid >> account.WeChatpassword >> account.name >> connectStr >> onlineStr)
        {
            // 转换布尔值
            account.ifconnect = (connectStr == "1" || connectStr == "true" || connectStr == "yes");
            account.ifonline = (onlineStr == "1" || onlineStr == "true" || onlineStr == "yes");
            typedData.push_back(account);
        }
        else
        {
            cerr << "行格式错误: " << line << endl;
        }
    }
    file.close();
    return typedData;
}
void WeChatWriterLXY::writeTyped(const list<WeChataccountIfoLXY>& data)
{
    ofstream file("WeChataccountIfoLXY.txt");
    if (!file.is_open())
    {
        cerr << "WeChataccountIfoLXY.txt打开失败" << endl;
        return;
    }
    for (const auto& account : data)
    {
        file << account.WeChatid << " "
            << account.WeChatpassword << " "
            << account.name << " "
            << (account.ifconnect ? 1 : 0) << " "  // 布尔值存为1/0
            << (account.ifonline ? 1 : 0)           // 布尔值存为1/0
            << "\n";
    }
    file.close();
}
void WeChatViewerLXY::showTyped(const list<WeChataccountIfoLXY>& data)
{
    if (data.empty()) {
        cout << "没有微信账号数据" << endl;
        return;
    }
    int count = 1;
    for (const auto& account : data)
    {
        cout << "=== 微信账号 #" << count++ << " ===" << endl;
        cout << "微信 ID: " << account.WeChatid << endl;
        cout << "密码: " << account.WeChatpassword << endl;
        cout << "昵称: " << account.name << endl;
        cout << "连接状态: " << (account.ifconnect ? "已连接" : "未连接") << endl;
        cout << "在线状态: " << (account.ifonline ? "在线" : "离线") << endl;
        cout << "--------------------------" << endl;
    }
}
//WeiBo
list<WeiBoaccountIfoLXY> WeiBoReaderLXY::readTyped()
{
    list<WeiBoaccountIfoLXY> typedData;
    ifstream file("WeiBoaccountIfoLXY.txt");
    if (!file.is_open())
    {
        cerr << "WeiBoaccountIfoLXY.txt打开失败或文件不存在" << endl;
        return typedData;  // 返回空列表
    }
    string line;
    while (getline(file, line))//一行一行读
    {
        if (line.empty()) continue;  // 跳过空行
        istringstream iss(line);
        WeiBoaccountIfoLXY account;
        string onlineStr;//先用字符串接收布尔值，后面再转换
        string connectStr;//先用字符串接收布尔值，后面再转换
        if (iss >> account.WeiBoid >> account.WeiBopassword >> account.name >> connectStr >> onlineStr)
        {
            // 转换布尔值
            account.ifconnect = (connectStr == "1" || connectStr == "true" || connectStr == "yes");
            account.ifonline = (onlineStr == "1" || onlineStr == "true" || onlineStr == "yes");
            typedData.push_back(account);
        }
        else
        {
            cerr << "行格式错误: " << line << endl;
        }
    }
    file.close();
    return typedData;
}
void WeiBoWriterLXY::writeTyped(const list<WeiBoaccountIfoLXY>& data)
{
    ofstream file("WeiBoaccountIfoLXY.txt");
    if (!file.is_open())
    {
        cerr << "WeiBoaccountIfoLXY.txt打开失败" << endl;
        return;
    }
    for (const auto& account : data)
    {
        file << account.WeiBoid << " "
            << account.WeiBopassword << " "
            << account.name << " "
            << (account.ifconnect ? 1 : 0) << " "  // 布尔值存为1/0
            << (account.ifonline ? 1 : 0)           // 布尔值存为1/0
            << "\n";
    }
    file.close();
}
void WeiBoViewerLXY::showTyped(const list<WeiBoaccountIfoLXY>& data)
{
    if (data.empty()) {
        cout << "没有微博账号数据" << endl;
        return;
    }
    int count = 1;
    for (const auto& account : data)
    {
        cout << "=== 微博账号 #" << count++ << " ===" << endl;
        cout << "微博 ID: " << account.WeiBoid << endl;
        cout << "密码: " << account.WeiBopassword << endl;
        cout << "昵称: " << account.name << endl;
        cout << "连接状态: " << (account.ifconnect ? "已连接" : "未连接") << endl;
        cout << "在线状态: " << (account.ifonline ? "在线" : "离线") << endl;
        cout << "--------------------------" << endl;
    }
}
