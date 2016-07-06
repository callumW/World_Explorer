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
#ifndef FLAT_TERRAIN_H
#define FLAT_TERRAIN_H
#include <irrlicht.h>

class Flat_Terrain {
public:
    /**
     * Constructor
     * \param t_width The width of the terrain
     * \param t_height The height of the terrain
     * \param t_scale The scale of the terrain
     */
    Flat_Terrain(irr::u16 t_width, irr::u16 t_height, irr::f32 t_scale,
        irr::video::IVideoDriver* driver);

    /**
     * Destructor
     * Drops pointer to the mesh
     */
    ~Flat_Terrain();

    irr::scene::SMesh* mesh;   /**< The mesh representation of the terrain */
private:
    irr::u16 width;  /**< width of the terrain */
    irr::u16 height; /**< height of the terrain */
    irr::f32 scale;  /**< scale of the terrain */

    /**
     * Add a strip between y0, and y1
     */
    void add_strip(irr::u16 y0, irr::u16 y1, irr::u32 bufNum);
};
#endif
