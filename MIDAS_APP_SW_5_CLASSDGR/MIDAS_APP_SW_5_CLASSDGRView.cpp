
// MIDAS_APP_SW_5_CLASSDGRView.cpp : CMIDAS_APP_SW_5_CLASSDGRView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MIDAS_APP_SW_5_CLASSDGR.h"
#endif

#include "MIDAS_APP_SW_5_CLASSDGRDoc.h"
#include "MIDAS_APP_SW_5_CLASSDGRView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMIDAS_APP_SW_5_CLASSDGRView

IMPLEMENT_DYNCREATE(CMIDAS_APP_SW_5_CLASSDGRView, CView)

BEGIN_MESSAGE_MAP(CMIDAS_APP_SW_5_CLASSDGRView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CMIDAS_APP_SW_5_CLASSDGRView 생성/소멸

CMIDAS_APP_SW_5_CLASSDGRView::CMIDAS_APP_SW_5_CLASSDGRView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

	m_rect.SetRect(10, 10, 110, 110);
	m_StartToMove = false;
	m_rectSelect = false;

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
	CMIDAS_APP_SW_5_CLASSDGRDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
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


void CMIDAS_APP_SW_5_CLASSDGRView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	// 클릭시 사각형 생성 버튼이 클릭되어 있는 경우

	// 클릭시 사각형이 범위안에 있는 경우 -> 사각형을 선택한다 (8방위에 네모 클릭 생성)
	if (m_rect.PtInRect(point)) {
		m_StartPos = point;
		m_StartToMove = true;
	}
	// 클릭시 사각형이 없는 경우

	SetCapture();

	CView::OnLButtonDown(nFlags, point);
}


void CMIDAS_APP_SW_5_CLASSDGRView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CView::OnPaint()을(를) 호출하지 마십시오.

	dc.Rectangle(m_rect);
}


void CMIDAS_APP_SW_5_CLASSDGRView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (m_StartToMove) {
		m_EndPos = point;

		CPoint pos = m_EndPos - m_StartPos;

		m_StartPos = point;

		m_rect.SetRect(m_rect.TopLeft() + pos, m_rect.BottomRight() + pos);
		Invalidate();
	}
	CView::OnMouseMove(nFlags, point);
}


void CMIDAS_APP_SW_5_CLASSDGRView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (m_StartToMove == true) {
		m_EndPos = point;
		m_rectSelect = true;
		
		CRect point;
		CPaintDC dc(&m_rect);
		dc.Rectangle(m_rect);

		Invalidate();
	}

	ReleaseCapture();
	m_StartToMove = false;
	CView::OnLButtonUp(nFlags, point);
}
