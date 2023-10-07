#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// texture sampler
uniform sampler2D texture1;
uniform sampler2D texture2;
void main()
{
    // texture是采样用的内置函数,从纹理上采样一个像素
    // 获取texture1在TexCoord上的位置
	FragColor = mix(texture(texture1,TexCoord), texture(texture2,TexCoord),0.2);
    // FragColor = texture(texture1, TexCoord) * vec4(ourColor, 1.0);
}

