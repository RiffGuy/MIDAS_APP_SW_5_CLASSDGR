
// ChildFrm.cpp : CChildFrame Ŭ������ ����
//

#include "stdafx.h"
#include "MIDAS_APP_SW_5_CLASSDGR.h"
#include "MainFrm.h"

#include "ChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
	ON_COMMAND(ID_32781, &CChildFrame::OnPrint_BTM)
	ON_COMMAND(ID_FILE_SAVE, &CChildFrame::OnFileSave)
END_MESSAGE_MAP()

// CChildFrame ����/�Ҹ�

CChildFrame::CChildFrame()
{
	// TODO: ���⿡ ��� �ʱ�ȭ �ڵ带 �߰��մϴ�.
	printf("Child ����!\n");
}

CChildFrame::~CChildFrame()
{
}


BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡�� Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.
	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}

// CChildFrame ����

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}
#endif //_DEBUG

// CChildFrame �޽��� ó����





void CChildFrame::OnPrint_BTM()
{
	// TODO: Add your command handler code here
	CRect rec;
	HDC h_screen_dc = ::GetWindowDC(NULL);
	GetWindowRect(rec);
	int width = rec.Width() - 40;
	int height = rec.Height() - 90;
	// DIB�� ������ �����Ѵ�.
	BITMAPINFO dib_define;
	dib_define.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	dib_define.bmiHeader.biWidth = width;
	dib_define.bmiHeader.biHeight = height;
	dib_define.bmiHeader.biPlanes = 1;
	dib_define.bmiHeader.biBitCount = 24;
	dib_define.bmiHeader.biCompression = BI_RGB;
	dib_define.bmiHeader.biSizeImage = (((width * 24 + 31) & ~31) >> 3) * height;
	dib_define.bmiHeader.biXPelsPerMeter = rec.TopLeft().x;
	dib_define.bmiHeader.biYPelsPerMeter = rec.TopLeft().y;
	dib_define.bmiHeader.biClrImportant = 0;
	dib_define.bmiHeader.biClrUsed = 0;

	// DIB�� ���� �̹��� ��Ʈ ������ ������ ������ ����
	BYTE *p_image_data = NULL;

	// dib_define�� ���ǵ� �������� DIB�� �����Ѵ�.
	HBITMAP h_bitmap = ::CreateDIBSection(h_screen_dc, &dib_define, DIB_RGB_COLORS, (void **)&p_image_data, 0, 0);

	// �̹����� �����ϱ� ���ؼ� ���� DC�� �����Ѵ�. ���� DC������ ���������� ��Ʈ�ʿ� �����Ͽ�
	// �̹��� ������ ���� �� ���� �����̴�.
	HDC h_memory_dc = ::CreateCompatibleDC(h_screen_dc);

	// ���� DC�� �̹����� ������ ��Ʈ���� �����Ѵ�.
	HBITMAP h_old_bitmap = (HBITMAP)::SelectObject(h_memory_dc, h_bitmap);

	// ���� ��ũ�� ȭ���� ĸ���Ѵ�.
	Sleep(1000);
	::BitBlt(h_memory_dc, 0, 0, width, height, h_screen_dc, rec.TopLeft().x + 20, rec.TopLeft().y + 70, SRCCOPY);

	// ������ ��Ʈ������ �����Ѵ�.
	::SelectObject(h_memory_dc, h_old_bitmap);

	// ���� DC�� �����Ѵ�.
	DeleteDC(h_memory_dc);

	// DIB ������ ��� ������ �����Ѵ�.
	BITMAPFILEHEADER dib_format_layout;
	ZeroMemory(&dib_format_layout, sizeof(BITMAPFILEHEADER));
	dib_format_layout.bfType = *(WORD*)"BM";
	dib_format_layout.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dib_define.bmiHeader.biSizeImage;
	dib_format_layout.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	// DIB ������ �����Ѵ�.
	FILE *p_file = fopen("image.bmp", "wb");
	if (p_file != NULL) {
		printf("���ϻ���\n");
		fwrite(&dib_format_layout, 1, sizeof(BITMAPFILEHEADER), p_file);
		fwrite(&dib_define, 1, sizeof(BITMAPINFOHEADER), p_file);
		fwrite(p_image_data, 1, dib_define.bmiHeader.biSizeImage, p_file);
		fclose(p_file);
	}

	// ����ߴ� ��Ʈ�ʰ� DC �� �����Ѵ�.
	if (NULL != h_bitmap) DeleteObject(h_bitmap);
	if (NULL != h_screen_dc) ::ReleaseDC(NULL, h_screen_dc);
}


void CChildFrame::OnFileSave()
{
	
}
