#version 330 core

// Vertex attributes
layout(location = 0) in vec3 aVertexPosition;
layout(location = 1) in vec3 aVertexNormal;
layout(location = 2) in vec2 aVertexTexture;
layout(location = 3) in vec3 aCubePosition;
layout(location = 4) in vec4 aCubeColor;

// Uniform : transformation matrix
uniform mat4 uMVPMatrix;
uniform mat4 uMVMatrix;
uniform mat4 uNormalMatrix;

// Output
out vec3 vFragPosition;
out vec3 vNormal;
out vec4 vColor;
out vec2 vTexture;
out vec3 vPosition;

void main()
{
    vec4 position = vec4(aVertexPosition + aCubePosition, 1.0);
    vPosition = position.xyz;
    gl_Position = uMVPMatrix * position;
    // output
    vFragPosition = aVertexPosition;
    vTexture = aVertexTexture;
    vNormal = aVertexNormal;
    vColor = aCubeColor;
}