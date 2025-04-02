#pragma once
#include "VectorListElement.h"

class VectorList
{
public:
	VectorList();
	~VectorList();

	void AddVector(Vector2 start, Vector2 end);
	void DrawVector(VectorListElement* selectedVector, VectorListElement* secondSelectedVector);
	VectorListElement* GetHead();
	void SetHead(VectorListElement* newHead);

private:
	void DrawArrow(Vector2 start, Vector2 end, float size, Color color);
	VectorListElement* m_head;
	Color m_lineColor;
};

