#include "Terrain_generator.h"
#include "Shader_call_back.h"
#include <irrlicht.h>
#include <assert.h>

Terrain_generator::Terrain_generator(int w, int h, irr::scene::ISceneManager*
    smgr, irr::video::IVideoDriver* d) : width{w}, height{h}
{
    assert(smgr != NULL);
/*
    Shader_call_back* mc = new Shader_call_back();

    irr::video::IGPUProgrammingServices* gpu = d->getGPUProgrammingServices();

    irr::s32 height_color_material = 0;

    const irr::video::E_GPU_SHADING_LANGUAGE shading_language =
        irr::video::EGSL_DEFAULT;

    height_color_material = gpu->addHighLevelShaderMaterialFromFiles(
        "height_color.vert", "vertexMain", irr::video::EVST_VS_1_1,
        "height_color.frag", "pixelMain", irr::video::EPST_PS_1_1,
        mc, irr::video::EMT_SOLID, 0, shading_language);
*/
    for (int y=0; y<height; y++) {
        for (int x=0; x<width; x++) {
            terrains.push_back(smgr->addTerrainSceneNode(
                "Map.bmp",
                NULL,
                -1,
                irr::core::vector3df{x*512.0f, 0.0f, y*512.0f},
                irr::core::vector3df{0, 0, 0},
                irr::core::vector3df{0.125f, 0.0375, 0.125f}));
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

                if (!shaders) {
                    terrains[y*width + x]->setMaterialTexture(0,
                        d->getTexture("Color_Map.bmp"));
                }
                else {/*
                    terrains[y*width + x]->setMaterialType(
                        (irr::video::E_MATERIAL_TYPE)height_color_material);*/
                }
            }
        }
    }
}

Terrain_generator::~Terrain_generator()
{
    for (irr::scene::ITerrainSceneNode* node : terrains) {
        node->drop();
    }
}
