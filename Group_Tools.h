#ifndef GROUP_TOOLS
#define GROUP_TOOLS
#include <list>
#include <string>
#include <memory>
enum class GroupRole : char   // 单角色，互斥
{
	Owner = 0,
	Admin = 1,
	Member = 2
};

struct GroupMemberLXY
{
	int groupid;    // 冗余存一份，查群快
	int memberid;
	GroupRole  role;      
};

struct GroupInfoLXY          
{
	int        groupid;
	std::string groupname;
	std::list<GroupMemberLXY> members;   
	int        creatorId;   // 冗余存一份，查群快
};
class Group_ReaderLXY
{
public:
	virtual std::list<GroupInfoLXY> readTyped() = 0;
};
class Main_Group_ReaderLXY : public Group_ReaderLXY
{
	public:
	std::list<GroupInfoLXY> readTyped() override;
};
class QQ_Group_ReaderLXY : public Group_ReaderLXY
{
	public:
	std::list<GroupInfoLXY> readTyped() override;
};
class WeChat_Group_ReaderLXY : public Group_ReaderLXY
{
	public:
	std::list<GroupInfoLXY> readTyped() override;
};
class WeiBo_Group_ReaderLXY : public Group_ReaderLXY
{
	public:
	std::list<GroupInfoLXY> readTyped() override;
};
class Group_WriterLXY
{
	public:
	virtual void writeTyped(const std::list<std::shared_ptr<GroupInfoLXY>>& data) = 0;
};
class Main_Group_WriterLXY : public Group_WriterLXY
{
	public:
	void writeTyped(const std::list<std::shared_ptr<GroupInfoLXY>>& data) override;
};
class QQ_Group_WriterLXY : public Group_WriterLXY
{
	public:
	void writeTyped(const std::list<std::shared_ptr<GroupInfoLXY>>& data) override;
};
class WeChat_Group_WriterLXY : public Group_WriterLXY
{
	public:
	void writeTyped(const std::list<std::shared_ptr<GroupInfoLXY>>& data) override;
};
class WeiBo_Group_WriterLXY : public Group_WriterLXY
{
	public:
	void writeTyped(const std::list<std::shared_ptr<GroupInfoLXY>>& data) override;
};
class Group_FactoryLXY
{
	public:
	virtual std::unique_ptr<Group_ReaderLXY> createReader() = 0;
	virtual std::unique_ptr<Group_WriterLXY> createWriter() = 0;
};
class Main_Group_FactoryLXY : public Group_FactoryLXY
{
	public:
	std::unique_ptr<Group_ReaderLXY> createReader() override;
	std::unique_ptr<Group_WriterLXY> createWriter() override;
};
class QQ_Group_FactoryLXY : public Group_FactoryLXY
{
	public:
		std::unique_ptr<Group_ReaderLXY> createReader() override;
	std::unique_ptr<Group_WriterLXY> createWriter() override;
};
class WeChat_Group_FactoryLXY : public Group_FactoryLXY
{
	public:
	std::unique_ptr<Group_ReaderLXY> createReader() override;
	std::unique_ptr<Group_WriterLXY> createWriter() override;
};
class WeiBo_Group_FactoryLXY : public Group_FactoryLXY
{
	public:
	std::unique_ptr<Group_ReaderLXY> createReader() override;
	std::unique_ptr<Group_WriterLXY> createWriter() override;
};
#endif // !GROUP_TOOLS
