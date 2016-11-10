R"(
	#version 330 core
	in vec2 LVertexPos2D; 
	out vec4 position;
	void main() 
	{ 
		gl_Position = vec4( LVertexPos2D.x, LVertexPos2D.y , 0, 1 );
		position = gl_Position;
	}
)"