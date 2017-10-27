//
// Created by Daniel Lopez on 10/26/17.
//

#ifndef __CUBEMAP_TEXTURE_CPP_
#define __CUBEMAP_TEXTURE_CPP_

#include <Magick++/Image.h>
#include "graphics_headers.h"
#include "cubeMapTexture.h"

CubeMapTexture::CubeMapTexture(string directory,
                               const string &posX, const string &negX,
                               const string &posY, const string &negY,
                               const string &posZ, const string &negZ) {
    if (directory.find('/') == -1) {
        directory += "/";
    }
    faces[GL_TEXTURE_CUBE_MAP_POSITIVE_X] = directory + posX;
    faces[GL_TEXTURE_CUBE_MAP_POSITIVE_Y] = directory + posY;
    faces[GL_TEXTURE_CUBE_MAP_POSITIVE_Z] = directory + posZ;
    faces[GL_TEXTURE_CUBE_MAP_NEGATIVE_X] = directory + negX;
    faces[GL_TEXTURE_CUBE_MAP_NEGATIVE_Y] = directory + negY;
    faces[GL_TEXTURE_CUBE_MAP_NEGATIVE_Z] = directory + negZ;
}

bool CubeMapTexture::Load() {
    glGenTextures(1, &textureObj);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureObj);

    Magick::Image texture;
    Magick::Blob blob;

    // load each image over
    for (auto face : faces) {
        cout << "reading in: " << face.second << endl;
        texture.read(face.second);
        try {
            GLsizei width = (GLsizei) texture.columns();
            GLsizei height = (GLsizei) texture.rows();

            texture.write(&blob, "RGBA");

            glTexImage2D(face.first, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, blob.data());

            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        } catch (Magick::Error& error) {
            cerr << "Error in reading stuff for skybox:" << face.second << endl;
            cerr << "Error: " << error.what() << endl;
            return false;
        }

    }
    return true;
}

void CubeMapTexture::Bind(GLenum textureUnit) {
    glActiveTexture(textureUnit);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureObj);
}

#endif // __CUBEMAP_TEXTURE_CPP_