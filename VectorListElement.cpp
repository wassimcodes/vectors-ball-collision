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

VectorListElement* VectorListElement::GetNext()
{
	return m_next;
}

void VectorListElement::SetNext(VectorListElement* next)
{
	m_next = next;
}
