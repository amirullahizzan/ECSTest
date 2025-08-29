#include "Time.h"

void Time::Update()
{
	// Get the current time
	static auto lastTime = std::chrono::high_resolution_clock::now();
	auto currentTime = std::chrono::high_resolution_clock::now();

	// Calculate the time difference between frames
	std::chrono::duration<float> duration = currentTime - lastTime;
	deltaTime = duration.count();
	deltaTime_ms = deltaTime * 1000.0f;

	// Update the last time for the next frame
	lastTime = currentTime;
}

Time gameTime;
