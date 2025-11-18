#include "Platform.h"
#include "Data_Manager.h"
#include <set>
using namespace std;

void PlatformLXY::addfriend(int id1, int id2)
{
	if (platformusermanager->searchifidlegal(id2) == true)
	{
		friendslist.push_back(make_shared<Friend_ShipLXY>(id1, id2));
		return friendsdatamanager->addfriends(id1, id2);
	}
	else
	{
		cout << "该用户不存在" << endl;
		return;
	}
}
void Main_PlatformLXY::addfriend(int id1, int id2)
{
	if (mainusermanager->searchifidlegal(id2) == true)
	{
		friendslist.push_back(make_shared<Friend_ShipLXY>(id1, id2));
		return friendsdatamanager->addfriends(id1, id2);
	}
	else
	{
		cout << "该用户不存在" << endl;
		return;
	}
}
void PlatformLXY::deletefriend(int id1, int id2)
{
	friendsdatamanager->deletefriends(id1, id2);
}
PlatformLXY::PlatformLXY()
	: datamanager(std::make_shared<Data_ManagerLXY>())
	, friendsdatamanager(std::make_shared<Friends_Data_ManagerLXY>())
	, platformusermanager(std::make_shared<Platform_User_ManagerLXY>())
	, groupmanager(std::make_shared<Group_ManagerLXY>()){}

QQ_PlatformLXY::QQ_PlatformLXY():PlatformLXY()
{
	datamanager->setQQFactory();
	friendsdatamanager->setQQPlatform();
	platformusermanager->setQQfactory();
	groupmanager->setQQPlatform();
}
WeChat_PlatformLXY::WeChat_PlatformLXY():PlatformLXY()
{
	datamanager->setWeChatFactory();
	friendsdatamanager->setWeChatPlatform();
	platformusermanager->setWeChatfactory();
	groupmanager->setWeChatPlatform();
}
WeiBo_PlatformLXY::WeiBo_PlatformLXY():PlatformLXY()
{
	datamanager->setWeiBoFactory();
	friendsdatamanager->setWeiBoPlatform();
	platformusermanager->setWeiBofactory();
	groupmanager->setWeiBoPlatform();
}
Main_PlatformLXY::Main_PlatformLXY():mainusermanager(make_unique<User_ManagerLXY>()),PlatformLXY()
{
	datamanager->setMainFactory();
	friendsdatamanager->setMainPlatform();
	groupmanager->setMainPlatform();
}
std::shared_ptr<UserLXY> Main_PlatformLXY::Mainsigninchecking(int id)
{
	auto user = mainusermanager->get_main_user_ifo(id);   // shared_ptr
	if (!user)
		std::cout << "该主账号不存在" << std::endl;
	return user;
}
LoginStatus PlatformLXY::Signin(int id)
{
	return platformusermanager->Signin(id);
}
LoginStatus PlatformLXY::Signup()
{
	return platformusermanager->Signup();
}
std::shared_ptr<UserLXY> Main_PlatformLXY::QQsigninchecking(int id)
{
	auto user = mainusermanager->get_main_user_ifo_by_QQ(id);
	if (!user)
		std::cout << "该QQ号并未绑定主平台" << std::endl;
	return user;
}

std::shared_ptr<UserLXY> Main_PlatformLXY::WeChatsigninchecking(int id)
{
	auto user = mainusermanager->get_main_user_ifo_by_WeChat(id);
	if (!user)
		std::cout << "该微信号并未绑定主平台" << std::endl;
	return user;
}

std::shared_ptr<UserLXY> Main_PlatformLXY::WeiBosigninchecking(int id)
{
	auto user = mainusermanager->get_main_user_ifo_by_WeiBo(id);
	if (!user)
		std::cout << "该微博号并未绑定主平台" << std::endl;
	return user;
}
LoginStatus Main_PlatformLXY::Main_Signin(int id)
{
	return mainusermanager->Signin(id);
}
LoginStatus Main_PlatformLXY::Main_Signup()
{
	return mainusermanager->Signup();
}
void Main_PlatformLXY::show_all_user()
{
	mainusermanager->show_all_user();
}
void PlatformLXY::show_all_user()
{
	platformusermanager->show_all_user();
}
void PlatformLXY::getfriends(int id)
{
	friendslist.clear();
	friendslist = friendsdatamanager->getfriends(id);
}
int PlatformLXY::showfriends(int id)//传入的id是主人的id，另一个id就是主人的朋友
{
	int count = 0;
	for (const auto& item : friendslist)
	{
		count++;
		if (id == item->id1)
		{
			cout << "好友id:" << item->id2 << "......" << "序号:" << count << endl;
		}
		else
		{
			cout <<"好友id" << item->id1 << "......" <<"序号" << count << endl;
		}
	}
	return count;
}
int PlatformLXY::showgroups(int id)
{
	int count = 0;
	for(const auto& group : grouplist)
	{
		count++;
		cout << "群id:" << group->showgroupid() << "......" << "群名:" << group->showgroupname() << "......" << "序号:" << count << endl;
	}
	return count;
}
void PlatformLXY::getgroups(int id)
{
	grouplist.clear();
	grouplist = groupmanager->getgroups(id);
}
int PlatformLXY::getfriendsid(int num, int id1)
{
	if (num < 0 || num >= static_cast<int>(friendslist.size()))
		return -1;

	auto it = friendslist.begin();
	std::advance(it, num);          // 把迭代器向前移动 num 步
	if (it->get()->id1 == id1)return it->get()->id2;
	else return it->get()->id1;
}
int PlatformLXY::getgroupsid(int num, int id1)
{
	if (num < 0 || num >= static_cast<int>(grouplist.size()))
		return -1;
	auto it = grouplist.begin();
	std::advance(it, num);          // 把迭代器向前移动 num 步
	return it->get()->showgroupid();
}
void Main_PlatformLXY::showoneuserbyid(int id)
{
	mainusermanager->showoneuserbyid(id);
}
void Main_PlatformLXY::writealluserifo()
{
	mainusermanager->save_all_user();
}

bool PlatformLXY::createGroup(int creatorId, const std::string& groupName)
{
	return groupmanager->creategroup(creatorId, groupName), true;
}
std::shared_ptr<GroupLXY> PlatformLXY::creategroupforsongroup(int creatorId, const std::string& groupName)
{
	return groupmanager->creategroupforsongroup(creatorId, groupName);
}
bool PlatformLXY::deleteGroup(int groupId, int requesterId)
{
	string errMsg;
	if (groupmanager->deletegroup(groupId, requesterId))
	{
		errMsg = "解散成功";
		cout << errMsg << endl;
		return true;
	}
	else
	{
		cout << errMsg << endl;
		errMsg = "解散失败，您不是群主";
		return false;
	}
}
bool PlatformLXY::exitGroup(int groupId, int memberId)
{
	string errMsg;
	if (groupmanager->deletemember(groupId, memberId, memberId))
	{
		errMsg = "退群成功";
		cout << errMsg << endl;
		return true;
	}
	else
	{
		errMsg = "退群失败";
		cout << errMsg << endl;
		return false;
	}
}
bool QQ_PlatformLXY::addGroup(int groupId, int memberId)
{
	//QQ平台直接加群
	string errMsg;
	if (groupmanager->addmember(groupId, memberId, GroupRole::Member))
	{
		errMsg = "加群成功";
		cout << errMsg << endl;
		return true;
	}
	else
	{
		errMsg = "加群失败";
		cout << errMsg << endl;
		return false;
	}
}
bool WeiBo_PlatformLXY::addGroup(int groupId, int memberId)
{
	//微博平台直接加群
	string errMsg;
	if (groupmanager->addmember(groupId, memberId, GroupRole::Member))
	{
		errMsg = "加群成功";
		cout << errMsg << endl;
		return true;
	}
	else
	{
		errMsg = "加群失败";
		cout << errMsg << endl;
		return false;
	}
}
bool Main_PlatformLXY::addGroup(int groupId, int memberId)
{
	//主平台直接加群
	string errMsg;
	if (groupmanager->addmember(groupId, memberId, GroupRole::Member))
	{
		errMsg = "加群成功";
		cout << errMsg << endl;
		return true;
	}
	else
	{
		errMsg = "加群失败";
		cout << errMsg << endl;
		return false;
	}
}
bool WeChat_PlatformLXY::addGroup(int groupId, int memberId)
{
	cout << "这个函数不该被调用的" << endl;
	return false;
}
bool QQ_PlatformLXY::inviteToGroup(int groupId, int memberId, int inviterId)
{
	//QQ平台直接加群
	string errMsg;
	if (groupmanager->addmember(groupId, memberId, GroupRole::Member))
	{
		errMsg = "邀请入群成功";
		cout << errMsg << endl;
		return true;
	}
	else
	{
		errMsg = "邀请入群失败";
		cout << errMsg << endl;
		return false;
	}
}
bool WeiBo_PlatformLXY::inviteToGroup(int groupId, int memberId, int inviterId)
{
	//微博平台直接加群
	string errMsg;
	if (groupmanager->addmember(groupId, memberId, GroupRole::Member))
	{
		errMsg = "邀请入群成功";
		cout << errMsg << endl;
		return true;
	}
	else
	{
		errMsg = "邀请入群失败";
		cout << errMsg << endl;
		return false;
	}
}
bool Main_PlatformLXY::inviteToGroup(int groupId, int memberId, int inviterId)
{
	//主平台直接加群
	string errMsg;
	if (groupmanager->addmember(groupId, memberId, GroupRole::Member))
	{
		errMsg = "邀请入群成功";
		cout << errMsg << endl;
		return true;
	}
	else
	{
		errMsg = "邀请入群失败";
		cout << errMsg << endl;
		return false;
	}
}
bool WeChat_PlatformLXY::inviteToGroup(int groupId, int memberId, int inviterId)
{
	//微信平台邀请入群
	//先检查一下邀请人和被邀请人是不是好友
	string errMsg;
	if (friendsdatamanager->isfriend(memberId,inviterId) == false)
	{
		errMsg = "邀请失败，您和被邀请人不是好友";
		cout << errMsg << endl;
		return false;
	}
	//再检查一下被邀请人是不是已经在群里了，可以把这个检查写到groupmanager里面
	if (groupmanager->ismember(groupId, memberId) == true)
	{
		errMsg = "邀请失败，被邀请人已经在群里了";
		cout << errMsg << endl;
		return false;
	}
	//最后加群
	if (groupmanager->addmember(groupId, memberId, GroupRole::Member))
	{
		errMsg = "邀请入群成功";
		cout << errMsg << endl;
		return true;
	}
	else
	{
		errMsg = "邀请入群失败";
		cout << errMsg << endl;
		return false;
	}
	return false;
}
list<GroupMemberLXY> PlatformLXY::getGroupMembers(int groupId)//从groupslist中搜出来
{
	for (auto& group : grouplist)
	{
		if (group->showgroupid() == groupId)//找到了对应的GroupLXY
		{
			return group->showallmembersifo();
		}
	}
	return {};
}
void QQ_PlatformLXY::createsongroup(int id1, int groupid)
{
	using namespace std;

	/* 1. 找到老群*/
	shared_ptr<GroupLXY> oldGroup;
	for (auto& g : grouplist)
		if (g->showgroupid() == groupid) { oldGroup = g; break; }

	if (!oldGroup) {
		cout << "未找到该群，无法创建子群！\n";
		return;
	}

	/*2. 把老群成员倒进一个 list 并编号 */
	list<GroupMemberLXY> memList = oldGroup->showallmembersifo();
	if (memList.empty()) {
		cout << "老群暂无成员，子群创建取消。\n";
		return;
	}

	cout << "请选择要带入子群的成员（输入序号，0 结束）：\n";
	int idx = 1;
	for (auto it = memList.begin(); it != memList.end(); ++it, ++idx)
		cout << idx << ". 用户ID: " << it->memberid << endl;

	/*3. 让用户挑序号*/
	list<int> chosenPos;         
	int no;
	cout << "请输入序号（可多次输入，0 结束）：";
	while (cin >> no && no != 0) {
		if (no < 1 || no > static_cast<int>(memList.size())) {
			cout << "序号非法，请重输：";
			continue;
		}
		// 查重
		bool dup = false;
		for (int p : chosenPos) if (p == no) { dup = true; break; }
		if (!dup) chosenPos.push_back(no);
		else      cout << "已选过，跳过。\n";
	}

	if (chosenPos.empty()) {
		cout << "未选择任何成员，子群创建取消。\n";
		return;
	}

	/* 4. 创建子群 */
	cout << "请输入子群名称：";
	string name;
	cin >> name;

	shared_ptr<GroupLXY> newGroup = creategroupforsongroup(id1, name);
	int newId = newGroup->showgroupid();

	/* 5. 按序号把成员加进去 */
	int cnt = 0;
	for (int pos : chosenPos) {
		auto it = memList.begin();
		advance(it, pos - 1);                 // list 只能顺序走
		int mid = it->memberid;
		if (mid == id1) continue;             // 创建人已在新群，跳过
		if (groupmanager->addmember(newId, mid, GroupRole::Member))
			++cnt;
	}

	cout << "已成功添加 " << cnt << " 位成员到子群！\n";
	cout << "按 1 确认创建，按 0 撤销：";
	int confirm;
	cin >> confirm;
	if (confirm != 1) {
		groupmanager->deletegroup(newId, id1);
		cout << "子群已撤销。\n";
	}
	else {
		cout << "子群创建完成！群ID=" << newId << '\n';
	}
}
void WeChat_PlatformLXY::createsongroup(int id, int groupid)
{
	cout << "微信群不支持创建子群!" << endl;
}
// WeiBo_PlatformLXY.cpp
void WeiBo_PlatformLXY::createsongroup(int id1, int groupid)
{
	using namespace std;

	shared_ptr<GroupLXY> oldGroup;
	for (auto& g : grouplist)
		if (g->showgroupid() == groupid) { oldGroup = g; break; }

	if (!oldGroup) {
		cout << "未找到该群，无法创建子群！\n";
		return;
	}

	list<GroupMemberLXY> memList = oldGroup->showallmembersifo();
	if (memList.empty()) {
		cout << "老群暂无成员，子群创建取消。\n";
		return;
	}

	cout << "请选择要带入子群的成员（输入序号，0 结束）：\n";
	int idx = 1;
	for (auto it = memList.begin(); it != memList.end(); ++it, ++idx)
		cout << idx << ". 用户ID: " << it->memberid << endl;
		

	list<int> chosenPos;
	int no;
	cout << "请输入序号（可多次输入，0 结束）：";
	while (cin >> no && no != 0) {
		if (no < 1 || no > static_cast<int>(memList.size())) {
			cout << "序号非法，请重输：";
			continue;
		}
		bool dup = false;
		for (int p : chosenPos) if (p == no) { dup = true; break; }
		if (!dup) chosenPos.push_back(no);
		else      cout << "已选过，跳过。\n";
	}

	if (chosenPos.empty()) {
		cout << "未选择任何成员，子群创建取消。\n";
		return;
	}

	cout << "请输入子群名称：";
	string name;
	cin >> name;

	shared_ptr<GroupLXY> newGroup = creategroupforsongroup(id1, name);
	int newId = newGroup->showgroupid();

	int cnt = 0;
	for (int pos : chosenPos) {
		auto it = memList.begin();
		advance(it, pos - 1);
		int mid = it->memberid;
		if (mid == id1) continue;
		if (groupmanager->addmember(newId, mid, GroupRole::Member))
			++cnt;
	}

	cout << "已成功添加 " << cnt << " 位成员到子群！\n";
	cout << "按 1 确认创建，按 0 撤销：";
	int confirm;
	cin >> confirm;
	if (confirm != 1) {
		groupmanager->deletegroup(newId, id1);
		cout << "子群已撤销。\n";
	}
	else {
		cout << "子群创建完成！群ID=" << newId << '\n';
	}
}
#include "Platform.h"   // 里面有类声明
#include <iostream>
#include <string>
#include <list>
using namespace std;

void Main_PlatformLXY::createsongroup(int id1, int groupid)
{
	/*-------- 1. 找老群（用的是主平台自己的 grouplist） --------*/
	shared_ptr<GroupLXY> oldGroup;
	for (auto& g : grouplist)
		if (g->showgroupid() == groupid) { oldGroup = g; break; }

	if (!oldGroup) {
		cout << "未找到该群，无法创建子群！\n";
		return;
	}

	/*-------- 2. 列出成员 --------*/
	list<GroupMemberLXY> memList = oldGroup->showallmembersifo();
	if (memList.empty()) {          // 理论上不会空，因为至少有群主
		cout << "老群无成员，子群创建取消。\n";
		return;
	}

	cout << "请选择要带入子群的成员（输入序号，0 结束）：\n";
	int idx = 1;
	for (auto it = memList.begin(); it != memList.end(); ++it, ++idx)
		cout << idx << ". 用户ID: " << it->memberid << endl;
		

	/*-------- 3. 手工选序号 + 手工去重 --------*/
	list<int> chosenPos;          // 只存 1-based 序号
	int no;
	cout << "请输入序号（可多次输入，0 结束）：";
	while (cin >> no && no != 0) {
		if (no < 1 || no > static_cast<int>(memList.size())) {
			cout << "序号非法，请重输：";
			continue;
		}
		bool dup = false;
		for (int p : chosenPos) if (p == no) { dup = true; break; }
		if (!dup) chosenPos.push_back(no);
		else      cout << "已选过，跳过。\n";
	}

	if (chosenPos.empty()) {
		cout << "未选择任何成员，子群创建取消。\n";
		return;
	}

	/*-------- 4. 创建子群 --------*/
	cout << "请输入子群名称：";
	string name;
	cin >> name;

	shared_ptr<GroupLXY> newGroup = creategroupforsongroup(id1, name);
	int newId = newGroup->showgroupid();

	/*-------- 5. 把选中成员拉进来 --------*/
	int cnt = 0;
	for (int pos : chosenPos) {
		auto it = memList.begin();
		advance(it, pos - 1);   // 走 pos-1 步
		int mid = it->memberid;
		if (mid == id1) continue;   // 创建人已存在
		if (groupmanager->addmember(newId, mid, GroupRole::Member))
			++cnt;
	}

	cout << "已成功添加 " << cnt << " 位成员到子群！\n";
	cout << "按 1 确认创建，按 0 撤销：";
	int confirm;
	cin >> confirm;
	if (confirm != 1) {
		groupmanager->deletegroup(newId, id1);
		cout << "子群已撤销。\n";
	}
	else {
		cout << "主平台子群创建完成！群ID=" << newId << '\n';
		groupmanager->write_back(); // ④ 写回主平台数据文件
	}
}