#vertex
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUv;
layout (location = 2) in vec3 aNormal;

out vec2 uv;

uniform mat4 view;
uniform mat4 proj;
uniform mat4 model;
uniform vec3 scale;

void main() {

    vec3 norm = normalize(aNormal);
    uv = aUv * (norm.x * scale.zy + norm.y * scale.xz + norm.z * scale.xy);

	gl_Position = proj * view * model * vec4(aPos * scale, 1.0f);
}


#fragment
#version 330 core


out vec4 frag_color;

in vec2 uv;

uniform sampler2D mesh_texture;

void main() {

	frag_color = texture(mesh_texture, uv);
}
