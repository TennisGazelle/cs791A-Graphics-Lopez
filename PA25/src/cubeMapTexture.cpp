//
// Created by Daniel Lopez on 10/26/17.
//

#ifndef __CUBEMAP_TEXTURE_CPP_
#define __CUBEMAP_TEXTURE_CPP_

#include <Magick++/Image.h>
#include "graphics_headers.h"
#include "CubeMapTexture.h"

CubeMapTexture::CubeMapTexture(const string &directory,
                               const string &posX, const string &negX,
                               const string &posY, const string &negY,
                               const string &posZ, const string &negZ) {
    filenames.push_back(directory + posX);
    filenames.push_back(directory + posY);
    filenames.push_back(directory + posZ);
    filenames.push_back(directory + negX);
    filenames.push_back(directory + negY);
    filenames.push_back(directory + negZ);
}

void CubeMapTexture::Load() {
    glGenTextures(1, &textureObj);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureObj);

    Magick::Image texture;
    Magick::Blob blob;

    // load each image over
    for (auto filename : filenames) {
        cout << "reading in: " << filename << endl;

    }
}
#endif // __CUBEMAP_TEXTURE_CPP_