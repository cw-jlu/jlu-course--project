#ifndef  Group_H
#define Group_H
/*这个类可以类比UserLXY*/
#include <iostream>
#include <list>
#include <string>
#include "Group_Tools.h"

class GroupLXY
{
private:
	GroupInfoLXY groupifo;//这个是最根源的信息，所以不用指针用值
public:
	GroupLXY(const GroupInfoLXY& info) : groupifo(info) {}
	
	/*函数到cpp中写，然后在cpp中include Group_Tools，这样就不会报错*/
	int showgroupid();
	std::string showgroupname();
	int showcreatorid();
	GroupInfoLXY& getgroupifo();
	void showallmembers();
	std::list<GroupMemberLXY>showallmembersifo();
	bool addmember(int memberid, GroupRole role);
	bool deletemember(int memberid, int requesterId);
	bool ismember(int memberid);
	int getmembercount();


};
#endif // ! Group_H
