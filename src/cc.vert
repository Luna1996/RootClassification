uniform mat4 mvp;

in vec3 vertex;
in vec3 vcolor;
varying vec3 color;

void main(){
	color = vcolor;
	vec4 tmp = mvp*vec4(vertex,1);
	gl_Position	 = vec4(tmp.xy,0,1);
}
