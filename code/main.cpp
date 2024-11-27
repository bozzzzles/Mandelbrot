#include "ComplexPlane.h"

int main() {
    // Create a video mode object
	int pixelWidth = VideoMode::getDesktopMode().width / 2;
	int pixelHeight = VideoMode::getDesktopMode().height / 2;
	VideoMode vm(pixelWidth, pixelHeight);

	// Create and open a window for the game
	RenderWindow window(vm, "Mandelbrot Set", Style::Default);

    // Set font to arial
    Font arial;
    if (!arial.loadFromFile("fonts/Arial.ttf")) {
		cout << "Error loading font from file." << endl;
		return 1;
	}

    // Create text object, load with specs (Arial font, 14 size, white color)
    Text info;
    info.setFont(arial);
    info.setCharacterSize(14);
    info.setFillColor(Color::White);

    // Create ComplexPlane object
    ComplexPlane plane(pixelWidth, pixelHeight);

    // While loop controlling program, ends when window is closed
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
                // Control zoom with right/ left click
			    if (event.mouseButton.button == Mouse::Left)
			    {
                    plane.zoomIn();
                    Vector2i mousePixel(event.mouseButton.x, event.mouseButton.y);
                    plane.setCenter(mousePixel);
                }
                if (event.mouseButton.button == Mouse::Right)
                {
                    plane.zoomOut();
                    Vector2i mousePixel(event.mouseButton.x, event.mouseButton.y);
                    plane.setCenter(mousePixel);
                }
            }
            // Check mouse location
            if (event.type == Event::MouseMoved)
            {
                Vector2i mousePixel(event.mouseMove.x, event.mouseMove.y);
                plane.setMouseLocation(mousePixel);
            }
            // Exit loop with escape key
            if (Keyboard::isKeyPressed(Keyboard::Escape))
		    {
			    window.close();
		    }
        }

        // Update plane
        plane.updateRender();
        plane.loadText(info);

        window.clear();
        window.draw(plane);
        window.draw(info);
        window.display();

    }
    return 0;
}