#ifndef GROUP_MANAGER_H
#define GROUP_MANAGER_H
#include "Group_Tools.h"
#include "Group.h"
class Group_ManagerLXY
{
public:
	void setFactory(std::unique_ptr<Group_FactoryLXY> factory);
	void setMainPlatform();
	void setQQPlatform();
	void setWeChatPlatform();
	void setWeiBoPlatform();

	// 业务接口
	void write_back();
	bool creategroup(int creatorId, const std::string& groupName);
	std::shared_ptr<GroupLXY> creategroupforsongroup(int creatorId, const std::string& groupName);
	bool deletegroup(int groupId, int requesterId);
	bool addmember(int groupId, int memberId, GroupRole role);

	bool deletemember(int groupId, int memberId, int requesterId);
	void showgroupmembers(int groupId);
	bool ismember(int groupId, int memberId);

	std::list<std::shared_ptr<GroupLXY>> getgroups(int id);

private:
	std::list<std::shared_ptr<GroupLXY>> groupslist; // 群组信息

	std::unique_ptr<Group_ReaderLXY> groupreader; // 读取工具
	std::unique_ptr<Group_WriterLXY> groupwriter; // 写入工具
	std::unique_ptr<Group_FactoryLXY> groupfactory; // 工厂
};

#endif // !GROUP_MANAGER_H