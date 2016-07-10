#include "Terrain_generator.h"
#include <irrlicht.h>
#include <assert.h>

Terrain_generator::Terrain_generator(int w, int h, irr::scene::ISceneManager*
    smgr, irr::video::IVideoDriver* d) : width{w}, height{h}
{
    assert(smgr != NULL);

    for (int y=0; y<height; y++) {
        for (int x=0; x<width; x++) {
            terrains.push_back(smgr->addTerrainSceneNode(
                "Map.bmp",
                NULL,
                -1,
                irr::core::vector3df{x*512.0f, 0.0f, y*512.0f},
                irr::core::vector3df{0, 0, 0},
                irr::core::vector3df{1.0f, 0.3f, 1.0f}));
            /*terrains.push_back(smgr->addTerrainMesh(
                "mesh.mesh",
                d->createImageFromFile("Color_Map.bmp"),
                d->createImageFromFile("Map.bmp")));*/
            if (terrains[y*width + x] == NULL)
                terrains.pop_back();
            else {
                /*terrains[y*width + x]->setMaterialFlag(
                    irr::video::EMF_WIREFRAME, true);*/
                terrains[y*width + x]->setMaterialFlag(
                    irr::video::EMF_LIGHTING, false);
                terrains[y*width + x]->setMaterialTexture(0,
                    d->getTexture("Color_Map.bmp"));
            }
        }
    }
}
