#pragma once

#include "raylib/raylib.h"
#include "VectorList.h"

class Ball
{
public:
	Ball(Vector2 startPos, float startRadius);
	virtual ~Ball();
	void UpdatePosition(float time);
	void DrawBall();
	void WindowCollision(int screenWidth, int screenHeight);
	void LaunchBall(bool& isMouseDragging, Vector2& dragStartPos, float velocityMultiplier);
	
private:
	Vector2 m_position;
	Vector2 m_velocity;
	float m_radius;
	Vector2 m_normal;
	Vector2 m_ballToWall;
	float m_dotProduct;
	float m_velocityDotProduct;
	VectorListElement* m_currentVector;

	Vector2 WallNormal(Vector2 startPoint, Vector2 endPoint);
	float ProjectedAmount(Vector2 ballPos, Vector2 start, Vector2 direction, float lengthSquared);
	Vector2 GetClosestPointOnLine(Vector2 start, Vector2 direction, float positionOnLine);
	float GetDistance(Vector2 point1, Vector2 point2);
	void ReflectVelocity(Vector2& velocity, Vector2 normal);

public:
	void VectorCollision(VectorList* vectorList); 
};

