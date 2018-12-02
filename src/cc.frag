#version 440

flat in int mark;

out vec4 color;

void main(void){
	switch (int(mark)){
		case 0:color=vec4(1,0,0,1);break;
		case 1:color=vec4(0,0,1,1);break;
		default:color=vec4(.5,.5,.5,1);break;
	}
}