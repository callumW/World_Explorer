#ifndef SHADER_CALL_BACK_H
#define SHADER_CALL_BACK_H
#include <irrlicht.h>
class Shader_call_back : public irr::video::IShaderConstantSetCallBack {
public:
    virtual void OnSetConstants(irr::video::IMaterialRendererServices* services,
            irr::s32 userData);
};
#endif
