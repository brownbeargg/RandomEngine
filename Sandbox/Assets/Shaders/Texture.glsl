#[vertex]
#version 450 core

layout(location = 0) in vec3 a_Pos;
layout(location = 1) in vec2 a_TexCoord;

uniform mat4 u_MVP;

out vec2 v_TexCoord;

void main()
{
    v_TexCoord = a_TexCoord;
    gl_Position = u_MVP * vec4(a_Pos, 1.0);
}

#[fragment]
#version 450 core

out vec4 FragColor;

in vec2 v_TexCoord;
uniform sampler2D u_Texture;

void main()
{
    // FragColor = texture(u_Texture, v_TexCoord);
    FragColor = vec4(0.8, 0.2, 0.2, 1.0);
}
