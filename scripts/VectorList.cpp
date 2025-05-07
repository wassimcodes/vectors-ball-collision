#include "VectorList.h"
#include "raylib/raylib.h"
#include <iostream>

VectorList::VectorList()
{
    m_firstElement = nullptr;
    std::cout << "VectorList created" << std::endl;
}

VectorList::~VectorList()
{
    std::cout << "VectorList destroyed" << std::endl;
}

void VectorList::AddVector(Vector2 start, Vector2 end)
{
    VectorListElement* newElement = new VectorListElement(start, end);
    if (m_firstElement == nullptr)
    {
        m_firstElement = newElement;
    }
    else
    {
        VectorListElement* currentElement = m_firstElement;
        while (currentElement->GetNextElement() != nullptr)
        {
            currentElement = currentElement->GetNextElement();
        }
        currentElement->SetNextElement(newElement);
    }
}

void VectorList::DrawVector(VectorListElement* selectedVector, VectorListElement* secondSelectedVector)
{
    VectorListElement* currentVector = m_firstElement;
    while (currentVector != nullptr)
    {
        if (currentVector == selectedVector || currentVector == secondSelectedVector)
        {
            m_lineColor = RED;
        }
        else
        {
            m_lineColor = BLUE;
        }

        DrawCircleV(currentVector->GetStartPoint(), 5, m_lineColor);
        DrawLineV(currentVector->GetStartPoint(), currentVector->GetEndPoint(), m_lineColor);
        DrawArrow(currentVector->GetStartPoint(), currentVector->GetEndPoint(), 25, m_lineColor);

        currentVector = currentVector->GetNextElement();
    }
}

VectorListElement* VectorList::GetFirstElement()
{
    return m_firstElement;
}

void VectorList::SetFirstElement(VectorListElement* newFirstElement)
{
    m_firstElement = newFirstElement;
}

void VectorList::DrawArrow(Vector2 startPoint, Vector2 endPoint, float size, Color color)
{
    float angle = atan2f(endPoint.y - startPoint.y, endPoint.x - startPoint.x);
    Vector2 arrowPoint1 = {endPoint.x - size * cosf(angle + 45), 
                            endPoint.y - size * sinf(angle + 45)};
	Vector2 arrowPoint2 = { endPoint.x - size * cosf(angle - 45),
                            endPoint.y - size * sinf(angle - 45)};

    DrawTriangle(endPoint, arrowPoint1, arrowPoint2, color);
}
