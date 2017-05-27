
// MIDAS_APP_SW_5_CLASSDGRView.cpp : CMIDAS_APP_SW_5_CLASSDGRView Ŭ������ ����
//

#include "stdafx.h"
#include <iostream>
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "MIDAS_APP_SW_5_CLASSDGR.h"
#endif

#include "MIDAS_APP_SW_5_CLASSDGRDoc.h"
#include "MIDAS_APP_SW_5_CLASSDGRView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// printf �Լ��� Ȱ���ؼ� ǥ�� ��� ����� �ֿܼ� ��� �ϱ� ���� �߰��� �ڵ�
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console") 

// CMIDAS_APP_SW_5_CLASSDGRView

IMPLEMENT_DYNCREATE(CMIDAS_APP_SW_5_CLASSDGRView, CView)

BEGIN_MESSAGE_MAP(CMIDAS_APP_SW_5_CLASSDGRView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_ADD_CLASS, &CMIDAS_APP_SW_5_CLASSDGRView::OnAddClass)
END_MESSAGE_MAP()

// CMIDAS_APP_SW_5_CLASSDGRView ����/�Ҹ�

CMIDAS_APP_SW_5_CLASSDGRView::CMIDAS_APP_SW_5_CLASSDGRView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	m_Brush = new Brushs();
	m_Brush->setBrushWnd(this);
	m_StartToMove = false;
	m_CurSelectRect = false;
}

CMIDAS_APP_SW_5_CLASSDGRView::~CMIDAS_APP_SW_5_CLASSDGRView()
{
}

BOOL CMIDAS_APP_SW_5_CLASSDGRView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CMIDAS_APP_SW_5_CLASSDGRView �׸���

void CMIDAS_APP_SW_5_CLASSDGRView::OnDraw(CDC* /*pDC*/)
{

	CDC* pDC2 = GetDC(); // Brush ������ �ѱ�� CDC��ü�� ���� ���;� �Ѵ�.(�ش� �Լ� �Ű����� CDC�� �Ҹ��)
	m_Brush->setCDC(pDC2);

	CMIDAS_APP_SW_5_CLASSDGRDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.

	
}


// CMIDAS_APP_SW_5_CLASSDGRView �μ�

BOOL CMIDAS_APP_SW_5_CLASSDGRView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CMIDAS_APP_SW_5_CLASSDGRView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CMIDAS_APP_SW_5_CLASSDGRView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CMIDAS_APP_SW_5_CLASSDGRView ����

#ifdef _DEBUG
void CMIDAS_APP_SW_5_CLASSDGRView::AssertValid() const
{
	CView::AssertValid();
}

void CMIDAS_APP_SW_5_CLASSDGRView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMIDAS_APP_SW_5_CLASSDGRDoc* CMIDAS_APP_SW_5_CLASSDGRView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{	

	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMIDAS_APP_SW_5_CLASSDGRDoc)));
	return (CMIDAS_APP_SW_5_CLASSDGRDoc*)m_pDocument;
}
#endif //_DEBUG


// CMIDAS_APP_SW_5_CLASSDGRView �޽��� ó����


void CMIDAS_APP_SW_5_CLASSDGRView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	
	CView::OnMouseMove(nFlags, point);

//�簢�� Ŭ���� �����̱�
	if (m_StartToMove) {
		m_EndPos = point;
		CPoint pos = m_EndPos - m_StartPos;
		m_StartPos = point;
		m_CurSelectRect->setStartPoint(m_CurSelectRect->getStartPoint() + pos);
		m_CurSelectRect->setEndPoint(m_CurSelectRect->getEndPoint() + pos);

		m_Brush->Draw(point, nFlags, L_MOUSE_UP);
		Invalidate();
		UpdateWindow();
		m_Brush->ReDrawAll();
	}
//����ȭ�� Ŭ���� �׸���
	else if (m_Brush->Draw(point, nFlags, MOUSE_MOVE)) {
		Invalidate();
		UpdateWindow();
		m_Brush->ReDrawAll();
	}
}


void CMIDAS_APP_SW_5_CLASSDGRView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CView::OnLButtonUp(nFlags, point);

	if (m_StartToMove == true) {
		m_EndPos = point;
		m_StartToMove = false;
	}
	m_Brush->Draw(point, nFlags, L_MOUSE_UP);
}


void CMIDAS_APP_SW_5_CLASSDGRView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	
	CView::OnLButtonDown(nFlags, point);

	if (m_Brush->polygonList.size() > 0) {
		m_CurSelectRect = findrect(point);
	}

	//�簢�� Ŭ���� �����̱� �غ�
	if (m_CurSelectRect != NULL) {
		m_StartPos = point;
		m_StartToMove = true;
	}else{
	//����ȭ�� Ŭ���� �׸���(���߿� ������ �κ�)
		m_CurSelectRect = NULL;
		OnDrawRect();
		//OnDrawLine();
		m_Brush->Draw(point, nFlags, L_MOUSE_DOWN);

	}


	
}

M_Polygon* CMIDAS_APP_SW_5_CLASSDGRView::findrect(CPoint point) {
	
	for (int i = 0; i < m_Brush->polygonList.size(); i++) {
		if (m_Brush->polygonList[i]->getPolygonType() == 'C') {
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
/*
���� ���� ��ư �̺�Ʈ ó����
*/


void CMIDAS_APP_SW_5_CLASSDGRView::OnDrawLine()
{
	Line* c = new Line();
	M_Polygon* mp = c;
	m_Brush->setDrawMode(D_MODE_LINE, mp);
}


void CMIDAS_APP_SW_5_CLASSDGRView::OnDrawRect()
{
	DiagramClass* c = new DiagramClass();
	M_Polygon* mp = c;
	m_Brush->setDrawMode(D_MODE_RECT, mp);
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
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	OnDrawRect();
}
