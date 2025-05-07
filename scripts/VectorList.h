#pragma once
#include "VectorListElement.h"

class VectorList
{
public:
	VectorList();
	~VectorList();

	void AddVector(Vector2 start, Vector2 end);
	void DrawVector(VectorListElement* selectedVector, VectorListElement* secondSelectedVector);
	VectorListElement* GetFirstElement();
	void SetFirstElement(VectorListElement* newHead);

private:
	void DrawArrow(Vector2 start, Vector2 end, float size, Color color);
	VectorListElement* m_firstElement;
	Color m_lineColor;
};

