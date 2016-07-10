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
                irr::core::vector3df{x*255, 0, y*255},
                irr::core::vector3df{0, 0, 0}));

            if (mesh_nodes[y*width_patches + x] != NULL) {
                mesh_nodes[y*width_patches + x]->setMaterialFlag(
                    irr::video::EMF_BACK_FACE_CULLING, true);
                mesh_nodes[y*width_patches + x]->setMaterialFlag(
                    irr::video::EMF_WIREFRAME, true);
            }
            else {
                mesh_nodes.pop_back();
                std::cout << "Error in terrain mesh" << std::endl;
            }
        }
    }
}
