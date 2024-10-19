#include "MessageDialog.h"

#include <boost/algorithm/string.hpp>

#include <imgui.h>

#include "Base/LoggingService.h"

#include "AlienImGui.h"
#include "WindowController.h"

void MessageDialog::process()
{
    if (!_show) {
        return;
    }
    switch (_dialogType) {
    case DialogType::Information:
        processInformation();
        break;
    case DialogType::YesNo:
        processYesNo();
        break;
    }
}

void MessageDialog::information(std::string const& title, std::string const& message)
{
    _show = true;
    _title = title;
    _message = message;
    _dialogType = DialogType::Information;
    log(Priority::Important, "message dialog showing: '" + message + "'");
}

void MessageDialog::information(std::string const& title, std::vector<PersisterErrorInfo> const& errors)
{
    std::vector<std::string> errorMessages;
    for (auto const& error : errors) {
        errorMessages.emplace_back(error.message);
    }
    MessageDialog::get().information(title, boost::join(errorMessages, "\n\n"));
}

void MessageDialog::yesNo(std::string const& title, std::string const& message, std::function<void()> const& yesFunction)
{
    _show = true;
    _title = title;
    _message = message;
    _dialogType = DialogType::YesNo;
    _execFunction = yesFunction;
}

void MessageDialog::processInformation()
{
    ImGui::OpenPopup((_title + "##msg").c_str());
    ImGui::SetNextWindowPos(ImGui::GetMainViewport()->GetCenter(), ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
    if (ImGui::BeginPopupModal((_title + "##msg").c_str(), NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
        if (!_sizeInitialized) {
            auto size = ImGui::GetWindowSize();
            auto factor = WindowController::get().getContentScaleFactor() / WindowController::get().getLastContentScaleFactor();
            ImGui::SetWindowSize({size.x * factor, size.y * factor});
            _sizeInitialized = true;
        }

        AlienImGui::Text(_message);
        AlienImGui::Separator();

        if (AlienImGui::Button("OK")) {
            ImGui::CloseCurrentPopup();
            _show = false;
        }
        ImGui::EndPopup();
    }
}

void MessageDialog::processYesNo()
{
    ImGui::OpenPopup(_title.c_str());
    ImGui::SetNextWindowPos(ImGui::GetMainViewport()->GetCenter(), ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
    if (ImGui::BeginPopupModal(_title.c_str(), NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
        if (!_sizeInitialized) {
            auto size = ImGui::GetWindowSize();
            auto factor = WindowController::get().getContentScaleFactor() / WindowController::get().getLastContentScaleFactor();
            ImGui::SetWindowSize({size.x * factor, size.y * factor});
            _sizeInitialized = true;
        }

        AlienImGui::Text(_message);
        AlienImGui::Separator();

        if (AlienImGui::Button("Yes")) {
            ImGui::CloseCurrentPopup();
            _show = false;
            _execFunction();
        }
        ImGui::SameLine();
        if (AlienImGui::Button("No")) {
            ImGui::CloseCurrentPopup();
            _show = false;
        }
        ImGui::EndPopup();
    }
}
