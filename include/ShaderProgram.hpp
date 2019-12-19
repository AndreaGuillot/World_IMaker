#pragma once

#include <GL/glew.h>
#include <iostream>
#include <glimac/Program.hpp>
#include "glimac/glm.hpp"

using namespace glimac;

struct ShaderProgram
{
    Program m_program;

    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;

    ShaderProgram(const FilePath &applicationPath, std::string object)
        : m_program(loadProgram(applicationPath.dirPath() + "../shaders/3D.vs.glsl", applicationPath.dirPath() + "../shaders" + object))
    {
        uMVPMatrix = glGetUniformLocation(m_program.getGLId(), "uMVPMatrix");
        uMVMatrix = glGetUniformLocation(m_program.getGLId(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(m_program.getGLId(), "uNormalMatrix");
    }
};