#include "Group_Manager.h"
#include <iostream>
using namespace std;
void Group_ManagerLXY::setFactory(std::unique_ptr<Group_FactoryLXY> factory)
{
    groupfactory = std::move(factory);
    groupreader  = groupfactory->createReader();
    groupwriter  = groupfactory->createWriter();

    // 把整个 list 包成 shared_ptr
    auto rawList = groupreader->readTyped();              // 先读值
    // 把值列表搬进 shared_ptr 列表
	for (auto& g : rawList)
	{
		groupslist.push_back(make_shared<GroupLXY>(g));
	}
}
void Group_ManagerLXY::setMainPlatform()
{
	setFactory(std::make_unique<Main_Group_FactoryLXY>());
}
void Group_ManagerLXY::setQQPlatform()
{
	setFactory(std::make_unique<QQ_Group_FactoryLXY>());
}
void Group_ManagerLXY::setWeChatPlatform()
{
	setFactory(std::make_unique<WeChat_Group_FactoryLXY>());
}
void Group_ManagerLXY::setWeiBoPlatform()
{
	setFactory(std::make_unique<WeiBo_Group_FactoryLXY>());
}
void Group_ManagerLXY::write_back()
{
	if (!groupwriter) {
		std::cout << "写入工具未初始化，请先 setFactory。" << std::endl;
		return;
	}

	// 把 GroupLXY 内部数据转发给 Writer
	std::list<std::shared_ptr<GroupInfoLXY>> temp;
	for (const auto& grp : groupslist)
		temp.push_back(std::make_shared<GroupInfoLXY>(grp->getgroupifo()));

	groupwriter->writeTyped(temp);
}
bool Group_ManagerLXY::creategroup(int creatorId, const std::string& groupName)
{
	if (groupName.empty()) return false;
	GroupInfoLXY newGroupInfo;
	if(groupslist.empty())
	{
		newGroupInfo.groupid = 1; // 若无群则为1
		cout << "创建成功，群ID为1" << endl;
	}
	else
	{
		newGroupInfo.groupid = groupslist.back()->showgroupid() + 1; // 新群ID为当前最大ID+1
		cout << "创建成功，群ID为" << newGroupInfo.groupid << endl;
	}
	newGroupInfo.groupname = groupName;
	newGroupInfo.creatorId = creatorId;
	newGroupInfo.members.push_back({ newGroupInfo.groupid, creatorId, GroupRole::Owner });
	groupslist.push_back(std::make_shared<GroupLXY>(newGroupInfo));
	write_back();
	return true;
}
std::shared_ptr<GroupLXY> Group_ManagerLXY::creategroupforsongroup(int creatorId, const std::string& groupName)
{
	GroupInfoLXY newGroupInfo;
	if (groupslist.empty())
	{
		newGroupInfo.groupid = 1; // 若无群则为1
		cout << "创建成功，群ID为1" << endl;
	}
	else
	{
		newGroupInfo.groupid = groupslist.back()->showgroupid() + 1; // 新群ID为当前最大ID+1
		cout << "创建成功，群ID为" << newGroupInfo.groupid << endl;
	}
	newGroupInfo.groupname = groupName;
	newGroupInfo.creatorId = creatorId;
	newGroupInfo.members.push_back({ newGroupInfo.groupid, creatorId, GroupRole::Owner });
	std::shared_ptr<GroupLXY> group = std::make_shared<GroupLXY>(newGroupInfo);
	groupslist.push_back(group);
	write_back();
	return group;
}
bool Group_ManagerLXY::deletegroup(int groupId, int requesterId)
{
    for(auto it : groupslist)
	{
		if(it->showgroupid() == groupId)
		{
			if(it->showcreatorid() == requesterId)
			{
				groupslist.remove(it);
				write_back();
				return true;
			}
			else
			{
				cout << "只有群主可以解散群聊" << endl;
				return false;
			}
		}
	}
	return false;
}

/* ---------- 成员进出 ---------- */
bool Group_ManagerLXY::addmember(int groupId, int memberId, GroupRole role)
{
	for(auto& it : groupslist)
	{
		if(it->showgroupid() == groupId)
		{
			if(it->ismember(memberId))
			{
				cout << "该用户已经在群里了" << endl;
				return false;
			}
			else
			{
				it->addmember(memberId,role);
				write_back();
				return true;
			}
		}
	}
	cout << "群聊不存在" << endl;
	return false;
}

bool Group_ManagerLXY::deletemember(int groupId, int memberId, int requesterId)//这里不判断是不是管理员或群主，把这个下放到Group里面
{
   for(auto& it : groupslist)
   {
	   if(it->showgroupid() == groupId)
	   {
		   it->deletemember(memberId,requesterId);
		   return true;
	   }
   }
   return false;
}

/* ---------- 查询 ---------- */
void Group_ManagerLXY::showgroupmembers(int groupId)
{
    
}//今天就先写到这里，明天要把groupmanager和platform结合起来，再把接口往上传递，仿照friends和user一样，然后在system中写引导用户，测试一下基本上就完工了。
bool Group_ManagerLXY::ismember(int groupId, int memberId)
{
	for(auto& it : groupslist)
	{
		if(it->showgroupid() == groupId)
		{
			return it->ismember(memberId);
		}
	}
	return false;
}
std::list<std::shared_ptr<GroupLXY>> Group_ManagerLXY::getgroups(int id)
{
	std::list<std::shared_ptr<GroupLXY>> result;
	for (const auto& group : groupslist)
	{
		if (group->ismember(id))
		{
			result.push_back(group);
		}
	}
	return result;
}