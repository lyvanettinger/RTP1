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

		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			if (action == GLFW_PRESS)
			{
				switch (key)
				{
				case GLFW_KEY_ESCAPE:
					glfwSetWindowShouldClose(window, GLFW_TRUE);
					break;
				default:
					break;
				}
			}
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

			// set window hints
			glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);

			// create window according to preference
#ifdef FULL_SCREEN
			// set monitor
			monitor = glfwGetPrimaryMonitor();
			window = glfwCreateWindow(640, 480, "3d_raytracer", monitor, NULL);
#elif WINDOWED_FULL_SCREEN
			monitor = glfwGetPrimaryMonitor();
			const GLFWvidmode* mode = glfwGetVideoMode(monitor);
			glfwWindowHint(GLFW_RED_BITS, mode->redBits);
			glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
			glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
			glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

			GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "3d_raytracer", monitor, NULL);
#else
			window = glfwCreateWindow(640, 480, "3d_raytracer", monitor, NULL);
#endif
			if (!window)
			{
				fprintf(stderr, "Failed to create GLFW window\n");
				glfwTerminate();
				exit(EXIT_FAILURE);
			}

			if (monitor)
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

			glfwMakeContextCurrent(window);

			glfwSetKeyCallback(window, key_callback);

			glfwSetTime(0.0);

			return success;
		}

		void update()
		{
			glfwPollEvents();
		}

		bool should_close()
		{
			return glfwWindowShouldClose(window); // as test
		}

		void shutdown()
		{
			glfwDestroyWindow(window);
			glfwTerminate();
		}
	}
}

