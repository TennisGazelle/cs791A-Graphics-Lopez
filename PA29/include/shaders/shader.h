#ifndef SHADER_H
#define SHADER_H

#include <vector>
#include <string>
#include <sstream>
#include <fstream>

#include "graphics_headers.h"

using namespace std;

class Shader {
public:
    Shader();
    ~Shader();
    virtual bool Initialize();
    void Enable();
    bool LoadShader(GLenum ShaderType, std::string filename = "");
    bool Finalize();
    GLint GetUniformLocation(const char* pUniformName);
    virtual bool LinkShaderProps() = 0;
    virtual bool FullInitAndLink() = 0;

protected:
    GLuint m_shaderProg;
private:
    std::vector<GLuint> m_shaderObjList;
};

#endif  /* SHADER_H */
