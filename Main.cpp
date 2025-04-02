#include "raylib/raylib.h"
#include "Button.h"
#include "VectorManager.h"

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
	
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);
		button.DrawButton();
		vectorManager.CreateVector(button);
		vectorManager.CheckSelection();
		vectorManager.DrawVectors();
		vectorManager.MoveSelectedVector(3.0f);
		EndDrawing();
	}

	CloseWindow();
	return 0;
	
}