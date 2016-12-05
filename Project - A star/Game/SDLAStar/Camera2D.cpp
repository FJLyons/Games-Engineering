#include "stdafx.h"
#include "Camera2D.h"

Camera2D::Camera2D(Rect viewPort, float initScale) : viewPort(viewPort), scale(initScale), scaleUnit(1.1f), moveUnit(30), levelSize(Size2D(1, 1))
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
	viewPort.pos.x -= moveUnit * scale;
	limitValues();
}

void Camera2D::MoveRight()
{
	viewPort.pos.x += moveUnit * scale;
	limitValues();
}

void Camera2D::MoveUp()
{
	viewPort.pos.y -= moveUnit * scale;
	limitValues();
}

void Camera2D::MoveDown()
{
	viewPort.pos.y += moveUnit * scale;
	limitValues();
}

void Camera2D::increaseScale()
{
	Point2D centre(viewPort.getCentreCopy());
	centre = centre / scale;

	scale *= scaleUnit;

	centre = centre * scale;
	viewPort.pos.x = centre.x - (viewPort.size.w / 2);
	viewPort.pos.y = centre.y - (viewPort.size.h / 2);
	limitValues();
}

void Camera2D::decreaseScale()
{
	Point2D centre(viewPort.getCentreCopy());
	centre = centre / scale;

	scale /= scaleUnit;
	if (scale < 1)
	{
		scale = 1;
	}

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
	if (viewPort.pos.x > levelSize.w * scale - viewPort.size.w)
	{
		viewPort.pos.x = levelSize.w * scale - viewPort.size.w;
	}
	if (viewPort.pos.x < 0)
	{
		viewPort.pos.x = 0;
	}
	if (viewPort.pos.y > levelSize.h * scale - viewPort.size.h)
	{
		viewPort.pos.y = levelSize.h * scale - viewPort.size.h;
	}
	if (viewPort.pos.y < 0)
	{
		viewPort.pos.y = 0;
	}
}
