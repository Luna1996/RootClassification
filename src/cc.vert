#version 440

uniform mat4 mvp;

in vec4 vertex;
in int vmark;
in vec3 color;
flat out int mark;
out vec3 C;

void main(){
	mark=vmark;
	C=color;
	vec4 temp = mvp*vertex;
	gl_Position	= temp;
}
