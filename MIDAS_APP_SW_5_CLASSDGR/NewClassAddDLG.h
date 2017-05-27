#pragma once
#include "afxwin.h"
#include <vector>

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
	CString className; // �߰��ϰ��� �ϴ� Ŭ���� �̸�
	std::vector<CString> attbList; // �Ӽ� ����Ʈ�� ���� �Ӽ� ����
	std::vector<CString> prmtList; // �Ű����� ����Ʈ�� ���� ����
	std::vector<CString> operationList; // ���۷��̼� ����Ʈ�� ���� ����

	DECLARE_MESSAGE_MAP()
public:
	CString getClassName() { return className; }
	CString getAttrbute(int i) { return attbList[i]; }
	int getAttrbuteSize() { return attbList.size(); }
	CString getOperation(int i) { return operationList[i]; }
	int getOperationSize() { return operationList.size(); }
	// Ŭ���� �̸��� �Է� �޴� EditBox ��ü
	CEdit AddNewClass_classNameEdit;
	

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
	afx_msg void OnBnClickedAddNewClassOpOk();
	afx_msg void OnBnClickedAddNewClassOpCancel();
	CListBox m_AddNewOpList;
	afx_msg void OnBnClickedAddNewClassCancel();
	afx_msg void OnBnClickedAddNewClassOk();
};
