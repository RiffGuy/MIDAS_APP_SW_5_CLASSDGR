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

BOOL NewClassAddDLG::OnInitDialog() {
	CDialogEx::OnInitDialog();
	printf("OninitDialog!\n");
	initData();
	return TRUE;
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
	DDX_Control(pDX, IDC_ADD_NEW_CLASS_OP_LIST, m_AddNewOpList);
}


BEGIN_MESSAGE_MAP(NewClassAddDLG, CDialogEx)
	
	ON_BN_CLICKED(ID_ADD_NEW_CLASS_ATTB_OK, &NewClassAddDLG::OnBnClickedAddNewClassAttbOk)
	ON_BN_CLICKED(ID_ADD_NEW_CLASS_ATTB_CANCEL, &NewClassAddDLG::OnBnClickedAddNewClassAttbCancel)
	ON_BN_CLICKED(ID_ADD_NEW_CLASS_PRMT_OK, &NewClassAddDLG::OnBnClickedAddNewClassPrmtOk)
	ON_BN_CLICKED(ID_ADD_NEW_CLASS_PRMT_CANCEL, &NewClassAddDLG::OnBnClickedAddNewClassPrmtCancel)
	ON_BN_CLICKED(ID_ADD_NEW_CLASS_OP_OK, &NewClassAddDLG::OnBnClickedAddNewClassOpOk)
	ON_BN_CLICKED(ID_ADD_NEW_CLASS_OP_CANCEL, &NewClassAddDLG::OnBnClickedAddNewClassOpCancel)
	ON_BN_CLICKED(ID_ADD_NEW_CLASS_CANCEL, &NewClassAddDLG::OnBnClickedAddNewClassCancel)
	ON_BN_CLICKED(ID_ADD_NEW_CLASS_OK, &NewClassAddDLG::OnBnClickedAddNewClassOk)
END_MESSAGE_MAP()


// NewClassAddDLG �޽��� ó�����Դϴ�.


// �Ӽ� �߰� �� ���� �Լ� 

void NewClassAddDLG::OnBnClickedAddNewClassAttbOk()
{
	CString attbName, attbType, attbRange;

	m_AttbRangeComboBox.GetLBText(m_AttbRangeComboBox.GetCurSel(), attbRange);
	m_AddNewAttbName.GetWindowTextW(attbName);
	m_AddNewAttbType.GetWindowTextW(attbType);
	
	CString attb = attbName + _T(" : ") + attbRange + " " + attbType + " " + attbName;
	
	// add to List
	m_AddNewAttbList.AddString(attb);

	// add to vector list
	attbList.push_back(attb);
	

}


void NewClassAddDLG::OnBnClickedAddNewClassAttbCancel()
{
	// remove from list
	int rmvIndex = m_AddNewAttbList.GetCurSel();
	if (rmvIndex >= 0) {
		m_AddNewAttbList.DeleteString(rmvIndex);
		attbList.erase(attbList.begin() + rmvIndex);
	}
}


// ���۷��̼� - �Ű����� �߰� �� ���� �Լ�
void NewClassAddDLG::OnBnClickedAddNewClassPrmtOk()
{
	CString prmtType;
	m_AddNewPrmtType.GetWindowTextW(prmtType);

	// add to List
	m_AddNewPrmtList.AddString(prmtType);

	// add to vector list
	prmtList.push_back(prmtType);
}


void NewClassAddDLG::OnBnClickedAddNewClassPrmtCancel()
{
	// remove from list
	int rmvIndex = m_AddNewPrmtList.GetCurSel();
	if (rmvIndex >= 0) {
		m_AddNewPrmtList.DeleteString(rmvIndex);
		prmtList.erase(prmtList.begin() + rmvIndex);
	}
}


// ���۷��̼� - �߰� �� ����

void NewClassAddDLG::OnBnClickedAddNewClassOpOk()
{
	CString opName, opType, opRange;
	m_AddNewOpRtType.GetWindowTextW(opType);
	m_AddNewOpName.GetWindowTextW(opName);
	m_OperationRangeComboBox.GetLBText(m_OperationRangeComboBox.GetCurSel(), opRange);

	CString operation = opName + "(";
	for (int i = 0; i < prmtList.size(); i++) {
		operation += prmtList[i];
		if (i + 1 != prmtList.size())operation += ",";
	}
	operation += ") : ";
	operation += opRange + " " + opType;

	m_AddNewOpList.AddString(operation);
	operationList.push_back(operation);
}


void NewClassAddDLG::OnBnClickedAddNewClassOpCancel()
{
	// remove from list
	int rmvIndex = m_AddNewOpList.GetCurSel();
	if (rmvIndex >= 0) {
		m_AddNewOpList.DeleteString(rmvIndex);
		operationList.erase(operationList.begin() + rmvIndex);
	}
}

// Ŭ���� �߰� ���� Ȯ�� �� ��� ��ư

void NewClassAddDLG::OnBnClickedAddNewClassCancel()
{
	className = "";
	while (attbList.size() != 0)attbList.pop_back();
	while (prmtList.size() != 0)prmtList.pop_back();
	while (operationList.size() != 0)operationList.pop_back();
	CDialogEx::OnCancel();
}


void NewClassAddDLG::OnBnClickedAddNewClassOk()
{
	AddNewClass_classNameEdit.GetWindowTextW(className);
	CDialogEx::OnOK();
}

void NewClassAddDLG::saveData(CArchive& ar) {
	printf("save Dialog !\n");
	if (ar.IsStoring()) {
		// save
		int attbSize = attbList.size();
		int prmtSize = prmtList.size();
		int operationSize = operationList.size();
		
		ar << attbSize;
		for (int i = 0; i < attbSize; i++) {
			ar << attbList[i];
		}

		ar << prmtSize;
		for (int i = 0; i < prmtSize; i++) {
			ar << prmtSize;
		}

		ar << operationSize;
		for (int i = 0; i < operationSize; i++) {
			ar << operationList[i];
		}

		ar << className;

	}
	else {
		// load

		int attbSize = 0;
		int prmtSize =0;
		int operationSize = 0;
		ar >> attbSize;
		for (int i = 0; i < attbSize; i++) {
			CString attb;
			ar >> attb;
			attbList.push_back(attb);
		}

		ar >> prmtSize;
		for (int i = 0; i < prmtSize; i++) {
			CString prmt;
			ar >> prmt;
			prmtList.push_back(prmt);
		}

		ar >> operationSize;
		for (int i = 0; i < operationSize; i++) {
			CString operation;
			ar >> operation;
			operationList.push_back(operation);
		}

		ar >> className;
	}
}

void NewClassAddDLG::initData() {
	int attbSize = attbList.size();
	int prmtSize = prmtList.size();
	int operationSize = operationList.size();
	printf("Size %d %d %d\n", attbSize, prmtSize, operationSize);
	for (int i = 0; i < attbSize; i++) {
		m_AddNewAttbList.AddString( attbList[i]);
	}

	
	for (int i = 0; i < prmtSize; i++) {
		m_AddNewPrmtList.AddString(prmtList[i]);
	}

	
	for (int i = 0; i < operationSize; i++) {
		m_AddNewOpList.AddString(operationList[i]);
	}

	AddNewClass_classNameEdit.SetWindowTextW(className);
}