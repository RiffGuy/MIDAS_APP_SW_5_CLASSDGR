#include "stdafx.h"
#include "Dummy.h"
#include "DiagramClass.h"
#include "Brushs.h"

Dummy::Dummy() {

}
Dummy::Dummy(M_Polygon* poly)
{
	drawMode = WAIT;
	//polyAt = at;
//	ptrPoly = poly;
//	dataPoly = *poly;
//	*poly = *(new Dummy());

	
	mpoly = poly;
	mpoly->isVisual = false;
	/*
	startPoint = poly->getStartPoint();
	endPoint = poly->getEndPoint();
	if (poly->getType() == D_MODE_CLASSDIAGRAM) {
		dlg = ((DiagramClass*)poly)->getStatus();
		((DiagramClass*)poly)->setStatus(NULL);
	}
	poly->startPoint.x = 0;
	poly->startPoint.y = 0;
	poly->setEndPoint(CPoint(-1, -1));
	mpoly = poly;
	*/
	printf("dummy »ý¼º\n");
	
}


Dummy::~Dummy()
{
	//ptrPoly = new M_Polygon(dataPoly);
	/*
	mpoly->setStartPoint(startPoint);
	mpoly->setEndPoint(endPoint);
	if (mpoly->getType() == D_MODE_CLASSDIAGRAM) {
		((DiagramClass*)mpoly)->setStatus(dlg);
	}
	*/
	printf("dummy ¼Ò¸ê\n");
	
}

void Dummy::reset(){
	/*
	mpoly->setStartPoint(startPoint);
	mpoly->setEndPoint(endPoint);
	if (mpoly->getType() == D_MODE_CLASSDIAGRAM) {
		((DiagramClass*)mpoly)->setStatus(dlg);
	}*/

	mpoly->isVisual = true;
	printf("dummy reset\n");

}

