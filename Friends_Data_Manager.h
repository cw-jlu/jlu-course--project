#ifndef FRIENDS_DATA_MANAGER_H
#define FRIENDS_DATA_MANAGER_H

#include <list>
#include <memory>
#include <iostream>
#include "Friends_Data_Tools.h"

class Friends_Data_ManagerLXY
{
public:
    /* 工厂与平台切换 */
    void setFactory(std::unique_ptr<Friends_Factory> factory);
    void setQQPlatform();
    void setWeChatPlatform();
    void setWeiBoPlatform();
    void setMainPlatform();
    /* 业务接口 */
    void write_back();
    int search_same(int id1, int id2);
    void addfriends(int id1, int id2);
    void deletefriends(int id1, int id2);
	void showfriends(int id);
	bool isfriend(int id1, int id2);
    std::list<Friend_ShipLXY>& showandgetfriends(int id);
    std::list<std::shared_ptr<Friend_ShipLXY>> getfriends(int id);

private:
    std::list<std::shared_ptr<Friend_ShipLXY>> friendslist;//好友需要共享，用shared
    std::unique_ptr<Friends_Data_ToolsLXY>     friendstools;//工具独享，用unique
    std::unique_ptr<Friends_Factory>           friendsfactory;//工厂独享，用unique
};

#endif // FRIENDS_DATA_MANAGER_H
