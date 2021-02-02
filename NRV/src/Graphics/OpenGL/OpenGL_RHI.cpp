#include "OpenGL_RHI.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "NRV/LogWrapper.h"

namespace NRV {
	namespace Graphics {

        OpenGL::OpenGL()
        {
            CreateWindow("TEMPORARY NAME", 1920, 1080, true);
        }

        OpenGL::~OpenGL()
        {

        }

		void OpenGL::CreateWindow(const char* window_name, uint32_t width, uint32_t height, bool is_fullscreen) {
            LogMessage("Creating window...", Log::LogLevel::Message);
			GLFWwindow* window;

            if (!glfwInit())
                LogMessage("glfwInit failed!", Log::LogLevel::Message);

            /* Create a windowed mode window and its OpenGL context */
            window = glfwCreateWindow(1920, 1080, window_name, NULL, NULL);
            if (!window)
            {
                glfwTerminate();
                LogMessage("Window creation failed!", Log::LogLevel::Error);
                return;
            }

            /* Make the window's context current */
            glfwMakeContextCurrent(window);
            glfwSwapInterval(1);

            if (glewInit() != GLEW_OK)
                LogMessage("glewInit failed!", Log::LogLevel::Error);

            std::cout << "Holding for input...";
            std::cin.get();

            glfwTerminate();
		}

	}
}