
// ExamColorDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "ExamColor.h"
#include "ExamColorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CExamColorDlg 대화 상자



CExamColorDlg::CExamColorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_EXAMCOLOR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExamColorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CExamColorDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CExamColorDlg 메시지 처리기

BOOL CExamColorDlg::OnInitDialog()
{
	
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	HDC h_dc = ::GetWindowDC(NULL);
	int cx = ::GetSystemMetrics(SM_CXSCREEN);
	int cy = ::GetSystemMetrics(SM_CYSCREEN);
	int color_depth = ::GetDeviceCaps(h_dc, BITSPIXEL);

	m_image.Create(cx, cy, color_depth, 0);
	::BitBlt(m_image.GetDC(), 0, 0, cx, cy, h_dc, 0, 0, SRCCOPY);

	HBITMAP h_bmp = m_image;//m_image의 비트맵 핸들을 반환,
							//연산자 오버로딩이 되어있음
	unsigned int *p_data = new unsigned int[cx * cy];

	::GetBitmapBits(h_bmp, cx*cy*sizeof(unsigned int), p_data);
	//비트맵 핸들을 주고 비트맵 모든 정보를 가져옴
	//해당 비트맵만큼 메모리(폭*높이*4바이트)가 필요
	//p_data로 복사해온다

	COLORREF color;// color 한개에 대한 정보
	int r, g, b, avr;

	for (int y = 0; y < cy; y++) {
		for (int x = 0; x < cx; x++) {
			color = *(p_data + y*cx + x);//getpixel 대체, p_data로 복사해온다
			r = color & 0x000000FF;//리틀 엔디안 기준이기 때문에 역순
			g = (color & 0x0000FF00) >> 8;//00~FF 값만 가능
			b = (color & 0x00FF0000) >> 16;
			avr = (r + g + b) / 3;
			*(p_data + y*cx + x) = RGB(avr, avr, avr); 
			m_image.SetPixel(x, y, color);//색 바꿈
		}
	}

	//바꾼 데이터를 대입해준다
	::SetBitmapBits(h_bmp, cx * cy * sizeof(unsigned int), p_data);
	delete[] p_data;
	
	/*
	for (int y = 0; y < cy; y++) {
		for (int x = 0; x < cx; x++) {
			color = m_image.GetPixel(x, y);//원래 이미지 색 가져옴
			//r = GetRValue(color);
			r = color & 0x000000FF;//리틀 엔디안 기준이기 때문에 역순
			g = (color & 0x0000FF00) >> 8;//00~FF 값만 가능
			b = (color & 0x00FF0000) >> 16;
			avr = (r + g + b) / 3;
			color = RGB(avr, avr, avr);
			m_image.SetPixel(x, y, color);//색 바꿈
		}
	}*/

	::ReleaseDC(NULL, h_dc);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CExamColorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		m_image.Draw(dc, 0, 0);
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CExamColorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CExamColorDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
//	HDC h_dc=::GetDC(NULL);
	CClientDC dc(this);
	CString str;
	str = L"minji";
	//	dc.Rectangle(point.x, point.y, point.x, point.y);
	//	SetTextAlign(h_dc, TA_BOTTOM);
	//	TextOut(h_dc, point.x, point.y, str, sizeof(str));
	dc.TextOut(point.x, point.y, str);
	CDialogEx::OnLButtonDown(nFlags, point);
	
	CBrush black_brush(RGB(0, 0, 0));
	
	/* 클릭시 A를 찍음 */
	/* 
	CBrush *p_old_brush = dc.SelectObject(&black_brush);

	long height;
	long width;

	char A[8][8] =
	{
		{ 0,0,0,1,1,0,0,0 },
		{ 0,0,0,1,1,0,0,0 },
		{ 0,0,1,0,0,1,0,0 },
		{ 0,0,1,0,0,1,0,0 },
		{ 0,1,1,1,1,1,1,0 },
		{ 0,1,0,0,0,0,1,0 },
		{ 1,0,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,0,1 } 
	};
	
	char *word = A[0];

	for (int y = 0; y < 8; y++)
	{
		height = point.y + 4 * y;

		for (int x = 0; x < 8; x++)
		{
			width = point.x + 4 * x;
			if (*word++ == 1)
			{
				dc.Rectangle(width, height, width + 4, height + 4);

			}
		}
	}
	dc.SelectObject(p_old_brush);
	*/

}
