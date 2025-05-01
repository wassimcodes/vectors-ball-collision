#include "Ball.h"
#include "math.h"
#include <iostream>

Ball::Ball(Vector2 startPos, float startRadius)
{
	m_position = startPos;
	m_velocity = {0, 0};
	m_radius = startRadius;
	m_normal = { 0, 0 };
	m_ballToWall = { 0, 0 };
	m_dotProduct = 0;
	m_velocityDotProduct = 0;
	m_currentVector = nullptr;


	std::cout << "Ball created at position: (" << m_position.x << ", " << m_position.y << ")" << std::endl;
}

Ball::~Ball()
{
	std::cout << "Ball destroyed" << std::endl;
}

void Ball::UpdatePosition(float time)
{
	m_position.x += m_velocity.x * time;
	m_position.y += m_velocity.y * time;
}

void Ball::DrawBall()
{
	DrawCircleV(m_position, m_radius, YELLOW);
}

void Ball::WindowCollision(int screenWidth, int screenHeight)
{
    if (m_position.x - m_radius < 0 || m_position.x + m_radius >= screenWidth)
    {
        m_velocity.x *= -1;
    }
    if (m_position.y - m_radius < 0 || m_position.y + m_radius >= screenHeight)
    {
        m_velocity.y *= -1;
    }
}


void Ball::LaunchBall(bool& isMouseDragging, Vector2& dragStartPos, float velocityMultiplier)
{
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        isMouseDragging = true;
        dragStartPos = GetMousePosition();
    }
    if (isMouseDragging)
    {
        Vector2 currentMousePos = GetMousePosition();
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            isMouseDragging = false;
            Vector2 dragVector = { dragStartPos.x - currentMousePos.x, dragStartPos.y - currentMousePos.y };
            m_velocity = { dragVector.x * velocityMultiplier, dragVector.y * velocityMultiplier };
        }
    }
}

Vector2 Ball::WallNormal(Vector2 startPoint, Vector2 endPoint)
{
    m_normal = { -(endPoint.y - startPoint.y), endPoint.x - startPoint.x };
	float length = sqrt(m_normal.x * m_normal.x + m_normal.y * m_normal.y);
	m_normal.x /= length;
	m_normal.y /= length;
    return m_normal;
}

float Ball::ProjectedAmount(Vector2 ballPos, Vector2 start, Vector2 direction, float lengthSquared)
{
    m_ballToWall = { ballPos.x - start.x, ballPos.y - start.y };
    m_dotProduct = m_ballToWall.x * direction.x + m_ballToWall.y * direction.y;
    return m_dotProduct / lengthSquared;
}

Vector2 Ball::GetClosestPointOnLine(Vector2 start, Vector2 direction, float positionOnLine)
{
    return { start.x + positionOnLine * direction.x, start.y + positionOnLine * direction.y };
}


float Ball::GetDistance(Vector2 point1, Vector2 point2)
{
	return sqrt(pow((point1.x - point2.x),2) + pow((point1.y - point2.y),2));
}

void Ball::ReflectVelocity(Vector2& velocity, Vector2 normal)
{
    m_velocityDotProduct = velocity.x * normal.x + velocity.y * normal.y;
	velocity.x -= 2 * m_velocityDotProduct * normal.x;
	velocity.y -= 2 * m_velocityDotProduct * normal.y;
}

void Ball::VectorCollision(VectorList* vectorList)
{
    VectorListElement* currentVector = vectorList->GetFirstElement();

    while (currentVector != nullptr)
    {
        Vector2 start = currentVector->GetStartPoint();
        Vector2 end = currentVector->GetEndPoint();
        Vector2 wallDirection = { end.x - start.x, end.y - start.y };
		Vector2 wallNormal = WallNormal(start, end);
        float wallLengthSquared = wallDirection.x * wallDirection.x + wallDirection.y * wallDirection.y;
        float projectedAmount = ProjectedAmount(m_position, start, wallDirection, wallLengthSquared);


        if (projectedAmount < 0.0f || projectedAmount > 1.0f)
        {
            currentVector = currentVector->GetNextElement();
            continue;
        }

        Vector2 closestPoint = GetClosestPointOnLine(start, wallDirection, projectedAmount);
        float distance = GetDistance(m_position, closestPoint);

        if (distance < m_radius)
        {
            ReflectVelocity(m_velocity, WallNormal(start, end));
            break;
        }
        currentVector = currentVector->GetNextElement();
    }
}




