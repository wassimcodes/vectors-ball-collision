#include "VectorManager.h"

void VectorManager::CreateVector(Button& button)
{
    if (button.IsPressed())
    {
        m_isCreatingVector = true;
        m_isComplete = false;
        m_start = { 0,0 };
        m_end = { 0, 0 };
        m_buttonJustPressed = true;
    }
    if (m_isCreatingVector && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        if (m_buttonJustPressed)
        {
            m_buttonJustPressed = false;
        }
        else if (!m_isComplete)
        {
            if (m_start.x == 0 && m_start.y == 0)
            {
                m_start = GetMousePosition();
            }
            else
            {
                m_end = GetMousePosition();
                m_isComplete = true;
                m_isCreatingVector = false;
                m_vectors.Add(m_start, m_end);
            }
        }
    }

    if (m_start.x != 0 && m_start.y != 0)
    {
        DrawCircleV(m_start, 5, RED);
    }

    if (m_isComplete)
    {
        float angle = atan2f(m_end.y - m_start.y, m_end.x - m_start.x);
        float size = 40.0f;
        Vector2 arrowPoint1 = { m_end.x - size * cosf(angle - PI / 6), m_end.y - size * sinf(angle - PI / 6) };
        Vector2 arrowPoint2 = { m_end.x - size * cosf(angle + PI / 6), m_end.y - size * sinf(angle + PI / 6) };

        DrawTriangle(m_end, arrowPoint1, arrowPoint2, BLUE);
    }
}

void VectorManager::DrawVectors()
{
    m_vectors.Draw();
}
