//
// Created by Daniel Lopez on 10/26/17.
//

#ifndef __CUBEMAP_TEXTURE_H_
#define __CUBEMAP_TEXTURE_H_


#include <string>
#include <vector>
#include <OpenGL/OpenGL.h>
#include <map>

using namespace std;

class CubeMapTexture {
public:
    CubeMapTexture(string directory,
                   const string& posX, const string& negX,
                   const string& posY, const string& negY,
                   const string& posZ, const string& negZ);

    bool Load();
    void Bind(GLenum textureUnit);
private:
    map<GLenum, string> faces;
    GLuint textureObj;
};


#endif //__CUBEMAP_TEXTURE_H_
