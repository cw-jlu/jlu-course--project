#include "System.h"
#include "Useful_Tools.h"
#define Spacenum 10
using namespace std;
void SystemLXY::start()
{
	currentuser = nullptr;
	signingguide();//登录注册
	mainguide();//主引导
}
void SystemLXY::signingguide()
{
	cout << "欢迎使用本系统,请进行登录或注册。" << endl;
	int choice;
	standardcout({ "登录请按1" , "注册请按2" , "返回请按3" },Spacenum );
	choice = readIntOnly("");
	while (choice != 3)
	{
		if (choice == 1)
		{
			
			standardcout({ "请选择您的登录平台",
						  "主平台登录......1",
						  "QQ登录..........2",
						  "微信登录........3",
						  "微博登录........4",
						  "返回............0" }, Spacenum);
			delaycout("请选择平台");
			int judge = readIntOnly("");
			while (judge != 0)
			{
				if (judge == 1)
				{
					cout << "进入主登录" << endl;
					delaycout("请输入主平台id");
					int id = readIntOnly("");
					auto user = Mainplatform->Mainsigninchecking(id);
					if (user && Mainplatform->Main_Signin(id) == LoginStatus::SUCCESS)
					{
						currentuser = user;   // shared_ptr 直接赋值
						break;
					}
				}
				else if (judge == 2)
				{
					cout << "进入QQ登录" << endl;
					delaycout("请输入QQid");
					int id = readIntOnly("");
					auto user = Mainplatform->QQsigninchecking(id);
					if (user && QQplatform->Signin(id) == LoginStatus::SUCCESS)
					{
						currentuser = user;
						break;
					}
				}
				else if (judge == 3)
				{
					cout << "进入微信登录" << endl;
					delaycout("请输入微信id");
					int id = readIntOnly("");
					auto user = Mainplatform->WeChatsigninchecking(id);
					if (user && WeChatplatform->Signin(id) == LoginStatus::SUCCESS)
					{
						currentuser = user;
						break;
					}
				}
				else if (judge == 4)
				{
					cout << "进入微博登录" << endl;
					delaycout("请输入微博id");
					int id = readIntOnly("");
					auto user = Mainplatform->WeiBosigninchecking(id);
					if (user && WeiBoplatform->Signin(id) == LoginStatus::SUCCESS)
					{
						currentuser = user;
						break;
					}
				}
				else
				{
					std::cout << "请输入正确的数字\n";
				}
				
				standardcout({ "请选择您的登录平台:",
								"主账号登录......1",
								"QQ登录.........2",
								"微信登录.......3",
								"微博登录.......4",
								"返回...........0" }, Spacenum);
				delaycout("请选择平台");
				judge = readIntOnly("");
			}
		}
		else if (choice == 2)
		{
			
			standardcout({ "请选择您的注册平台:",
			   "主账号注册......1",
			   "QQ注册.........2",
			   "微信注册........3",
			   "微博注册........4",
			   "返回...........0" }, Spacenum);
			int judge;
			judge = readIntOnly("请选择平台");
			while (judge != 0)
			{
				if (judge == 1)
				{
					if (Mainplatform->Main_Signup() == LoginStatus::SUCCESS)
					{
						cout<<"注册成功" << endl;
						Mainplatform.reset(new Main_PlatformLXY());
						break;
					}
					else
					{
						cout << "注册失败，请重新注册" << endl;
					}
				}
				else if (judge == 2)
				{
					QQplatform->Signup();
					QQplatform.reset(new QQ_PlatformLXY());
				}
				else if (judge == 3)
				{
					WeChatplatform->Signup();
					WeChatplatform.reset(new WeChat_PlatformLXY());
				}
				else if (judge == 4)
				{
					WeiBoplatform->Signup();
					WeiBoplatform.reset(new WeiBo_PlatformLXY());
				}
				else
				{
					cout << "请输入正确的数字" << endl;
				}

				
				standardcout({ "请选择您的注册平台:",
				   "主账号注册......1",
				   "QQ注册.........2",
				   "微信注册........3",
				   "微博注册........4",
				   "返回...........0" }, Spacenum);
				judge = readIntOnly("请选择平台");
			}
		}
		if (currentuser != nullptr)
			break;
		
		standardcout({ "登录请按1，注册请按2，返回请按3" }, Spacenum);
		choice = readIntOnly("");
	}
}
void SystemLXY::mainguide()
{
	if(currentuser == nullptr)
	{
		return;
	}
	
	standardcout({ "您已成功登录",
				   "好友操作..........1",
				   "群组操作..........2",
				   "查看个人信息......3",
				   "账号绑定...........4",
				   "退出登录..........0" }, Spacenum);
	delaycout("请选择操作");
	int choice = readIntOnly("");
	while (choice != 0)
	{
		if (choice == 1)
		{
			friendsguide();
		}
		else if (choice == 2)
		{
			groupguide();
		}
		else if (choice == 3)
		{
			selfguide();
		}
		else if (choice == 4)
		{
			bindguide();
		}
		
		standardcout({ "您已成功登录",
					   "好友操作..........1",
					   "群组操作..........2",
					   "查看个人信息......3",
					   "账号绑定...........4",
					   "退出登录..........0" }, Spacenum);
		delaycout("请选择操作");
		choice = readIntOnly("");
	}
}
void SystemLXY::friendsguide()
{
	//这里需要用currentuser在对应的平台上进行加好友删好友等操作
	int choice;
	int id1;//这里要确定平台，拿到对应平台的id
	
	standardcout({ "主平台好友.......1",
				   "QQ平台好友........2",
				   "微信平台好友......3",
				   "微博平台好友......4",
				   "返回.............0" }, Spacenum);
	delaycout("请选择平台");
	choice = readIntOnly("");
	while (choice != 0)
	{
		if (choice == 1)
		{
			id1 = currentuser->showid();
			furtherfriendsguide(id1,*Mainplatform);
		}
		else if (choice == 2)
		{
			id1 = currentuser->showQQid();
			furtherfriendsguide(id1,*QQplatform);
		}
		else if (choice == 3)
		{
			id1 = currentuser->showWeChatid();
			furtherfriendsguide(id1,*WeChatplatform);
		}
		else if (choice == 4)
		{
			id1 = currentuser->showWeiBoid();
			furtherfriendsguide(id1,*WeiBoplatform);
		}
		else
		{
			cout << "请输入正确的数字" << endl;
		}
		
		standardcout({ "主平台好友.......1",
					   "QQ平台好友........2",
					   "微信平台好友......3",
					   "微博平台好友......4",
					   "返回.............0" }, Spacenum);
		delaycout("请选择平台");
		choice = readIntOnly("");
	}
}
void SystemLXY::bindguide()
{
	if (currentuser == nullptr)
	{
		cout << "当前没有登录用户，无法进行绑定" << endl;
		return;
	}
	
	standardcout({ "请选择绑定平台:",
				   "QQ绑定........1",
				   "微信绑定......2",
				   "微博绑定......3",
				   "返回.........0" }, Spacenum);
	int choice;
	choice = readIntOnly("请选择平台");
	while (choice != 0)
	{
		if (choice == 1)
		{
			Mainplatform->QQbinding(*currentuser);
		}
		else if (choice == 2)
		{
			Mainplatform->WeChatbinding(*currentuser);
		}
		else if (choice == 3)
		{
			Mainplatform->WeiBobinding(*currentuser);
		}
		else
		{
			cout << "请输入正确的数字" << endl;
		}
		
		standardcout({ "请选择绑定平台:",
					   "QQ绑定........1",
					   "微信绑定......2",
					   "微博绑定......3",
					   "返回.........0" }, Spacenum);
		choice = readIntOnly("请选择平台");
	}
}
void SystemLXY::showalluserfortest()
{
	cout << "以下是主用户信息" << endl;
	Mainplatform->show_all_user();
	cout << "以下是QQ用户信息" << endl;
	QQplatform->show_all_user();
	cout << "以下是微信用户信息" << endl;
	WeChatplatform->show_all_user();
	cout << "以下是微博用户信息" << endl;
	WeiBoplatform->show_all_user();
}
void SystemLXY::furtherfriendsguide(int id1,PlatformLXY& platform)
{
	
	standardcout({ "添加好友.........1",
				   "查看好友..........2",
				   "查看好友推荐......3",
				   "返回.............0" }, Spacenum);
	delaycout("请选择");
	int choice = readIntOnly("");
	while (choice != 0)
	{
		if (choice == 1)
		{
			int id2 = readIntOnly("请输入您要添加的用户id");
			addfriends(id1,id2,platform);
		}
		else if (choice == 2)
		{
			delaycoutline();
			platform.getfriends(id1);
			int maxamount = platform.showfriends(id1);
			delaycout("请根据序号选择好友，按0返回");
			int num = readIntOnly("");
			if (num == 0)break;
			while (true)//判断输入是否合法
			{
				if (num < 0)
				{
					cout << "不能输入负数，请重新选择" << endl;
				}
				else if (num > maxamount)
				{
					cout << "该序号超过好友数，并不对应某个好友，请重新选择" << endl;
				}
				else
				{
					break;
				}
				num = readIntOnly("请根据序号选择好友");
			}
			int id2 = platform.getfriendsid(num-1,id1);		
			delaycout("您选择的好友的id为：" + to_string(id2));
			int judge;
			delaycout("确认选择......1\n重新选择......2");
			judge = readIntOnly("");
			while (judge != 0)
			{
				if (judge == 1)
				{
					furfurtherfriendsguide(id1,id2,platform);
					break;
				}
				else if (judge == 2)
				{
					break;
				}
				else
				{
					cout << "输入不合法，请重新输入" << endl;
				}
			}
			
		}
		else if (choice == 3)
		{
			//这里得要判断传进来的是哪个平台，然后调用其他三个平台的推荐函数
			if (dynamic_cast<Main_PlatformLXY*>(&platform)) 
			{         
				QQfriends_recommend(platform,id1);
				WeChatfriends_recommend(platform, id1);
				WeiBofriends_recommend(platform, id1);
			}
			else if (dynamic_cast<QQ_PlatformLXY*>(&platform))
			{
				Mainfriends_recommend(platform, id1);
				WeChatfriends_recommend(platform, id1);
				WeiBofriends_recommend(platform, id1);
			}
			else if (dynamic_cast<WeChat_PlatformLXY*>(&platform)) 
			{
				Mainfriends_recommend(platform,id1);
				QQfriends_recommend(platform, id1);
				WeiBofriends_recommend(platform, id1);
			}
			else if (dynamic_cast<WeiBo_PlatformLXY*>(&platform)) 
			{
				Mainfriends_recommend(platform, id1);
				QQfriends_recommend(platform, id1);
				WeChatfriends_recommend(platform, id1);
			}
			else 
			{
				std::cout << "发生错误，无法进行好友推荐\n";
			}
		}
		else
		{
			cout << "输入不合法请重新输入" << endl;	
		}
		
		standardcout({ "添加好友.........1",
					   "查看好友..........2",
					   "查看好友推荐......3",
					   "返回.............0" }, Spacenum);
		delaycout("请选择");
		choice = readIntOnly("");
	}
}
void SystemLXY::addfriends(int id1,int id2,PlatformLXY& platform)//id2这个2代表是被加的，现在还是有个问题，就是我得区分id1是哪个平台的，或许直接用参数传递比较好
{
	platform.addfriend(id1, id2);
}
void SystemLXY::furfurtherfriendsguide(int id1,int id2, PlatformLXY& platform)
{
	
	standardcout({ "您正在对" + to_string(id2) + "进行好友操作",
				   "发消息......1",
				   "查看好友信息......2",
				   "删除好友......3",
				   "返回......0" }, Spacenum);
	delaycout("请选择");
	int choice = readIntOnly("");
	while (choice != 0)
	{
		if (choice == 1)
		{
			cout << "发消息功能正在开发中!" << endl;;
		}
		else if (choice == 2)
		{
			delaycoutline();
			//这里要判断platform是哪个平台的，然后吧id2转化为main平台，直接可以到推荐好友里面抄一段过来
			shared_ptr<UserLXY> user;
			if (dynamic_cast<Main_PlatformLXY*>(&platform))
			{
				user = Mainplatform->Mainsigninchecking(id2);//啥也不做，id2本来就是mainid
			}
			else if (dynamic_cast<QQ_PlatformLXY*>(&platform))
			{
				user = Mainplatform->QQsigninchecking(id2);//这个函数起名有点歧义，其实就是通过QQid找mainuser
				if (user == nullptr)
				{
					cout << "无法查看未绑定账号的主平台信息" << endl;
					return;
				}
				id2 = user->showid();
			}
			else if (dynamic_cast<WeChat_PlatformLXY*>(&platform))
			{
				user = Mainplatform->WeChatsigninchecking(id2);
				if (user == nullptr)
				{
					cout << "无法查看未绑定账号的主平台信息" << endl;
					return;
				}
				id2 = user->showid();
			}
			else if (dynamic_cast<WeiBo_PlatformLXY*>(&platform))
			{
				user = Mainplatform->WeiBosigninchecking(id2);
				if (user == nullptr)
				{
					cout << "无法查看未绑定账号的主平台信息" << endl;
					return;
				}
				id2 = user->showid();
			}
			else
			{
				std::cout << "发生错误，无法进行好友推荐\n";
				return;
			}
			if (user == nullptr)
			{
				delaycout("该用户并未绑定当前平台");
				return;
				//这里缺 return，程序继续往下执行
			}
			//现在id2被转化为了mainid
			Mainplatform->showoneuserbyid(id2);//查看好友只看main平台的信息
		}
		else if (choice == 3)
		{
			//platform.deletefriend();
			
			standardcout({ "您确定要删除" + to_string(id2) + "吗",
						   "确认......1",
						   "取消......2" }, Spacenum);
			delaycout("请选择");
			int judge = readIntOnly("");
			while (judge != 2)
			{
				if (judge == 1)
				{
					platform.deletefriend(id1,id2);
					return;//删掉好友之后furfurther就没有意义了，直接return
				}
				else
				{
					cout << "输入不合法，请重新输入" << endl;
				}
				
				standardcout({ "您确定要删除" + to_string(id2) + "吗",
							   "确认......1",
							   "取消......2" }, Spacenum);
				delaycout("请选择");
				judge = readIntOnly("");
			}
		}
		else
		{
			cout << "输入不合法请重新输入" << endl;
		}
		
		standardcout({ "发消息...............1",
					   "查看好友信息.........2",
					   "删除好友.............3",
					   "返回.................0" }, Spacenum);
		delaycout("请选择");
		choice = readIntOnly("");
	}
}
void SystemLXY::selfguide()
{	
	
	Mainplatform->showoneuserbyid(currentuser->showid());
	standardcout({ "修改用户名......1",
				   "修改密码.........2",
				   "修改手机号.......3",
				   "修改邮箱.........4",
				   "返回.............0" }, Spacenum);
	delaycout("请选择");
	int choice = readIntOnly("");
	while (choice != 0)
	{
		if (choice == 1)
		{
			currentuser->changename();
			Mainplatform->writealluserifo();//currentuser是shared_ptr，不用担心修改不到的问题
		}
		else if (choice == 2)
		{
			currentuser->changepassword();
			Mainplatform->writealluserifo();
		}
		else if (choice == 3)
		{
			currentuser->changephonenumber();
			Mainplatform->writealluserifo();
		}
		else if (choice == 4)
		{
			currentuser->changeemail();
			Mainplatform->writealluserifo();
		}
		else
		{
			cout << "输入不合法，请重新输入" << endl;
		}
		
		standardcout({ "修改用户名......1",
					   "修改密码.........2",
					   "修改手机号.......3",
					   "修改邮箱.........4",
					   "返回.............0" }, Spacenum);
		delaycout("请选择");
		choice = readIntOnly("");
	}
}
void SystemLXY::groupguide()
{
	//这里需要用currentuser在对应的平台上进行加群删群等操作
	int choice;
	int id1;
	
	standardcout({ "主平台群聊........1",
				   "QQ平台群聊........2",
				   "微信平台群聊......3",
				   "微博平台群聊......4",
				   "返回.............0" }, Spacenum);
	delaycout("请选择平台");
	choice = readIntOnly("");
	while (choice != 0)
	{
		if (choice == 1)
		{
			id1 = currentuser->showid();
			furthergroupguide(id1,*Mainplatform);
		}
		else if (choice == 2)
		{
			id1 = currentuser->showQQid();
			furthergroupguide(id1,*QQplatform);
		}
		else if (choice == 3)
		{
			id1 = currentuser->showWeChatid();
			furthergroupguide(id1,*WeChatplatform);
		}
		else if (choice == 4)
		{
			id1 = currentuser->showWeiBoid();
			furthergroupguide(id1,*WeiBoplatform);
		}
		else
		{
			cout << "请输入正确的数字" << endl;
		}
		
		standardcout({ "主平台群聊........1",
					   "QQ平台群聊........2",
					   "微信平台群聊......3",
					   "微博平台群聊......4",
					   "返回.............0" }, Spacenum);
		delaycout("请选择平台");
		choice = readIntOnly("");
	}
}
void SystemLXY::furthergroupguide(int id1,PlatformLXY& platform)//这里加群的逻辑最好改一下，因为我现在只能拿到currentuser的主平台id，我可能得通过平台来区分id，或者作为参数传下来
{
	
	standardcout({ "加入群聊......1",
				   "查看群聊......2",
				   "创建群聊......3",
				   "返回..........0" }, Spacenum);
	delaycout("请选择");
	int choice = readIntOnly("");
	while (choice != 0)
	{
		if (choice == 1)
		{
			addgroup(id1, platform);
		}
		else if(choice == 2)
		{
			delaycoutline();
			platform.getgroups(id1);
			int maxamount = platform.showgroups(id1);
			delaycout("请根据序号选择群聊，按0返回");
			int num = readIntOnly("");
			if (num == 0)break;
			while (true)//判断输入是否合法
			{
				if (num < 0)
				{
					cout << "不能输入负数，请重新选择" << endl;
				}
				else if (num > maxamount)
				{
					cout << "该序号超过群聊数，并不对应某个群聊，请重新选择" << endl;
				}
				else
				{
					break;
				}
				num = readIntOnly("请根据序号选择群聊");
			}
			if (num == 0)break;
			int groupid = platform.getgroupsid(num - 1, id1);
			delaycout("您选择的群聊的id为：" + to_string(groupid));
			int judge;
			delaycout("确认选择......1\n重新选择......2");
			judge = readIntOnly("");
			while (judge != 0)
			{
				if (judge == 1)
				{
					furfurthergroupguide(id1, groupid, platform);
					break;
				}
				else if (judge == 2)
				{
					break;
				}
				else
				{
					cout << "输入不合法，请重新输入" << endl;
				}
			}
			
		}
		else if (choice == 3)
		{
			creategroup(platform,id1);
		}
		else
		{
			cout << "输入不合法请重新输入" << endl;
		}
		
		standardcout({ "加入群聊......1",
					   "查看群聊......2",
					   "创建群聊......3",
					   "返回..........0" }, Spacenum);
		delaycout("请选择");
		choice = readIntOnly("");
	}
}
void SystemLXY::furfurthergroupguide(int id1, int groupid, PlatformLXY& platform)
{
	
	standardcout({ "您正在对" + to_string(groupid) + "进行群聊操作",
				   "发消息...........1",
				   "查看群信息........2",
				   "退出群聊..........3",
				   "邀请好友入群......4",
				   "解散群聊..........5",
				   "创立子群..........6",
				   "返回..............0" }, Spacenum);
	delaycout("请选择");
	int choice = readIntOnly("");
	while (choice != 0)
	{
		if (choice == 1)
		{
			cout << "发消息功能正在开发中!";
		}
		else if (choice == 2)
		{
			delaycoutline();
			auto members = platform.getGroupMembers(groupid);
			cout << "群成员列表:" << endl;
			for (const auto& member : members)
			{
				cout << "成员ID: " << member.memberid;
				if (member.role == GroupRole::Owner)
				{
					cout << "......群主" << endl;
				}
				else if (member.role == GroupRole::Admin)
				{
					cout << "......管理员" << endl;
				}
				else if (member.role == GroupRole::Member)
				{
					cout << "......成员" << endl;
				}
			}
		}
		else if (choice == 3)
		{
			
			standardcout({ "您确定要退出群聊" + to_string(groupid) + "吗",
						   "确认......1",
						   "取消......2" }, Spacenum);
			delaycout("请选择");
			int judge = readIntOnly("");
			while (judge != 2)
			{
				if (judge == 1)
				{
					exitgroup(groupid,id1, platform);
					return;//退群之后furfurther就没有意义了，直接return
				}
				else
				{
					cout << "输入不合法，请重新输入" << endl;
				}
				
				standardcout({ "您确定要退出群聊" + to_string(groupid) + "吗",
							   "确认......1",
							   "取消......2" }, Spacenum);
				delaycout("请选择");
				judge = readIntOnly("");
			}
		}
		else if (choice == 4)
		{
			delaycout("请输入好友id");
			int id2 = readIntOnly("");
			platform.inviteToGroup(groupid, id2, id1);
		}
		else if (choice == 5)
		{
			if (deletegroup(groupid, id1, platform) == true)
			{
				return;
			}
		}
		else if (choice == 6)
		{
			createsongroup(platform,id1,groupid);
		}
		else
		{
			cout << "输入不合法请重新输入" << endl;
		}
		
		standardcout({ "您正在对" + to_string(groupid) + "进行群聊操作",
					   "发消息...........1",
					   "查看群信息........2",
					   "退出群聊..........3",
					   "邀请好友入群......4",
					   "解散群聊..........5",
					   "创立子群..........6",
					   "返回..............0" }, Spacenum);
		delaycout("请选择");
		choice = readIntOnly("");
	}
}
void SystemLXY::addgroup(int id,PlatformLXY& platform)//有点麻烦，好像找不到user的对应的平台id，没法直接多态写，得要上层传递下来
{
	delaycout("请输入您要加入的群聊id");
	int groupid = readIntOnly("");
	platform.addGroup(groupid, id);
}
void SystemLXY::exitgroup(int groupid,int id, PlatformLXY& platform)
{
	platform.exitGroup(groupid, id);
}
bool SystemLXY::deletegroup(int groupid, int id, PlatformLXY& platform)
{
	return platform.deleteGroup(groupid , id);
}
void SystemLXY::creategroup(PlatformLXY& platform,int id)
{
	delaycout("请输入您要创建的群聊名称");
	string groupname;
	cin >> groupname;
	platform.createGroup(id, groupname);
}
void SystemLXY::friends_recommend(PlatformLXY& currentplatform,PlatformLXY& recommendplatform,int currentid,int recommendid)
{
	//不用再找一遍了，直接用platform中私用的friendlist就行，已经找好了
	int maxamount = recommendplatform.showfriends(recommendid);
	if (maxamount == 0)
	{
		delaycout("您在这个平台没有好友，请查看其他平台好友");
		return;
	}
	delaycout("以下是推荐的好友列表，请根据序号选择，按0返回");
	int num = readIntOnly("");
	if (num == 0)return;
	while (true)//判断输入是否合法
	{
		if (num < 0)
		{
			cout << "不能输入负数，请重新选择" << endl;
		}
		else if (num > maxamount)
		{
			cout << "该序号超过好友数，并不对应某个好友，请重新选择" << endl;
		}
		else
		{
			break;
		}
		num = readIntOnly("请根据序号选择好友");
	}
	if (num == 0)return;
	int id2 = recommendplatform.getfriendsid(num - 1, recommendid);//这个id2是被推荐的好友在被推荐的平台的id，我需要把这个id2转化为currentplatform的id，然后再加好友
	delaycout("您选择的好友的id为：" + to_string(id2));//但是我并不知道platform到底是哪个平台，所以可能还是得强制判断一下
	//首先通过把id2转化为mainuser，再通过mainuser找currentplatform的id，这里要强制判断currentplatform到底是哪个平台

	shared_ptr<UserLXY> user;
	if(dynamic_cast<Main_PlatformLXY*>(&recommendplatform))
	{
		user = Mainplatform->Mainsigninchecking(id2);//啥也不做，id2本来就是mainid
	}
	else if (dynamic_cast<QQ_PlatformLXY*>(&recommendplatform))
	{
		user = Mainplatform->QQsigninchecking(id2);//这个函数起名有点歧义，其实就是通过QQid找mainuser
		if (user == nullptr)
		{
			delaycout("发生错误，无法找到该用户");
			return;
		}
		id2 = user->showid();
	}
	else if (dynamic_cast<WeChat_PlatformLXY*>(&recommendplatform))
	{
		user = Mainplatform->WeChatsigninchecking(id2);
		if (user == nullptr)
		{
			delaycout("发生错误，无法找到该用户");
			return;
		}
		id2 = user->showid();
	}
	else if (dynamic_cast<WeiBo_PlatformLXY*>(&recommendplatform))
	{
		user = Mainplatform->WeiBosigninchecking(id2);
		if (user == nullptr)
		{
			delaycout("发生错误，无法找到该用户");
			return;
		}
		id2 = user->showid();
	}
	else
	{
		std::cout << "发生错误，无法进行好友推荐\n";
		return;
	}
	if (user == nullptr)
	{
		delaycout("该用户并未绑定当前平台");
		return;
		//这里缺 return，程序继续往下执行
	}
	//现在id2已经是mainid了，然后通过mainid找currentplatform的id，又要强制判断currentplatform到底是哪个平台,应该把上面的user留着，不用再找一遍
	if (dynamic_cast<Main_PlatformLXY*>(&currentplatform))
	{
		;//啥也不做，id2本来就是mainid
	}
	else if (dynamic_cast<QQ_PlatformLXY*>(&currentplatform))
	{
		id2 = user->showQQid();
	}
	else if (dynamic_cast<WeChat_PlatformLXY*>(&currentplatform))
	{
		id2 = user->showWeChatid();
	}
	else if (dynamic_cast<WeiBo_PlatformLXY*>(&currentplatform))
	{
		id2 = user->showWeiBoid();
	}
	else
	{
		std::cout << "发生错误，无法进行好友推荐\n";
		return;
	}
	//现在id2已经是currentplatform的id了
	if(id2 == -1 || id2 == 0)
	{
		delaycout("该用户在当前平台没有账号，无法添加为好友");
		return;
	}
	delaycout("您选择的好友在当前平台的id为：" + to_string(id2));
	int judge;
	delaycout("确认选择......1\n取消......2");
	judge = readIntOnly("");
	while (judge != 2)
	{
		if (judge == 1)
		{
			addfriends(currentid, id2, currentplatform);
			return;
		}
		else
		{
			cout << "输入不合法，请重新输入" << endl;
		}
		delaycout("您选择的好友的id为：" + to_string(id2));
		delaycout("确认选择......1\n取消......2");
		judge = readIntOnly("");
	}
}
void SystemLXY::Mainfriends_recommend(PlatformLXY& currentplatform,int currentid)
{
	//这里只管找到mainid，然后更新链表，然后调用friends_recommend
	//还要判断currentuser有没有绑定main平台
	if (currentuser->showid() == -1)
	{
		delaycout("您还没有绑定主平台，请先绑定");
		return;
	}
	int id1 = currentuser->showid();
	Mainplatform->getfriends(id1);
	friends_recommend(currentplatform, *Mainplatform,currentid,id1);
}
void SystemLXY::QQfriends_recommend(PlatformLXY& currentplatform,int currentid)
{
	//这里只管找到QQid，然后更新链表，然后调用friends_recommend
	//还要判断currentuser有没有绑定QQ平台
	if(currentuser->showQQid() == -1)
	{
		delaycout("您还没有绑定QQ平台，请先绑定");
		return;
	}
	int id1 = currentuser->showQQid();
	QQplatform->getfriends(id1);
	friends_recommend(currentplatform, *QQplatform,currentid,id1);
}
void SystemLXY::WeChatfriends_recommend(PlatformLXY& currentplatform, int currentid)
{
	//这里只管找到WeChatid，然后更新链表，然后调用friends_recommend
	//还要判断currentuser有没有绑定WeChat平台
	if (currentuser->showWeChatid() == -1)
	{
		delaycout("您还没有绑定微信平台，请先绑定");
		return;
	}
	int id1 = currentuser->showWeChatid();
	WeChatplatform->getfriends(id1);
	friends_recommend(currentplatform, *WeChatplatform, currentid, id1);
}
void SystemLXY::WeiBofriends_recommend(PlatformLXY& currentplatform, int currentid)
{
	//这里只管找到WeiBoid，然后更新链表，然后调用friends_recommend
	//还要判断currentuser有没有绑定WeiBo平台
	if (currentuser->showWeiBoid() == -1)
	{
		delaycout("您还没有绑定微博平台，请先绑定");
		return;
	}
	int id1 = currentuser->showWeiBoid();
	WeiBoplatform->getfriends(id1);
	friends_recommend(currentplatform, *WeiBoplatform, currentid, id1);
}
void SystemLXY::createsongroup(PlatformLXY& platform,int id1 , int groupid)
{
	platform.createsongroup(id1 ,groupid);
}
