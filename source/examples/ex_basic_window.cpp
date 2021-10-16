#include <GameWindow/GameWindow.hpp>
#include <Devices/Joystick.hpp>


int main() {

	Sincronia::GameWindow window;


	window.initWindow();

	Sincronia::JoystickContainer joysticks;

	Sincronia::setJoystickCallBack();

	while (window.shouldClose()) {
		window.config_init();
		Sincronia::pollJoysticks(joysticks);

	}


	window.finishWindow();

	return 0;
}

