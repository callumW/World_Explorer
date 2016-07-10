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
#include "Terrain_manager.h"
#include "Flat_Terrain.h"
#include <assert.h>
#include <iostream>

Terrain_manager::Terrain_manager(irr::scene::ISceneManager* smgr, int w, int h,
    Terrain_type type, irr::video::IVideoDriver* vd) : scene_manager{smgr},
    width{w}, height{h}, tt{type}
{
    assert(smgr != NULL);
    assert(vd != NULL);

    int width_patches;
    if (width % 256 != 0)
        width_patches = width / 256 + 1;
    else
        width_patches = width / 256;

    int height_patches;
    if (height % 256 != 0)
        height_patches = height / 256 + 1;
    else
        height_patches = height / 256;


    Flat_Terrain terrain{256, 256, 1, vd};
    for (int y=0; y<height_patches; y++) {
        for (int x=0; x<width_patches; x++) {
            mesh_nodes.push_back(scene_manager->addMeshSceneNode(
                terrain.mesh,
                NULL,
                -1,
                irr::core::vector3df{x*256, 0, y*256},
                irr::core::vector3df{0, 0, 0}));

            if (mesh_nodes[y*width_patches + x] != NULL) {
                mesh_nodes[y*width_patches + x]->setMaterialFlag(
                    irr::video::EMF_BACK_FACE_CULLING, true);
                mesh_nodes[y*width_patches + x]->setMaterialFlag(
                    irr::video::EMF_WIREFRAME, true);
                    mesh_nodes[y*width_patches + x]->setMaterialFlag(
                        irr::video::EMF_LIGHTING, false);
            }
            else {
                mesh_nodes.pop_back();
                std::cout << "Error in terrain mesh" << std::endl;
            }
        }
    }
}
