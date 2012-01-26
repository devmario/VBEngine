attribute vec2 at_vtx;
attribute vec2 at_txc;
attribute vec4 at_color_per;
attribute vec4 at_color_add;

varying vec4 color_per;
varying vec4 color_add;
varying vec2 txc;

uniform sampler2D texure;
uniform mat4 mvpmat;

void main() {
    gl_Position = mvpmat * vec4(at_vtx.x, at_vtx.y, 0.0, 1.0);
    
    txc = at_txc;
    
    color_per = at_color_per;
    color_add = at_color_add;
}