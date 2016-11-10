R"(
	#version 330 core
	out vec4 color;
	uniform vec4 LSampleFrag;
	uniform float radius;
	in vec4 position;
	uniform vec4 parameters;
	void main() 
	{ 
		float c1 = parameters.x;
		float c2 = parameters.y;
		float c3 = parameters.z;
		float c4 = parameters.w;
		float distance = position.x*position.x * c3 *c3 + 0.60* position.y*position.y * c3 * c3;
		float r2 = radius*radius*c3*c3;
		
		float li = 0.0;
		if (distance<1)
			li = 1.0;
		else
		{
			li = (c2/(distance * distance) + c1/(distance));
			li = pow(li,c4); 
		}
		color = LSampleFrag + vec4(li,li,li,1.0);
	}
)"