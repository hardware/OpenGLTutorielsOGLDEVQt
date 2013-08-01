#version 330

in vec3 vertexPosition;
in vec3 vertexColor;

out vec3 outColor;

void main()
{
    outColor = vertexColor;
    gl_Position = vec4(0.5 * vertexPosition.x, 0.5 * vertexPosition.y, vertexPosition.z, 1.0);
}
