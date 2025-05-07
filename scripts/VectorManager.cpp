#include "VectorManager.h"
#include <iostream>

VectorManager::VectorManager()
{
    m_isVectorComplete = false;
    m_isCreatingVector = false;
    m_buttonJustPressed = false;
	m_vectorJustCreated = false;
    m_selectedVector = nullptr;
	m_secondSelectedVector = nullptr;
}

void VectorManager::CreateVector(Button button)
{
    if (button.IsButtonPressed())
    {
        m_isCreatingVector = true;
        m_isVectorComplete = false;
        m_start = { 0,0 };
        m_end = { 0, 0 };
        m_buttonJustPressed = true;
    }

    if (IsKeyPressed(KEY_BACKSPACE))
    {
        if (m_isCreatingVector)
        {
            m_isCreatingVector = false;
            m_isVectorComplete = false;
        }
		else if (m_selectedVector != NULL)
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
        else if (!m_isVectorComplete)
        {
            if (m_start.x == 0 && m_start.y == 0)
            {
                m_start = GetMousePosition();
            }
            else
            {
                m_end = GetMousePosition();
                m_isVectorComplete = true;
                m_isCreatingVector = false;
                m_vectors.AddVector(m_start, m_end);
				m_vectorJustCreated = true;
            }
        }
    }
}

void VectorManager::DrawVectors()
{
    m_vectors.DrawVector(m_selectedVector, m_secondSelectedVector);
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

    VectorListElement* currentVector = m_vectors.GetFirstElement();

    while (currentVector != nullptr)
    {
        if (CheckCollisionPointLine(mousePos, currentVector->GetStartPoint(), currentVector->GetEndPoint(), 30))
        {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                if (m_selectedVector == nullptr)
                {
                    m_selectedVector = currentVector;
                }
                else if (m_selectedVector != currentVector)
                {
                    m_secondSelectedVector = currentVector;
                    CompareVectors();
                }
                vectorSelected = true;
            }

            break;
        }
        currentVector = currentVector->GetNextElement();
    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !vectorSelected)
    {
        m_selectedVector = nullptr;
		m_secondSelectedVector = nullptr;
    }
}

void VectorManager::DeleteSelectedVector()
{
    if (m_vectors.GetFirstElement() == m_selectedVector)
    {
        VectorListElement* nextVec = m_selectedVector->GetNextElement();
		delete m_selectedVector;
        m_vectors.SetFirstElement(nextVec);
    }

    else
    {
        VectorListElement* prevVec = m_vectors.GetFirstElement();
        while (prevVec != nullptr && prevVec->GetNextElement() != m_selectedVector)
        {
            prevVec = prevVec->GetNextElement();
        }

        if (prevVec != nullptr)
        {
            VectorListElement* next = m_selectedVector->GetNextElement();
            delete m_selectedVector;
            prevVec->SetNextElement(next);
        }
    }

    m_selectedVector = nullptr;
}

void VectorManager::MoveSelectedVector(float moveSpeed)
{
	if (IsKeyDown(KEY_W))
	{
		m_selectedVector->MoveStartPoint(0, -moveSpeed);
		m_selectedVector->MoveEndPoint(0, -moveSpeed);
	}
	if (IsKeyDown(KEY_S))
	{
		m_selectedVector->MoveStartPoint(0, moveSpeed);
		m_selectedVector->MoveEndPoint(0, moveSpeed);
	}
	if (IsKeyDown(KEY_A))
	{
		m_selectedVector->MoveStartPoint(-moveSpeed, 0);
		m_selectedVector->MoveEndPoint(-moveSpeed, 0);
	}
	if (IsKeyDown(KEY_D))
	{
		m_selectedVector->MoveStartPoint(moveSpeed, 0);
		m_selectedVector->MoveEndPoint(moveSpeed, 0);
	}
}

void VectorManager::CompareVectors()
{
    Vector2 startPoint1 = m_selectedVector->GetStartPoint();
    Vector2 endPoint1 = m_selectedVector->GetEndPoint();
    Vector2 startPoint2 = m_secondSelectedVector->GetStartPoint();
    Vector2 endPoint2 = m_secondSelectedVector->GetEndPoint();

    Vector2 vector1 = { endPoint1.x - startPoint1.x, endPoint1.y - startPoint1.y };
    Vector2 vector2 = { endPoint2.x - startPoint2.x, endPoint2.y - startPoint2.y };

    float dotProduct = vector1.x * vector2.x + vector1.y * vector2.y;
    Vector2 sum = { vector1.x + vector2.x, vector1.y + vector2.y };
	std::cout << "Vector 1 Coordinates: (" << startPoint1.x << ", " << startPoint1.y << "), (" << endPoint1.x << ", " << endPoint1.y << ")" << std::endl;
	std::cout << "Vector 2 Coordinates: (" << startPoint2.x << ", " << startPoint2.y << "), (" << endPoint2.x << ", " << endPoint2.y << ")" << std::endl;
    std::cout << "Vector 1: (" << vector1.x << ", " << vector1.y << ")" << std::endl;
    std::cout << "Vector 2: (" << vector2.x << ", " << vector2.y << ")" << std::endl;
    std::cout << "Dot Product: " << dotProduct << std::endl;
    std::cout << "Sum: (" << sum.x << ", " << sum.y << ")" << std::endl;
}

VectorList* VectorManager::GetVectorList()
{
    return &m_vectors;
}

