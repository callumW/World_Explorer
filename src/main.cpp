/*
COPYRIGHT (c) 2016 Callum Wilson

MIT License

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#include <irrlicht.h>
#include <iostream>
#include <assert.h>
#include <driverChoice.h>
#include "Input_Handler.h"
#include "Flat_Terrain.h"
using namespace irr;

constexpr u32 window_width = 1024;
constexpr u32 window_height = 768;

int main()
{
    /* Ask user to pick a graphics driver */
    video::E_DRIVER_TYPE driver_type = driverChoiceConsole();
    if (driver_type == video::EDT_COUNT) {
        std::cout << "Failed to get driver" << std::endl;
        return 1;
    }

    /** Window Variables **/
    core::dimension2d<u32> window_size{window_width, window_height};
    u32 bit_depth = 32;
    bool fullscreen = false;
    bool stencilbuffer = false;
    bool vsync = true;

    Input_Handler input_handler;

    /** setup window **/
    IrrlichtDevice *device = createDevice(driver_type, window_size,
        bit_depth, fullscreen, stencilbuffer, vsync, &input_handler);

    if (!device) {
        std::cout << "Failed to create device!" << std::endl;
        return 1;
    }

    device->setResizable(false);


    video::IVideoDriver* driver = device->getVideoDriver();
    gui::IGUIEnvironment* guienv = device->getGUIEnvironment();
    scene::ISceneManager* smgr = device->getSceneManager();

    guienv->addStaticText(L"!! Text!", core::rect<s32>(10, 10, 260, 44), true);
    scene::ICameraSceneNode* cam = smgr->addCameraSceneNodeFPS();
    if (cam) {
        cam->setPosition(core::vector3df(0, 0, -40));
        cam->setTarget(core::vector3df(3, 6, 2));
        cam->setFarValue(20000);
    }

    /** add mesh **/
    Flat_Terrain terrain{25, 25, 10.0, driver};

    scene::IMeshSceneNode* mesh_node = smgr->addMeshSceneNode(terrain.mesh);

    mesh_node->setMaterialFlag(video::EMF_BACK_FACE_CULLING, false);

    scene::ILightSceneNode *node = smgr->addLightSceneNode(0,
        core::vector3df(0,0,-40), video::SColorf(1.0f, 0.6f, 0.7f, 1.0f),
            500.0f);
    if (node)
    {
        node->getLightData().Attenuation.set(0.f, 1.f/500.f, 0.f);
    }

    device->getCursorControl()->setVisible(false);

    int lastFPS = -1;
    /** Enter main loop **/
    while (device->run()) {
        if (device->isWindowActive()) {

            if (input_handler.is_key_down(KEY_ESCAPE))
                device->closeDevice();

            driver->beginScene(true, true, video::SColor(255, 0, 0, 0));
            smgr->drawAll();
            guienv->drawAll();
            driver->endScene();

            int fps = driver->getFPS();
            /** Write FPS to window **/

            if (lastFPS != fps) {
                core::stringw str = L"World Explorer -";
                str += " FPS: ";
                str += fps;
                core::vector3df vec = cam->getTarget();

                str += " x: ";
                str += vec.X;
                str += " y: ";
                str += vec.Y;
                str += " z: ";
                str += vec.Z;

                core::vector3df pos_vec = cam->getPosition();

                str += " px: ";
                str += pos_vec.X;
                str += " py: ";
                str += pos_vec.Y;
                str += " pz: ";
                str += pos_vec.Z;

                device->setWindowCaption(str.c_str());
                lastFPS = fps;
            }
        }
        else {
            device->yield();
        }
    }

    device->drop();
    return 0;
}
