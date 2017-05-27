
// MIDAS_APP_SW_5_CLASSDGRView.h : CMIDAS_APP_SW_5_CLASSDGRView 클래스의 인터페이스
//

#pragma once
#include "Brushs.h"
#include "Line.h"
#include "DiagramClass.h"
#include "InheritanceLine.h"
#include "dependencyLine.h"
#include "Dummy.h"
class CMIDAS_APP_SW_5_CLASSDGRView : public CView
{
protected: // serialization에서만 만들어집니다.
	CMIDAS_APP_SW_5_CLASSDGRView();
	DECLARE_DYNCREATE(CMIDAS_APP_SW_5_CLASSDGRView)

// 특성입니다.
public:
	CMIDAS_APP_SW_5_CLASSDGRDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CMIDAS_APP_SW_5_CLASSDGRView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	//Brush
	Brushs* m_Brush;
	CPoint m_StartPos;
	CPoint m_EndPos;

	M_Polygon* m_CurSelectRect;
	M_Polygon* m_CurSelectRect_Temp;
	int m_CurSelectRectAt;
	bool m_StartToMove;
	bool m_SelectObject;
	bool m_MakeClass;
	bool m_drawline;
	bool invalidateFlag = false;
	M_Polygon* findrect(CPoint);
	M_Polygon* findLine(CPoint);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDrawRect();
	afx_msg void OnDrawLine();
	afx_msg void OnDrawNone();
	afx_msg void OnDrawInheritaceLine(CPoint centerPoint);
	afx_msg void OnDrawDependencyLine(CPoint centerPoint);
	afx_msg void OnEraseAll();
	afx_msg void OnEraser();
	afx_msg void OnRedo();
	afx_msg void OnUndo();
	afx_msg void OnAddClass();
	afx_msg void OnAddNewClassOnMenu();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMenuProperties();
	afx_msg void OnMenuInheritance();
	afx_msg void OnMenuDelete();
	afx_msg void OnMenuDependency();
	afx_msg void OnMoveClass();
	afx_msg void OnIddRedoClass();
	afx_msg void OnIddUndoClass();
	afx_msg void OnEditUndo();
	afx_msg void OnEditRedo();
	afx_msg void OnReconnect();
};

#ifndef _DEBUG  // MIDAS_APP_SW_5_CLASSDGRView.cpp의 디버그 버전
inline CMIDAS_APP_SW_5_CLASSDGRDoc* CMIDAS_APP_SW_5_CLASSDGRView::GetDocument() const
   { return reinterpret_cast<CMIDAS_APP_SW_5_CLASSDGRDoc*>(m_pDocument); }
#endif

