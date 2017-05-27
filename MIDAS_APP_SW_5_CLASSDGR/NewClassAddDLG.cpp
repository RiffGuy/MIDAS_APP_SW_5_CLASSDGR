// NewClassAddDLG.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MIDAS_APP_SW_5_CLASSDGR.h"
#include "NewClassAddDLG.h"
#include "afxdialogex.h"


// NewClassAddDLG 대화 상자입니다.

IMPLEMENT_DYNAMIC(NewClassAddDLG, CDialogEx)

NewClassAddDLG::NewClassAddDLG(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ADD_CLASS_DLG, pParent)
{
	
}

NewClassAddDLG::~NewClassAddDLG()
{
}

void NewClassAddDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ADD_NEW_CLASS_CLASS_NAME, AddNewClass_classNameEdit);
	DDX_Control(pDX, IDC_ADD_NEW_CLASS_ATTB_RANGE, m_AttbRangeComboBox);
	DDX_Control(pDX, IDC_ADD_NEW_CLASS_OP_RANGE, m_OperationRangeComboBox);

	m_AttbRangeComboBox.AddString(_T("public"));
	m_AttbRangeComboBox.AddString(_T("protected"));
	m_AttbRangeComboBox.AddString(_T("private"));
	m_AttbRangeComboBox.SetCurSel(0);
	m_OperationRangeComboBox.AddString(_T("public"));
	m_OperationRangeComboBox.AddString(_T("protected"));
	m_OperationRangeComboBox.AddString(_T("private"));
	m_OperationRangeComboBox.SetCurSel(0);
	DDX_Control(pDX, IDC_ADD_NEW_CLASS_ATTB_TYPE, m_AddNewAttbType);
	DDX_Control(pDX, IDC_ADD_NEW_CLASS_ATTB_NAME, m_AddNewAttbName);
	DDX_Control(pDX, IDC_ADD_NEW_CLASS_ATTB_LIST, m_AddNewAttbList);
	DDX_Control(pDX, IDC_ADD_NEW_CLASS_RET_TYPE, m_AddNewOpRtType);
	DDX_Control(pDX, IDC_ADD_NEW_CLASS_OP_NAME, m_AddNewOpName);
	DDX_Control(pDX, IDC_ADD_NEW_CLASS_PRMT_TYPE, m_AddNewPrmtType);
	DDX_Control(pDX, ID_ADD_NEW_CLASS_PRMT_OK, m_AddNewPrmtOK);
	DDX_Control(pDX, IDC_ADD_NEW_CLASS_PRMT_LIST, m_AddNewPrmtList);
}


BEGIN_MESSAGE_MAP(NewClassAddDLG, CDialogEx)
	
	ON_BN_CLICKED(ID_ADD_NEW_CLASS_ATTB_OK, &NewClassAddDLG::OnBnClickedAddNewClassAttbOk)
	ON_BN_CLICKED(ID_ADD_NEW_CLASS_ATTB_CANCEL, &NewClassAddDLG::OnBnClickedAddNewClassAttbCancel)
	ON_BN_CLICKED(ID_ADD_NEW_CLASS_PRMT_OK, &NewClassAddDLG::OnBnClickedAddNewClassPrmtOk)
	ON_BN_CLICKED(ID_ADD_NEW_CLASS_PRMT_CANCEL, &NewClassAddDLG::OnBnClickedAddNewClassPrmtCancel)
END_MESSAGE_MAP()


// NewClassAddDLG 메시지 처리기입니다.



void NewClassAddDLG::OnBnClickedAddNewClassAttbOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void NewClassAddDLG::OnBnClickedAddNewClassAttbCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void NewClassAddDLG::OnBnClickedAddNewClassPrmtOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void NewClassAddDLG::OnBnClickedAddNewClassPrmtCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
