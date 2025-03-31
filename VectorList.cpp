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

void VectorList::Print()
{
    VectorListElement* current = m_head;
    
        std::cout << "Start: (" << current->GetStart().x << ", " << current->GetStart().y << "), "
            << "End: (" << current->GetEnd().x << ", " << current->GetEnd().y << ")" << std::endl;
        current = current->GetNext();
    
}

void VectorList::Draw() 
{
    VectorListElement* currentVector = m_head;
    while (currentVector != nullptr)
    {
        DrawCircleV(currentVector->GetStart(), 5, RED);
        DrawLineV(currentVector->GetStart(), currentVector->GetEnd(), BLUE);
        DrawTriangleAtEnd(currentVector->GetStart(), currentVector->GetEnd(), 10, BLUE);

        currentVector = currentVector->GetNext();
    }
}

void VectorList::DrawTriangleAtEnd(Vector2 start, Vector2 end, float size, Color color)
{
    float angle = atan2f(end.y - start.y, end.x - start.x);
    Vector2 arrowPoint1 = { end.x - size * cosf(angle + PI / 6), end.y - size * sinf(angle + PI / 6) };
    Vector2 arrowPoint2 = { end.x - size * cosf(angle - PI / 6), end.y - size * sinf(angle - PI / 6) };

    DrawTriangle(end, arrowPoint1, arrowPoint2, color);
}
