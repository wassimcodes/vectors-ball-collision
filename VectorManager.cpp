#include "VectorManager.h"
#include <iostream>

VectorManager::VectorManager()
{
    m_isComplete = false;
    m_isCreatingVector = false;
    m_buttonJustPressed = false;
	m_vectorJustCreated = false;
    m_selectedVector = nullptr;
	m_secondSelectedVector = nullptr;
}

void VectorManager::CreateVector(Button& button)
{
    if (button.IsPressed())
    {
        m_isCreatingVector = true;
        m_isComplete = false;
        m_start = { 0,0 };
        m_end = { 0, 0 };
        m_buttonJustPressed = true;
    }

    if (IsKeyPressed(KEY_BACKSPACE))
    {
        if (m_isCreatingVector)
        {
            m_isCreatingVector = false;
            m_isComplete = false;
            m_start = { 0,0 };
            m_end = { 0, 0 };
        }
		else if (m_selectedVector != nullptr)
        {
            DeleteSelectedVector();
        }
    }

    

    if (m_isCreatingVector && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        if (m_buttonJustPressed)
        {
            m_buttonJustPressed = false;
        }
        else if (!m_isComplete)
        {
            if (m_start.x == 0 && m_start.y == 0)
            {
                m_start = GetMousePosition();
            }
            else
            {
                m_end = GetMousePosition();
                m_isComplete = true;
                m_isCreatingVector = false;
                m_vectors.Add(m_start, m_end);
				m_vectorJustCreated = true;
            }
        }
    }
}

void VectorManager::DrawVectors()
{
    m_vectors.Draw(m_selectedVector, m_secondSelectedVector);
}

void VectorManager::CheckSelection()
{
    if (m_isCreatingVector)
    {
        return;
    }

	if (m_vectorJustCreated)
	{
		m_vectorJustCreated = false;
		return;
	}

    Vector2 mousePos = GetMousePosition();
    bool vectorSelected = false;
    bool mouseClicked = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

    VectorListElement* current = m_vectors.GetHead();

    while (current != nullptr)
    {
        Vector2 start = current->GetStart();
        Vector2 end = current->GetEnd();

        if (CheckCollisionPointLine(mousePos, start, end, 30))
        {
            if (mouseClicked)
            {
                if (m_selectedVector == nullptr)
                {
                    m_selectedVector = current;
                }
                else if (m_selectedVector != current)
                {
                    m_secondSelectedVector = current;
                    CompareVectors();
                }
                vectorSelected = true;
            }

            break;
        }
        current = current->GetNext();
    }

    if (mouseClicked && !vectorSelected)
    {
        m_selectedVector = nullptr;
		m_secondSelectedVector = nullptr;
        std::cout << "No vector selected" << std::endl;
    }
}

void VectorManager::DeleteSelectedVector()
{
    if (m_vectors.GetHead() == m_selectedVector)
    {
        VectorListElement* next = m_selectedVector->GetNext();
		delete m_selectedVector;
        m_vectors.SetHead(next);
    }

    else
    {
        VectorListElement* prev = m_vectors.GetHead();
        while (prev != nullptr && prev->GetNext() != m_selectedVector)
        {
            prev = prev->GetNext();
        }

        if (prev != nullptr)
        {
            VectorListElement* next = m_selectedVector->GetNext();
            delete m_selectedVector;
            prev->SetNext(next);
        }
    }

    m_selectedVector = nullptr;
}

void VectorManager::MoveSelectedVector(float moveSpeed)
{
	if (m_selectedVector == nullptr)
	{
		return;
	}
	if (IsKeyDown(KEY_W))
	{
		m_selectedVector->MoveStart(0, -moveSpeed);
		m_selectedVector->MoveEnd(0, -moveSpeed);
	}
	if (IsKeyDown(KEY_S))
	{
		m_selectedVector->MoveStart(0, moveSpeed);
		m_selectedVector->MoveEnd(0, moveSpeed);
	}
	if (IsKeyDown(KEY_A))
	{
		m_selectedVector->MoveStart(-moveSpeed, 0);
		m_selectedVector->MoveEnd(-moveSpeed, 0);
	}
	if (IsKeyDown(KEY_D))
	{
		m_selectedVector->MoveStart(moveSpeed, 0);
		m_selectedVector->MoveEnd(moveSpeed, 0);
	}
}

void VectorManager::CompareVectors()
{
    if (m_selectedVector == nullptr || m_secondSelectedVector == nullptr)
    {
        return;
    }
        

    Vector2 start1 = m_selectedVector->GetStart();
    Vector2 end1 = m_selectedVector->GetEnd();
    Vector2 start2 = m_secondSelectedVector->GetStart();
    Vector2 end2 = m_secondSelectedVector->GetEnd();

    Vector2 vec1 = { end1.x - start1.x, end1.y - start1.y };
    Vector2 vec2 = { end2.x - start2.x, end2.y - start2.y };

    float dotProduct = vec1.x * vec2.x + vec1.y * vec2.y;
    Vector2 sum = { vec1.x + vec2.x, vec1.y + vec2.y };

    std::cout << "Vector 1: (" << vec1.x << ", " << vec1.y << ")" << std::endl;
    std::cout << "Vector 2: (" << vec2.x << ", " << vec2.y << ")" << std::endl;
    std::cout << "Dot Product: " << dotProduct << std::endl;
    std::cout << "Sum: (" << sum.x << ", " << sum.y << ")" << std::endl;
}

