//
// Created by cx9ps3 on 19.06.2023.
//

#include "FileMenu.h"
#include "../Shortcuts.h"
#include "../native_file_dialog/FileDialog.h"
#include "../MessageBox.h"
#include "../../IconsFontAwesome5.h"
#include "../../../project/Project.h"
#include <imgui.h>

edit::gui::FileMenu::FileMenu(std::string name) : Menu(std::move(name))
{
    newProjectWindow = core::mem::make_unique<NewProjectWindow>("New Project");

    saveAsFileCallback = [](){

        FileDialog fileDialog;
        INativeFileDialog::FileFilter filter;
        std::string pathToProject;

        std::pair<std::string,std::string> allFiles , sceneFile;

        allFiles.first = "All files";
        allFiles.second = "all";

        sceneFile.first = "Scene";
        sceneFile.second = "hxscene;";

        filter.push_back(allFiles);
        filter.push_back(sceneFile);

        std::string path;
        if (fileDialog.saveDialog(filter, pathToProject, path) == INativeFileDialog::Status::STATUS_ERROR)
        {
            ImGuiMessageBox::add(std::string("Error!"),std::string("Failed to saving file"));
        }

    };

    saveFileCallback = [](){

    };

    newSceneCallback = [](){

    };

    openSceneCallback = []() {

        FileDialog fileDialog;
        INativeFileDialog::FileFilter filter;
        std::string pathToProject;
        filter.push_back({{"Scenes"},{"hxscene;"}});
        std::string path;
        if (fileDialog.openDialog(filter, pathToProject, path) == INativeFileDialog::Status::STATUS_ERROR)
        {
            ImGuiMessageBox::add(std::string("Error!"),std::string("Failed to select scene file!"));
        }

    };


    Shortcuts::addShortcut({ImGuiKey_LeftCtrl,ImGuiKey_S},saveFileCallback);
    Shortcuts::addShortcut({ImGuiKey_LeftCtrl,ImGuiKey_O},openSceneCallback);
    Shortcuts::addShortcut({ImGuiKey_LeftCtrl,ImGuiKey_N},newSceneCallback);
    Shortcuts::addShortcut({ImGuiKey_LeftCtrl,ImGuiKey_LeftShift,ImGuiKey_S}, saveAsFileCallback);
}

void edit::gui::FileMenu::begin()
{
    newProjectWindow->begin();
}

void edit::gui::FileMenu::draw()
{
    showMainMenu();
    newProjectWindow->draw();
}

void edit::gui::FileMenu::end()
{
    newProjectWindow->end();
}

void edit::gui::FileMenu::showMainMenu()
{
    if(ImGui::BeginMainMenuBar())
    {
        show();
        ImGui::EndMainMenuBar();
    }
}



void edit::gui::FileMenu::show()
{
    auto callback = [this]() {
        showNewScene();
        showOpenScene();
        showOpenRecentScene();
        ImGui::Separator();
        showNewProject();
        showOpenProject();
        showSaveProject();
        ImGui::Separator();
        showSave();
        showSaveAs();
        ImGui::Separator();
        showExit();
    };
    showMenu(getName(),callback);
}

void edit::gui::FileMenu::showNewScene()
{

    showMenuItem( ICON_FA_MAP " New Scene","CTRL+N",newSceneCallback);
}

void edit::gui::FileMenu::showOpenScene()
{

    showMenuItem( ICON_FA_FILE_IMPORT" Open Scene","CTRL+O",openSceneCallback);
}

void edit::gui::FileMenu::showOpenRecentScene()
{
    auto callback = [this]() {

    };
    showMenu(ICON_FA_FILE_IMPORT" Open Recent Scene",callback);
}

void edit::gui::FileMenu::showSave()
{

    showMenuItem(ICON_FA_SAVE" Save","CTRL+S",saveFileCallback);
}

void edit::gui::FileMenu::showSaveAs()
{
    showMenuItem(ICON_FA_FOLDER_OPEN " Save As...","CTRL+SHIFT+S",saveAsFileCallback);
}

void edit::gui::FileMenu::showNewProject()
{
    auto callback = [this] ()
    {
        newProjectWindow->setOpen(true);
    };
    showMenuItem(ICON_FA_FOLDER_OPEN " New Project...", "",callback);
}

void edit::gui::FileMenu::showOpenProject()
{
    auto callback = [this]() {

        FileDialog fileDialog;
        INativeFileDialog::FileFilter filter;
        std::string pathToProject;
        filter.push_back({{"Project"},{"hxproj;"}});
        std::string path;

        auto status = fileDialog.openDialog(filter, pathToProject, path);

        if ( status == INativeFileDialog::Status::STATUS_ERROR)
        {
            ImGuiMessageBox::add(std::string("Error!"),std::string("Failed to select project file!"));
        }
        else if (status == INativeFileDialog::Status::STATUS_OK)
        {
            auto project = core::mem::make_shared<Project>(path);
            Project::setCurrentProject(project);
        }
    };
    showMenuItem(ICON_FA_FILE" Open Project...", "",callback);
}

void edit::gui::FileMenu::showSaveProject()
{
    auto callback = [this]() {

        auto project = Project::getCurrentProject();
        project->save();
    };
    showMenuItem(ICON_FA_SAVE" Save Project", "",callback);
}

void edit::gui::FileMenu::showExit()
{
    auto callback = [this]() {

        exit(0);
    };
    showMenuItem(ICON_FA_WINDOW_CLOSE" Exit", "",callback);
}