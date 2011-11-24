//
//  Shader.fsh
//  TalkingSample
//
//  Created by Mario on 11. 1. 10..
//  Copyright 2011 Vanilla Breeze. All rights reserved.
//

varying lowp vec4 colorVarying;

void main()
{
    gl_FragColor = colorVarying;
}
