
// MIDAS_APP_SW_5_CLASSDGRView.cpp : CMIDAS_APP_SW_5_CLASSDGRView Ŭ������ ����
//

#include "stdafx.h"
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


// CMIDAS_APP_SW_5_CLASSDGRView

IMPLEMENT_DYNCREATE(CMIDAS_APP_SW_5_CLASSDGRView, CView)

BEGIN_MESSAGE_MAP(CMIDAS_APP_SW_5_CLASSDGRView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CMIDAS_APP_SW_5_CLASSDGRView ����/�Ҹ�

CMIDAS_APP_SW_5_CLASSDGRView::CMIDAS_APP_SW_5_CLASSDGRView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

	m_rect.SetRect(10, 10, 110, 110);
	m_StartToMove = false;
	m_rectSelect = false;

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


void CMIDAS_APP_SW_5_CLASSDGRView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	
	// Ŭ���� �簢�� ���� ��ư�� Ŭ���Ǿ� �ִ� ���

	// Ŭ���� �簢���� �����ȿ� �ִ� ��� -> �簢���� �����Ѵ� (8������ �׸� Ŭ�� ����)
	if (m_rect.PtInRect(point)) {
		m_StartPos = point;
		m_StartToMove = true;
	}
	// Ŭ���� �簢���� ���� ���

	SetCapture();

	CView::OnLButtonDown(nFlags, point);
}


void CMIDAS_APP_SW_5_CLASSDGRView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
					   // �׸��� �޽����� ���ؼ��� CView::OnPaint()��(��) ȣ������ ���ʽÿ�.

	dc.Rectangle(m_rect);
}


void CMIDAS_APP_SW_5_CLASSDGRView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

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
