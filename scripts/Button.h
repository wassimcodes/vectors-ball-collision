#pragma once

#include <string>
#include "raylib/raylib.h"

class Button
{
public:
	Button(float x, float y, float w, float h, std::string t);
	void DrawButton();
	bool IsButtonPressed();
private:
	Rectangle m_button;
	std::string m_text;
};

