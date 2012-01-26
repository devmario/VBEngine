varying lowp vec4 color_per;
varying lowp vec4 color_add;
varying lowp vec2 txc;

uniform sampler2D texure;

void main()
{
    lowp vec4 color = texture2D(texure, txc) * color_per;
    
    color.r += color_add.r;
    if(color.r > 1.0)
        color.r = 1.0;
    if(color.r < 0.0)
        color.r = 0.0;
    
    color.g += color_add.g;
    if(color.g > 1.0)
        color.g = 1.0;
    if(color.g < 0.0)
        color.g = 0.0;
    
    color.b += color_add.b;
    if(color.b > 1.0)
        color.b = 1.0;
    if(color.b < 0.0)
        color.b = 0.0;
    
    if(color.a != 0.0)
        color.a += color_add.a;
    if(color.a > 1.0)
        color.a = 1.0;
    if(color.a < 0.0)
        color.a = 0.0;
    
    gl_FragColor = color;
}
