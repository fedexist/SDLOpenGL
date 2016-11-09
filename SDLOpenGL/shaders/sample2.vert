R"(
	#version 330 core
	in vec2 LVertexPos2D; 
	layout (location = 1) in vec3 color;
	out vec4 LSampleFrag;
	void main() 
	{ 
		gl_Position = vec4( LVertexPos2D.x, LVertexPos2D.y, 0, 1 );
		LSampleFrag = vec4(color, 1.0);
	}
)"