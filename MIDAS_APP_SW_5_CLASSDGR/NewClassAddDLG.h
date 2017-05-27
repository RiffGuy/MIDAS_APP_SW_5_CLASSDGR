#pragma once
#include "afxwin.h"
#include <vector>

// NewClassAddDLG 대화 상자입니다.

class NewClassAddDLG : public CDialogEx
{
	DECLARE_DYNAMIC(NewClassAddDLG)

public:
	NewClassAddDLG(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~NewClassAddDLG();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADD_CLASS_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	CString className; // 추가하고자 하는 클래스 이름
	std::vector<CString> attbList; // 속성 리스트에 들어가는 속성 정보
	std::vector<CString> prmtList; // 매개변수 리스트에 들어가는 정보
	std::vector<CString> operationList; // 오퍼레이션 리스트에 들어가는 정보

	DECLARE_MESSAGE_MAP()
public:
	CString getClassName() { return className; }
	CString getAttrbute(int i) { return attbList[i]; }
	int getAttrbuteSize() { return attbList.size(); }
	CString getOperation(int i) { return operationList[i]; }
	int getOperationSize() { return operationList.size(); }
	// 클래스 이름을 입력 받는 EditBox 객체
	CEdit AddNewClass_classNameEdit;
	

	/************************ 속성 ************************/

	// 속성 - 범위 설정 콤보 박스
	CComboBox m_AttbRangeComboBox;
	
	// 속성 - 타입 입력 박스
	CEdit m_AddNewAttbType;

	// 속성 - 이름 입력 박스
	CEdit m_AddNewAttbName;

	// 속성 - 입력 완료 버튼 리스너
	afx_msg void OnBnClickedAddNewClassAttbOk();

	// 속성 - 추가된 속성 값을 표시해주는 리스트
	CListBox m_AddNewAttbList;
	
	// 속성 - 취소 버튼
	afx_msg void OnBnClickedAddNewClassAttbCancel();

	/************************오퍼레이션************************/

	// 오퍼레이션 - 리턴 타입 입력 박스
	CEdit m_AddNewOpRtType;

	// 오퍼레이션 - 범위 설정 콤보 박스
	CComboBox m_OperationRangeComboBox;

	// 오퍼레이션 - 추가하고자 하는 오퍼레이션의 이름
	CEdit m_AddNewOpName;

	// 오퍼레이션 - 매개변수 - 추가하고자 하는 매개변수의 타입
	CEdit m_AddNewPrmtType;

	// 오퍼레이션 - 매개변수 - 추가하고자 하는 매개변수의 이름
	//CEdit m_AddNewPrmtName;

	// 오퍼레이션 - 매개변수 - 입력 완료 버튼 객체 ( 사용? )
	CButton m_AddNewPrmtOK;

	// 오퍼레이션 - 매개변수 - 추가 버튼
	afx_msg void OnBnClickedAddNewClassPrmtOk();

	// 오퍼레이션 - 매개변수 - 삭제 버튼
	afx_msg void OnBnClickedAddNewClassPrmtCancel();

	// 오퍼레이션 - 매개변수 - 추가된 매개변수 리스트
	CListBox m_AddNewPrmtList;
	afx_msg void OnBnClickedAddNewClassOpOk();
	afx_msg void OnBnClickedAddNewClassOpCancel();
	CListBox m_AddNewOpList;
	afx_msg void OnBnClickedAddNewClassCancel();
	afx_msg void OnBnClickedAddNewClassOk();
};
