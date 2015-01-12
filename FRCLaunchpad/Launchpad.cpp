#include "Launchpad.h"

//Use bit twiddling for these operations
Color mkColor(int red, int green){
	return (Color)(16 * green + red + 12);
}

Color dimColor(Color c){
	int red = c & 3;
	int green = c & 3 * 16;
	red -= 1;
	green -= 1 * 16;
	if (red < 0) red = 0;
	if (green < 0 * 16) green = 0;
	return (Color)(red + green);
}

Color brightenColor(Color c){
	int red = c & 3;
	int green = c & 3 * 16;
	red += 1;
	green += 1 * 16;
	if (red > 3) red = 3;
	if (green > 3 * 16) green = 3 * 16;
	return (Color)(red + green);
}

void onMessage(double deltatime, std::vector< unsigned char > *message, void *userData){
	std::cout << "On message!" << std::endl;
}

Launchpad::Launchpad(){
	// Check available ports.
	std::cout << "Input ports:\n";
	for (unsigned int i = 0; i < input.getPortCount(); i++){
		std::cout << i << ": " << input.getPortName(i) << "\n";
	}
	input.openPort(0);

	std::cout << "\nOutput ports:\n";
	for (unsigned int i = 0; i < output.getPortCount(); i++){
		std::cout << i << ": " << output.getPortName(i)  << "\n";
	}
	output.openPort(1);

	// Don't ignore sysex, timing, or active sensing messages.
	input.ignoreTypes(false, false, false);
	// Set our callback function.  This should be done immediately after
	// opening the port to avoid having incoming messages written to the
	// queue.
	message.resize(3);

	input.setCallback(&onMessage, NULL);

	//Flash the launchpad to show that we're ready
	// All LEDs on full
	message[0] = 0xB0;
	message[1] = 0;
	message[2] = 127;
	output.sendMessage(&message);
	// Reset
	message[0] = 0xB0;
	message[1] = 0;
	message[2] = 0;
	output.sendMessage(&message);

	std::cout << "Launchpad ready." << std::endl;

	//Make a little grid
	message[0] = 0x90;
	for (int x = 0; x < 4; x++){
		for (int y = 0; y < 4; y++){
			message[1] = x + y * 16;
			message[2] = x + y * 16;
			output.sendMessage(&message);
		}
	}
}

Launchpad::~Launchpad(){
	input.closePort();
	//Reset the launchpad before closing it
	message[0] = 0xB0;
	message[1] = 0x00;
	message[2] = 0x00;
	output.sendMessage(&message);
	output.closePort();
}

void Launchpad::setColor(int x, int y, Color color){
	message[0] = 0x90;
	message[1] = x + y * 16;
	message[2] = color;
	output.sendMessage(&message);
}