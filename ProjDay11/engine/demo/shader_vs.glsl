#version 310 es

layout(location = 0) in highp vec4 in_POSITION0;
void main()
{
    //MOV
    gl_Position = in_POSITION0;
    //RET
    return;
}
