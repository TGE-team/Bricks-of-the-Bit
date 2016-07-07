#include "FpsMeter.hpp"

void FpsMeter::update()
{
	if(clock.getElapsedTime().asSeconds() >= 1)
	{
		setString(std::to_string(frames) + " FPS");
		clock.restart();
		frames = 0;
	}
	frames++;
}
