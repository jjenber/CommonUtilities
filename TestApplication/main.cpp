#include "../CommonUtilities/Timer.h"
#include <iostream>
#include <thread>
#include <chrono>

int main()
{
	CommonUtilities::Timer timer;

	while (true)
	{
		timer.Update();

		const int fps = static_cast<int>(1.f / timer.GetDeltaTime() + 0.5f);
		printf("Total Time: %10f  -  Delta Time: %10f  -  FPS: %i\n", timer.GetTotalTime(), timer.GetDeltaTime(), fps);
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}
