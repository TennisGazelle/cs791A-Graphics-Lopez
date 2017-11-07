//
// Created by Daniel Lopez on 10/30/17.
//

#ifndef TUTORIAL_TEXTUREMANAGER_H
#define TUTORIAL_TEXTUREMANAGER_H

#include <string>
#include <map>

using namespace std;

#include "graphics_headers.h"
#include "texture.h"
#include "shaders/shader.h"

class TextureManager {
public:
    static TextureManager* getInstance();

    bool initHandler(Shader *shaderManager);
    bool addTexture(const string textName, string fileName);
    void setTextureUnit(unsigned int samplerIndex);
    void enableTexture(string textName, GLenum textureUnit);
    void disableTexture(string textName);

    Texture* getTexture(string textName) const;

private:
    TextureManager();

    static TextureManager* instance;
    GLint samplerHander;
    map<string, Texture*> textures;
};

#define TMInstance TextureManager::getInstance()

#endif //TUTORIAL_TEXTUREMANAGER_H
