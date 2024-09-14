#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>

class TextRenderer {
public:
    TextRenderer();
    ~TextRenderer();

    void init(int screenWidth, int screenHeight);
    void renderText(const std::string& text, float x, float y, float scale);

private:
    unsigned int VAO, VBO;
    unsigned int shaderProgram;

    void setupShaders();
    void checkShaderCompileErrors(unsigned int shader, std::string type);
};

#endif