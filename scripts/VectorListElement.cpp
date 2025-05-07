#include "VectorListElement.h"
#include <iostream>

VectorListElement::VectorListElement(Vector2 start, Vector2 end)
{
	m_startPoint = start;
	m_endPoint = end;
	m_nextElement = nullptr;
	std::cout << "Vector created" << std::endl;
}

VectorListElement::~VectorListElement()
{
	std::cout << "Vector destroyed" << std::endl;
}

Vector2 VectorListElement::GetStartPoint()
{
	return m_startPoint;
}

Vector2 VectorListElement::GetEndPoint()
{
	return m_endPoint;
}

void VectorListElement::MoveStartPoint(float x, float y)
{
	m_startPoint.x += x;
	m_startPoint.y += y;
}

void VectorListElement::MoveEndPoint(float x, float y)
{
	m_endPoint.x += x;
	m_endPoint.y += y;
}

VectorListElement* VectorListElement::GetNextElement()
{
	return m_nextElement;
}

void VectorListElement::SetNextElement(VectorListElement* next)
{
	m_nextElement = next;
}
