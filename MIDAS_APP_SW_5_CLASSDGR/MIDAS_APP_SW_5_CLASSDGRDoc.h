
// MIDAS_APP_SW_5_CLASSDGRDoc.h : CMIDAS_APP_SW_5_CLASSDGRDoc Ŭ������ �������̽�
//


#pragma once


class CMIDAS_APP_SW_5_CLASSDGRDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CMIDAS_APP_SW_5_CLASSDGRDoc();
	DECLARE_DYNCREATE(CMIDAS_APP_SW_5_CLASSDGRDoc)

// Ư���Դϴ�.
public:

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// �����Դϴ�.
public:
	virtual ~CMIDAS_APP_SW_5_CLASSDGRDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// �˻� ó���⿡ ���� �˻� �������� �����ϴ� ����� �Լ�
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
