//
// Created by cx9ps3 on 13.07.2023.
//

#include "FramebufferWindow.h"
#include "imgui.h"
#include "imgui_internal.h"
#include <iostream>
#include <GL/glew.h>


edit::gui::FramebufferWindow::FramebufferWindow(const std::string &name) : GUIWindow(name)
{
    frameBufferTexture = core::mem::make_unique<core::rend::FrameBufferTexture>(glm::vec2(1280,720));
    frameBufferObject.bindRenderBuffer();
    frameBufferObject.setSize(glm::vec2(1280,720));
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "S_ERROR::FRAMEBUFFER:: Framebuffer is not complete!\n";
    }
    frameBufferObject.unbind();
    frameBufferTexture->unbind();
    frameBufferObject.unbindRenderBuffer();
}


void edit::gui::FramebufferWindow::draw()
{
    ImGui::Begin(getName().c_str());
    {
        // Using a Child allow to fill all the space of the window.
        // It also alows customization
        ImGui::BeginChild("GameRender");
        // Get the size of the child (i.e. the whole draw size of the windows).
        ImVec2 windowSize = ImGui::GetWindowSize();
        // Because I use the texture from OpenGL, I need to invert the V from the UV.
        ImGui::Image((ImTextureID)frameBufferTexture->getID(), windowSize, ImVec2(0, 1), ImVec2(1, 0));
        ImGui::EndChild();
    }
    ImGui::End();
}



void edit::gui::FramebufferWindow::clear()
{
    // Set background color as cornflower blue
    glClearColor(0.39f, 0.58f, 0.93f, 1.f);
    // Clear color buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void edit::gui::FramebufferWindow::end()
{

}



void edit::gui::FramebufferWindow::begin()
{

}

void edit::gui::FramebufferWindow::render()
{
    clear();
}


void edit::gui::FramebufferWindow::bindFramebuffer()
{
    frameBufferObject.bind();
    render();
}


void edit::gui::FramebufferWindow::unbindFramebuffer()
{

    frameBufferObject.unbind();
}
