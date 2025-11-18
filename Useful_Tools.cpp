#include "Useful_Tools.h"
#include "Windows.h"
using namespace std;
int readIntOnly(const std::string& prompt)
{
    std::cout << prompt;
    std::string buf;
    char ch;
    while ((ch = getKey()) != '\r') {
        if (std::isdigit(static_cast<unsigned char>(ch))) {
            buf += ch;
            std::cout << ch;
        }
        else if (ch == '\b' && !buf.empty()) {
            buf.pop_back();
            std::cout << "\b \b";
        }
    }
    std::cout << '\n';

    if (buf.empty() || buf.size() > 9) {   // ← 防止空串 / 超大数
        std::cout << "输入非法，请重新输入数字\n";
        return readIntOnly(prompt);
    }
    return std::stoi(buf);
}
long long readLongLongOnly(const std::string& prompt)
{
    std::cout << prompt;
    std::string buf;
    char ch;
    while ((ch = getKey()) != '\r') {
        if (std::isdigit(static_cast<unsigned char>(ch))) {
            buf += ch;
            std::cout << ch;
        }
        else if (ch == '\b' && !buf.empty()) {
            buf.pop_back();
            std::cout << "\b \b";
        }
    }
    std::cout << '\n';

    if (buf.empty()) {
        std::cout << "输入不能为空，请重新输入\n";
        return readLongLongOnly(prompt);
    }

    // 检查长度，手机号应该是11位
    if (buf.length() != 11) {
        std::cout << "手机号必须是11位数字\n";
        return readLongLongOnly(prompt);
    }

    try {
        return std::stoll(buf);  // 使用 stoll 而不是 stoi
    }
    catch (const std::exception& e) {
        std::cout << "输入非法，请重新输入数字\n";
        return readLongLongOnly(prompt);
    }
}
bool ifphonenumberlegal(long long phonenumeber)
{
    if(phonenumeber<10000000000||phonenumeber>19999999999)return false;
	return true;
}
void coutline()//打印一个分隔符号
{
    std::cout << "==============================================" << std::endl;
}
void delaycout(const std::string& str)   // 传 const 引用更高效
{
    for (char ch : str)
    {
        std::cout << ch << std::flush;   // flush 保证立即输出
        std::this_thread::sleep_for(std::chrono::milliseconds(10)); // 100 ms
    }
    cout << endl;
}
void delaycoutline()
{
    string str = "==============================================";
    for (char ch : str)
    {
        std::cout << ch << std::flush;   // flush 保证立即输出
        std::this_thread::sleep_for(std::chrono::milliseconds(3)); // 100 ms
    }
    cout << endl;
}
void clearScreen() {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD home = { 0, 0 };
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(h, &csbi);
    DWORD cell = csbi.dwSize.X * csbi.dwSize.Y, written;
    FillConsoleOutputCharacter(h, ' ', cell, home, &written);
    FillConsoleOutputAttribute(h, csbi.wAttributes, cell, home, &written);
    SetConsoleCursorPosition(h, home);
}

void standardcout(std::initializer_list<std::string> texts, int howmanyspace)
{
    int n = texts.size();
    int max = 0;

    // 找到最长的字符串长度
    for (const auto& text : texts)
    {
        int size = text.size();
        if (size > max)
        {
            max = size;
        }
    }

    int length = max + 2 * howmanyspace;

    // 打印上边框
    for (int i = 0; i < length; i++)
    {
        cout << "-";
    }
    cout << endl;

    // 打印内容
    for (const auto& text : texts)
    {
        cout << "|";
        for (int j = 0; j < howmanyspace; j++)
        {
            cout << " ";
        }
        cout << text;

        // 添加右侧空格使所有行等宽
        int spaces_needed = max - text.size() + howmanyspace;
        for (int j = 0; j < spaces_needed; j++)
        {
            cout << " ";
        }
        cout << "|" << endl;
    }

    // 打印下边框
    for (int i = 0; i < length; i++)
    {
        cout << "-";
    }
    cout << endl;
}