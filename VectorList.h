#pragma once
#include "VectorListElement.h"

class VectorList
{
public:
	VectorList();
	~VectorList();

	void Add(Vector2 start, Vector2 end);
	void Draw(VectorListElement* selectedVector, VectorListElement* secondSelectedVector);
	VectorListElement* GetHead();
	void SetHead(VectorListElement* newHead);

private:
	void DrawArrow(Vector2 start, Vector2 end, float size, Color color);
	VectorListElement* m_head;
};

