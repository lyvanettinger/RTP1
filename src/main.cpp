
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "device.h"
#include "renderer.h"

int main(int argc, char** argv)
{
	rtp::device::init();

	// the main loop
	while (!rtp::device::should_close())
	{

	}

	rtp::device::shutdown();
}