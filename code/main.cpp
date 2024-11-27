#include "ComplexPlane.h"

int main() {
    // Create a video mode object
	int pixelWidth = VideoMode::getDesktopMode().width;
	int pixelHeight = VideoMode::getDesktopMode().height;
	VideoMode vm(pixelWidth, pixelHeight);

	// Create and open a window for the game
	RenderWindow window(vm, "Mandelbrot Set", Style::Default);

    Font arial;
    if (!arial.loadFromFile("Fonts/Arial.ttf")) {
		cout << "Error loading font from file." << endl;
		return 1;
	}

    return 0;
}