#pragma once

namespace rtp
{
	namespace device
	{
		/// <summary>
		/// intializes device and window
		/// </summary>
		/// <returns>succes of device initialization</returns>
		bool init();

		/// <summary>
		/// checks if device should close
		/// </summary>
		/// <returns></returns>
		bool should_close();

		/// <summary>
		/// clean up and shut down device
		/// </summary>
		void shutdown();
	}
}