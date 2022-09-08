#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

int window_width = 800;
int window_height = 600;

void glfwWindowSizeCallback(GLFWwindow* pWindow, int width, int height);
void glfwKeyCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mode);

int main(void)
{	
    /* Initialize the library */
    if (!glfwInit())
    {
		std::cout << "Can`t init glfw" << std::endl;
		return -1;
	}
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
       

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* pWindow = glfwCreateWindow(window_width, window_height, "Battle City", nullptr, nullptr);
    if (!pWindow)
    {
		std::cout << "Can`t create window" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glfwSetWindowSizeCallback(pWindow, glfwWindowSizeCallback);
	glfwSetKeyCallback(pWindow, glfwKeyCallback);
	
    /* Make the window's context current */
    glfwMakeContextCurrent(pWindow);
    
    if (!gladLoadGL())
    {
		std::cout << "Cant load Glad\n";
		return -1;
	}
	
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "OpenGL version" << glGetString(GL_VERSION) << std::endl;

	glClearColor(0, 1, 1, 1);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(pWindow))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(pWindow);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}


void glfwWindowSizeCallback(GLFWwindow* pWindow, int width, int height)
{
	window_width = width;
    window_height = height;
    glViewport(0, 0, window_width, window_height);
}

void glfwKeyCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(pWindow, GL_TRUE);
	}
}

