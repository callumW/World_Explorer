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
#ifndef TERRAIN_MANAGER_H
#define TERRAIN_MANAGER_H

#include <irrlicht.h>
#include <vector>

enum Terrain_type {
    flat_terrain
};

class Terrain_manager {
public:
    Terrain_manager(irr::scene::ISceneManager* smgr, int w, int h,
        Terrain_type type, irr::video::IVideoDriver* vd);
private:
    irr::scene::ISceneManager* scene_manager;   /**< reference to scene
                                                 * manger*/
    int width;
    int height;
    Terrain_type tt;
    std::vector<irr::scene::IMeshSceneNode*> mesh_nodes;
};
#endif
