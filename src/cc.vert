uniform mat4 mvp;

in vec3 vertex;
in int vmark;
varying int mark;

void main(){
	mark=vmark;
	gl_Position	 = mvp*vec4(vertex,1);
}
