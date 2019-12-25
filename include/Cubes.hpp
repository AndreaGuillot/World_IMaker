#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <glimac/glm.hpp>
#include <glimac/common.hpp>
#include <glimac/Program.hpp>
#include "ShaderProgram.hpp"
#include "TrackballCamera.hpp"

using namespace glimac;

/********************************
 *       CREATE A 3D CUBE       *
 ********************************/

class Cubes
{
    protected:
        std::vector<ShapeVertex> m_vertex;
        std::vector<glm::vec3> m_position;
        std::vector<glm::vec4> m_color;
        GLuint vbo;
        GLuint vbPos;
        GLuint vbCol;
        GLuint vao;
        GLuint ibo;
        GLuint iboWireframe;

    public:
        // constructor
        Cubes();
        // draw
        void getLocation(GLint &uMVPMatrix, GLint &uMVMatrix, GLint &uNormalMatrix, ShaderProgram &object);
        void transformMatrix(GLint &uMVPMatrix, GLint &uMVMatrix, GLint &uNormalMatrix, GLint &uLightDir, const TrackballCamera &camera) const;
        void drawCube();
        void drawCubeWireframe();
        void updateGPU();
        // color
        inline std::vector<glm::vec4> getColor() const { return m_color; }
        void editColor(glm::vec3 position, glm::vec4 color);
        // sculpting
        int findCube(glm::vec3 position);
        void removeCube(glm::vec3 position);
        void addCube(glm::vec3 position, glm::vec4 color);
        void extrudeCube(glm::vec3 position, glm::vec4 color);
        void digCube(glm::vec3 position);
        // delete data
        void deleteData();
        // destructor
        ~Cubes();
};