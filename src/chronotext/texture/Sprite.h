/*
 * THE NEW CHRONOTEXT TOOLKIT: https://github.com/arielm/new-chronotext-toolkit
 * COPYRIGHT (C) 2012, ARIEL MALKA ALL RIGHTS RESERVED.
 *
 * THE FOLLOWING SOURCE-CODE IS DISTRIBUTED UNDER THE MODIFIED BSD LICENSE:
 * https://github.com/arielm/new-chronotext-toolkit/blob/master/LICENSE.md
 */

#pragma once

#include "chronotext/texture/Texture.h"

namespace chronotext
{
    typedef std::shared_ptr<class Sprite> SpriteRef;
    
    class Sprite
    {
    public:
        TextureRef texture;
        
        float w;
        float h;
        float ox;
        float oy;
        float ow;
        float oh;
        bool rotated;
        
        float tx1;
        float ty1;
        float tx2;
        float ty2;
        
        Sprite() {}
        Sprite(TextureRef texture); // IMAGE-BASED
        Sprite(TextureRef texture, float w, float h, float ox, float oy, float ow, float oh, bool rotated, float tx1, float ty1, float tx2, float ty2); // ATLAS-BASED
        
        ci::Vec2f getSize() const;
        float getWidth() const;
        float getHeight() const;
        
        void beginTexture();
        void endTexture();
        
        void drawFromCenter();
        void draw(float rx = 0, float ry = 0);
    };
}

namespace chr = chronotext;
