#include "main.h"

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE  && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	else if (key == 65)
		printf("left\n");
	else
		printf("key : %d was pressed\n", key);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

int main(void){
	GLFWwindow *window;
	int success;
	char infoLog[512];
	char *vertexShaderSource, *orangeFragmentShaderSource, *yellowFragmentShaderSource;
	unsigned int vertexShader, orangeFragmentShader, yellowFragmentShader;
	unsigned int orangeShaderProgram, yellowShaderProgram;
	unsigned int VBOs[2], VAOs[2];

	vertexShaderSource = readFile("basic.vert");
	orangeFragmentShaderSource = readFile("orange.frag");
	yellowFragmentShaderSource = readFile("yellow.frag");

	if(!vertexShaderSource || !orangeFragmentShaderSource || !yellowFragmentShaderSource)
		exit(EXIT_FAILURE);
	if (!glfwInit())
		exit(EXIT_FAILURE);
	window = glfwCreateWindow(800, 600, "Test window", NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	
	glfwSetKeyCallback(window, key_callback);
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// vertexShader
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// fragmentShaderOrange
	orangeFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(orangeFragmentShader, 1, &orangeFragmentShaderSource, NULL);
	glCompileShader(orangeFragmentShader);
	glGetShaderiv(orangeFragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(orangeFragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// fragmentShaderOrange
	yellowFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(yellowFragmentShader, 1, &yellowFragmentShaderSource, NULL);
	glCompileShader(yellowFragmentShader);
	glGetShaderiv(yellowFragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(yellowFragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// linkShaderOrange
	orangeShaderProgram = glCreateProgram();
	glAttachShader(orangeShaderProgram, vertexShader);
	glAttachShader(orangeShaderProgram, orangeFragmentShader);
	glLinkProgram(orangeShaderProgram);
	glGetProgramiv(orangeShaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(orangeShaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	// linkShaderYellow
	yellowShaderProgram = glCreateProgram();
	glAttachShader(yellowShaderProgram, vertexShader);
	glAttachShader(yellowShaderProgram, yellowFragmentShader);
	glLinkProgram(yellowShaderProgram);
	glGetProgramiv(yellowShaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(yellowShaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}


	glDeleteShader(vertexShader);
	glDeleteShader(orangeFragmentShader);
	glDeleteShader(yellowFragmentShader);

	// vertex data
	float triangle1[] = {
		-0.7f, -0.2f, 0.0f,
		-0.2f, -0.2f, 0.0f, 
		-0.5f,  0.5f, 0.0f
	};
	float triangle2[] = {
		0.7f, -0.2f, 0.0f,
		0.2f, -0.2f, 0.0f, 
		0.5f,  0.5f, 0.0f

	};
	
	glGenVertexArrays(2, VAOs);
	glGenBuffers(2, VBOs);

	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle1), triangle1, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle2), triangle2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	glBindBuffer(GL_ARRAY_BUFFER, 0); 
	glBindVertexArray(0);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(orangeShaderProgram);
		glBindVertexArray(VAOs[0]); 
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glUseProgram(yellowShaderProgram);
		glBindVertexArray(VAOs[1]); 
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(2, VAOs);
	glDeleteBuffers(2, VBOs);
	glDeleteProgram(orangeShaderProgram);
	glDeleteProgram(yellowShaderProgram);

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
