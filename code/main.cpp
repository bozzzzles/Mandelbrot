#include "ComplexPlane.h"

int main() {
    // Create a video mode object
	int pixelWidth = VideoMode::getDesktopMode().width / 2;
	int pixelHeight = VideoMode::getDesktopMode().height / 2;
	VideoMode vm(pixelWidth, pixelHeight);

	// Create and open a window for the game
	RenderWindow window(vm, "Mandelbrot Set", Style::Default);

    Font arial;
    if (!arial.loadFromFile("Fonts/Arial.ttf")) {
		cout << "Error loading font from file." << endl;
		return 1;
	}

    Text info;
    info.setFont(arial);
    info.setCharacterSize(14);
    info.setFillColor(Color::White);

    ComplexPlane plane(pixelWidth, pixelHeight);

    while(window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
		{
		    if (event.type == Event::Closed)
		    {
					// Quit the game when the window is closed
					window.close();
		    }
            if (event.type == Event::MouseButtonPressed)
		    {
			    if (event.mouseButton.button == Mouse::Left)
			    {
                    plane.zoomIn();
                    plane.setCenter(event.mouseButton);
                }
                if (event.mouseButton.button == Mouse::Right)
                {
                    plane.zoomOut();
                    plane.setCenter(event.mouseButton);
                }
            }
            if (Keyboard::isKeyPressed(Keyboard::Escape))
		    {
			    window.close();
		    }
        }

        plane.updateRender();
        plane.loadText(info);

        window.clear();
        plane.draw();
        info.draw();
        window.display();

    }
    return 0;
}