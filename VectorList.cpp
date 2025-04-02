#include "VectorList.h"
#include "raylib/raylib.h"
#include <iostream>

VectorList::VectorList()
{
    m_head = nullptr;
    std::cout << "VectorList created" << std::endl;
}

VectorList::~VectorList()
{
    VectorListElement* current = m_head;
    
    VectorListElement* next = current->GetNextElement();
    delete current;
    current = next;
    std::cout << "VectorList destroyed" << std::endl;

}

void VectorList::AddVector(Vector2 start, Vector2 end)
{
    VectorListElement* newElement = new VectorListElement(start, end);
    if (m_head == nullptr)
    {
        m_head = newElement;
    }
    else
    {
        VectorListElement* current = m_head;
        while (current->GetNextElement() != nullptr)
        {
            current = current->GetNextElement();
        }
        current->SetNextElement(newElement);
    }
}

void VectorList::DrawVector(VectorListElement* selectedVector, VectorListElement* secondSelectedVector)
{
    VectorListElement* currentVector = m_head;
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
        DrawArrow(currentVector->GetStartPoint(), currentVector->GetEndPoint(), 10, m_lineColor);

        currentVector = currentVector->GetNextElement();
    }
}

VectorListElement* VectorList::GetHead()
{
    return m_head;
}

void VectorList::SetHead(VectorListElement* newHead)
{
    m_head = newHead;
}

void VectorList::DrawArrow(Vector2 startPoint, Vector2 endPoint, float size, Color color)
{
    float angle = atan2f(endPoint.y - startPoint.y, endPoint.x - startPoint.x);
    Vector2 arrowPoint1 = {endPoint.x - size * cosf(angle + PI / 4), 
                            endPoint.y - size * sinf(angle + PI / 4)};
    Vector2 arrowPoint2 = {endPoint.x - size * cosf(angle - PI / 4),
                            endPoint.y - size * sinf(angle - PI / 4)};

    DrawTriangle(endPoint, arrowPoint1, arrowPoint2, color);
}
