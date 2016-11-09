R"(
	#version 330
    out vec4 color;
    uniform vec4 LSampleFrag;
    void main()
    {
		color = LSampleFrag;
    }
)"