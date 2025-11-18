#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <iostream>
#include <string>
#include <list>
#include <memory>
#include <functional>
#include <vector>

/*这里是四个结构体，储存四种账号的信息*/
struct QQaccountIfoLXY
{
    int QQid;
    std::string QQpassword;
    std::string name;
    bool ifconnect = false;
    bool ifonline = false;
};

struct WeChataccountIfoLXY
{
    int WeChatid;
    std::string WeChatpassword;
    std::string name;
    bool ifconnect = false;
    bool ifonline = false;
};

struct WeiBoaccountIfoLXY
{
    int WeiBoid;
    std::string WeiBopassword;
    std::string name;
    bool ifconnect = false;
    bool ifonline = false;
};

struct MainaccountIfoLXY
{
    int id;
    long long int phoneNumber;
    std::string email;
    std::string Username;
    std::string password;
    std::string date;
    std::string address;
    int QQid;
    int WeChatid;
    int WeiBoid;
    bool ifonline = false;
};

/*保持原始接口不变*/
class IReaderLXY
{
public:
    virtual ~IReaderLXY() = default;
    virtual std::list<void*> read() = 0; // 保持原始接口
};

class IWriterLXY
{
public:
    virtual ~IWriterLXY() = default;
    virtual void write(const std::list<void*>&) = 0; // 保持原始接口
};

class IViewerLXY
{
public:
    virtual ~IViewerLXY() = default;
    virtual void show(const std::list<void*>&) = 0; // 保持原始接口
};

/*修正后的模板化具体实现 - 内部使用智能指针，但对外保持原始接口*/
template <typename T>
class TypedReaderLXY : public IReaderLXY
{
private:
    std::vector<std::shared_ptr<T>> managedMemory; // 管理内存生命周期

public:
    std::list<void*> read() override
    {
        managedMemory.clear(); // 清理之前的内存

        std::list<T> typedData = readTyped();
        std::list<void*> result;

        for (const auto& item : typedData) {
            // 使用shared_ptr管理内存，但返回原始指针
            auto ptr = std::make_shared<T>(item);
            managedMemory.push_back(ptr);
            result.push_back(ptr.get());
        }
        return result;
    }

    virtual std::list<T> readTyped() = 0;

    // 提供内存管理方法
    void clearManagedMemory() {
        managedMemory.clear();
    }
};

template <typename T>
class TypedWriterLXY : public IWriterLXY
{
public:
    void write(const std::list<void*>& data) override
    {
        std::list<T> typedData;
        for (auto item : data) {
            if (!item) continue;
            typedData.push_back(*static_cast<T*>(item));
        }
        writeTyped(typedData);
    }

    virtual void writeTyped(const std::list<T>& data) = 0;
};

template <typename T>
class TypedViewerLXY : public IViewerLXY
{
public:
    void show(const std::list<void*>& data) override
    {
        std::list<T> typedData;
        for (auto item : data) {
            if (!item) continue;
            typedData.push_back(*static_cast<T*>(item));
        }
        showTyped(typedData);
    }

    virtual void showTyped(const std::list<T>& data) = 0;
};

/*具体实现类声明保持不变*/
class MainReaderLXY : public TypedReaderLXY<MainaccountIfoLXY>
{
public:
    std::list<MainaccountIfoLXY> readTyped() override;
};

class MainWriterLXY : public TypedWriterLXY<MainaccountIfoLXY>
{
public:
    void writeTyped(const std::list<MainaccountIfoLXY>& data) override;
};

class MainViewerLXY : public TypedViewerLXY<MainaccountIfoLXY>
{
public:
    void showTyped(const std::list<MainaccountIfoLXY>& data) override;
};

/*QQ*/
class QQReaderLXY : public TypedReaderLXY<QQaccountIfoLXY>
{
public:
    std::list<QQaccountIfoLXY> readTyped() override;
};

class QQWriterLXY : public TypedWriterLXY<QQaccountIfoLXY>
{
public:
    void writeTyped(const std::list<QQaccountIfoLXY>& data) override;
};

class QQViewerLXY : public TypedViewerLXY<QQaccountIfoLXY>
{
public:
    void showTyped(const std::list<QQaccountIfoLXY>& data) override;
};

/*WeChat*/
class WeChatReaderLXY : public TypedReaderLXY<WeChataccountIfoLXY>
{
public:
    std::list<WeChataccountIfoLXY> readTyped() override;
};

class WeChatWriterLXY : public TypedWriterLXY<WeChataccountIfoLXY>
{
public:
    void writeTyped(const std::list<WeChataccountIfoLXY>& data) override;
};

class WeChatViewerLXY : public TypedViewerLXY<WeChataccountIfoLXY>
{
public:
    void showTyped(const std::list<WeChataccountIfoLXY>& data) override;
};

/*WeiBo*/
class WeiBoReaderLXY : public TypedReaderLXY<WeiBoaccountIfoLXY>
{
public:
    std::list<WeiBoaccountIfoLXY> readTyped() override;
};

class WeiBoWriterLXY : public TypedWriterLXY<WeiBoaccountIfoLXY>
{
public:
    void writeTyped(const std::list<WeiBoaccountIfoLXY>& data) override;
};

class WeiBoViewerLXY : public TypedViewerLXY<WeiBoaccountIfoLXY>
{
public:
    void showTyped(const std::list<WeiBoaccountIfoLXY>& data) override;
};

/*工厂接口保持不变*/
class IFactoryLXY
{
public:
    virtual ~IFactoryLXY() = default;
    virtual std::unique_ptr<IReaderLXY> createReader() = 0;
    virtual std::unique_ptr<IWriterLXY> createWriter() = 0;
    virtual std::unique_ptr<IViewerLXY> createViewer() = 0;
};

/*具体工厂保持不变*/
template <typename T, typename ReaderT, typename WriterT, typename ViewerT>
class GenericFactoryLXY : public IFactoryLXY
{
public:
    std::unique_ptr<IReaderLXY> createReader() override
    {
        return std::make_unique<ReaderT>();
    }

    std::unique_ptr<IWriterLXY> createWriter() override
    {
        return std::make_unique<WriterT>();
    }

    std::unique_ptr<IViewerLXY> createViewer() override
    {
        return std::make_unique<ViewerT>();
    }
};

/*写个别称*/
using MainFactoryLXY = GenericFactoryLXY<MainaccountIfoLXY, MainReaderLXY, MainWriterLXY, MainViewerLXY>;
using QQFactoryLXY = GenericFactoryLXY<QQaccountIfoLXY, QQReaderLXY, QQWriterLXY, QQViewerLXY>;
using WeChatFactoryLXY = GenericFactoryLXY<WeChataccountIfoLXY, WeChatReaderLXY, WeChatWriterLXY, WeChatViewerLXY>;
using WeiBoFactoryLXY = GenericFactoryLXY<WeiBoaccountIfoLXY, WeiBoReaderLXY, WeiBoWriterLXY, WeiBoViewerLXY>;

#endif // DATAMANAGER_H