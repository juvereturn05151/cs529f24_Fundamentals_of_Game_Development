#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include <glew/glew.h>
#include <glfw/glfw3.h>

class EBO
{
public:
	// ID reference of Elements Buffer Object
	GLuint ID;
	// Constructor that generates a Elements Buffer Object and links it to indices
	EBO(GLuint* indices, GLsizeiptr size);
	void EditEBO(GLuint* vertices, GLsizeiptr size);
	// Binds the EBO
	void Bind();
	// Unbinds the EBO
	void Unbind();
	// Deletes the EBO
	void Delete();
};

#endif