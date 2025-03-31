#pragma once
#include "raylib/raylib.h"

class VectorListElement
{
public:
		VectorListElement(Vector2 start, Vector2 end);
		Vector2 GetStart();
		Vector2 GetEnd();
		VectorListElement* GetNext();
		void SetNext(VectorListElement* next);

private:
	Vector2 m_start;
	Vector2 m_end;
	VectorListElement* m_next;

};

