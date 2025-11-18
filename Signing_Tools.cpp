#include <iostream>
#include <list>
#include <memory>
#include <string>
#include <limits>
#include "Data_Manager.h"
#include "Signing_Tools.h"
#include "Useful_Tools.h"
using namespace std;

/*以下是登录*/

LoginStatus Main_SigningLXY::sign_in()
{
    datamanager.setMainFactory();
    auto AccountIfo = datamanager.readData<MainaccountIfoLXY>();

    if (AccountIfo.empty()) {
        std::cout << "没有注册的账号，请先注册\n";
        return LoginStatus::NO_ACCOUNTS_REGISTERED;
    }

    int id = readIntOnly("正在进行登录，请输入主账号ID: ");

    std::cout << "请输入密码: ";
    std::string passwd;
    std::cin >> passwd;

    for (auto& account : AccountIfo) {
        if (account.id == id) {
            if (account.password != passwd) {
                std::cout << "密码错误\n";
                return LoginStatus::PASSWORD_ERROR;
            }
            // 登录成功
            std::cout << "登录成功！欢迎 " << account.Username << '\n';
            return LoginStatus::SUCCESS;
        }
    }
    // 遍历结束仍未找到
    std::cout << "账号不存在\n";
    return LoginStatus::ACCOUNT_NOT_EXIST;
}
LoginStatus QQ_SigningLXY::sign_in()
{
    datamanager.setQQFactory();                          // 1. 换工厂
    auto AccountIfo = datamanager.readData<QQaccountIfoLXY>(); // 2. 读 QQ 账号

    if (AccountIfo.empty()) {
        std::cout << "没有注册的QQ账号，请先注册\n";
        return LoginStatus::NO_ACCOUNTS_REGISTERED;
    }

    int id = readIntOnly("正在进行登录，请输入QQ账号ID: ");

    std::cout << "请输入密码: ";
    std::string passwd;
    std::cin >> passwd;

    for (auto& account : AccountIfo) {
        if (account.QQid == id) {
            if (account.QQpassword != passwd) {
                std::cout << "密码错误\n";
                return LoginStatus::PASSWORD_ERROR;
            }
            if (account.ifconnect == 0)
            {
                cout << "该微博号未绑定主账号，无法登录" << endl;
                return LoginStatus::NOT_BOUND;
            }
            std::cout << "QQ登录成功！欢迎 " << account.name << '\n';
            return LoginStatus::SUCCESS;
        }
    }
    std::cout << "QQ账号不存在\n";
    return LoginStatus::ACCOUNT_NOT_EXIST;
}
LoginStatus WeChat_SigningLXY::sign_in()
{
    datamanager.setWeChatFactory();
    auto AccountIfo = datamanager.readData<WeChataccountIfoLXY>();

    if (AccountIfo.empty()) {
        std::cout << "没有注册的微信账号，请先注册\n";
        return LoginStatus::NO_ACCOUNTS_REGISTERED;
    }

    int id = readIntOnly("正在进行登录，请输入微信账号ID: ");

    std::cout << "请输入密码: ";
    std::string passwd;
    std::cin >> passwd;

    for (auto& account : AccountIfo) {
        if (account.WeChatid == id) {
            if (account.WeChatpassword != passwd) {
                std::cout << "密码错误\n";
                return LoginStatus::PASSWORD_ERROR;
            }
            if (account.ifconnect == 0)
            {
                cout << "该微信号未绑定主账号，无法登录" << endl;
                return LoginStatus::NOT_BOUND;
            }
            std::cout << "微信登录成功！欢迎 " << account.name << '\n';
            return LoginStatus::SUCCESS;
        }
    }
    std::cout << "微信账号不存在\n";
    return LoginStatus::ACCOUNT_NOT_EXIST;
}
LoginStatus WeiBo_SigningLXY::sign_in()
{
    datamanager.setWeiBoFactory();
    auto AccountIfo = datamanager.readData<WeiBoaccountIfoLXY>();

    if (AccountIfo.empty()) {
        std::cout << "没有注册的微博账号，请先注册\n";
        return LoginStatus::NO_ACCOUNTS_REGISTERED;
    }

    int id = readIntOnly("正在进行登录，请输入微博账号ID: ");

    std::cout << "请输入密码: ";
    std::string passwd;
    std::cin >> passwd;

    for (auto& account : AccountIfo) {
        if (account.WeiBoid == id) {
            if (account.WeiBopassword != passwd) {
                std::cout << "密码错误\n";
                return LoginStatus::PASSWORD_ERROR;
            }
            if (account.ifconnect == 0)
            {
                cout << "该微博号未绑定主账号，无法登录" << endl;
                return LoginStatus::NOT_BOUND;
            }
            std::cout << "微博登录成功！欢迎 " << account.name << '\n';
            return LoginStatus::SUCCESS;
        }
    }
    std::cout << "微博账号不存在\n";
    return LoginStatus::ACCOUNT_NOT_EXIST;
}
LoginStatus Main_SigningLXY::sign_in(int id)
{
    datamanager.setMainFactory();
    auto AccountIfo = datamanager.readData<MainaccountIfoLXY>();

    if (AccountIfo.empty()) {
        std::cout << "没有注册的账号，请先注册\n";
        return LoginStatus::NO_ACCOUNTS_REGISTERED;
    }

    // ? 删掉这行：int id = readIntOnly("正在进行登录，请输入主账号ID: ");

    std::cout << "正在进行登录，账号ID: " << id << std::endl;
    std::cout << "请输入密码: ";
    std::string passwd;
    std::cin >> passwd;

    for (auto& account : AccountIfo) {
        if (account.id == id) {
            if (account.password != passwd) {
                std::cout << "密码错误\n";
                return LoginStatus::PASSWORD_ERROR;
            }
            std::cout << "登录成功！欢迎 " << account.Username << '\n';
            return LoginStatus::SUCCESS;
        }
    }
    std::cout << "账号不存在\n";
    return LoginStatus::ACCOUNT_NOT_EXIST;
}
LoginStatus QQ_SigningLXY::sign_in(int id)
{
    datamanager.setQQFactory();
    auto AccountIfo = datamanager.readData<QQaccountIfoLXY>();

    if (AccountIfo.empty()) {
        std::cout << "没有注册的QQ账号，请先注册\n";
        return LoginStatus::NO_ACCOUNTS_REGISTERED;
    }

    std::cout << "正在进行QQ登录，QQ号: " << id << std::endl;
    std::cout << "请输入QQ密码: ";
    std::string passwd;
    std::cin >> passwd;

    for (auto& account : AccountIfo) {
        if (account.QQid == id) {
            if (account.QQpassword != passwd) {
                std::cout << "QQ密码错误\n";
                return LoginStatus::PASSWORD_ERROR;
            }
            std::cout << "QQ登录成功！欢迎 " << account.name << '\n';
            return LoginStatus::SUCCESS;
        }
    }
    std::cout << "QQ号不存在\n";
    return LoginStatus::ACCOUNT_NOT_EXIST;
}
LoginStatus WeChat_SigningLXY::sign_in(int id)
{
    datamanager.setWeChatFactory();
    auto AccountIfo = datamanager.readData<WeChataccountIfoLXY>();

    if (AccountIfo.empty()) {
        std::cout << "没有注册的微信账号，请先注册\n";
        return LoginStatus::NO_ACCOUNTS_REGISTERED;
    }

    std::cout << "正在进行微信登录，微信号: " << id << std::endl;
    std::cout << "请输入微信密码: ";
    std::string passwd;
    std::cin >> passwd;

    for (auto& account : AccountIfo) {
        if (account.WeChatid == id) {
            if (account.WeChatpassword != passwd) {
                std::cout << "微信密码错误\n";
                return LoginStatus::PASSWORD_ERROR;
            }
            std::cout << "微信登录成功！欢迎 " << account.name << '\n';
            return LoginStatus::SUCCESS;
        }
    }
    std::cout << "微信号不存在\n";
    return LoginStatus::ACCOUNT_NOT_EXIST;
}
LoginStatus WeiBo_SigningLXY::sign_in(int id)
{
    datamanager.setWeiBoFactory();
    auto AccountIfo = datamanager.readData<WeiBoaccountIfoLXY>();

    if (AccountIfo.empty()) {
        std::cout << "没有注册的微博账号，请先注册\n";
        return LoginStatus::NO_ACCOUNTS_REGISTERED;
    }

    std::cout << "正在进行微博登录，微博ID: " << id << std::endl;
    std::cout << "请输入微博密码: ";
    std::string passwd;
    std::cin >> passwd;

    for (auto& account : AccountIfo) {
        if (account.WeiBoid == id) {
            if (account.WeiBopassword != passwd) {
                std::cout << "微博密码错误\n";
                return LoginStatus::PASSWORD_ERROR;
            }
            std::cout << "微博登录成功！欢迎 " << account.name << '\n';
            return LoginStatus::SUCCESS;
        }
    }
    std::cout << "微博ID不存在\n";
    return LoginStatus::ACCOUNT_NOT_EXIST;
}
LoginStatus Main_SigningLXY::sign_in_for_binding(int id)//这下面几个带id的函数是用来引导绑定的，不要把ifconnect的逻辑弄错了
{
    datamanager.setMainFactory();
    auto AccountIfo = datamanager.readData<MainaccountIfoLXY>();

    if (AccountIfo.empty()) {
        std::cout << "没有注册的账号\n";
        return LoginStatus::NO_ACCOUNTS_REGISTERED;
    }

    std::cout << "正在进行主账号绑定，账号ID: " << id << std::endl;
    std::cout << "请输入密码: ";
    std::string passwd;
    std::cin >> passwd;

    for (auto& account : AccountIfo) {
        if (account.id == id) {
            if (account.password != passwd) {
                std::cout << "密码错误\n";
                return LoginStatus::PASSWORD_ERROR;
            }
            // 登录成功
            std::cout << "绑定成功！ " << account.Username << '\n';
            return LoginStatus::SUCCESS;
        }
    }

    std::cout << "账号不存在\n";
    return LoginStatus::ACCOUNT_NOT_EXIST;
}
LoginStatus QQ_SigningLXY::sign_in_for_binding(int id)
{
    datamanager.setQQFactory();
    auto AccountIfo = datamanager.readData<QQaccountIfoLXY>();

    if (AccountIfo.empty()) {
        std::cout << "没有注册的QQ账号\n";
        return LoginStatus::NO_ACCOUNTS_REGISTERED;
    }

    std::cout << "正在进行QQ绑定，QQ号: " << id << std::endl;
    std::cout << "请输入QQ密码: ";
    std::string passwd;
    std::cin >> passwd;

    for (auto& account : AccountIfo) {
        if (account.QQid == id) {
            if (account.QQpassword != passwd) {
                std::cout << "QQ密码错误\n";
                return LoginStatus::PASSWORD_ERROR;
            }
            if (account.ifconnect == true)  // 仿照微信逻辑
            {
                cout << "QQ号已被绑定\n";  // 统一提示信息
                return LoginStatus::ALREADY_CONNECT;  // 统一状态码
            }
            std::cout << "QQ绑定成功! " << account.name << '\n';
            account.ifconnect = true;  // 添加：标记为已绑定
            datamanager.writeData(AccountIfo);  // 添加：保存状态
            return LoginStatus::SUCCESS;
        }
    }
    std::cout << "QQ号不存在\n";
    return LoginStatus::ACCOUNT_NOT_EXIST;
}
LoginStatus WeChat_SigningLXY::sign_in_for_binding(int id)
{
    datamanager.setWeChatFactory();
    auto AccountIfo = datamanager.readData<WeChataccountIfoLXY>();

    if (AccountIfo.empty()) {
        std::cout << "没有注册的微信账号\n";
        return LoginStatus::NO_ACCOUNTS_REGISTERED;
    }

    std::cout << "正在进行微信绑定，微信号: " << id << std::endl;
    std::cout << "请输入微信密码: ";
    std::string passwd;
    std::cin >> passwd;

    for (auto& account : AccountIfo) {
        if (account.WeChatid == id) {
            if (account.WeChatpassword != passwd) {
                std::cout << "微信密码错误\n";
                return LoginStatus::PASSWORD_ERROR;
            }
            if (account.ifconnect == true)
            {
                cout << "微信号已被绑定" << endl;
                return LoginStatus::ALREADY_CONNECT;
            }
            std::cout << "微信绑定成功! " << account.name << '\n';
            account.ifconnect = true;
            datamanager.writeData(AccountIfo);
            return LoginStatus::SUCCESS;
        }
    }

    std::cout << "微信号不存在\n";
    return LoginStatus::ACCOUNT_NOT_EXIST;
}
LoginStatus WeiBo_SigningLXY::sign_in_for_binding(int id)
{
    datamanager.setWeiBoFactory();
    auto AccountIfo = datamanager.readData<WeiBoaccountIfoLXY>();

    if (AccountIfo.empty()) {
        std::cout << "没有注册的微博账号\n";
        return LoginStatus::NO_ACCOUNTS_REGISTERED;
    }

    std::cout << "正在进行微博绑定，微博ID: " << id << std::endl;
    std::cout << "请输入微博密码: ";
    std::string passwd;
    std::cin >> passwd;

    for (auto& account : AccountIfo) {
        if (account.WeiBoid == id) {
            if (account.WeiBopassword != passwd) {
                std::cout << "微博密码错误\n";
                return LoginStatus::PASSWORD_ERROR;
            }
            // 仿照微信逻辑：检查是否已绑定
            if (account.ifconnect == true)  // 统一用true/false或1/0
            {
                cout << "微博账号已被绑定\n";
                return LoginStatus::ALREADY_CONNECT;  // 统一状态码
            }
            std::cout << "微博绑定成功! " << account.name << '\n';
            account.ifconnect = true;  // 标记为已绑定
            datamanager.writeData(AccountIfo);  // 保存状态
            return LoginStatus::SUCCESS;
        }
    }
    std::cout << "微博ID不存在\n";
    return LoginStatus::ACCOUNT_NOT_EXIST;
}

/*以上是登录*/
/*以下是注册*/

LoginStatus Main_SigningLXY::sign_up()
{
    datamanager.setMainFactory();
    auto AccountIfo = datamanager.readData<MainaccountIfoLXY>();

    MainaccountIfoLXY newAccount;

    // 生成ID（找到最大ID+1）
    int newId = 1;
    if (!AccountIfo.empty()) {
        auto maxIt = std::max_element(AccountIfo.begin(), AccountIfo.end(),
            [](const MainaccountIfoLXY& a, const MainaccountIfoLXY& b) {
                return a.id < b.id;
            });
        newId = maxIt->id + 1;
    }
    newAccount.id = newId;

    std::cout << "正在注册主账号，系统分配ID: " << newId << std::endl;

    // 输入其他信息
    std::cout << "请输入用户名: ";
    std::cin >> newAccount.Username;

    std::cout << "请输入密码: ";
    std::cin >> newAccount.password;

    while (true)
    {
        std::cout << "请输入手机号: ";
        long long temp = readLongLongOnly("");
        if (ifphonenumberlegal(temp) == false)
        {
            cout << "手机号个数错误，请重新输入" << endl;
        }
        else if (temp < 0)
        {
			cout << "手机号不能为负数，请重新输入" << endl;
        }
        else
        {
            newAccount.phoneNumber = temp;
			break;
        }
    }
    std::cout << "请输入邮箱: ";
    std::cin >> newAccount.email;

    std::cout << "请输入日期(YYYY-MM-DD): ";
    std::cin >> newAccount.date;

    std::cout << "请输入地址: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 清干净
    std::getline(std::cin, newAccount.address);

    // 初始化其他字段
    newAccount.QQid = 0;
    newAccount.WeChatid = 0;
    newAccount.WeiBoid = 0;
    newAccount.ifonline = false;

    // 添加到列表并写入文件
    AccountIfo.push_back(newAccount);
    datamanager.writeData(AccountIfo);

    std::cout << "主账号注册成功！ID: " << newId << std::endl;
    return LoginStatus::SUCCESS;
}
LoginStatus QQ_SigningLXY::sign_up()
{
    datamanager.setQQFactory();
    auto AccountIfo = datamanager.readData<QQaccountIfoLXY>();

    if (AccountIfo.empty()) {
        std::cout << "没有注册的QQ账号，请先注册\n";
        return LoginStatus::NO_ACCOUNTS_REGISTERED;
    }

    QQaccountIfoLXY newAccount;

    // 自动生成 QQ 号（最大 ID + 1）
    int newQQId = 10001;                  // 起始号段
    if (!AccountIfo.empty()) {
        auto maxIt = std::max_element(AccountIfo.begin(), AccountIfo.end(),
            [](const QQaccountIfoLXY& a, const QQaccountIfoLXY& b) {
                return a.QQid < b.QQid;
            });
        newQQId = maxIt->QQid + 1;
    }

    std::cout << "正在注册QQ账号，系统分配QQ号: " << newQQId << std::endl;
    newAccount.QQid = newQQId;
    std::cout << "请输入QQ密码: ";
    std::cin >> newAccount.QQpassword;

    std::cout << "请输入昵称: ";
    std::cin >> newAccount.name;

    // 初始化状态
    newAccount.ifconnect = false;
    newAccount.ifonline = false;

    // 添加到列表并写入文件
    AccountIfo.push_back(newAccount);
    datamanager.writeData(AccountIfo);

    std::cout << "QQ账号注册成功！QQ号: " << newQQId << std::endl;
    return LoginStatus::SUCCESS;
}
LoginStatus WeChat_SigningLXY::sign_up()
{
    datamanager.setWeChatFactory();
    auto AccountIfo = datamanager.readData<WeChataccountIfoLXY>();

    if (AccountIfo.empty()) {
        std::cout << "没有注册的微信账号，请先注册\n";
        return LoginStatus::NO_ACCOUNTS_REGISTERED;
    }

    WeChataccountIfoLXY newAccount;

    // 自动生成微信号（最大 ID + 1）
    int newWeChatId = 20001;                  // 起始号段
    if (!AccountIfo.empty()) {
        auto maxIt = std::max_element(AccountIfo.begin(), AccountIfo.end(),
            [](const WeChataccountIfoLXY& a, const WeChataccountIfoLXY& b) {
                return a.WeChatid < b.WeChatid;
            });
        newWeChatId = maxIt->WeChatid + 1;
    }

    std::cout << "正在注册微信账号，系统分配微信号: " << newWeChatId << std::endl;
    newAccount.WeChatid = newWeChatId;
    std::cout << "请输入微信密码: ";
    std::cin >> newAccount.WeChatpassword;

    std::cout << "请输入昵称: ";
    std::cin >> newAccount.name;

    // 初始化状态
    newAccount.ifconnect = false;
    newAccount.ifonline = false;

    // 添加到列表并写入文件
    AccountIfo.push_back(newAccount);
    datamanager.writeData(AccountIfo);

    std::cout << "微信账号注册成功！微信号: " << newWeChatId << std::endl;
    return LoginStatus::SUCCESS;
}
LoginStatus WeiBo_SigningLXY::sign_up()
{
    datamanager.setWeiBoFactory();
    auto AccountIfo = datamanager.readData<WeiBoaccountIfoLXY>();

    if (AccountIfo.empty()) {
        std::cout << "没有注册的微博账号，请先注册\n";
        return LoginStatus::NO_ACCOUNTS_REGISTERED;
    }

    WeiBoaccountIfoLXY newAccount;

    // 自动生成微博ID（最大 ID + 1）
    int newWeiBoId = 30001;                  // 起始号段
    if (!AccountIfo.empty()) {
        auto maxIt = std::max_element(AccountIfo.begin(), AccountIfo.end(),
            [](const WeiBoaccountIfoLXY& a, const WeiBoaccountIfoLXY& b) {
                return a.WeiBoid < b.WeiBoid;
            });
        newWeiBoId = maxIt->WeiBoid + 1;
    }

    std::cout << "正在注册微博账号，系统分配微博ID: " << newWeiBoId << std::endl;
    newAccount.WeiBoid = newWeiBoId;
    std::cout << "请输入微博密码: ";
    std::cin >> newAccount.WeiBopassword;

    std::cout << "请输入昵称: ";
    std::cin >> newAccount.name;

    // 初始化状态
    newAccount.ifconnect = false;
    newAccount.ifonline = false;

    // 添加到列表并写入文件
    AccountIfo.push_back(newAccount);
    datamanager.writeData(AccountIfo);

    std::cout << "微博账号注册成功！微博ID: " << newWeiBoId << std::endl;
    return LoginStatus::SUCCESS;
}
//以上是注册