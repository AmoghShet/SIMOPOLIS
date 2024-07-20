//To ensure C++ doesnt open the shaderClass twice
#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H


//includes needed for OpenGL & text reader func
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>


//Function that will read the shader text file & outputs context of textfile as string
std::string get_file_contents(const char* filename);


//The actual shaderClass
class Shader
{
	public:
		GLuint ID;	//Public ID or Reference
		
		//Constructor
		Shader(const char* vertexFile, const char* fragmentFile);

		void Activate();
		void Delete(); 
};

#endif
