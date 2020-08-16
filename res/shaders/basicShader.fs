#version 330 core

varying vec2 texCoord0;
varying vec3 normal0;

uniform sampler2D diffuse;

void main()
{
	// shader without light
	// gl_FragColor = texture2D(diffuse, texCoord0);

	// shader with light
	gl_FragColor = texture2D(diffuse, texCoord0) * clamp(dot(-vec3(0,0,-1), -normal0), 0.0, 1.0);
}
