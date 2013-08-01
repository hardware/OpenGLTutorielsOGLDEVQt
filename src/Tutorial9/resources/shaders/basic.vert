#version 330

in vec3 vertexPosition;

uniform mat4 gWorld;

out vec4 Color;

void main()
{
    Color = vec4(clamp(vertexPosition, 0.0, 1.0), 1.0);
    gl_Position = gWorld * vec4(vertexPosition, 1.0);
}
