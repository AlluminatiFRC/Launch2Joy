//Needed for the MIDI library, it's crossplatform
#define __WINDOWS_MM__

#include <iostream>
#include <cstdlib>
#include "RtMidi.h"
#include "Launchpad.h"

int main()
{
	Launchpad launchpad;
	launchpad.setColor(5, 5, dimAmber);
	launchpad.setColor(6, 5, brightenColor(dimAmber));
	std::cout << "\nReading MIDI input ... press <enter> to quit.\n";
	char input;
	std::cin.get(input);
}