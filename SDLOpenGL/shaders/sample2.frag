R"(
	#version 330 core
	out vec4 color;
	uniform vec4 LSampleFrag;
	void main() 
	{ 
		color = LSampleFrag; 
	}
)"