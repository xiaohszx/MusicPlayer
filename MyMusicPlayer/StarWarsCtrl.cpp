/****************************************************************/
/*																*/
/*  StarWarsCtrl.cpp											*/
/*																*/
/*  Implementation of the CStarWarsCtrl.cpp class.				*/
/*																*/
/*  Programmed by Pablo van der Meer							*/
/*  Copyright Pablo Software Solutions 2002						*/
/*	http://www.pablovandermeer.nl								*/
/*																*/
/*  Last updated: 10 july 2002									*/
/*																*/
/****************************************************************/


#include "stdafx.h"
#include "resource.h"
#include "StarWarsCtrl.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define getrandom(min,max) ((rand()%(int)(((max)+1)-(min)))+(min));


CStarWarsCtrl::CStarWarsCtrl()
{
	// protected bitmaps to restore the memory DC's
	m_pOldBitmap = NULL;

	m_Font.CreateFont(30, 0, 0, 0, FW_BOLD,
                       FALSE, FALSE, 0, ANSI_CHARSET,
                       OUT_DEFAULT_PRECIS, 
                       CLIP_DEFAULT_PRECIS,
                       DEFAULT_QUALITY, 
                       DEFAULT_PITCH|FF_SWISS, _T("华文行楷"));
	m_nScrollSpeed = 8;
	m_nStarsSpeed = 20;
}

CStarWarsCtrl::~CStarWarsCtrl()
{
	if (m_pOldBitmap != NULL)
		m_MainDC.SelectObject(m_pOldBitmap);  
}


BEGIN_MESSAGE_MAP(CStarWarsCtrl, CStatic)
	//{{AFX_MSG_MAP(CStarWarsCtrl)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/********************************************************************/
/*																	*/
/* Function name : PreSubclassWindow								*/
/* Description   : Initialize some stuff							*/
/*																	*/
/********************************************************************/
void CStarWarsCtrl::PreSubclassWindow() 
{
	CClientDC dc(this);

	GetClientRect(m_rectClient);
/*[00:15.58]
[00:24.88]寻不到花的折翼枯叶蝶
[00:29.47]永远也看不见凋谢
[00:35.76]江南夜色下的小桥屋檐
[00:42.43]读不懂塞北的荒野
[00:45.43]
[00:49.09]梅开时节因寂寞而缠绵
[00:54.15]春归后又很快湮灭
[01:00.87]独留我赏烟花飞满天
[01:06.26]摇曳后就随风飘远
[01:10.26]
[01:13.53]断桥是否下过雪
[01:16.11]我望着湖面
[01:18.86]水中寒月如雪
[01:21.92]指尖轻点融解
[01:24.92]
[01:25.12]断桥是否下过雪
[01:27.89]又想起你的脸
[01:30.90]若是无缘再见
[01:34.09]白堤柳帘垂泪好几遍
[01:41.93]
[01:42.93]
[02:02.87]
[02:03.87]寻不到花的折翼枯叶蝶
[02:09.77]永远也看不见凋谢
[02:15.40]江南夜色下的小桥屋檐
[02:21.32]读不懂塞北的荒野
[02:27.16]
[02:27.96]梅开时节因寂寞而缠绵
[02:33.43]春归后又很快湮灭
[02:39.28]独留我赏烟花飞满天
[02:44.88]摇曳后就随风飘远
[02:50.06]
[02:52.07]断桥是否下过雪
[02:54.97]我望着湖面
[02:57.85]水中寒月如雪
[03:01.05]指尖轻点融解
[03:03.91]
[03:04.26]断桥是否下过雪
[03:07.76]又想起你的脸
[03:09.84]若是无缘再见
[03:12.97]白堤柳帘垂泪好几遍
[03:18.94]
[03:19.94]本歌词由网友忍者提供
�
*/
	// initialize stars
	for (int i = 0; i < NUM_STARS; i++)
	{
		m_StarArray[i].x = getrandom(0, 1024);
		m_StarArray[i].x -= 512;
		m_StarArray[i].y = getrandom(0, 1024);
		m_StarArray[i].y -= 512;
		m_StarArray[i].z = getrandom(0, 512);
		m_StarArray[i].z -= 256;
	}

	m_TextLines.Add(_T("寻不到花的折翼枯叶蝶"));
	m_TextLines.Add(_T(""));
	m_TextLines.Add(_T("永远也看不见凋谢"));
	m_TextLines.Add(_T(""));
	m_TextLines.Add(_T("江南夜色下的小桥屋檐 "));
	m_TextLines.Add(_T(""));
	m_TextLines.Add(_T("读不懂塞北的荒野"));
	m_TextLines.Add(_T(""));
	m_TextLines.Add(_T("梅开时节因寂寞而缠绵"));
	m_TextLines.Add(_T(""));


	m_TextLines.Add(_T("春归后又很快湮灭"));
	m_TextLines.Add(_T(""));
	m_TextLines.Add(_T("独留我赏烟花飞满天"));
	m_TextLines.Add(_T(""));
	m_TextLines.Add(_T("摇曳后就随风飘远"));
	m_TextLines.Add(_T(""));
	m_TextLines.Add(_T("断桥是否下过雪"));
	m_TextLines.Add(_T(""));
	m_TextLines.Add(_T("我望着湖面"));
	m_TextLines.Add(_T(""));
	m_TextLines.Add(_T("水中寒月如雪"));
	m_TextLines.Add(_T(""));
	m_TextLines.Add(_T("指尖轻点融解"));
	m_TextLines.Add(_T(""));
	m_TextLines.Add(_T("断桥是否下过雪 "));
	m_TextLines.Add(_T(""));
	m_TextLines.Add(_T("又想起你的脸 "));
	m_TextLines.Add(_T(""));
	m_TextLines.Add(_T("若是无缘再见 "));
	m_TextLines.Add(_T(""));
	m_TextLines.Add(_T("白堤柳帘垂泪好几遍"));
	m_TextLines.Add(_T(""));
	m_TextLines.Add(_T("许嵩-《断桥残雪》"));
	m_TextLines.Add(_T(""));
	m_TextLines.Add(_T("Jelin 最爱"));
	m_TextLines.Add(_T(""));
	m_TextLines.Add(_T("e-mail:Jelinyao@163.com"));

	m_nScrollPos = m_rectClient.Height();

	// calculate speed so that it scrolls the same speed on a different machine
	DWORD t1 = GetTickCount();
	InvalidateCtrl();
	DWORD t2 = GetTickCount();

	t2 -= t1; // = 50 on my system

	m_nScrollSpeed = (m_nScrollSpeed * t2)/50;

	SetTimer(1, 75, NULL);

	CStatic::PreSubclassWindow();
}


/********************************************************************/
/*																	*/
/* Function name : OnPaint											*/
/* Description   : Called when the application makes a request to	*/
/*				   repaint a portion of the window.					*/
/*																	*/
/********************************************************************/
void CStarWarsCtrl::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CDC memDC;
	CBitmap memBitmap;
	CBitmap* oldBitmap;

	// to avoid flicker, establish a memory dc, draw to it 
	// and then BitBlt it to the client
	memDC.CreateCompatibleDC(&dc);
	memBitmap.CreateCompatibleBitmap(&dc, m_rectClient.Width(), m_rectClient.Height());
	oldBitmap = (CBitmap *)memDC.SelectObject(&memBitmap);

	if (memDC.GetSafeHdc() != NULL)
	{
		// first drop the bitmap on the memory dc
		memDC.BitBlt(0, 0, m_rectClient.Width(), m_rectClient.Height(), &m_MainDC, 0, 0, SRCCOPY);
		// finally send the result to the display
		dc.BitBlt(0, 0, m_rectClient.Width(), m_rectClient.Height(), &memDC, 0, 0, SRCCOPY);
	}
	memDC.SelectObject(oldBitmap);
}


/********************************************************************/
/*																	*/
/* Function name : OnSize											*/
/* Description   : The framework calls this member function after	*/
/*				   the window抯 size has changed.					*/
/*																	*/
/********************************************************************/
void CStarWarsCtrl::OnSize(UINT nType, int cx, int cy) 
{
	CStatic::OnSize(nType, cx, cy);
	
	// OnSize automatically gets called during the setup of the control
	GetClientRect(m_rectClient);

	// destroy and recreate the main bitmap
	CClientDC dc(this);
	if (m_pOldBitmap && m_MainBitmap.GetSafeHandle() && m_MainDC.GetSafeHdc())
	{
		m_MainDC.SelectObject(m_pOldBitmap);
		m_MainBitmap.DeleteObject();
		m_MainBitmap.CreateCompatibleBitmap(&dc, m_rectClient.Width(), m_rectClient.Height());
		m_pOldBitmap = m_MainDC.SelectObject(&m_MainBitmap);
	}
}


/********************************************************************/
/*																	*/
/* Function name : DoStars											*/
/* Description   : Draw stars										*/
/*																	*/
/********************************************************************/
void CStarWarsCtrl::DoStars(CDC *pDC)
{
	m_MainDC.SetBkColor(RGB(0,0,0));
	m_MainDC.SetTextColor(RGB(255,255,255));
	m_MainDC.FillSolidRect(m_rectClient, RGB(0,0,0));

	int nFunFactor = 100;
	int x, y, z;
	for(int i = 0; i < NUM_STARS; i++)
	{
        m_StarArray[i].z = m_StarArray[i].z - m_nStarsSpeed;
        if (m_StarArray[i].z > 255)
		{
			m_StarArray[i].z = -255;
		}
        if (m_StarArray[i].z < -255)
		{
			m_StarArray[i].z = 255;
		}
        
		z = m_StarArray[i].z + 256;
        x = (m_StarArray[i].x * nFunFactor / z) + (m_rectClient.Width() / 2);
        y = (m_StarArray[i].y * nFunFactor / z) + (m_rectClient.Height() / 2);
		
		CPen myPen;

		// create a white pen which luminosity depends on the z position (for 3D effect!)
		int nColor = 255 - m_StarArray[i].z;
		myPen.CreatePen(PS_COSMETIC, 1, RGB(nColor,nColor,nColor));

		CPen *pOldPen = (CPen *)m_MainDC.SelectObject(&myPen);
		// draw star
		m_MainDC.Ellipse(CRect(x, y, x+3, y+3));
		m_MainDC.SelectObject(pOldPen);
    }
}


/********************************************************************/
/*																	*/
/* Function name : InvalidateCtrl									*/
/* Description   : Draw the Matrix to a bitmap.						*/
/*																	*/
/********************************************************************/
void CStarWarsCtrl::InvalidateCtrl()
{
	// in case we haven't established the memory dc's
	CClientDC dc(this);

	// if we don't have one yet, set up a memory dc for the control 
	if (m_MainDC.GetSafeHdc() == NULL)
	{
		m_MainDC.CreateCompatibleDC(&dc);
		m_MainBitmap.CreateCompatibleBitmap(&dc, m_rectClient.Width(), m_rectClient.Height());
		m_pOldBitmap = m_MainDC.SelectObject(&m_MainBitmap);
	}
  
	DoStars(&dc);	
	DoScrollText(&dc);

	// finally, force redraw
	InvalidateRect(m_rectClient);
} 


/********************************************************************/
/*																	*/
/* Function name : OnTimer											*/
/* Description   : Update display									*/
/*																	*/
/********************************************************************/
void CStarWarsCtrl::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent == 1)
		InvalidateCtrl();

	CStatic::OnTimer(nIDEvent);
}


/********************************************************************/
/*																	*/
/* Function name : DoScrollText										*/
/* Description   : Do scrolling text like in the movie 'Star Wars'	*/
/*																	*/
/********************************************************************/
void CStarWarsCtrl::DoScrollText(CDC *pDC)
{
	int nPosX =0;
	int nPosY =0;

	CDC memDC;
	CBitmap memBitmap;
	CFont *oldFont;

	memDC.CreateCompatibleDC(pDC);
	memBitmap.CreateCompatibleBitmap(pDC, m_rectClient.Width(), m_rectClient.Height());
	memDC.SelectObject(&memBitmap);
	memDC.SetBkColor(RGB(0,0,0));
	memDC.SetTextColor(RGB(0,255,0));
    memDC.SetBkMode(TRANSPARENT);

	oldFont = memDC.SelectObject(&m_Font);

	// black
	memDC.BitBlt(0, 0, m_rectClient.Width(), m_rectClient.Height(), NULL, 0, 0, BLACKNESS);
	
	// draw Credits on the hidden Picture
	for(int i=0; i < m_TextLines.GetSize(); i++)
	{
		// set position for this line
		CSize size = memDC.GetTextExtent(m_TextLines.GetAt(i));

		nPosY = m_nScrollPos + (i * size.cy);
		if (nPosY > 0)
		{
			nPosX = (m_rectClient.Width() / 2) - (size.cx / 2);

			if (nPosY >100)
			{
				memDC.SetTextColor(RGB(150, 0, 200));
			}
			else
			{
				// set fade color
				memDC.SetTextColor(RGB(nPosY, nPosY, nPosY));
			}
			
			
			// print text
			memDC.TextOut(nPosX, nPosY, m_TextLines.GetAt(i));
		}
		else
		{
			// start all over ...
			if (i == (m_TextLines.GetSize()-1))
			{
				m_nScrollPos = m_rectClient.Height();
			}
		}
	}

	int nWidth = m_rectClient.Width();
	int nHeight = m_rectClient.Height();

	// shrink text from bottom to top to create Star Wars effect
	for (int y=0; y <nHeight; y++)
	{
		double nScale = (double)y/(double)nHeight;
		int nOffset = (int)(nWidth - nWidth*nScale)/2;
		m_MainDC.StretchBlt(nOffset, y, (int)(nWidth*nScale), 1, &memDC, 0, y, nWidth, 1, SRCPAINT);
	}

	// restore the font
	memDC.SelectObject(oldFont);

	// move text up one pixel
	m_nScrollPos = m_nScrollPos - m_nScrollSpeed;
}


/********************************************************************/
/*																	*/
/* Function name : SetScrollSpeed									*/
/* Description   : Set speed of scrolling							*/
/*																	*/
/********************************************************************/
void CStarWarsCtrl::SetScrollSpeed(int nSpeed)
{
	m_nScrollSpeed = nSpeed;
}


/********************************************************************/
/*																	*/
/* Function name : SetStarSpeed										*/
/* Description   : Set speed of the stars							*/
/*																	*/
/********************************************************************/
void CStarWarsCtrl::SetStarSpeed(int nSpeed)
{
	m_nStarsSpeed = nSpeed;
}


/********************************************************************/
/*																	*/
/* Function name : UpdateVersionInformation							*/
/* Description   : Show version information from resource.			*/
/*																	*/
/********************************************************************/
/*CString CStarWarsCtrl::GetVersionInformation(LPCTSTR lpszModuleName)
{
/*	CString strResult;
	BYTE		*pDataBlock = NULL;
	DWORD FAR	*translation;
	DWORD FAR	*buffer;     
	DWORD		dwHandle;
	UINT		nBytes;
	
	// WinAPI wants non-const arguments
	LPTSTR lpszExeName = const_cast<LPTSTR>(lpszModuleName); 

	char szName[512];       // StringFileInfo data block.

	// Get the actual size of the information block.
	nBytes = (UINT)GetFileVersionInfoSize(lpszExeName, &dwHandle);

	if (nBytes)
	{
		pDataBlock = new BYTE[nBytes];

		// Get the actual block for the version information
		if (GetFileVersionInfo(lpszExeName, dwHandle, nBytes, pDataBlock))
		{
			if (VerQueryValue(pDataBlock, _T("\\VarFileInfo\\Translation"), (VOID FAR * FAR *)&translation, (UINT FAR *)&nBytes)) 
			{
				// The File Version for this application
				wsprintf(szName, _T("\\StringFileInfo\\%04x%04x\\PrivateBuild"), LOWORD(*translation), HIWORD(*translation));

				if (VerQueryValue(pDataBlock, szName, (VOID FAR * FAR *)&buffer, (UINT FAR *)&nBytes)) 
				{
					strResult.Format((char far *)buffer);
				}
			}
			else 
			{
				// sorry ...
			}
		}
		if (pDataBlock)
			delete[] pDataBlock;
	}
	return strResult;
}*/


/********************************************************************/
/*																	*/
/* Function name : OnLButtonDown									*/
/* Description   : Go to our website...								*/
/*																	*/
/********************************************************************/
void CStarWarsCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
    // open URL in the browser.

	CStatic::OnLButtonDown(nFlags, point);
}
