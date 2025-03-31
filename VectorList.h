#pragma once
#include "VectorListElement.h"

class VectorList
{
public:
	VectorList();
	~VectorList();

	void Add(Vector2 start, Vector2 end);
	void Print();
	void Draw();

private:
	void DrawTriangleAtEnd(Vector2 start, Vector2 end, float size, Color color);
	VectorListElement* m_head;
};

