#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

/*
	OpenGL Pipeline:
		Vertex Data[]			    ->	      Array of vertex which has point, color & texture data 
		      |
		Vertex Shader			    ->		  Draws (& transforms) all the positions/vertices
		      |
		Shape Assembly              ->        Connects positions via primitives (points, lines or triangles)
		      |
		Geometry Assembly			->		  Add vertices & create new primitives out of existing primitives 
		      |
		Rasterization				->		  Converts perfect geometrics shapes to actual pixels
		      |
		Fragment Shader				->		  Adds color values to the rasterized pixels
		      |
		Tests & Blending			->		  Deals with transparency & overlapping & blending
*/


using namespace std;

void main()
{
	//Start OpenGL
	glfwInit();


	//Program dumb doesnt know shit so we have to tell it shit
	//Telling it which major & minor version its running
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//Telling which OpenGL profile (pkg of functions) to use 
	//There are 2 main profiles; Core = all modern funcs & Compatibility = modern + outdated funcs
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	//Triangle Vertices; every 3 floats = 1 coordinate
	//GLfloat because regular float may vary system to system
	//Coordinates need to be between -1 & 1
	GLfloat vertices[] =
	{
		(-0.5f), (-0.5f * float(sqrt(3)) / 3), (0.0f),		//0 - Lower left
		(0.5f), (-0.5f * float(sqrt(3)) / 3), (0.0f),		//1 - Lower right
		(0.0f), (0.5f * float(sqrt(3)) * 2 / 3), (0.0f),	//2 - Upper
		
		(-0.5/2), (0.5f * float(sqrt(3)) / 6), (0.0f),		//3 - Inner Left
		(0.5f/2), (0.5f * float(sqrt(3)) / 6), (0.0f),		//4 - Inner right
		(0.0f), (-0.5f * float(sqrt(3)) / 3), (0.0f),		//5 - Inner Down
	};


	//Indices
	//Tells OpenGL in which order to draw the vertices 
	//GLunit because regular unsigned int may vary system to system
	GLuint indices[] =
	{
		0, 3, 5,	//Lower left triangle
		3, 2, 4,	//Lower right triangle
		5, 4, 1		//Upper triangle 
	};


	//Create a window
	//(width, hight, name, fullscreen, idk)
	GLFWwindow* window = glfwCreateWindow(800,800, "Simopolis", NULL, NULL);
	if (window == NULL)
	{
		cerr <<"ERROR: FAILED TO CREATE GLFW WINDOW";
		glfwTerminate();
	}
	//Tell OpenGL to use the window, cause it stupid
	//Context "holds" what is created & being used
	glfwMakeContextCurrent(window);


	//Load needed configs for OpenGL
	gladLoadGL();
	//Area you want OpenGL to render in
	//(0,0) -> Bottom Left  (800,800) -> Top Right
	glViewport(0, 0, 800, 800);
	//Set Back Buffer with colour we want
	//Front Buffer = The buffer from which frames are read to be displayed
	//Back Buffer = The buffer to which the frames are written
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	//(R, G, B, Alpha/Transparency)
	glClear(GL_COLOR_BUFFER_BIT);
	//Swap front buffer which has default colors, w/ back buffer which has the color we want
	glfwSwapBuffers(window);


	//Create Buffer
	//Information from CPU to GPU is slow so sent in batches/buffers
	//Not to be confused with Front & Back buffers, which deals with frames
	//VBO is a buffer; here only 1 object so no array
	//VAO stores pointers to 1 or more VBOs; switch b/w VBOs fast
	//EBO is the index buffer 
	GLuint VAO, VBO, EBO; 
	//Generate Buffers
	//VAO must be generated before VBO
	//(No. of 3D objects, Pointing to reference
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &EBO);
	//Bind VBO, VOA & EBO
	//Binding means making a certain obj the current obj
	//Any function that modifies that type of obj, modifies current obj
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//Linking VBO & EBO to VAO
	//(Type of buffer, size of data, data, use of data)
	//Use of data can be (Stream, Static or Dynamic) + (Draw, Read or Copy)
	//Stream = Vertices modified once & used a few times
	//Static = Vertices modified once & used many times
	//Dynamic = Vertices modified & used many times
	//Draw = Vertices are modified & used to draw an image on the screen
	//Read = Vertices are modified & read?
	//Copy = Vertices are modified & copied?
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	//Config VAO to tell OpenGL how to interpert them 
	//Vertex Attribute is a way of communicating w/ a vertex shader from the outside
	//(Pos of Vertex Attribute, values per vertex, value type, int?, spread, offset)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
	//Enable Vertex Attributes
	//(pos of Vertex Attribute)
	glEnableVertexAttribArray(0);
	//To ensure we wont exceed until VAO/VBO is changed
	//The order is important: VBO -> VAO -> EBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	 
	//Loop till the window is closed
	while (!glfwWindowShouldClose(window)) 
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//Bind VAO to tell OpenGL to use this one
		glBindVertexArray(VAO);

		//Drawing
		/* (Primitive type, starting index of vertices, amt.of vertices)
		glDrawArrays(GL_TRIANGLES, 0, 3); */
		//(Primitive type, no. of indices to draw, Indices datatype, index of indices)
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);


		//Swap Buffers
		//Make sure image gets updated each frame
		glfwSwapBuffers(window);

		//Processes all pending events. Makes window responsive
		glfwPollEvents();
	}

	//Delete VAO
	glDeleteVertexArrays(1, &VAO);
	//Delete EBO
	glDeleteBuffers(1, &EBO);
	//Terminate Window
	glfwDestroyWindow(window);
	//Terminate OpenGL
	glfwTerminate();
}