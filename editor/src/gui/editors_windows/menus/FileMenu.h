//
// Created by cx9ps3 on 19.06.2023.
//

#ifndef HEXENEDITOR_FILEMENU_H
#define HEXENEDITOR_FILEMENU_H

#include "Menu.h"
#include "../NewProjectWindow.h"

namespace edit::gui
{
    class FileMenu  : public Menu
    {
    private:
        void showMainMenu();
        void showNewScene();
        void showOpenScene();
        void showOpenRecentScene();
        void showSave();
        void showSaveAs();
        void showNewProject();
        void showOpenProject();
        void showSaveProject();
        void show();
        void showExit();
        std::function<void()> saveFileCallback;
        std::function<void()> saveAsFileCallback;
        std::unique_ptr<NewProjectWindow> newProjectWindow;
        std::function<void()> newSceneCallback;
        std::function<void()> openSceneCallback;

    public:
        explicit FileMenu(std::string name);
        void begin() override;
        void draw() override;
        void end() override;
    };

}


#endif //HEXENEDITOR_FILEMENU_H