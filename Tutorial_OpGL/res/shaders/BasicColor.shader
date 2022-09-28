#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 colorSample;

out vec4 vertexColor;

uniform mat4 u_MVP;

void main()
{
	vertexColor = colorSample;
	gl_Position = u_MVP * position;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec4 vertexColor;

void main()
{
	color = vertexColor;
};