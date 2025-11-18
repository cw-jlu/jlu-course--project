#include "Group.h"
#include "Group_Tools.h"
#include "Useful_Tools.h"
int GroupLXY::showgroupid()
{
	return groupifo.groupid;
}
std::string GroupLXY::showgroupname()
{
	return groupifo.groupname;
}
void GroupLXY::showallmembers()
{
	std::cout << "群组 '" << groupifo.groupname << "' 成员列表：" << std::endl;
	for (const auto& member : groupifo.members)
	{
		std::string roleStr;
		switch (member.role)
		{
		case GroupRole::Owner:
			roleStr = "群主";
			break;
		case GroupRole::Admin:
			roleStr = "管理员";
			break;
		case GroupRole::Member:
			roleStr = "成员";
			break;
		default:
			roleStr = "未知角色";
			break;
		}
		std::cout << "成员ID: " << member.memberid << ", 角色: " << roleStr << std::endl;
	}
}
std::list<GroupMemberLXY> GroupLXY::showallmembersifo()
{
	return groupifo.members;
}
int GroupLXY::showcreatorid()
{
	return groupifo.creatorId;
}
GroupInfoLXY& GroupLXY::getgroupifo()
{
	return groupifo;
}
bool GroupLXY::addmember(int memberid, GroupRole role)
{
	if (ismember(memberid))
	{
		std::cout << "用户 " << memberid << " 已经是群成员，无法重复添加。" << std::endl;
		return false;
	}
	GroupMemberLXY newMember{ groupifo.groupid, memberid, static_cast<GroupRole>(role) };
	groupifo.members.push_back(newMember);
	return true;
}
bool GroupLXY::deletemember(int memberId, int requesterId)
{
	// 1. 被踢人必须在群里
	auto memIt = std::find_if(groupifo.members.begin(), groupifo.members.end(),
		[&](const GroupMemberLXY& m) { return m.memberid == memberId; });
	if (memIt == groupifo.members.end()) {
		std::cout << "被踢人不在群内。\n";
		return false;
	}

	// 2. 请求者必须在群里
	auto reqIt = std::find_if(groupifo.members.begin(), groupifo.members.end(),
		[&](const GroupMemberLXY& m) { return m.memberid == requesterId; });
	if (reqIt == groupifo.members.end()) {
		std::cout << "请求者不在群内，无法执行删除操作。\n";
		return false;
	}

	// 3. 如果是自己踢自己，相当于退群，不用检查管理员权限
	bool ifself = false;
	if (memberId == requesterId)
	{
		ifself = true;
	}
	// 4. 群主不能退群，只能解散群聊
	if (reqIt->role == GroupRole::Owner && memIt->role == GroupRole::Owner)
	{
		delaycout("群主不能退群，只能解散群聊!");
		return false;
	}
	// 5. 权限：群主 或 管理员（且不能踢群主）
	if (reqIt->role != GroupRole::Owner &&
		(reqIt->role != GroupRole::Admin || memIt->role == GroupRole::Owner)) {
		if (ifself == false)
		{
			std::cout << "权限不足，无法删除成员。\n";
			return false;
		}
	}
	// 6. 只删当前这一位
	groupifo.members.erase(memIt);
	return true;
}
bool GroupLXY::ismember(int memberid)
{
	for (auto& member : groupifo.members)
	{
		if (memberid == member.memberid)
		{
			return true;
		}
	}
	return false;
}