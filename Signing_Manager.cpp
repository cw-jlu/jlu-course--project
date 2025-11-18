#include "Signing_Manager.h"
#include <stdexcept>

Signing_ManagerLXY::Signing_ManagerLXY() = default;
Signing_ManagerLXY::~Signing_ManagerLXY() = default;

void Signing_ManagerLXY::setPlatform(std::unique_ptr<Signing_FactoryLXY> factory) {
    currentFactory = std::move(factory);
    currentPlatform = currentFactory->set_signing_platform();
}

void Signing_ManagerLXY::setMainPlatform() {
    setPlatform(std::make_unique<Main_FactoryLXY>());
}
void Signing_ManagerLXY::setQQPlatform() {
    setPlatform(std::make_unique<QQ_FactoryLXY>());
}
void Signing_ManagerLXY::setWeChatPlatform() {
    setPlatform(std::make_unique<WeChat_FactoryLXY>());
}
void Signing_ManagerLXY::setWeiBoPlatform() {
    setPlatform(std::make_unique<WeiBo_FactoryLXY>());
}

LoginStatus Signing_ManagerLXY::signIn() {
    if (!currentPlatform) throw std::runtime_error("平台未设置");
    return currentPlatform->sign_in();
}
LoginStatus Signing_ManagerLXY::signIn(int id) {
    if (!currentPlatform) throw std::runtime_error("平台未设置");
    return currentPlatform->sign_in(id);
}
LoginStatus Signing_ManagerLXY::signIn_for_binding(int id) {
    if (!currentPlatform) throw std::runtime_error("平台未设置");
    return currentPlatform->sign_in_for_binding(id);
}
LoginStatus Signing_ManagerLXY::signUp() {
    if (!currentPlatform) throw std::runtime_error("平台未设置");
    return currentPlatform->sign_up();
}

bool Signing_ManagerLXY::isPlatformSet() const {
    return currentPlatform != nullptr;
}