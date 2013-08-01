#version 330

in vec3 vertexPosition;
in vec3 vertexColor;

uniform mat4 gWVP;

out vec3 Color;

void main()
{
    Color = vertexColor;
    gl_Position = gWVP * vec4(vertexPosition, 1.0);
}
