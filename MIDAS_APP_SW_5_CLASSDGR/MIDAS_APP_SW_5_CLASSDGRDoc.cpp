
// MIDAS_APP_SW_5_CLASSDGRDoc.cpp : CMIDAS_APP_SW_5_CLASSDGRDoc 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MIDAS_APP_SW_5_CLASSDGR.h"
#endif

#include "MIDAS_APP_SW_5_CLASSDGRDoc.h"
#include "DiagramClass.h"
#include "Line.h"
#include "InheritanceLine.h"
#include "dependencyLine.h"
#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMIDAS_APP_SW_5_CLASSDGRDoc

IMPLEMENT_DYNCREATE(CMIDAS_APP_SW_5_CLASSDGRDoc, CDocument)

BEGIN_MESSAGE_MAP(CMIDAS_APP_SW_5_CLASSDGRDoc, CDocument)
END_MESSAGE_MAP()


// CMIDAS_APP_SW_5_CLASSDGRDoc 생성/소멸

CMIDAS_APP_SW_5_CLASSDGRDoc::CMIDAS_APP_SW_5_CLASSDGRDoc()
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.
	
}

CMIDAS_APP_SW_5_CLASSDGRDoc::~CMIDAS_APP_SW_5_CLASSDGRDoc()
{
}

BOOL CMIDAS_APP_SW_5_CLASSDGRDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	
	return TRUE;
}




// CMIDAS_APP_SW_5_CLASSDGRDoc serialization

void CMIDAS_APP_SW_5_CLASSDGRDoc::Serialize(CArchive& ar)
{
	Brushs* brush = theApp.viewBrushPtr;
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
		int listSize =0;

		for (int i = 0; i < brush->polygonList.size(); i++) {
			if (brush->polygonList[i]->isVisual) {
				listSize++;
			}
		}

		ar << listSize; // 폴리곤 리스트 개수를 저장

		for (int i = 0; i <  brush->polygonList.size(); i++) {
			if (brush->polygonList[i]->isVisual) {
			ar << brush->polygonList[i]->getType();
			}
		}

		for (int i = 0; i <  brush->polygonList.size(); i++) {
			if (brush->polygonList[i]->isVisual) {
			brush->polygonList[i]->saveData(ar);
			}
		}
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
		int listSize = 0;
		
		ar >> listSize; // 폴리곤 리스트 개수를 읽어옴

		printf("Load : read list size : %d\n", listSize);
		for (int i = 0; i < listSize; i++) {
			int PolyType;
			ar >> PolyType;
			printf("Load : TYPE : %d\n", PolyType);
			switch (PolyType) {
			case D_MODE_CLASSDIAGRAM: {
				printf("load ClassDiagram!\n");
				brush->polygonList.push_back(new DiagramClass());
				
				break;
			}
			case D_MODE_LINE: {
				printf("load Line!\n");
				brush->polygonList.push_back(new Line());
				
				break;
			}
			case D_MODE_LINE_INHERITANCE: {
				printf("load InheritanceLine!\n");
				brush->polygonList.push_back(new InheritanceLine());

				break;
			}
			case D_MODE_LINE_DEPENDENCY: {
				printf("load dependencyLine!\n");
				brush->polygonList.push_back(new dependencyLine());
				break;
			}
			}
			
		}
		printf("PolygonListSize : %d\n", brush->polygonList.size());
		for (int i = 0; i < brush->polygonList.size(); i++) {
			brush->polygonList[i]->saveData(ar);
			//brush->polygonList[i]->printPoint();
		}

		brush->reConnectLinesForLoadData();
		
	}
	
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CMIDAS_APP_SW_5_CLASSDGRDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CMIDAS_APP_SW_5_CLASSDGRDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMIDAS_APP_SW_5_CLASSDGRDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMIDAS_APP_SW_5_CLASSDGRDoc 진단

#ifdef _DEBUG
void CMIDAS_APP_SW_5_CLASSDGRDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMIDAS_APP_SW_5_CLASSDGRDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMIDAS_APP_SW_5_CLASSDGRDoc 명령
