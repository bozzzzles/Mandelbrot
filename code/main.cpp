#include "ComplexPlane.h"

int main() {
    // Create a video mode object
	int pixelWidth = VideoMode::getDesktopMode().width / 2;
	int pixelHeight = VideoMode::getDesktopMode().height / 2;
	VideoMode vm(pixelWidth, pixelHeight);

	// Create and open a window for the game
	RenderWindow window(vm, "Mandelbrot Set", Style::Default);

    Font arial;
    if (!arial.loadFromFile("fonts/Arial.ttf")) {
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
            if (event.type == Event::MouseMoved)
            {
                Vector2i mousePixel(event.MouseMoveEvent.x, event.MouseMoveEvent.y);
                plane.setMouseLocation(mousePixel);
            }
            if (Keyboard::isKeyPressed(Keyboard::Escape))
		    {
			    window.close();
		    }
        }

        plane.updateRender();
        plane.loadText(info);

        window.clear();
        window.draw(plane);
        window.draw(info);
        window.display();

    }
    return 0;
}