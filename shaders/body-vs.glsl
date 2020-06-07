#version 420

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vTexCoord;

uniform vec4 dColor;
uniform mat4 mvp;

out vec4 myColor;
out vec2 texCoord;

void main()
{
	gl_Position = mvp * vec4(vPosition, 1.0);
	myColor = dColor;
	texCoord = vTexCoord;
}
