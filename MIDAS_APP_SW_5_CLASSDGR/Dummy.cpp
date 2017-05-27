#include "stdafx.h"
#include "Dummy.h"
#include "DiagramClass.h"
#include "Brushs.h"

Dummy::Dummy() {
	startPoint = CPoint(0, 0);
	endPoint = CPoint(0, 0);
}
Dummy::Dummy(M_Polygon* poly)
{

	drawMode = WAIT;
	ptrPoly = poly;
	dataPoly = *poly;
	*poly = *(new Dummy());

	/*
	startPoint = poly->getStartPoint();
	endPoint = poly->getEndPoint();
	if (poly->getType() == D_MODE_CLASSDIAGRAM) {
		dlg = ((DiagramClass*)poly)->getStatus();
		((DiagramClass*)poly)->setStatus(NULL);
	}
	poly->setStartPoint(CPoint(0, 0));
	poly->setEndPoint(CPoint(0, 0));
	*/
}


Dummy::~Dummy()
{
	ptrPoly = new M_Polygon(dataPoly);
	/*
	mpoly->setStartPoint(startPoint);
	mpoly->setEndPoint(endPoint);
	if (mpoly->getType() == D_MODE_CLASSDIAGRAM) {
		((DiagramClass*)mpoly)->setStatus(dlg);
	}
	*/
}

