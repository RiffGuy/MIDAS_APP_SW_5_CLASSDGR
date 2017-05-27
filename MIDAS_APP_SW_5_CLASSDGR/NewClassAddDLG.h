#pragma once
#include "afxwin.h"


// NewClassAddDLG ��ȭ �����Դϴ�.

class NewClassAddDLG : public CDialogEx
{
	DECLARE_DYNAMIC(NewClassAddDLG)

public:
	NewClassAddDLG(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~NewClassAddDLG();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADD_CLASS_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	// Ŭ���� �̸��� �Է� �޴� EditBox ��ü
	CEdit AddNewClass_classNameEdit;
	CString className;

	/************************ �Ӽ� ************************/

	// �Ӽ� - ���� ���� �޺� �ڽ�
	CComboBox m_AttbRangeComboBox;
	
	// �Ӽ� - Ÿ�� �Է� �ڽ�
	CEdit m_AddNewAttbType;

	// �Ӽ� - �̸� �Է� �ڽ�
	CEdit m_AddNewAttbName;

	// �Ӽ� - �Է� �Ϸ� ��ư ������
	afx_msg void OnBnClickedAddNewClassAttbOk();

	// �Ӽ� - �߰��� �Ӽ� ���� ǥ�����ִ� ����Ʈ
	CListBox m_AddNewAttbList;
	
	// �Ӽ� - ��� ��ư
	afx_msg void OnBnClickedAddNewClassAttbCancel();

	/************************���۷��̼�************************/

	// ���۷��̼� - ���� Ÿ�� �Է� �ڽ�
	CEdit m_AddNewOpRtType;

	// ���۷��̼� - ���� ���� �޺� �ڽ�
	CComboBox m_OperationRangeComboBox;

	// ���۷��̼� - �߰��ϰ��� �ϴ� ���۷��̼��� �̸�
	CEdit m_AddNewOpName;

	// ���۷��̼� - �Ű����� - �߰��ϰ��� �ϴ� �Ű������� Ÿ��
	CEdit m_AddNewPrmtType;

	// ���۷��̼� - �Ű����� - �߰��ϰ��� �ϴ� �Ű������� �̸�
	//CEdit m_AddNewPrmtName;

	// ���۷��̼� - �Ű����� - �Է� �Ϸ� ��ư ��ü ( ���? )
	CButton m_AddNewPrmtOK;

	// ���۷��̼� - �Ű����� - �߰� ��ư
	afx_msg void OnBnClickedAddNewClassPrmtOk();

	// ���۷��̼� - �Ű����� - ���� ��ư
	afx_msg void OnBnClickedAddNewClassPrmtCancel();

	// ���۷��̼� - �Ű����� - �߰��� �Ű����� ����Ʈ
	CListBox m_AddNewPrmtList;
};
