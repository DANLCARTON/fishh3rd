#version 330 core

in vec3 fragPosition;
in vec3 fragNormal;
in vec2 fragTexCoords;

out vec4 fragColor;

uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;

uniform vec3 uLightPos_vs; // Remplacer uLightDir_vs par uLightPos_vs
uniform vec3 uLightIntensity;
uniform vec3 uLightPosIntensity;

vec3 pointLight(){
    vec3 wi = normalize(uLightPos_vs - fragPosition); // Calculer le vecteur wi à partir de la position du fragment et de la position de la lumière
    float d = length(uLightPos_vs - fragPosition); // Calculer la distance d entre le fragment et la lumière
    vec3 attenuatedIntensity = uLightIntensity / (d * d); // Appliquer une atténuation quadratique à l'intensité de la lumière

    vec3 halfVector = normalize(wi + normalize(-fragPosition));
    vec3 bp = attenuatedIntensity * (uKd * (dot(normalize(wi), fragNormal.rgb)) + uKs * pow(dot(halfVector, fragNormal), uShininess));
    return bp;
}

void main() {
    fragColor = vec4(pointLight(), 1);
}