#pragma once

#include "raylib/raylib.h"
#include "Button.h"
#include "VectorList.h"

class VectorManager
{
public:
	void CreateVector(Button& button);
	void DrawVectors();

private:
	Vector2 m_start;
	Vector2 m_end;
	bool m_isComplete;
	bool m_isCreatingVector;
	bool m_buttonJustPressed;
	VectorList m_vectors;
};


