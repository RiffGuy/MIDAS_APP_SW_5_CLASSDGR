#pragma once
#include "M_Polygon.h"
#include "NewClassAddDLG.h"

class Dummy :
	public M_Polygon
{
public:
	int drawMode = 0;
	int WAIT = 0;
	int START = 1;
	int MOVE = 2;
	int END = 3;
	int polyAt;
	M_Polygon* ptrPoly;
	M_Polygon dataPoly;
	M_Polygon* mpoly;
	NewClassAddDLG* dlg;
	Dummy();
	Dummy(M_Polygon* poly);
	~Dummy();

	void reset();

	inline virtual int getType() { return D_MODE_DUMMY; }
};


