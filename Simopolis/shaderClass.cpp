#include "shaderCLass.h"

//File Reader function 
std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	//Reference object to store vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//(Reference value, using 1 string for the whole shader, point to source code, idk)
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	//GPU cant understand the source code, so compile
	glCompileShader(vertexShader);


	//Reference object to store fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//(Reference value, using 1 string for the whole shader, point to source code, idk)
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	//GPU cant understand the source code, so compile
	glCompileShader(fragmentShader);

	//Wrap shaders up into a shader program
	ID = glCreateProgram();
	//Attach shader to shader program
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	//Wrap up the shader program
	glLinkProgram(ID);
	//Delete shaders because theyre already in the program now
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::Activate()
{
	//Activate Shader Program
	glUseProgram(ID);
}

void Shader::Delete()
{
	//Delete Shader Program
	glDeleteProgram(ID);
}