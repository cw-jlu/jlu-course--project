#ifndef System_h
#define System_h
#include "Platform.h"
enum class PlatTag { QQ, WeChat, WeiBo };
//系统层不考虑多态了，platform是多态的最后一层，系统层只负责引导，随便怎么写
class SystemLXY
{
public:
	SystemLXY(): QQplatform(std::make_unique<QQ_PlatformLXY>()),
				WeChatplatform(std::make_unique<WeChat_PlatformLXY>()),
				WeiBoplatform(std::make_unique<WeiBo_PlatformLXY>()),
				Mainplatform(std::make_unique<Main_PlatformLXY>()),currentuser(nullptr){}

	void start();//总引导
	void signingguide();//登录注册引导,平台中的调用usermanager中的函数来实现，这里应该需要再把usermanager的函数往上面传递一层到platform中，直接调用platform的成员函数
	void mainguide();//主页面引导

	void addfriends(int id1,int id2,PlatformLXY& platform);//加好友，调用friendmanager中的函数
	void deletefriends();//删好友，这个函数一不小心写到furfurtherfriendsguide中了
	void searchfriends();//搜好友，还没写 //这几个可能得下放到platform中实现
	void friends_recommend(PlatformLXY& currentplatform,PlatformLXY& recommendplatform,int currentid,int recommendid);
	//好友推荐，这个函数必须得放在system中实现，因为四个平台各自保存的当前用户的好友链表，在system中是可以访问的
	//这个参数代表的是，向当前用户推荐参数平台的用户，还要检查当前用户有没有绑定这个平台，以及当前用户在这个平台有没有好友
	//我想的是，先检查有没有绑定这个平台，如果没有绑定就提示绑定，如果绑定了就检查这个平台的好友链表，然后全部展示出来，让用户按1234这样来选，选完了就问要不要加好友，加好友要加到当前用户所在的平台，而不是又在参数平台加好友
	//可能参数少了一点，后面要的时候再加，现在先把引导写了，到时候要啥参数就很明了了

	void Mainfriends_recommend(PlatformLXY& currentplatform,int currentid);//主平台好友推荐
	void QQfriends_recommend(PlatformLXY& currentplatform,int currentid);//QQ好友推荐
	void WeChatfriends_recommend(PlatformLXY& currentplatform,int currentid);//微信好友推荐
	void WeiBofriends_recommend(PlatformLXY& currentplatform,int currentid);//微博好友推荐
	//虽说不用多态，也可以把共同点提炼出来，写成一个函数，然后传入不同的参数

	void addgroup(int id,PlatformLXY& platform);//加群，只负责引导，加群的id就是currentuser对应的平台id
	void exitgroup(int groupid , int id , PlatformLXY& platform);//退群，只负责引导
	bool deletegroup(int groupid, int id, PlatformLXY& platform);
	void creategroup(PlatformLXY& platform,int id);//创建群聊，只负责引导
	void createsongroup(PlatformLXY& platform,int id1,int groupid);//创建子群
	
	void friendsguide();
	void furtherfriendsguide(int id1,PlatformLXY& platform);//用一个平台引用作为参数进一步引导，体现结构化编程，也体现底层多态设计
	void furfurtherfriendsguide(int id1,int id2,PlatformLXY& platform);//更进一步引导好友操作，增删查改等
	void groupguide();//下次从这开始写，然后再把好友的引导写了，检查一下好友链表是不是正确的，有没有野指针之类的，还有账号绑定。
	void furthergroupguide(int id1,PlatformLXY& platform);//群组进一步引导
	void furfurthergroupguide(int id1, int id2, PlatformLXY& platform);//群组更进一步引导
	void selfguide();
	void bindguide();//账号绑定引导

	void showalluserfortest();//测试用，显示所有用户
	//后面想到啥再写

private:
	std::unique_ptr<PlatformLXY> QQplatform;
	std::unique_ptr<PlatformLXY> WeChatplatform;
	std::unique_ptr<PlatformLXY> WeiBoplatform;
	std::unique_ptr<PlatformLXY> Mainplatform;
	//好友链表存在flatform中
	std::shared_ptr<UserLXY> currentuser;//这个是从底层一层层传递上来的
};
#endif
//反正目前得慢慢把已经写出来的类大概都检查一下，然后开始写群组