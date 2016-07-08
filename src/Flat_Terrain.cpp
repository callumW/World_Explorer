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
#include "irrlicht.h"
#include "Flat_Terrain.h"
#include <assert.h>
#include <iostream>
using namespace irr;

Flat_Terrain::Flat_Terrain(u16 t_width, u16 t_height, f32 t_scale,
    video::IVideoDriver* driver)
    : width{t_width}, height{t_height}, scale{t_scale}
{
    mesh = new scene::SMesh();

    const u32 max_primitives = driver->getMaximalPrimitiveCount();
    const u32 strip_width = max_primitives / (6 * height);

    u32 i=0;
    for (u32 y0=0; y0 < height; y0 += strip_width) {
        u16 y1 = y0 + strip_width;

        if (y1 >= height) {
            y1 = height - 1;
        }

        add_strip(y0, y1, i);
        i++;
    }

    if (i<mesh->getMeshBufferCount()) {
        for (u32 j=i; j<mesh->getMeshBufferCount(); j++) {
            mesh->getMeshBuffer(j)->drop();
        }

        mesh->MeshBuffers.erase(i, mesh->getMeshBufferCount()-i);
    }

    mesh->setDirty();    //signal that this mesh has changed
    mesh->recalculateBoundingBox();
}

Flat_Terrain::~Flat_Terrain()
{
    mesh->drop();
}

void Flat_Terrain::add_strip(u16 y0, u16 y1, u32 bufNum)
{
    scene::SMeshBuffer* buf = 0;
    if (bufNum < mesh->getMeshBufferCount()) {
        buf = (scene::SMeshBuffer*) mesh->getMeshBuffer(bufNum);
    }
    else {
        buf = new scene::SMeshBuffer();
        mesh->addMeshBuffer(buf);
        buf->drop();
    }

    assert(buf != 0);

    buf->Vertices.set_used((1 + y1 - y0)*width);
    const f32 z = 0.0f;
    u32 i=0;
    for (u16 y=y0; y<=y1; y++) {
        for (u16 x=0; x < width; x++) {

            const f32 xx = (f32)x/(f32)width;
            const f32 yy = (f32)x/(f32)height;

            video::S3DVertex& v = buf->Vertices[i++];

            v.Pos = core::vector3df{x, scale*z, y};
            v.Normal = core::vector3df{0, 1, 0}.normalize();
            v.Color = video::SColor{255, 255, 255, 255};
            v.TCoords = core::vector2df{xx, yy};
        }
    }

    buf->Indices.set_used(6*(width - 1)*(y1-y0));
    i=0;
    for(u16 y = y0; y < y1; y++)
    {
        for(u16 x = 0; x < width - 1; x++)
        {
            const u16 n = (y-y0) * width + x;
            buf->Indices[i]=n;
            buf->Indices[++i]=n + width;
            buf->Indices[++i]=n + width + 1;
            buf->Indices[++i]=n + width + 1;
            buf->Indices[++i]=n + 1;
            buf->Indices[++i]=n;
            ++i;
        }
    }

    buf->recalculateBoundingBox();
}
