
// ExamColorDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "ExamColor.h"
#include "ExamColorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CExamColorDlg ��ȭ ����



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


// CExamColorDlg �޽��� ó����

BOOL CExamColorDlg::OnInitDialog()
{
	
	CDialogEx::OnInitDialog();

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	HDC h_dc = ::GetWindowDC(NULL);
	int cx = ::GetSystemMetrics(SM_CXSCREEN);
	int cy = ::GetSystemMetrics(SM_CYSCREEN);
	int color_depth = ::GetDeviceCaps(h_dc, BITSPIXEL);

	m_image.Create(cx, cy, color_depth, 0);
	::BitBlt(m_image.GetDC(), 0, 0, cx, cy, h_dc, 0, 0, SRCCOPY);

	HBITMAP h_bmp = m_image;//m_image�� ��Ʈ�� �ڵ��� ��ȯ,
							//������ �����ε��� �Ǿ�����
	unsigned int *p_data = new unsigned int[cx * cy];

	::GetBitmapBits(h_bmp, cx*cy*sizeof(unsigned int), p_data);
	//��Ʈ�� �ڵ��� �ְ� ��Ʈ�� ��� ������ ������
	//�ش� ��Ʈ�ʸ�ŭ �޸�(��*����*4����Ʈ)�� �ʿ�
	//p_data�� �����ؿ´�

	COLORREF color;// color �Ѱ��� ���� ����
	int r, g, b, avr;

	for (int y = 0; y < cy; y++) {
		for (int x = 0; x < cx; x++) {
			color = *(p_data + y*cx + x);//getpixel ��ü, p_data�� �����ؿ´�
			r = color & 0x000000FF;//��Ʋ ����� �����̱� ������ ����
			g = (color & 0x0000FF00) >> 8;//00~FF ���� ����
			b = (color & 0x00FF0000) >> 16;
			avr = (r + g + b) / 3;
			*(p_data + y*cx + x) = RGB(avr, avr, avr); 
			m_image.SetPixel(x, y, color);//�� �ٲ�
		}
	}

	//�ٲ� �����͸� �������ش�
	::SetBitmapBits(h_bmp, cx * cy * sizeof(unsigned int), p_data);
	delete[] p_data;
	
	/*
	for (int y = 0; y < cy; y++) {
		for (int x = 0; x < cx; x++) {
			color = m_image.GetPixel(x, y);//���� �̹��� �� ������
			//r = GetRValue(color);
			r = color & 0x000000FF;//��Ʋ ����� �����̱� ������ ����
			g = (color & 0x0000FF00) >> 8;//00~FF ���� ����
			b = (color & 0x00FF0000) >> 16;
			avr = (r + g + b) / 3;
			color = RGB(avr, avr, avr);
			m_image.SetPixel(x, y, color);//�� �ٲ�
		}
	}*/

	::ReleaseDC(NULL, h_dc);

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CExamColorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		m_image.Draw(dc, 0, 0);
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
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
	
	/* Ŭ���� A�� ���� */
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
