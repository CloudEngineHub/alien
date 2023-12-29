#pragma once

#include "Network/NetworkService.h"

#include "AlienDialog.h"
#include "Definitions.h"

class _ResetPasswordDialog : public _AlienDialog
{
public:
    _ResetPasswordDialog(NewPasswordDialog const& newPasswordDialog);

    void open(std::string const& userName, UserInfo const& userInfo);

private:
    void processIntern();

    void onResetPassword();

    NewPasswordDialog _newPasswordDialog; 

    std::string _userName;
    std::string _email;
    UserInfo _userInfo;
};