#include "EBO.h"

EBO::EBO(GLuint* indices, GLsizeiptr size)
{
	//Generate Buffers
	glGenBuffers(1, &ID);
	//Bind the buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	//Linking EBO to VAO
	//(Type of buffer, size of data, data, use of data)
	//Use of data can be (Stream, Static or Dynamic) + (Draw, Read or Copy)
	//Stream = Vertices modified once & used a few times
	//Static = Vertices modified once & used many times
	//Dynamic = Vertices modified & used many times
	//Draw = Vertices are modified & used to draw an image on the screen
	//Read = Vertices are modified & read?
	//Copy = Vertices are modified & copied?
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

void EBO::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void EBO::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::Delete()
{
	//Delete VBO
	glDeleteBuffers(1, &ID);
}