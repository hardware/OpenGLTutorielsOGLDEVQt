#version 330

in vec3 vertexPosition;
in vec3 vertexColor;

uniform mat4 gWorld;

out vec3 Color;

void main()
{
    Color = vertexColor;
    gl_Position = gWorld * vec4(vertexPosition, 1.0);
}
