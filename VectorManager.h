#pragma once

#include "raylib/raylib.h"
#include "Button.h"
#include "VectorList.h"

class VectorManager
{
public:
	VectorManager();
	void CreateVector(Button button);
	void DrawVectors();
	void CheckSelection();
	void DeleteSelectedVector();
	void MoveSelectedVector(float moveSpeed);
	void CompareVectors();
	VectorList* GetVectorList();


private:
	Vector2 m_start;
	Vector2 m_end;
	bool m_isVectorComplete;
	bool m_isCreatingVector;
	bool m_buttonJustPressed;
	bool m_vectorJustCreated;
	VectorList m_vectors;
	VectorListElement* m_selectedVector;
	VectorListElement* m_secondSelectedVector;
};


