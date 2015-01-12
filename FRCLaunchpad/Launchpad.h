#include "RtMidi.h"
#pragma once

enum Color{
	off = 0x0C,
	dimRed = 0x0D,
	brightRed = 0x0F,
	dimAmber = 0x1D,
	brightAmber = 0x3F,
	brightYellow = 0x3E,
	dimGreen = 0x1C,
	brightGreen = 0x3C,
	flashRed = 0x0B,
	flashAmber = 0x3B,
	flashYellow = 0x3A,
	flashGreen = 0x38
};

Color mkColor(int red, int green);
Color dimColor(Color c);
Color brightenColor(Color c);

class Launchpad{
public:
	Launchpad();
	~Launchpad();
	void setColor(int x, int y, Color color);

private:
	RtMidiIn input;
	RtMidiOut output;
	std::vector<unsigned char> message;
};