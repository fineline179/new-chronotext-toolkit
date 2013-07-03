#include "chronotext/texture/TextureManager.h"

using namespace std;
using namespace ci;

TextureManager::~TextureManager()
{
    for (auto it = cache.begin(); it != cache.end(); ++it)
    {
        delete *it;
    }
}

Texture* TextureManager::getFromCache(const TextureRequest &textureRequest)
{
    for (auto it = cache.cbegin(); it != cache.cend(); ++it)
    {
        Texture *texture = *it;

        if (textureRequest == texture->request)
        {
            return texture;
        }
    }
    
    return NULL;
}

void TextureManager::putInCache(Texture *texture)
{
    cache.push_back(texture);
}

Texture* TextureManager::getTexture(const string &resourceName, bool useMipmap, int flags, GLenum wrapS, GLenum wrapT)
{
    return getTexture(InputSource::getResource(resourceName), useMipmap, flags, wrapS, wrapT);
}

Texture* TextureManager::getTexture(InputSourceRef inputSource, bool useMipmap, int flags, GLenum wrapS, GLenum wrapT)
{
    return getTexture(TextureRequest(inputSource, useMipmap, flags, wrapS, wrapT));
}

Texture* TextureManager::getTexture(const TextureRequest &textureRequest)
{
    Texture *texture = getFromCache(textureRequest);
    
    if (!texture)
    {
        texture = new Texture(textureRequest);
        putInCache(texture);
    }
    
    return texture;
}

bool TextureManager::remove(Texture *texture)
{
    for (auto it = cache.begin(); it != cache.end(); ++it)
    {
        if (texture == *it)
        {
            delete *it;
            cache.erase(it);

            return true;
        }
    }
    
    return false;
}

void TextureManager::clear()
{
    for (auto it = cache.begin(); it != cache.end(); ++it)
    {
        delete *it;
    }

    cache.clear();
}

void TextureManager::unload()
{
    if (!unloaded)
    {
        unloaded = true;
        
        for (auto it = cache.begin(); it != cache.end(); ++it)
        {
            (*it)->unload();
        }
    }
}

void TextureManager::reload()
{
    if (unloaded)
    {
        unloaded = false;
        
        for (auto it = cache.begin(); it != cache.end(); ++it)
        {
            (*it)->reload();
        }
    }
}
