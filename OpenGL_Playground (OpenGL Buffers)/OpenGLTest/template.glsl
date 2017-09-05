//shadertype=glsl

/* Project - <project name>
*  Module - <module name>
*  Author - <Author name(s)>
*
*  Shader Name - <file name of the shader>
*  Shader Type - <shader type i.e. is it vertex or fragment or geometry etc.>
*  
*  Shader Discription:
*  <enter shader discription here>
*
*/

#version 440 core 

in vec4 position;

uniform mat4 perspective;
uniform mat4 lookAt;
uniform mat4 World; 

void main()
{
    gl_Position = perspective * lookAt * World * position;
}
