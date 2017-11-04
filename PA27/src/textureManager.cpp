//
// Created by Daniel Lopez on 10/30/17.
//

#include "textureManager.h"

TextureManager* TextureManager::instance = nullptr;

TextureManager* TextureManager::getInstance() {
    if (instance == nullptr) {
        instance = new TextureManager();
    }
    return instance;
}

TextureManager::TextureManager() : samplerHander(0) {

}

bool TextureManager::initHandler(Shader *shaderManager) {
    samplerHander = shaderManager->GetUniformLocation("gSampler");
    return samplerHander != INVALID_UNIFORM_LOCATION;
}

bool TextureManager::addTexture(const string textName, string fileName) {
    auto* texture = new Texture;

    if (!texture->loadTexture(fileName)){
        printf("texture manager couldn't add texture with filename %s", fileName.c_str());
        return false;
    }
    textures.insert({textName, texture});
    return true;
}

void TextureManager::setTextureUnit(unsigned int samplerIndex) {
    if (samplerHander != 0) {
        glUniform1i(samplerHander, samplerIndex);
    }
}

void TextureManager::enableTexture(string textName, GLenum textureUnit) {
    if (textures.find(textName) != textures.end()) {
        textures[textName]->enable(textureUnit);
    }
}

void TextureManager::disableTexture(string textName) {
    if (textures.find(textName) != textures.end()) {
        textures[textName]->disable();
    }
}

Texture* TextureManager::getTexture(string textName) const {
    if (textures.find(textName) != textures.end()) {
        return textures.at(textName);
    }
    return nullptr;
}