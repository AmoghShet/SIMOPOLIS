#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <glad/glad.h>

class VBO
{
	private:
		GLuint ID;	//Public ID or Reference

		//(Verticies, their size in bytes)
		VBO(GLfloat* vertices, GLsizeiptr size);

		void Bind();
		void Unbind();
		void Delete();
};

#endif
