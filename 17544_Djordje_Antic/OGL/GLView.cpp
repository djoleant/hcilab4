// GLView.cpp : implementation of the CGLView class
//

#include "stdafx.h"
#include "GL.h"

#include "GLDoc.h"
#include "GLView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGLView

IMPLEMENT_DYNCREATE(CGLView, CView)

BEGIN_MESSAGE_MAP(CGLView, CView)
	//{{AFX_MSG_MAP(CGLView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
	ON_WM_MOUSEHWHEEL()
	ON_WM_MOUSEHWHEEL()
	ON_WM_KEYDOWN()
	ON_WM_MOUSEACTIVATE()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGLView construction/destruction

CGLView::CGLView()
{
	// TODO: add construction code here

}

CGLView::~CGLView()
{
}

BOOL CGLView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CGLView drawing

void CGLView::OnDraw(CDC* pDC)
{
	CGLDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	m_glRenderer.DrawScene(pDC);
}

/////////////////////////////////////////////////////////////////////////////
// CGLView printing

BOOL CGLView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CGLView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CGLView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CGLView diagnostics

#ifdef _DEBUG
void CGLView::AssertValid() const
{
	CView::AssertValid();
}

void CGLView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGLDoc* CGLView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGLDoc)));
	return (CGLDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGLView message handlers

int CGLView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CDC* pDC = GetDC();
	m_glRenderer.CreateGLContext(pDC);
	ReleaseDC(pDC);
	
	return 0;
}

void CGLView::OnDestroy() 
{
	CView::OnDestroy();
	
	CDC* pDC = GetDC();
	m_glRenderer.DestroyScene(pDC);
	ReleaseDC(pDC);	
}

BOOL CGLView::OnEraseBkgnd(CDC* pDC) 
{
	return TRUE;
	
	//return CView::OnEraseBkgnd(pDC);
}

void CGLView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	CDC* pDC = GetDC();
	m_glRenderer.Reshape(pDC, cx, cy);
	ReleaseDC(pDC);
}

void CGLView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	CDC* pDC = GetDC();
	m_glRenderer.PrepareScene(pDC);
	ReleaseDC(pDC);
	
}


void CGLView::OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// This feature requires Windows Vista or greater.
	// The symbol _WIN32_WINNT must be >= 0x0600.
	// TODO: Add your message handler code here and/or call default
	if (zDelta > 0.0)
		m_glRenderer.m_z += 0.2;
	if (zDelta < 0.0)
		m_glRenderer.m_z -= 0.2;
	Invalidate();

	CView::OnMouseHWheel(nFlags, zDelta, pt);
}


void CGLView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default

	bool bShift = GetKeyState(VK_SHIFT) & 0x8000;
	if (nChar == VK_ADD)
		m_glRenderer.m_z += 0.2;
	if (nChar == VK_SUBTRACT)
		m_glRenderer.m_z -= 0.2;
	if(nChar == VK_RIGHT)
		if (bShift)
			m_glRenderer.m_Ry += 5.0;
		else
		m_glRenderer.m_x += 0.2;
	if (nChar == VK_LEFT)
		if (bShift)
			m_glRenderer.m_Ry -= 5.0;
		else
		m_glRenderer.m_x -= 0.2;
	if (nChar == VK_UP)
		if (bShift)
			m_glRenderer.m_Rx += 5.0;
		else
		m_glRenderer.m_y += 0.2;
	if (nChar == VK_DOWN)
		if (bShift)
			m_glRenderer.m_Rx -= 5.0;
		else
		m_glRenderer.m_y -= 0.2;
	Invalidate();

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}



void CGLView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CDC*pom = GetDC();
	m_glRenderer.PickObject(pom, point.x, point.y);

	CView::OnLButtonDown(nFlags, point);
}
