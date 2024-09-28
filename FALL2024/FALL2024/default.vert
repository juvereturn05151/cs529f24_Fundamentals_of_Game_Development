#version 330 core
// Positions/Coordinates
layout (location = 0) in vec3 position;
// Colors  // Expecting RGBA here
layout (location = 1) in vec4 vertexColor;

//Outputs the color for the Fragment Shader
out vec4 color;

void main()
{
	gl_Position = vec4(position.x, position.y, position.z, 1.0);
	color = vertexColor;
}