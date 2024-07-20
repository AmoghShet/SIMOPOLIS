#include "VBO.h"

VBO::VBO(GLfloat* vertices, GLsizeiptr size)
{
	//Generate Buffers
	glGenBuffers(1, &ID);
	//Bind the buffer
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	//Linking VBO to VAO
	//(Type of buffer, size of data, data, use of data)
	//Use of data can be (Stream, Static or Dynamic) + (Draw, Read or Copy)
	//Stream = Vertices modified once & used a few times
	//Static = Vertices modified once & used many times
	//Dynamic = Vertices modified & used many times
	//Draw = Vertices are modified & used to draw an image on the screen
	//Read = Vertices are modified & read?
	//Copy = Vertices are modified & copied?
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void VBO::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete()
{
	//Delete VBO
	glDeleteBuffers(1, &ID);
}