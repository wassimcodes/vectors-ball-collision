#include "Button.h"

Button::Button(float x, float y, float w, float h, std::string t)
{
	m_button = { x, y, w, h };
	m_text = t;
}

void Button::DrawButton()
{
	DrawRectangleRec(m_button, WHITE);
	DrawText(m_text.c_str(), m_button.x + 20, m_button.y + 5, 20, BLACK);
}

bool Button::IsButtonPressed()
{
		Vector2 mousePoint = GetMousePosition();
		return CheckCollisionPointRec(mousePoint, m_button) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
	
}
