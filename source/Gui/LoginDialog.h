#pragma once

#include "Network/Definitions.h"

#include "AlienDialog.h"
#include "Definitions.h"

class _LoginDialog : public _AlienDialog
{
public:
    _LoginDialog(
        SimulationController const& simController, 
        BrowserWindow const& browserWindow,
        CreateUserDialog const& createUserDialog,
        ActivateUserDialog const& activateUserDialog,
        ResetPasswordDialog const& resetPasswordDialog);
    ~_LoginDialog();

    bool isShareGpuInfo() const;

private:
    void processIntern();

    void onLogin();

    void saveSettings();
    UserInfo getUserInfo(); //can only be called when a simulation is loaded

    SimulationController _simController; 
    BrowserWindow _browserWindow;
    CreateUserDialog _createUserDialog;
    ActivateUserDialog _activateUserDialog;
    ResetPasswordDialog _resetPasswordDialog;

    bool _shareGpuInfo = true;
    bool _remember = true;
    std::string _userName;
    std::string _password;
};