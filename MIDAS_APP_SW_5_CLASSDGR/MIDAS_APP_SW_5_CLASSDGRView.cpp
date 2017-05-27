
// MIDAS_APP_SW_5_CLASSDGRView.cpp : CMIDAS_APP_SW_5_CLASSDGRView 클래스의 구현
//

#include "stdafx.h"
#include <iostream>
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MIDAS_APP_SW_5_CLASSDGR.h"
#endif

#include "MIDAS_APP_SW_5_CLASSDGRDoc.h"
#include "MIDAS_APP_SW_5_CLASSDGRView.h"
#include "NewClassAddDLG.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// printf 함수를 활용해서 표준 출력 결과를 콘솔에 출력 하기 위해 추가된 코드
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console") 

// CMIDAS_APP_SW_5_CLASSDGRView

IMPLEMENT_DYNCREATE(CMIDAS_APP_SW_5_CLASSDGRView, CView)

BEGIN_MESSAGE_MAP(CMIDAS_APP_SW_5_CLASSDGRView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_ADD_CLASS, &CMIDAS_APP_SW_5_CLASSDGRView::OnAddClass)
	ON_COMMAND(ID_ADD_NEW_CLASS_ON_MENU, &CMIDAS_APP_SW_5_CLASSDGRView::OnAddNewClassOnMenu)
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_MENU_PROPERTIES, &CMIDAS_APP_SW_5_CLASSDGRView::OnMenuProperties)
	ON_COMMAND(ID_MENU_INHERITANCE, &CMIDAS_APP_SW_5_CLASSDGRView::OnMenuInheritance)
	ON_COMMAND(ID_MENU_DELETE, &CMIDAS_APP_SW_5_CLASSDGRView::OnMenuDelete)
	ON_COMMAND(ID_MENU_DEPENDENCY, &CMIDAS_APP_SW_5_CLASSDGRView::OnMenuDependency)
	ON_COMMAND(ID_MOVE_CLASS, &CMIDAS_APP_SW_5_CLASSDGRView::OnMoveClass)
	ON_COMMAND(IDD_REDO_CLASS, &CMIDAS_APP_SW_5_CLASSDGRView::OnIddRedoClass)
	ON_COMMAND(IDD_UNDO_CLASS, &CMIDAS_APP_SW_5_CLASSDGRView::OnIddUndoClass)
END_MESSAGE_MAP()

// CMIDAS_APP_SW_5_CLASSDGRView 생성/소멸

CMIDAS_APP_SW_5_CLASSDGRView::CMIDAS_APP_SW_5_CLASSDGRView()
{
	
	// TODO: 여기에 생성 코드를 추가합니다.
	m_Brush = new Brushs();
	m_Brush->setBrushWnd(this);
	theApp.viewBrushPtr = m_Brush;
	m_StartToMove = false;
	m_CurSelectRect = NULL;
	m_CurSelectRect_Temp = NULL;
	m_MakeClass = false;
	m_drawline = false;
}

CMIDAS_APP_SW_5_CLASSDGRView::~CMIDAS_APP_SW_5_CLASSDGRView()
{
}

BOOL CMIDAS_APP_SW_5_CLASSDGRView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMIDAS_APP_SW_5_CLASSDGRView 그리기

void CMIDAS_APP_SW_5_CLASSDGRView::OnDraw(CDC* /*pDC*/)
{

	CDC* pDC2 = GetDC(); // Brush 측으로 넘기는 CDC객체는 새로 얻어와야 한다.(해당 함수 매개변수 CDC는 소멸됨)
	m_Brush->setCDC(pDC2);

	CMIDAS_APP_SW_5_CLASSDGRDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.

	m_Brush->ReDrawAll();
}


// CMIDAS_APP_SW_5_CLASSDGRView 인쇄

BOOL CMIDAS_APP_SW_5_CLASSDGRView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMIDAS_APP_SW_5_CLASSDGRView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMIDAS_APP_SW_5_CLASSDGRView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMIDAS_APP_SW_5_CLASSDGRView 진단

#ifdef _DEBUG
void CMIDAS_APP_SW_5_CLASSDGRView::AssertValid() const
{
	CView::AssertValid();
}

void CMIDAS_APP_SW_5_CLASSDGRView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMIDAS_APP_SW_5_CLASSDGRDoc* CMIDAS_APP_SW_5_CLASSDGRView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{	

	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMIDAS_APP_SW_5_CLASSDGRDoc)));
	return (CMIDAS_APP_SW_5_CLASSDGRDoc*)m_pDocument;
}
#endif //_DEBUG


// CMIDAS_APP_SW_5_CLASSDGRView 메시지 처리기


void CMIDAS_APP_SW_5_CLASSDGRView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	//printf("mode : %d\n", m_Brush->getDrawMode());
	CView::OnMouseMove(nFlags, point);

	

	if (m_Brush->getDrawMode() == D_MODE_CLASSDIAGRAM) {
		//사각형 클릭시 움직이기
		if (m_StartToMove) {
			m_EndPos = point;
			CPoint pos = m_EndPos - m_StartPos;
			m_StartPos = point;
			m_CurSelectRect->setStartPoint(m_CurSelectRect->getStartPoint() + pos);
			m_CurSelectRect->setEndPoint(m_CurSelectRect->getEndPoint() + pos);
			m_CurSelectRect->reConnectedPoint();
			Invalidate();
			UpdateWindow();
			m_Brush->ReDrawAll();
		}
		else if (m_Brush->Draw(point, nFlags, MOUSE_MOVE)) {
			Invalidate();
			UpdateWindow();
			m_Brush->ReDrawAll();
		}
	}else if (m_Brush->Draw(point, nFlags, MOUSE_MOVE)) {
		
		Invalidate();
		UpdateWindow();
		m_Brush->ReDrawAll();
	}

	
}


void CMIDAS_APP_SW_5_CLASSDGRView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CView::OnLButtonUp(nFlags, point);

	if (m_StartToMove == true) {
		m_EndPos = point;
	}
	if (m_MakeClass == true && m_Brush->polygonList.size() > 0) {
		m_Brush->polygonList[m_Brush->polygonList.size() - 1]->setContents();
		if (((DiagramClass *)m_Brush->polygonList[m_Brush->polygonList.size() - 1])->isClassContentsEmpty()) {
			m_Brush->polygonList.pop_back();
		}

		Invalidate();
		UpdateWindow();
		m_Brush->ReDrawAll();
	}
	m_Brush->Draw(point, nFlags, L_MOUSE_UP);

	m_StartToMove = false;
	m_MakeClass = false;
	std::cout << m_Brush->polygonList.size() << std::endl;


}


void CMIDAS_APP_SW_5_CLASSDGRView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	CView::OnLButtonDown(nFlags, point);

	if (m_Brush->polygonList.size() > 0) {
		m_CurSelectRect = findrect(point);
	}
	
	// 사각형 클릭시 움직이기 준비
	if (m_CurSelectRect != NULL) {
		printf("선택된 사각형이 있습니다.\n");
		m_StartPos = point;
		m_StartToMove = true;
		


		// 상속 혹은 의존 직선의 경우 클래스에 닿지 않으면 소멸되도록 함.
		// 해당 경우는 선이 사각형에 포함된 경우
		if (m_Brush->getDrawMode() == D_MODE_LINE_INHERITANCE || m_Brush->getDrawMode() == D_MODE_LINE_DEPENDENCY) {
			if (m_Brush->polygonList.size() - 1 >= 0) {
				// 시작 지점과 연결된 사각형 객체를 찾는다.
				M_Polygon* tempClassRect = findrect(CPoint(
					m_Brush->polygonList[m_Brush->polygonList.size() - 1]->startPoint
				));

				// 종료 지점과 연결된 사각형 객체는 이미 저장되어 있음.
				tempClassRect->addConnectedPoint(
					&(m_Brush->polygonList[m_Brush->polygonList.size() - 1]->startPoint),
					&(m_Brush->polygonList[m_Brush->polygonList.size() - 1]->endPoint)
				);
				m_CurSelectRect->addConnectedPoint(
					&(m_Brush->polygonList[m_Brush->polygonList.size() - 1]->endPoint),
					&(m_Brush->polygonList[m_Brush->polygonList.size() - 1]->startPoint)
					);
				Invalidate();
				UpdateWindow();
				m_Brush->ReDrawAll();
			}
			m_Brush->Draw(point, nFlags, L_MOUSE_DOWN);
			OnDrawRect();

		}
		
	}
	else if (m_MakeClass){
		//바탕화면 클릭시 그리기(나중에 수정할 부분)
		printf("선택된 사각형이 없습니다.\n");
		OnDrawRect();
		m_CurSelectRect = NULL;
		m_Brush->Draw(point, nFlags, L_MOUSE_DOWN);
		
	}
	else { // 상속 선 혹은 의존 선 -> 클래스에 선택되지 않은 경우
		if (m_Brush->getDrawMode() == D_MODE_LINE_INHERITANCE || m_Brush->getDrawMode() == D_MODE_LINE_DEPENDENCY) {
			m_Brush->mpoly->removeConnectedPoint();
			m_Brush->polygonList.pop_back();
			Invalidate();
			UpdateWindow();
			m_Brush->ReDrawAll();
			OnDrawNone();
		}
	}

}


M_Polygon* CMIDAS_APP_SW_5_CLASSDGRView::findrect(CPoint point) {
	
	for (int i = 0; i < m_Brush->polygonList.size(); i++) {
		if (m_Brush->polygonList[i]->getType() == D_MODE_CLASSDIAGRAM) {
			CPoint startPos = m_Brush->polygonList[i]->getStartPoint();
			CPoint endPos = m_Brush->polygonList[i]->getEndPoint();
			CPoint tmp;
			if (startPos.x > endPos.x) {
				tmp = endPos;
				endPos.x = startPos.x;
				startPos.x = tmp.x;
			}
			if (startPos.y > endPos.y) {
				tmp = endPos;
				endPos.y = startPos.y;
				startPos.y = tmp.y;
			}

			CRect rect(startPos, endPos);

			if (rect.PtInRect(point)) {
				return m_Brush->polygonList[i];
			}
		}
	}
	return NULL;
}


void CMIDAS_APP_SW_5_CLASSDGRView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CView::OnRButtonDown(nFlags, point);

	if (m_Brush->polygonList.size() > 0) {
		m_CurSelectRect = findrect(point);
	}


	if (m_CurSelectRect != NULL) {
		CMenu popup;
		CMenu* pMenu;
		popup.LoadMenuW(IDR_MENU1);
		pMenu = popup.GetSubMenu(0);
		CPoint pos;
		GetCursorPos(&pos);
		pMenu->TrackPopupMenu(TPM_LEFTALIGN || TPM_RIGHTBUTTON, pos.x, pos.y, this);


	}
}

/*
툴바 도형 버튼 이벤트 처리기
*/

void CMIDAS_APP_SW_5_CLASSDGRView::OnDrawNone()
{
	M_Polygon* c = new M_Polygon();
	M_Polygon* mp = c;
	m_Brush->setDrawMode(D_MODE_NONE, mp);
}
void CMIDAS_APP_SW_5_CLASSDGRView::OnDrawLine()
{
	Line* c = new Line();
	M_Polygon* mp = c;
	m_Brush->setDrawMode(D_MODE_LINE, mp);
}

void CMIDAS_APP_SW_5_CLASSDGRView::OnDrawInheritaceLine(CPoint centerPoint){
	m_drawline = true;
	InheritanceLine* c = new InheritanceLine(centerPoint);
	M_Polygon* mp = c;
	m_Brush->setDrawMode(D_MODE_LINE_INHERITANCE, mp);
	//m_Brush->setPenMode(PS_SOLID);
	//printf("Inheritace draw mode on , (%d , %d)\n", centerPoint.x, centerPoint.y);
	//m_CurSelectRect->addConnectedPoint(&(c->startPoint));
}

void CMIDAS_APP_SW_5_CLASSDGRView::OnDrawDependencyLine(CPoint centerPoint){
	m_drawline = true;
	dependencyLine* c = new dependencyLine(centerPoint);
	M_Polygon* mp = c;
	m_Brush->setDrawMode(D_MODE_LINE_DEPENDENCY, mp);
	//m_Brush->setPenMode(PS_DOT);
	//printf("DOT!!!!!!!!");
}

void CMIDAS_APP_SW_5_CLASSDGRView::OnDrawRect()
{
	printf("OnDrawRect!\n");
	DiagramClass* c = new DiagramClass();
	M_Polygon* mp = c;
	m_Brush->setDrawMode(D_MODE_CLASSDIAGRAM, mp);
}


void CMIDAS_APP_SW_5_CLASSDGRView::OnEraseAll()
{
	// Erase All Screen
	while (m_Brush->polygonList.size() != 0)m_Brush->polygonList.pop_back();
	Invalidate();
}


void CMIDAS_APP_SW_5_CLASSDGRView::OnEraser()
{
	// Eraser mode

}


void CMIDAS_APP_SW_5_CLASSDGRView::OnRedo()
{
	m_Brush->Redo();
	//eraseInvalidate();
	Invalidate();
	UpdateWindow();
	m_Brush->ReDrawAll();
}


void CMIDAS_APP_SW_5_CLASSDGRView::OnUndo()
{
	m_Brush->Undo();
	//eraseInvalidate();
	Invalidate();
	UpdateWindow();
	m_Brush->ReDrawAll();
}


void CMIDAS_APP_SW_5_CLASSDGRView::OnAddClass()
{
	m_MakeClass = true;
	OnDrawRect();
}


// 메뉴에서 편집 > 새 클래스 추가 버튼 클릭시 발생 이벤트 함수
void CMIDAS_APP_SW_5_CLASSDGRView::OnAddNewClassOnMenu()
{
	DiagramClass* dc;
	OnDrawRect();
	m_Brush->addPolygon(new DiagramClass(CPoint(0,0),CPoint(100,100)));
	dc = (DiagramClass *)m_Brush->getResentPolygon();
	dc->setContents();
	if (dc->isClassContentsEmpty()) {
		m_Brush->deletePolygon();
	}
	Invalidate();
	UpdateWindow();
	m_Brush->ReDrawAll();
	
	
}



void CMIDAS_APP_SW_5_CLASSDGRView::OnMenuProperties()
{
	// TODO: Add your command handler code here
	
	if (m_CurSelectRect != NULL) {
		m_CurSelectRect->setContents();
//DELETE Dummy 생성
		if (((DiagramClass *)m_CurSelectRect)->isClassContentsEmpty()) {
			Dummy* dummy = new Dummy(m_CurSelectRect);
			m_Brush->polygonList.push_back(dummy);
		}
		Invalidate();
		UpdateWindow();
		m_Brush->ReDrawAll();
	}
}


void CMIDAS_APP_SW_5_CLASSDGRView::OnMenuInheritance()
{
	// TODO: Add your command handler code here
	CPoint start_point = m_CurSelectRect->getStartPoint();
	CPoint end_point = m_CurSelectRect->getEndPoint();
	CPoint center_point;
	center_point.x = (start_point.x+end_point.x)/2;
	center_point.y = (start_point.y + end_point.y) / 2;
	OnDrawInheritaceLine(center_point); // 상속 선 설정
}

void CMIDAS_APP_SW_5_CLASSDGRView::OnMenuDependency()
{
	// TODO: Add your command handler code here
	CPoint start_point = m_CurSelectRect->getStartPoint();
	CPoint end_point = m_CurSelectRect->getEndPoint();
	CPoint center_point;
	center_point.x = (start_point.x + end_point.x) / 2;
	center_point.y = (start_point.y + end_point.y) / 2;
	OnDrawDependencyLine(center_point); // 상속 선 설정

}

void CMIDAS_APP_SW_5_CLASSDGRView::OnMenuDelete()
{
	// TODO: Add your command handler code here
	if (m_CurSelectRect != NULL) {
//DELETE Dummy 생성
		Dummy* dummy = new Dummy(m_CurSelectRect);
		m_Brush->polygonList.push_back(dummy);
		Invalidate();
		UpdateWindow();
		m_Brush->ReDrawAll();
	}
}





void CMIDAS_APP_SW_5_CLASSDGRView::OnMoveClass()
{
	OnDrawRect();
}


void CMIDAS_APP_SW_5_CLASSDGRView::OnIddRedoClass()
{
}


void CMIDAS_APP_SW_5_CLASSDGRView::OnIddUndoClass()
{
}
