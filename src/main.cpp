// Primordial Graphical Framework
// Emin Bursa
// July 28, 2019

// This is a OpenGL framework for any project,
// compilable to Linux or Windows (Mac later?)
// and using 100% generated surfaces, no textures

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <shader.h>

#include <iostream>
#include <cmath>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
//void render(unsigned int, unsigned int);

const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"out vec3 ourColor;\n"
"void main(){\n"
"	gl_Position = vec4(aPos, 1.0f);\n"
"	ourColor = aColor;\n"
"}\n";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 ourColor;\n"
"void main(){\n"
"	FragColor = vec4(ourColor, 1.0f);\n"
"}\n";

int main(){

	std::cout << "Initializing Primordial Graphical Framework" << std::endl;

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//below line required for Mac OS X
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "PGF", NULL, NULL);
	if(window == NULL){
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	Shader mainShader("shaders/3.3.main.vs", "shaders/3.3.main.fs");

/*
// a triangle
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};
*/

// positions with color attributes
	float vertices[] = {
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f
	};

/*
// a rectangle
	float vertices[] = {
		0.5f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f
	};

	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};
*/

	// create a vertex buffer object
	unsigned int VBO, EBO, VAO;
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);
	
	// unsets bound VAO ?
	//glBindVertexArray(0);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// ---- program loop ----
	while(!glfwWindowShouldClose(window))
	{
		// input
		processInput(window);

		// render
		//render(VAO, mainShader.ID);
	
		glClearColor(0.2f, 0.2f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		mainShader.use();
		glBindVertexArray(VAO);
		
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// check & call events, swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	std::cout << "Terminating Program...\n" << std::endl;

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	//glDeleteBuffers(1, &EBO);

	glfwTerminate();

	return 0;
}
/*
void render(unsigned int VAO, unsigned int shaderProgram){
		// rendering
		//glClearColor(0.2f, 0.35f, 0.25f, 1.0f);
		glClearColor(0.2f, 0.2f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		//float timeValue = glfwGetTime();
		//float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		//int vertexColorLocation = glGetUniformLocation(shaderProgram, "abc");
		
		glUseProgram(shaderProgram);
		//mainShader.use();
		
		//glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
		
		glBindVertexArray(VAO);

		glDrawArrays(GL_TRIANGLES, 0, 3);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
*/

void processInput(GLFWwindow* window){
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
		glfwSetWindowShouldClose(window, true);
	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
	glViewport(0, 0, width, height);
}

