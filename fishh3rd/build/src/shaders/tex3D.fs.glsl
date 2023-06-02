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
uniform vec3 uLightPos_vs;
uniform vec3 uLightIntensity;
uniform vec3 uLightPosIntensity;

vec3 blinnPhong(){
    //vec3 halfVector = normalize(-fragPosition);
    vec3 halfVector = normalize(uLightDir_vs + normalize(-fragPosition));
    vec3 bp = uLightIntensity*(uKd*(dot(normalize(uLightDir_vs), fragNormal.rgb))+uKs*pow(dot(halfVector, fragNormal), uShininess));
    return bp;
}

vec3 pointLight(){
    vec3 wi = normalize(uLightPos_vs - fragPosition); // Calculer le vecteur wi à partir de la position du fragment et de la position de la lumière
    float d = length(uLightPos_vs - fragPosition); // Calculer la distance d entre le fragment et la lumière
    vec3 attenuatedIntensity = uLightPosIntensity / (d * d); // Appliquer une atténuation quadratique à l'intensité de la lumière

    vec3 halfVector = normalize(wi + normalize(-fragPosition));
    vec3 bp = attenuatedIntensity * (uKd * (dot(normalize(wi), fragNormal.rgb)) + uKs * pow(dot(halfVector, fragNormal), uShininess));
    return bp;
}


void main() {
    vec4 texColor = texture(uTexture, fragTexCoords);
    fragColor = vec4(texColor.rgb*(blinnPhong().rgb+pointLight().rgb), 0.5);
}