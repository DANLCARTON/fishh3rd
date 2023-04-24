#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

uniform mat4 uMVPMatrix;
uniform mat4 uMVMatrix;
uniform mat4 uNormalMatrix;

out vec3 fragPosition;
out vec3 fragNormal;
out vec2 fragTexCoords;

void main () {
    fragPosition = vec3(uMVMatrix * vec4(position, 1.0));
    fragNormal = normalize(vec3(uNormalMatrix * vec4(normal, 0.0)));

    fragTexCoords = texCoords;

    gl_Position = uMVPMatrix*vec4(position, 1.0);
}