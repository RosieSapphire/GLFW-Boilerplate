#version 330 core

in vec2 uv;

out vec4 frag_color;

void main() {
	frag_color = vec4(uv.xy, 0.0, 1.0);
}
