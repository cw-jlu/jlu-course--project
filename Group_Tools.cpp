#include "Group_Tools.h"
#include "Group.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
list<GroupInfoLXY> Main_Group_ReaderLXY::readTyped()
{
    list<GroupInfoLXY> typedData;
    ifstream file("MainGroupInfoLXY.txt");
    if (!file.is_open())
    {
        cerr << "MainGroupInfoLXY.txt打开失败或文件不存在" << endl;
        return typedData;  // 返回空列表
    }
    string line;
    while (getline(file, line))//一行一行读
    {
        if (line.empty()) continue;  // 跳过空行
        istringstream iss(line);
        GroupInfoLXY account;
        // 只读 3 个字段，后面多余内容直接忽略
        if (!(iss >> account.groupid >> account.groupname >> account.creatorId))
        {
            cerr << "字段不足或格式错误，跳过整行: " << line << endl;
            continue;
        }
        typedData.push_back(account);
    }
    file.close();
    ifstream membersFile("MainGroupMembersLXY.txt");
    if (!membersFile.is_open())
    {
        cerr << "MainGroupMembersLXY.txt打开失败或文件不存在" << endl;
        return typedData;  // 返回空列表
    }
    string memberLine;
    while (getline(membersFile, memberLine))//一行一行读
    {
        if (memberLine.empty()) continue;  // 跳过空行
        istringstream iss(memberLine);
        GroupMemberLXY member;
        int roleVal = 0;                     // 先读成 int
        if (!(iss >> member.groupid >> member.memberid >> roleVal))
        {
            cerr << "字段不足或格式错误，跳过整行: " << memberLine << endl;
            continue;
        }
        member.role = static_cast<GroupRole>(roleVal);   // 安全转枚举
        // 找到对应的群，添加成员
        auto it = find_if(typedData.begin(), typedData.end(),
            [&](const GroupInfoLXY& g) { return g.groupid == member.groupid; });
        if (it != typedData.end())
        {
            it->members.push_back(member);
        }
        else
        {
            cerr << "未找到对应的群，跳过成员: " << memberLine << endl;
        }
    }
    membersFile.close();
    return typedData;
} 
list<GroupInfoLXY> QQ_Group_ReaderLXY::readTyped()
{
    list<GroupInfoLXY> typedData;
    ifstream file("QQGroupInfoLXY.txt");
    if (!file.is_open())
    {
        cerr << "QQGroupInfoLXY.txt打开失败或文件不存在" << endl;
        return typedData;  // 返回空列表
    }
    string line;
    while (getline(file, line))//一行一行读
    {
        if (line.empty()) continue;  // 跳过空行
        istringstream iss(line);
        GroupInfoLXY account;
        // 只读 3 个字段，后面多余内容直接忽略
        if (!(iss >> account.groupid >> account.groupname >> account.creatorId))
        {
            cerr << "字段不足或格式错误，跳过整行: " << line << endl;
            continue;
        }
        typedData.push_back(account);
    }
    file.close();

    ifstream membersFile("QQGroupMembersLXY.txt");
    if (!membersFile.is_open())
    {
        cerr << "QQGroupMembersLXY.txt打开失败或文件不存在" << endl;
        return typedData;  // 返回空列表
    }
    string memberLine;
    while (getline(membersFile, memberLine))//一行一行读
    {
        if (memberLine.empty()) continue;  // 跳过空行
        istringstream iss(memberLine);
        GroupMemberLXY member;
        int roleVal = 0;                     // 先读成 int
        if (!(iss >> member.groupid >> member.memberid >> roleVal))
        {
            cerr << "字段不足或格式错误，跳过整行: " << memberLine << endl;
            continue;
        }
        member.role = static_cast<GroupRole>(roleVal);   // 安全转枚举
        // 找到对应的群，添加成员
        auto it = find_if(typedData.begin(), typedData.end(),
            [&](const GroupInfoLXY& g) { return g.groupid == member.groupid; });
        if (it != typedData.end())
        {
            it->members.push_back(member);
        }
        else
        {
            cerr << "未找到对应的群，跳过成员: " << memberLine << endl;
        }
    }
    membersFile.close();

    return typedData;
}
list<GroupInfoLXY> WeChat_Group_ReaderLXY::readTyped()
{
    list<GroupInfoLXY> typedData;
    ifstream file("WeChatGroupInfoLXY.txt");
    if (!file.is_open())
    {
        cerr << "WeChatGroupInfoLXY.txt打开失败或文件不存在" << endl;
        return typedData;  // 返回空列表
    }
    string line;
    while (getline(file, line))//一行一行读
    {
        if (line.empty()) continue;  // 跳过空行
        istringstream iss(line);
        GroupInfoLXY account;
        // 只读 3 个字段，后面多余内容直接忽略
        if (!(iss >> account.groupid >> account.groupname >> account.creatorId))
        {
            cerr << "字段不足或格式错误，跳过整行: " << line << endl;
            continue;
        }
        typedData.push_back(account);
    }
    file.close();
    ifstream membersFile("WeChatGroupMembersLXY.txt");
    if (!membersFile.is_open())
    {
        cerr << "WeChatGroupMembersLXY.txt打开失败或文件不存在" << endl;
        return typedData;  // 返回空列表
    }
    string memberLine;
    while (getline(membersFile, memberLine))//一行一行读
    {
        if (memberLine.empty()) continue;  // 跳过空行
        istringstream iss(memberLine);
        GroupMemberLXY member;
        int roleVal = 0;                     // 先读成 int
        if (!(iss >> member.groupid >> member.memberid >> roleVal))
        {
            cerr << "字段不足或格式错误，跳过整行: " << memberLine << endl;
            continue;
        }
        member.role = static_cast<GroupRole>(roleVal);   // 安全转枚举
        // 找到对应的群，添加成员
        auto it = find_if(typedData.begin(), typedData.end(),
            [&](const GroupInfoLXY& g) { return g.groupid == member.groupid; });
        if (it != typedData.end())
        {
            it->members.push_back(member);
        }
        else
        {
			cerr << "未找到对应的群，跳过成员: " << memberLine << endl;
        }
    }
    membersFile.close();
	return typedData;
}
list <GroupInfoLXY> WeiBo_Group_ReaderLXY::readTyped()
{
    list<GroupInfoLXY> typedData;
    ifstream file("WeiBoGroupInfoLXY.txt");
    if (!file.is_open())
    {
        cerr << "WeiBoGroupInfoLXY.txt打开失败或文件不存在" << endl;
        return typedData;  // 返回空列表
    }
    string line;
    while (getline(file, line))//一行一行读
    {
        if (line.empty()) continue;  // 跳过空行
        istringstream iss(line);
        GroupInfoLXY account;
        // 只读 3 个字段，后面多余内容直接忽略
        if (!(iss >> account.groupid >> account.groupname >> account.creatorId))
        {
            cerr << "字段不足或格式错误，跳过整行: " << line << endl;
            continue;
        }
        typedData.push_back(account);
    }
    file.close();
    ifstream membersFile("WeiBoGroupMembersLXY.txt");
    if (!membersFile.is_open())
    {
        cerr << "WeiBoGroupMembersLXY.txt打开失败或文件不存在" << endl;
        return typedData;  // 返回空列表
    }
    string memberLine;
    while (getline(membersFile, memberLine))//一行一行读
    {
        if (memberLine.empty()) continue;  // 跳过空行
        istringstream iss(memberLine);
        GroupMemberLXY member;
        int roleVal = 0;                     // 先读成 int
        if (!(iss >> member.groupid >> member.memberid >> roleVal))
        {
            cerr << "字段不足或格式错误，跳过整行: " << memberLine << endl;
            continue;
        }
        member.role = static_cast<GroupRole>(roleVal);   // 安全转枚举
        // 找到对应的群，添加成员
        auto it = find_if(typedData.begin(), typedData.end(),
            [&](const GroupInfoLXY& g) { return g.groupid == member.groupid; });
        if (it != typedData.end())
        {
            it->members.push_back(member);
        }
        else
        {
			cerr << "未找到对应的群，跳过成员: " << memberLine << endl;
            }
    }
	membersFile.close();
	return typedData;
}
void Main_Group_WriterLXY::writeTyped(const std::list<std::shared_ptr<GroupInfoLXY>>& data)
{
    std::ofstream grpFile("MainGroupInfoLXY.txt");
    if (!grpFile) {
        std::cerr << "MainGroupInfoLXY.txt 打开失败\n";
        return;
    }
    for (const auto& g : data) {
        grpFile << g->groupid << ' '
            << g->groupname << ' '
            << g->creatorId << '\n';
    }
    grpFile.close();

    std::ofstream memFile("MainGroupMembersLXY.txt");
    if (!memFile) {
        std::cerr << "MainGroupMembersLXY.txt 打开失败\n";
        return;
    }
    for (const auto& g : data) {
        for (const auto& m : g->members) {
            memFile << m.groupid << ' '
                << m.memberid << ' '
                << static_cast<int>(m.role) << '\n';
        }
    }
    memFile.close();
}
void QQ_Group_WriterLXY::writeTyped(const list<shared_ptr<GroupInfoLXY>>& data)
{
    ofstream file("QQGroupInfoLXY.txt");
    if (!file.is_open())
    {
        cerr << "QQGroupInfoLXY.txt打开失败" << endl;
        return;
    }
    for (const auto& group : data)
    {
        file << group->groupid << " "
            << group->groupname << " "
            << group->creatorId
            << "\n";
    }
    file.close();
    ofstream membersFile("QQGroupMembersLXY.txt");
    if (!membersFile.is_open())
    {
        cerr << "QQGroupMembersLXY.txt打开失败" << endl;
        return;
    }
    for (const auto& group : data)
    {
        for (const auto& member : group->members)
        {
            membersFile << member.groupid << " "
                << member.memberid << " "
                << static_cast<int>(member.role)  // 枚举转 int 存储
                << "\n";
        }
    }
    membersFile.close();
}
void WeChat_Group_WriterLXY::writeTyped(const std::list<shared_ptr<GroupInfoLXY>>& data)
{
    std::ofstream grpFile("WeChatGroupInfoLXY.txt");
    if (!grpFile) {
        std::cerr << "WeChatGroupInfoLXY.txt 打开失败\n";
        return;
    }
    for (const auto& g : data) {
        grpFile << g->groupid << ' '
            << g->groupname << ' '
            << g->creatorId << '\n';
    }
    grpFile.close();

    std::ofstream memFile("WeChatGroupMembersLXY.txt");
    if (!memFile) {
        std::cerr << "WeChatGroupMembersLXY.txt 打开失败\n";
        return;
    }
    for (const auto& g : data) {
        for (const auto& m : g->members) {
            memFile << m.groupid << ' '
                << m.memberid << ' '
                << static_cast<int>(m.role) << '\n';
        }
    }
    memFile.close();
}
void WeiBo_Group_WriterLXY::writeTyped(const std::list<shared_ptr<GroupInfoLXY>>& data)
{
    std::ofstream grpFile("WeiBoGroupInfoLXY.txt");
    if (!grpFile) {
        std::cerr << "WeiBoGroupInfoLXY.txt 打开失败\n";
        return;
    }
    for (const auto& g : data) {
        grpFile << g->groupid << ' '
            << g->groupname << ' '
            << g->creatorId << '\n';
    }
    grpFile.close();

    std::ofstream memFile("WeiBoGroupMembersLXY.txt");
    if (!memFile) {
        std::cerr << "WeiBoGroupMembersLXY.txt 打开失败\n";
        return;
    }
    for (const auto& g : data) {
        for (const auto& m : g->members) {
            memFile << m.groupid << ' '
                << m.memberid << ' '
                << static_cast<int>(m.role) << '\n';
        }
    }
    memFile.close();
}
std::unique_ptr<Group_ReaderLXY> Main_Group_FactoryLXY::createReader()
{
    return std::make_unique<Main_Group_ReaderLXY>();
}

std::unique_ptr<Group_WriterLXY> Main_Group_FactoryLXY::createWriter()
{
    return std::make_unique<Main_Group_WriterLXY>();
}
std::unique_ptr<Group_ReaderLXY> QQ_Group_FactoryLXY::createReader()
{
    return std::make_unique<QQ_Group_ReaderLXY>();
}

std::unique_ptr<Group_WriterLXY> QQ_Group_FactoryLXY::createWriter()
{
    return std::make_unique<QQ_Group_WriterLXY>();
}
std::unique_ptr<Group_ReaderLXY> WeChat_Group_FactoryLXY::createReader()
{
    return std::make_unique<WeChat_Group_ReaderLXY>();
}

std::unique_ptr<Group_WriterLXY> WeChat_Group_FactoryLXY::createWriter()
{
    return std::make_unique<WeChat_Group_WriterLXY>();
}
std::unique_ptr<Group_ReaderLXY> WeiBo_Group_FactoryLXY::createReader()
{
    return std::make_unique<WeiBo_Group_ReaderLXY>();
}

std::unique_ptr<Group_WriterLXY> WeiBo_Group_FactoryLXY::createWriter()
{
    return std::make_unique<WeiBo_Group_WriterLXY>();
}