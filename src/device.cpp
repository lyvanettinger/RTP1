#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <stdio.h>

#include "device.h"

//#define FULL_SCREEN
//#define WINDOWED_FULL_SCREEN

namespace rtp
{
	namespace device
	{
		void error_callback(int error, const char* description)
		{
			fputs(description, stderr);
		}

		namespace internal
		{
			GLFWwindow* window = nullptr;
			GLFWmonitor* monitor = NULL;
		}

		using namespace rtp::device::internal;

		bool init()
		{
			// initialize glfw
			bool success = glfwInit();
			if (!success)
			{
				fprintf(stderr, "Failed to initialize GLFW\n");
				exit(EXIT_FAILURE);
			}

			// set the error callback
			glfwSetErrorCallback(error_callback);

			// create window according to preference
#ifdef FULL_SCREEN
			window = glfwCreateWindow(640, 480, "3d_raytracer", glfwGetPrimaryMonitor(), NULL);
#elif WINDOWED_FULL_SCREEN
			const GLFWvidmode* mode = glfwGetVideoMode(monitor);

			glfwWindowHint(GLFW_RED_BITS, mode->redBits);
			glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
			glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
			glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

			GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "My Title", monitor, NULL);
#else
			window = glfwCreateWindow(640, 480, "3d_raytracer", NULL, NULL);
#endif
			if (!window)
			{
				glfwTerminate();
				exit(EXIT_FAILURE);
			}

			// set current context
			glfwMakeContextCurrent(window);

			return success;
		}

		bool should_close()
		{
			return glfwWindowShouldClose(window); // as test
		}

		void shutdown()
		{
			// terminate window and glfw
			glfwDestroyWindow(window);
			glfwTerminate();
		}
	}
}

