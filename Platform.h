#ifndef Platform
#define Platform
#include "Data_Manager.h"
#include "User_Manager.h"
#include "Friends_Data_Manager.h"
#include "Group_Manager.h"
class PlatformLXY
{
public:
	PlatformLXY();

	virtual void addfriend(int id1 , int id2);//几个平台加好友，删好友的操作差不多，直接写到父类算了，免得每个子类都要写一遍
	//其他三个平台一样，main不同，所以main平台单独写

	virtual void deletefriend(int id1 , int id2);//这里都只是文件操作，具体引导用户加删好友，写到别的函数里面

	virtual LoginStatus Signin(int id);//三个平台的直接登录函数,相当于判定一下有没有登录成功
	virtual LoginStatus Signup();//四个平台的直接注册

	virtual LoginStatus Main_Signin(int id) { std::cout << "不小心进入了Platform的基类"; return LoginStatus::REGISTER_FAILED; }//主平台登录
	virtual LoginStatus Main_Signup() { std::cout << "不小心进入了Platform的基类"; return LoginStatus::REGISTER_FAILED;}//主平台注册
	
	//searchfriend后面确定了再写
	virtual void show_all_user();

	//这三个是检查一下账户是否绑定,如果绑定了就把该User返回，具体登录操作利用系统层来完成
	virtual	std::shared_ptr<UserLXY>  QQsigninchecking(int id) { std::cout << "不小心进入了Platform的基类" ; return nullptr; }
	virtual std::shared_ptr<UserLXY>  WeChatsigninchecking(int id) { std::cout << "不小心进入了Platform的基类" ; return nullptr; }
	virtual std::shared_ptr<UserLXY>  WeiBosigninchecking(int id) { std::cout << "不小心进入了Platform的基类"; return nullptr; }
	virtual std::shared_ptr<UserLXY>  Mainsigninchecking(int id) { std::cout << "不小心进入了Platform的基类"; return nullptr; }

	int showfriends(int id); //显示某个用户的所有好友,既是展示，也是提供选项选择
	void getfriends(int id);//通过id搜出来所有好友链表,并且更新类的私有链表，需要改进一下，因为每次输入都是主平台的id，内部弄一个id转化
	//但是不能这样写，因为这样会丧失多态，还是在system层面传入当前用户的id比较好，所以在system中写四个函数，分别调用这四个平台的getfriends，在system中区分id

	int showgroups(int id);//显示某个用户的所有群聊，这里不用虚函数，因为多态写好的
	void getgroups(int id);//通过id搜出来所有群聊链表,并且更新类的私有链表，这里不用虚函数，因为多态写好的
	virtual void createsongroup(int id1, int groupid) {};

	virtual void QQbinding(UserLXY& user) {}
	virtual void WeChatbinding(UserLXY& user) {}
	virtual void WeiBobinding(UserLXY& user) {}
	int getfriendsid(int num,int id1);
	int getgroupsid(int num, int id1);

	virtual void showoneuserbyid(int id) {};//这个函数main平台专有

	virtual void writealluserifo() {}


	/*接下来写一些群组的函数，要注意，各个平台的差距从platform层面开始体现了*/

	/*多态的好处来了，这里我不需要用虚函数来写这几个群聊函数，加群除外。因为各个工具都在构造函数里面多态区分好了*/

	/*========  群生命周期  ========*/
	// 创建群聊
	bool createGroup(int creatorId, const std::string& groupName);
	std::shared_ptr<GroupLXY> creategroupforsongroup(int createID, const std::string& groupName);
	// 解散群聊
	bool deleteGroup(int groupId, int requesterId);
	/*========  成员进出  ========*/
	// 加入群（微信可内部检查“是否好友”）
	virtual bool addGroup(int groupId, int memberId) = 0;//这里是虚函数，因为微信要检查是否好友
	virtual bool inviteToGroup(int groupId, int memberId, int inviterId) = 0;//邀请入群,微信没有addgroup，只有邀请入群
	// 退群
	bool exitGroup(int groupId, int memberId);
	// 踢人（管理员/群主权限）
	bool deleteFriendInGroup(int groupId, int memberId, int requesterId);
	/*========  查询/展示  ========*/
	// 返回群成员 list（UI 层想怎么展示就怎么展示）
	std::list<GroupMemberLXY> getGroupMembers(int groupId);
	// 当前用户所在的所有群（主界面侧边栏用）
	std::list<std::shared_ptr<GroupInfoLXY>> getMyGroups(int userId) const;
protected:
	std::shared_ptr<Data_ManagerLXY> datamanager;
	std::shared_ptr<Friends_Data_ManagerLXY> friendsdatamanager;//这里包含了所有的朋友信息
	std::shared_ptr<Platform_User_ManagerLXY> platformusermanager;//这里包含了所有用户
	std::shared_ptr<Group_ManagerLXY> groupmanager;//这里包含了所有群组信息
	std::list<std::shared_ptr<Friend_ShipLXY>> friendslist;//这里是当前用户的好友信息，得要分平台
	std::list<std::shared_ptr<GroupLXY>> grouplist; //这里是当前用户的群组信息,得要分平台,所以必须经常更新

	//这里应该加入一些群组管理器,后面写了再说
};


class QQ_PlatformLXY :public PlatformLXY
{
public:
	QQ_PlatformLXY();
	//这里加一些群组函数，写的时候再说
	bool addGroup(int groupId, int memberId) override;
	bool inviteToGroup(int groupId, int memberId, int inviterId) override;
	void createsongroup(int id1 , int groupid)override;
};
class WeChat_PlatformLXY :public PlatformLXY
{
public:
	WeChat_PlatformLXY();
	bool addGroup(int groupId, int memberId) override;
	bool inviteToGroup(int groupId, int memberId, int inviterId) override;
	void createsongroup(int id1 , int groupid)override;
};
class WeiBo_PlatformLXY :public PlatformLXY
{
public:
	WeiBo_PlatformLXY();
	bool addGroup(int groupId, int memberId) override;
	bool inviteToGroup(int groupId, int memberId, int inviterId) override;
	void createsongroup(int id1 , int groupid)override;
};
class Main_PlatformLXY : public PlatformLXY
{
public:
	Main_PlatformLXY();
	std::shared_ptr<UserLXY>  QQsigninchecking(int id) override;
	std::shared_ptr<UserLXY>  WeChatsigninchecking(int id) override;
	std::shared_ptr<UserLXY>  WeiBosigninchecking(int id) override;
	std::shared_ptr<UserLXY>  Mainsigninchecking(int id) override;
	void createsongroup(int id1 , int groupid)override;



	LoginStatus Main_Signin(int id);//主平台登录
	LoginStatus Main_Signup();
	
	void show_all_user();
	void QQbinding(UserLXY& user) override { mainusermanager->attach_QQ(user); }
	void WeChatbinding(UserLXY& user)override { mainusermanager->attach_WeChat(user); }
	void WeiBobinding(UserLXY& user)override { mainusermanager->attach_WeiBo(user); }
	void addfriend(int id1, int id2)override;
	void showoneuserbyid(int id)override;
	void writealluserifo()override;

	bool addGroup(int groupId, int memberId) override;
	bool inviteToGroup(int groupId, int memberId, int inviterId) override;
private:
	std::unique_ptr<User_ManagerLXY> mainusermanager;
};
#endif