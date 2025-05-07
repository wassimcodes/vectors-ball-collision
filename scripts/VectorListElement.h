#pragma once
#include "raylib/raylib.h"

class VectorListElement
{
public:
		VectorListElement(Vector2 start, Vector2 end);
		~VectorListElement();

		Vector2 GetStartPoint();
		Vector2 GetEndPoint();
		void MoveStartPoint(float x, float y);
		void MoveEndPoint(float x, float y);
		VectorListElement* GetNextElement();
		void SetNextElement(VectorListElement* next);

private:
	Vector2 m_startPoint;
	Vector2 m_endPoint;
	VectorListElement* m_nextElement;

};

