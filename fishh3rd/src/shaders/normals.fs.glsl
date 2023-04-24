#version 330 core

in vec3 fragPosition;
in vec3 fragNormal;
in vec2 fragTexCoords;

out vec4 fragColor;

void main() {
    fragColor = vec4(fragNormal, 1.0);
}