#version 330 core
// Positions/Coordinates
layout (location = 0) in vec3 aPos;
// Colors
layout (location = 1) in vec4 aColor;

//Outputs the color for the Fragment Shader
out vec4 color;

void main()
{
gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
color = aColor;
};