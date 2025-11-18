#ifndef SIGNING_MANAGER_H
#define SIGNING_MANAGER_H

#include <memory>
#include "Signing_Tools.h"

class Signing_ManagerLXY {
public:
    Signing_ManagerLXY();
    ~Signing_ManagerLXY();

    /* Æ½Ì¨ÇÐ»» */
    void setPlatform(std::unique_ptr<Signing_FactoryLXY> factory);
    void setMainPlatform();
    void setQQPlatform();
    void setWeChatPlatform();
    void setWeiBoPlatform();

    /* µÇÂ¼×¢²á */
    LoginStatus signIn();
	LoginStatus signIn(int id);
    LoginStatus signIn_for_binding(int id);
    LoginStatus signUp();

    /* ×´Ì¬ */
    bool isPlatformSet() const;

private:
    std::unique_ptr<Signing_PlatformLXY> currentPlatform;
    std::unique_ptr<Signing_FactoryLXY>   currentFactory;
};

#endif // SIGNING_MANAGER_H
