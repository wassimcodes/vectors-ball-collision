#include "VectorListElement.h"

VectorListElement::VectorListElement(Vector2 start, Vector2 end)
{
	m_start = start;
	m_end = end;
	m_next = nullptr;
}

Vector2 VectorListElement::GetStart()
{
	return m_start;
}

Vector2 VectorListElement::GetEnd()
{
	return m_end;
}

void VectorListElement::MoveStart(float x, float y)
{
	m_start.x += x;
	m_start.y += y;
}

void VectorListElement::MoveEnd(float x, float y)
{
	m_end.x += x;
	m_end.y += y;
}

VectorListElement* VectorListElement::GetNext()
{
	return m_next;
}

void VectorListElement::SetNext(VectorListElement* next)
{
	m_next = next;
}
