#pragma once

class WidgetState {
public:
	WidgetState(bool hovered, bool focused) : hovered(hovered), focused(focused) {};
	bool hovered;
	bool focused;
};