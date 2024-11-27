#include "ComplexPlane.h"

/* Definition of ComplexPlane constructor. Takes two arguments,
   pixelWidth and pixelHeight which are taken from VideoMode class
   function calls
*/
ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight)
{
    // Sets window's pixel size 2d vector to passed argument
    m_pixel_size = { pixelWidth, pixelHeight };
    // Calculates window's aspect ratio via passed argument to prevent distortion
    m_aspectRatio = static_cast<float>(pixelHeight) / pixelWidth;
    // Sets center of plane to coordinates (0, 0)
    m_plane_center = { 0, 0 };
    // Scales size of plane by aspect ratio (calculated above)
    m_plane_size = { BASE_WIDTH, BASE_HEIGHT * m_aspectRatio };
    // Assings inital zoom to 0
    m_zoomCount = 0;
    // Flips state of obect to "calculating" as discussed with enum to begin Mandelbrot set
    m_state = State::CALCULATING;
    // Sets vertex array to "Points", which has to do with how SFML graphics are stored
    m_vArray.setPrimitiveType(Points);
    // Changes size of m_vArray
    m_vArray.resize(pixelWidth * pixelHeight);
}

// Draws our complex plane
void ComplexPlane::draw(RenderTarget& target, RenderStates States) const
{
    target.draw(m_vArray);
}

// This is important, yo
void ComplexPlane::updateRender()
{
// Checks state
    if (m_state == CALCULATING)
    {
        int workableThreads = thread::hardware_concurrency();
// Double for loop controlling x (j) and y(i)
        for (int i = 0; i < m_pixel_size.y; i++)
        {
            for (int j = 0; j < m_pixel_size.x; j++)
            {
// Map x/ y coordinate to corresponding vector position
                m_vArray[j + i * m_pixel_size.x].position = { (float)j,(float)i };
// Used mapPixelToCoords to find 2d complex coordinate that corresponds with screen pixel
// Stored above in int using countIterations
                int n = countIterations(mapPixelToCoords({ j, i }));
// Set RGB values at corresponding coordinate
                Uint8 r, g, b;
                iterationsToRGB(n, r, g, b);
                m_vArray[j + i * m_pixel_size.x].color = { r,g,b };
            }
        }
// Set state to displaying
        m_state = DISPLAYING;
    }
}

void ComplexPlane::zoomIn()
{
    // Increment zoomCount
    m_zoomCount++;
    // Scale x/y zoom exponentially
    float x = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
    float y = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);
    m_plane_size = { x, y };
    // Set state to calculating
    m_state = CALCULATING;
}

void ComplexPlane::zoomOut()
{
    // Decrement zoomCount
    m_zoomCount--;
    // Scale x/y zoom exponentially
    float x = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
    float y = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);
    m_plane_size = { x, y };
    // Set state to calculating
    m_state = CALCULATING;
}

// Find Vector2f coord in complex plane corresponding with screen pixel location
// Set center
void ComplexPlane::setCenter(Vector2i mousePixel)
{
    m_plane_center = mapPixelToCoords(mousePixel);
    // Set to calculating
    m_state = CALCULATING;
}
// Find Vector2f coord in complex plane corresponding with screen pixel location
// Set mouse position
void ComplexPlane::setMouseLocation(Vector2i mousePixel)
{
    m_mouseLocation = mapPixelToCoords(mousePixel);
}

// Sets output information to a stringstream which is converted to a string
void ComplexPlane::loadText(Text& text)
{
    stringstream info;
    info << "Mandelbrot Set" << endl;
    info << "Center: (" << m_plane_center.x << ", " << m_plane_center.y << ")" << endl;
    info << "Cursor: (" << m_mouseLocation.x << ", " << m_mouseLocation.y << ")" << endl;
    info << "Left-click to Zoom in" << endl;
    info << "Right-click to Zoom out" << endl;
    text.setString(info.str());
}

// Counts number of iterations of set for given coordinate
int ComplexPlane::countIterations(Vector2f coord)
{
    complex<double> c(coord.x, coord.y);
    complex<double> z = c;
    int i = 0;
    while(abs(z) < 2.0 && i < MAX_ITER)
    {
        z = z * z + c;
        i++;
    }
    return i;
}

void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{
    //TODO: Add sliding effect?? would be cool
    if (count == MAX_ITER)
    {
        r = 0;
        g = 0;
        b = 0;
    }
    else if (count > 53)
    {
        r = 223;
        g = 255;
        b = 0;
    }
    else if (count > 43)
    {
        r = 255;
        g = 187 + (53 - count) * 5;
        g = 0;
    }
    else if (count > 32)
    {
        r = 119 - (43 - count) * 5;
        g = 255;
        b = 0;
    }
    else if (count > 21)
    {
        r = 0;
        g = 255 - (32 - count) * 5;
        b = 217;
    }
    else if (count > 11)
    {
        r = 0;
        g = 72 - (21 - count) * 5;
        b = 255;
    }
    else
    {
        r = 164;
        g = 125;
        b = 121 + (11 - count) * 5;
    }
}

// Maps pixel on monitor to a complex coordinate
Vector2f ComplexPlane::mapPixelToCoords(Vector2i mousePixel)
{
    // Creates 2d coordinate vector
    Vector2f coord;
    // Maps x coordinate
    coord.x = (static_cast<float>(mousePixel.x) / (m_pixel_size.x)) 
              * m_plane_size.x + (m_plane_center.x - m_plane_size.x / 2.0);
    // Maps y coordninate
    coord.y = (static_cast<float>(mousePixel.y - m_pixel_size.y) / -(m_pixel_size.y)) 
              * m_plane_size.y + (m_plane_center.y - m_plane_size.y / 2.0);
    return coord;
}