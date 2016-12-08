#pragma once
#include "BasicTypes.h"

class Camera2D
{
public:
	Camera2D(Rect viewPort, float initScale);
	Rect getViewport();
	float getScale();

	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();

	void scaleUp();
	void scaleDown();

	void setLevelSize(Size2D size);

private:
	Rect viewPort;
	Size2D levelSize;

	float scale;
	float moveBy;
	float scaleBy;

	void limitValues();
};

