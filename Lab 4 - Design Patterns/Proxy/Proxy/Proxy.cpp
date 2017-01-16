// Common Interface (Subject)
#ifndef IGRAPHIC_H
#define IGRAPHIC_H

//Common Interface
class IGraphic
{
public:
	virtual void Draw() = 0;
};

#endif

// Real Subject (Definition)
#ifndef GRAPHIC_H
#define GRAPHIC_H

#include "IGraphic.h"

class Graphic : public IGraphic
{
public:
	Graphic();
	~Graphic();
	void Draw();
};

#endif

// Real Subject (Implementation)
#include <iostream>
#include "Graphic.h"

using namespace std;

Graphic::Graphic() {
}

Graphic::~Graphic() {
}

void Graphic::Draw()
{
	cout << "Drawing Graphic Object" << endl;
}

// Proxy (Definition)
#ifndef GRAPHIC_PROXY_H
#define GRAPHIC_PROXY_H
#include "Graphic.h"
#include "IGraphic.h"
class GraphicProxy : public IGraphic
{
public:
	GraphicProxy();
	~GraphicProxy();
	void Draw();
private:
	Graphic* graphic;
	Graphic* getInstance(void);
};
#endif

// Proxy (Implementation)
#include <iostream>
#include "Graphic.h"
#include "GraphicProxy.h"
using namespace std;
GraphicProxy::GraphicProxy()
{
	this->graphic = 0;
}
GraphicProxy::~GraphicProxy()
{
	if (graphic)
		delete graphic;
}

Graphic* GraphicProxy::getInstance(void)
{
	if (!graphic)
		graphic = new Graphic();
	return graphic;
}
void GraphicProxy::Draw()
{
	getInstance()->Draw();
}

// Client (Implementation)
#include <iostream>
#include "GraphicProxy.h"

using namespace std;

int main(void)
{
	GraphicProxy gp;
	gp.Draw();
}
