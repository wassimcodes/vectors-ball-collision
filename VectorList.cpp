#include "VectorList.h"
#include "raylib/raylib.h"
#include <iostream>

VectorList::VectorList()
{
    m_head = nullptr;
}

VectorList::~VectorList()
{
    VectorListElement* current = m_head;
    
    VectorListElement* next = current->GetNext();
    delete current;
    current = next;
}

void VectorList::Add(Vector2 start, Vector2 end)
{
    VectorListElement* newElement = new VectorListElement(start, end);
    if (m_head == nullptr)
    {
        m_head = newElement;
    }
    else
    {
        VectorListElement* current = m_head;
        while (current->GetNext() != nullptr)
        {
            current = current->GetNext();
        }
        current->SetNext(newElement);
    }
}

void VectorList::Draw(VectorListElement* selectedVector, VectorListElement* secondSelectedVector)
{
    VectorListElement* currentVector = m_head;
    while (currentVector != nullptr)
    {
        Color lineColor;
        if (currentVector == selectedVector || currentVector == secondSelectedVector)
        {
            lineColor = RED;
        }
        else
        {
            lineColor = BLUE;
        }

        DrawCircleV(currentVector->GetStart(), 5, RED);
        DrawLineV(currentVector->GetStart(), currentVector->GetEnd(), lineColor);
        DrawArrow(currentVector->GetStart(), currentVector->GetEnd(), 10, lineColor);

        currentVector = currentVector->GetNext();
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

void VectorList::DrawArrow(Vector2 start, Vector2 end, float size, Color color)
{
    float angle = atan2f(end.y - start.y, end.x - start.x);
    Vector2 arrowPoint1 = { end.x - size * cosf(angle + PI / 6), end.y - size * sinf(angle + PI / 6) };
    Vector2 arrowPoint2 = { end.x - size * cosf(angle - PI / 6), end.y - size * sinf(angle - PI / 6) };

    DrawTriangle(end, arrowPoint1, arrowPoint2, color);
}
