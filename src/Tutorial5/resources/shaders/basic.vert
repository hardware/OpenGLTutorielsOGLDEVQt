#version 330

in vec3 vertexPosition;
in vec3 vertexColor;

uniform float gScale;

out vec3 outColor;

void main()
{
    outColor = vertexColor;
    gl_Position = vec4(gScale * vertexPosition.x, gScale * vertexPosition.y, vertexPosition.z, 1.0);
}
