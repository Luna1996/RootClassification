#version 440

uniform mat4 mvp;

in vec4 vertex;
in int vmark;
flat out int mark;

void main(){
	mark=vmark;
	vec4 temp = mvp*vertex;
	gl_Position	= temp;
}
