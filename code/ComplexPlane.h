#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <cmath>
#include <iostream>
#include <complex>
#include <string>
#include <thread>
#include <vector>

using namespace std;
using namespace sf;

// Global constants declared at top of file

const unsigned int MAX_ITER = 64;
const float BASE_WIDTH = 4.0;
const float BASE_HEIGHT = 4.0;
const float BASE_ZOOM = 0.5;

/* Enumerator class created to hold two states. State variable Calculating actively calculates 
   complex plane, while Displaying is used to allow us to do so once per click (or on startup)
*/
enum State { CALCULATING, DISPLAYING };

/* Specifications of ComplexPlane class as described in UML diagram
   Inherits from SFML class Drawable to call window.draw(), uses SFML VertexArray class to
   draw each pixel as a colored point on the monitor
*/
class ComplexPlane : public Drawable 
{
public:
    ComplexPlane(int pixelWidth, int pixelHeight);
    void draw(RenderTarget& target, RenderStates States) const override;
    void zoomIn();
    void zoomOut();
    void setCenter(Vector2i mousePixel);
    void setMouseLocation(Vector2i mousePixel);
    void loadText(Text& text);
    void updateRender();

private:
    VertexArray m_vArray;
    State m_state;
    /* 2d vectors holding program's information. "f" is floating point",
       "i" is integer.
    */
    Vector2f m_mouseLocation;
    Vector2i m_pixel_size;
    Vector2f m_plane_center;
    Vector2f m_plane_size;
    int m_zoomCount;
    // Aspect ratio of monitor
    float m_aspectRatio;

    int countIterations(Vector2f coord);
    void iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b);
    Vector2f mapPixelToCoords(Vector2i mousePixel);
};

