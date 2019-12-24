#version 330 core

// Vertex attributes
layout(location = 0) in vec3 aVertexPosition;
layout(location = 1) in vec3 aCubePosition;
layout(location = 2) in vec3 aNormal;
layout(location = 3) in vec4 aColor;

// Uniform : transformation matrix
uniform mat4 uMVPMatrix;
uniform mat4 uMVMatrix;
uniform mat4 uNormalMatrix;

// Output
out vec3 vNormal;
out vec4 vColor;

void main()
{
    vec4 position = vec4(aVertexPosition + aCubePosition, 1.0);

    vNormal = aNormal;
    vColor = aColor;

    gl_Position = uMVPMatrix * position;
}