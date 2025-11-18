#ifndef Data_Manager
#define Data_Manager

#include <memory>
#include <list>
#include <stdexcept>
#include <vector>
#include "Data_Tools.h"

class Data_ManagerLXY
{
private:
    std::unique_ptr<IReaderLXY> reader;
    std::unique_ptr<IWriterLXY> writer;
    std::unique_ptr<IViewerLXY> viewer;
    std::unique_ptr<IFactoryLXY> currentFactory;

    // 管理从reader读取的内存
    std::vector<std::shared_ptr<void>> managedMemory;

    // 内部类型转换辅助方法 - 保持原始接口
    template<typename T>
    std::list<void*> convertToVoidList(const std::list<T>& typedData)
    {
        std::list<void*> voidData;
        for (const auto& item : typedData)
        {
            // 深拷贝到堆，再存指针
            voidData.push_back(new T(item));
        }
        return voidData;
    }

    template<typename T>
    std::list<T> convertFromVoidList(const std::list<void*>& voidData)
    {
        std::list<T> typedData;
        for (auto item : voidData)
        {
            if (!item) continue;
            T* raw = static_cast<T*>(item);
            typedData.push_back(*raw); // 使用拷贝构造，避免移动问题
            // 注意：这里不删除指针，因为指针由Reader管理
        }
        return typedData;
    }

    // 清理管理的内存
    void clearManagedMemory() {
        managedMemory.clear();
    }

public:
    Data_ManagerLXY() = default;

    ~Data_ManagerLXY() {
        clearManagedMemory();
    }

    // 设置工厂
    void setFactory(std::unique_ptr<IFactoryLXY> factory)
    {
        // 清理旧的内存
        clearManagedMemory();

        currentFactory = std::move(factory);
        reader = currentFactory->createReader();
        writer = currentFactory->createWriter();
        viewer = currentFactory->createViewer();
    }

    void setMainFactory() { setFactory(std::make_unique<MainFactoryLXY>()); }
    void setQQFactory() { setFactory(std::make_unique<QQFactoryLXY>()); }
    void setWeChatFactory() { setFactory(std::make_unique<WeChatFactoryLXY>()); }
    void setWeiBoFactory() { setFactory(std::make_unique<WeiBoFactoryLXY>()); }

    //读取
    template<typename T>
    std::list<T> readData()
    {
        if (!reader) throw std::runtime_error("Reader not initialized");

        // 清理旧内存
        clearManagedMemory();

        auto voidData = reader->read();
        return convertFromVoidList<T>(voidData);
    }

    // 写入
    template<typename T>
    void writeData(const std::list<T>& data)
    {
        if (!writer) throw std::runtime_error("Writer not initialized");
        auto voidData = convertToVoidList(data);

        // 写入完成后立即清理临时内存
        writer->write(voidData);
        for (auto ptr : voidData) {
            delete static_cast<T*>(ptr);
        }
    }

    // 显示
    template<typename T>
    void showData(const std::list<T>& data)
    {
        if (!viewer) throw std::runtime_error("Viewer not initialized");
        auto voidData = convertToVoidList(data);

        viewer->show(voidData);

        // 显示完成后立即清理临时内存
        for (auto ptr : voidData) {
            delete static_cast<T*>(ptr);
        }
    }
    //读取并自动显示
    template<typename T>
    void readAndShow()
    {
        auto data = readData<T>();
        showData(data);
    }
    // 检查是否已设置工厂
    bool isInitialized() const
    {
        return reader != nullptr && writer != nullptr && viewer != nullptr;
    }
};

#endif // Data_Manager