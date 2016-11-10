R"(
	#version 330
    layout (location = 0) in vec3 position;
    layout (location = 1) in vec3 color;
    out vec4 LSampleFrag;
	out vec4 pposition;
    void main()
    {
		float resize = 0.8f;
		
		gl_Position = vec4(position.xyz * resize, 1.0);
		pposition = gl_Position;
		LSampleFrag = vec4(0.0,0.0,1.0,1.0);
    }
)"