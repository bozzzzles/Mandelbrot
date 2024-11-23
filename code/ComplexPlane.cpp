#include "ComplexPlane.h"

ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight)
{
    m_pixel_size = { pixelWidth, pixelHeight };
    m_aspectRatio = static_cast<float>(pixelHeight) / pixelWidth;
    m_plane_center = { 0, 0 };
    m_plane_size = { BASE_WIDTH, BASE_HEIGHT * m_aspectRatio };
    m_zoomCount = 0;
    m_state = State::CALCULATING;
    m_vArray.setPrimitiveType(Points);
    m_vArray.resize(pixelWidth * pixelHeight);
}

void ComplexPlane::draw(RenderTarget& target, RenderStates States) const
{
    target.draw(m_vArray);
}

void ComplexPlane::updateRender()
{
    if (m_state == CALCULATING)
    {
        for (int i = 0; i < m_pixel_sixe.y; i++)
        {
            for (int j = 0; j < m_pixel_size.x; j++)
            {
                vArray[j + i * pixelWidth].position = { (float)j,(float)i };
                int n = countIterations(mapPixelToCoords({ j, i }));
                Uint8 r, g, b;
                iterationsToRGB(n, r, g, b);
                vArray[j + i * pixelWidth].color = { r,g,b };
            }
        }
        m_state = DISPLAYING;
    }
}

void ComplexPlane::zoomIn()
{
    m_zoomCount++;
    float x = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
    float y = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);
    m_plane_size = { x, y };
    m_state = CALCULATING;
}

void ComplexPlane::zoomOut()
{
    m_zoomCount--;
    float x = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
    float y = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);
    m_plane_size = { x, y };
    m_state = CALCULATING;
}

void ComplexPlane::setCenter(Vector2i mousePixel)
{
    m_plane_center = mapPixelToCoords(mousePixel);
    m_state = CALCULATING;
}

void ComplexPlane::setMouseLocation(Vector2i mousePixel)
{
    m_mouseLocation = mapPixelToCoords(mousePixel);
}

void ComplexPlane::loadText(Text& text)
{
    stringstream info;
    info << "Mandelbrot Set" << endl;
    info << "Center: (" << m_plane_center.x << ", " << m_plane_center.y << ")" << endl;
    info << "Cursor: (" << m_mouseLocation.x << ", " << m_mouseLocation.y << ")" << endl;
    info << "Left-click to Zoom in" << endl;
    info << "Right-click to Zoom out" << endl;
    text.setString(info);
}