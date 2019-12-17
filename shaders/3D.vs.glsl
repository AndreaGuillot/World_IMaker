#version 330 core

// Vertex attributes
layout(location = 0) in vec3 aVertexPosition;
layout(location = 1) in vec3 aVertexNormal;
layout(location = 2) in vec2 aVertexTexCoords;

// Uniform : transformation matrix
uniform mat4 uMVPMatrix;
uniform mat4 uMVMatrix;
uniform mat4 uNormalMatrix;

// Output
out vec3 vFragPosition;
out vec3 vFragNormal;
out vec2 vFragTexCoords;

void main()
{
	// homogeneous coordinates
    vec4 vertexPosition = vec4(aVertexPosition, 1.0);
    vec4 vertexNormal = vec4(aVertexNormal, 0.0);
    // view coordinates
    vFragPosition = vec3(uMVMatrix * vertexPosition);
    vFragNormal = vec3(uNormalMatrix * vertexNormal);
    vFragTexCoords = aVertexTexCoords;
    // projected position
    gl_Position = uMVPMatrix * vertexPosition;
}