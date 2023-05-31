#version 330 core

in vec3 fragPosition;
in vec3 fragNormal;
in vec2 fragTexCoords;

uniform sampler2D uTexture;

out vec4 fragColor;

uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;

uniform vec3 uLightDir_vs;
uniform vec3 uLightIntensity;

vec3 blinnPhong(){
    //vec3 halfVector = normalize(-fragPosition);
    vec3 halfVector = normalize(uLightDir_vs + normalize(-fragPosition));
    vec3 bp = uLightIntensity*(uKd*(dot(normalize(uLightDir_vs), fragNormal.rgb))+uKs*pow(dot(halfVector, fragNormal), uShininess));
    return bp;
}


void main() {
    vec4 texColor = texture(uTexture, fragTexCoords);
    fragColor = vec4(texColor.rgb*blinnPhong().rgb, 0.5);
}