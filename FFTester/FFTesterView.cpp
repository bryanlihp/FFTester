
// FFTesterView.cpp : implementation of the CFFTesterView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "FFTester.h"
#endif

#include "FFTesterDoc.h"
#include "FFTesterView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFFTesterView

IMPLEMENT_DYNCREATE(CFFTesterView, CView)

BEGIN_MESSAGE_MAP(CFFTesterView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CFFTesterView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CFFTesterView construction/destruction

CFFTesterView::CFFTesterView()
{
	// TODO: add construction code here

}

CFFTesterView::~CFFTesterView()
{
}

BOOL CFFTesterView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CFFTesterView drawing

void CFFTesterView::OnDraw(CDC* /*pDC*/)
{
	CFFTesterDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CFFTesterView printing


void CFFTesterView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CFFTesterView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CFFTesterView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CFFTesterView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CFFTesterView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CFFTesterView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CFFTesterView diagnostics

#ifdef _DEBUG
void CFFTesterView::AssertValid() const
{
	CView::AssertValid();
}

void CFFTesterView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFFTesterDoc* CFFTesterView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFFTesterDoc)));
	return (CFFTesterDoc*)m_pDocument;
}
#endif //_DEBUG


// CFFTesterView message handlers
