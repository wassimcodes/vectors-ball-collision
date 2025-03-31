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
	Button button((screenWidth - buttonWidth) / 2, (screenHeight - buttonHeight) - 40, buttonWidth, buttonHeight, "Create Vector");
	VectorManager vectorCreator;
	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);
		button.DrawButton();
		vectorCreator.CreateVector(button);
		vectorCreator.DrawVectors();
		EndDrawing();
	}

	CloseWindow();
	return 0;
	
}