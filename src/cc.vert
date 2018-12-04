#version 440

uniform mat4 mvp;

in vec4 vertex;
in vec3 color;
out vec3 C;

void main(){
	C=color;
	vec4 temp = mvp*vertex;
	gl_Position	= temp;
}
