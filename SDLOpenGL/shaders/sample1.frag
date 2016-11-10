R"(
	#version 330
    out vec4 color;
    //uniform vec4 LSampleFrag;
	uniform float threshold;
	in vec4 LSampleFrag;
	in vec4 pposition;
    void main()
    { 
		vec4 colormodifier = vec4(0.0,0.0,0.0,1.0);
		if (pposition.x > threshold)
			colormodifier += vec4(0.0,0.5,0.0,0.0);
		else if (pposition.x < -threshold)
			colormodifier += vec4(0.5,0.0,0.0,0.0);
		
		if (pposition.y > threshold)
			colormodifier += vec4(0.0,0.5,0.0,0.0);
		else if (pposition.y < -threshold)
			colormodifier += vec4(0.5,0.0,0.0,0.0);
		
		color = LSampleFrag + colormodifier;
    }
)"