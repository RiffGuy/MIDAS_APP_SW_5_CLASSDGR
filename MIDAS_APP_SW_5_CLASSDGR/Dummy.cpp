#include "stdafx.h"
#include "Dummy.h"
#include "DiagramClass.h"
#include "Brushs.h"

Dummy::Dummy(M_Polygon* poly)
{
	drawMode = WAIT;
	deletePoly = poly;
	poly = new M_Polygon();
	resetPoly = poly;

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
	resetPoly = deletePoly;
	/*
	mpoly->setStartPoint(startPoint);
	mpoly->setEndPoint(endPoint);
	if (mpoly->getType() == D_MODE_CLASSDIAGRAM) {
		((DiagramClass*)mpoly)->setStatus(dlg);
	}
	*/
}

