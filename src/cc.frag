varying int mark;

void main(void){
	switch (mark){
		case 0:gl_FragColor=vec4(1,0,0,1);break;
		case 1:gl_FragColor=vec4(0,0,1,1);break;
		case 2:gl_FragColor=vec4(.5,.5,.5,1);break;
	default:gl_FragColor=vec4(0,0,0,1);break;
	}
}