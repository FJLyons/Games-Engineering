#include "stdafx.h"
#include "Camera2D.h"

Camera2D::Camera2D(Rect viewPort, float initScale) : 
	viewPort(viewPort), 
	scale(initScale), 
	scaleBy(1.1f), 
	moveBy(30), 
	levelSize(Size2D(1, 1))
{
}

Rect Camera2D::getViewport()
{
	return viewPort;
}

float Camera2D::getScale()
{
	return scale;
}

void Camera2D::MoveLeft()
{
	viewPort.pos.x -= moveBy * scale;
	limitValues();
}

void Camera2D::MoveRight()
{
	viewPort.pos.x += moveBy * scale;
	limitValues();
}

void Camera2D::MoveUp()
{
	viewPort.pos.y -= moveBy * scale;
	limitValues();
}

void Camera2D::MoveDown()
{
	viewPort.pos.y += moveBy * scale;
	limitValues();
}

void Camera2D::scaleUp()
{
	Point2D centre(viewPort.getCentreCopy());
	centre = centre / scale;

	scale *= scaleBy;
	centre = centre * scale;

	viewPort.pos.x = centre.x - (viewPort.size.w / 2);
	viewPort.pos.y = centre.y - (viewPort.size.h / 2);

	limitValues();
}

void Camera2D::scaleDown()
{
	Point2D centre(viewPort.getCentreCopy());
	centre = centre / scale;

	scale /= scaleBy;
	if (scale < 1) { scale = 1; }
	centre = centre * scale;

	viewPort.pos.x = centre.x - (viewPort.size.w / 2);
	viewPort.pos.y = centre.y - (viewPort.size.h / 2);

	limitValues();
}

void Camera2D::setLevelSize(Size2D size)
{
	levelSize = size;
}

void Camera2D::limitValues()
{
	if (viewPort.pos.x > levelSize.w * scale - viewPort.size.w) // Right
	{
		viewPort.pos.x = levelSize.w * scale - viewPort.size.w; 
	}
	if (viewPort.pos.x < 0) // Left
	{
		viewPort.pos.x = 0;
	}
	if (viewPort.pos.y > levelSize.h * scale - viewPort.size.h) // Bottom
	{
		viewPort.pos.y = levelSize.h * scale - viewPort.size.h;
	}
	if (viewPort.pos.y < 0) // Top
	{
		viewPort.pos.y = 0;
	}
}
