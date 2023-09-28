#include <GLFW/glfw3.h>
#include <iostream>

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE  && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	else
		printf("key : %d was pressed\n", key);
}


int main(void){
	GLFWwindow *window;

	if (!glfwInit())
		exit(EXIT_FAILURE);
	window = glfwCreateWindow(640, 480, "Test window", NULL, NULL);
	if (!window)
		exit(EXIT_FAILURE);
	
	glfwSetKeyCallback(window, key_callback);
	glfwMakeContextCurrent(window);

	while (!glfwWindowShouldClose(window))
	{
		//
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
