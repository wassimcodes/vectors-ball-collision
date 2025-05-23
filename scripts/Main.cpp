#include "raylib/raylib.h"
#include "Button.h"
#include "VectorManager.h"
#include "Ball.h"

int main()
{
	int screenWidth = 1080;
	int screenHeight = 720;
	float buttonWidth = 200;
	float buttonHeight = 30;

	InitWindow(screenWidth, screenHeight, "Vectors - Raylib");
	SetTargetFPS(60);

	Button button((screenWidth - buttonWidth) / 2, (screenHeight - buttonHeight) - 40, buttonWidth, buttonHeight, "Create Vector");
	VectorManager vectorManager;
	Ball ball({ screenWidth / 2.0f, screenHeight / 2.0f }, 10);

	bool isMouseDragging = false;
	Vector2 dragStartPos = { 0, 0 };

	while (!WindowShouldClose())
	{
		// Vector manipulation
		BeginDrawing();
		ClearBackground(BLACK);
		button.DrawButton();
		vectorManager.CreateVector(button);
		vectorManager.CheckSelection();
		vectorManager.DrawVectors();
		vectorManager.MoveSelectedVector(3.0f);

		// Ball collision
		ball.DrawBall();
		ball.LaunchBall(isMouseDragging, dragStartPos, 1.5f);
		ball.UpdatePosition(GetFrameTime());
		ball.WindowCollision(screenWidth, screenHeight);
		ball.VectorCollision(vectorManager.GetVectorList());

		EndDrawing();
	}


	CloseWindow();
	return 0;
	
}