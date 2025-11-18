#ifndef Friends_Data_Tools_H
#define Friends_Data_Tools_H
#include <iostream>
#include <list>
#include <memory>
struct Friend_ShipLXY
{
	int id1;
	int id2;
	Friend_ShipLXY(int i1, int i2) : id1(i1), id2(i2){}
};
class Friends_Data_ToolsLXY
{
public:
	virtual std::list<std::shared_ptr<Friend_ShipLXY>> get_friend_list() = 0;
	virtual void write_friend_list(std::list<std::shared_ptr<Friend_ShipLXY>>&) = 0;
};
class Main_Friends_ToolsLXY :public Friends_Data_ToolsLXY
{
public:
	std::list<std::shared_ptr<Friend_ShipLXY>> get_friend_list();
	void write_friend_list(std::list<std::shared_ptr<Friend_ShipLXY>>&);
};
class QQ_Friends_ToolsLXY : public Friends_Data_ToolsLXY
{
public:
	std::list<std::shared_ptr<Friend_ShipLXY>> get_friend_list();
	void write_friend_list(std::list<std::shared_ptr<Friend_ShipLXY>>&);
};
class WeChat_Friends_ToolsLXY : public Friends_Data_ToolsLXY
{
public:
	std::list<std::shared_ptr<Friend_ShipLXY>> get_friend_list();
	void write_friend_list(std::list<std::shared_ptr<Friend_ShipLXY>>&);
};
class WeiBo_Friends_ToolsLXY : public Friends_Data_ToolsLXY
{
public:
    std::list<std::shared_ptr<Friend_ShipLXY>> get_friend_list();
	void write_friend_list(std::list<std::shared_ptr<Friend_ShipLXY>>&);
};
class Friends_Factory
{
public:
	virtual std::unique_ptr<Friends_Data_ToolsLXY> GetTools() = 0;
};
class Main_Friends_Factory :public Friends_Factory
{
public:
	std::unique_ptr<Friends_Data_ToolsLXY> GetTools();
};
class QQ_Friends_Factory : public Friends_Factory
{
public:
	std::unique_ptr<Friends_Data_ToolsLXY> GetTools();
};
class WeChat_Friends_Factory :public Friends_Factory
{
public:
	std::unique_ptr<Friends_Data_ToolsLXY> GetTools();
};
class WeiBo_Friends_Factory : public Friends_Factory
{
public:
	std::unique_ptr<Friends_Data_ToolsLXY> GetTools();
};
#endif
