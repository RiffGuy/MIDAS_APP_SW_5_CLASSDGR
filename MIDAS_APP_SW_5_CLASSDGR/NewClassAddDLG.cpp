// NewClassAddDLG.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MIDAS_APP_SW_5_CLASSDGR.h"
#include "NewClassAddDLG.h"
#include "afxdialogex.h"


// NewClassAddDLG ��ȭ �����Դϴ�.

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


// NewClassAddDLG �޽��� ó�����Դϴ�.



void NewClassAddDLG::OnBnClickedAddNewClassAttbOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void NewClassAddDLG::OnBnClickedAddNewClassAttbCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void NewClassAddDLG::OnBnClickedAddNewClassPrmtOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void NewClassAddDLG::OnBnClickedAddNewClassPrmtCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}
