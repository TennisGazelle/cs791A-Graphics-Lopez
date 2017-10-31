#include <textureManager.h>
#include "object.h"

Object::Object() {
    VBO = 0;
    IBO = 0;
}

// TODO safely delete the buffers from OpenGL
Object::~Object() = default;

bool Object::Init(const std::string &filename) {
    if (!LoadVerticiesFromFile(filename)) {
        printf("Error loading file\n");
        return false;
    }

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW);

    return true;
}

bool Object::LoadVerticiesFromFile(const std::string &filename) {
    //declare incoming variables stuff
    Assimp::Importer importer;
    const aiScene *aiScene = importer.ReadFile(filename, aiProcess_Triangulate | aiProcess_CalcTangentSpace);
    if (aiScene == nullptr) {
        std::cerr << "File contents had problems but was successfully opened." << std::endl;
        return false;
    }

    // iterate through the meshes and go through
    for (unsigned int meshIndex = 0; meshIndex < aiScene->mNumMeshes; meshIndex++) {
        int numFacesInMesh = aiScene->mMeshes[meshIndex]->mNumFaces;
        //iterate through faces
        for (int faceIndex = 0; faceIndex < numFacesInMesh; faceIndex++) {
            //helper
            Vertex tempVert(glm::vec3(0.0), glm::vec3(0.0), glm::vec3(0.0), glm::vec3(0.0), glm::vec2(-1.0f));

            //get val from faces' mIndeces array
            for (int i = 0; i < 3; i++) {
                //go to aiMesh's mVertices Array
                unsigned int vertexIndex = aiScene->mMeshes[meshIndex]->mFaces[faceIndex].mIndices[i];

                //get position
                for (int j = 0; j < 3; j++) {
                    tempVert.position[j] = aiScene->mMeshes[meshIndex]->mVertices[vertexIndex][j];
                    tempVert.color[j] = float(rand() % 100) / 100.0f;
                    //tempVert.color[j] = 0;
                    tempVert.normal[j] = aiScene->mMeshes[meshIndex]->mNormals[vertexIndex][j];
                    tempVert.tangent[j] = aiScene->mMeshes[meshIndex]->mTangents[vertexIndex][j];
                }

                if (aiScene->mMeshes[meshIndex]->mTextureCoords != nullptr) {
                    tempVert.uv[0] = aiScene->mMeshes[meshIndex]->mTextureCoords[0][vertexIndex][0];
                    tempVert.uv[1] = aiScene->mMeshes[meshIndex]->mTextureCoords[0][vertexIndex][1];
                }

                //add to the final vec
                vertices.push_back(tempVert);
                indices.push_back(vertexIndex);
            }
        }
    }

    return true;
}

void Object::SetTextureID(const std::string &textID) {
    textureID = textID;
}

void Object::Update(unsigned int dt) {
    // angle += dt * M_PI/1000;
    // model = glm::rotate(glm::mat4(1.0f), (angle), glm::vec3(0.0, 1.0, 0.0));
}

glm::mat4 Object::GetModel() {
    return model;
}

void Object::setModel(const glm::mat4 &incomingMatrix) {
    model = incomingMatrix;
}

void Object::Render() {
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
    glEnableVertexAttribArray(4);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, position));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, color));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, normal));
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, tangent));
    glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, uv));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    // if my textureID is not the null string, ask the manager to activate it
    if (!textureID.empty()) {
        TextureManager::getInstance()->setTextureUnit(0);
        TextureManager::getInstance()->enableTexture(textureID, GL_TEXTURE0);
    }

    glDrawElements(GL_TRIANGLES, (GLsizei) indices.size(), GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(3);
    glDisableVertexAttribArray(4);

//    glDisable(GL_TEXTURE0);
}
