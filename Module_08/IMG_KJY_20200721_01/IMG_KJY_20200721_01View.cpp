
// IMG_KJY_20200721_01View.cpp: CIMGKJY2020072101View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "IMG_KJY_20200721_01.h"
#endif

#include "IMG_KJY_20200721_01Doc.h"
#include "IMG_KJY_20200721_01View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CIMGKJY2020072101View

IMPLEMENT_DYNCREATE(CIMGKJY2020072101View, CView)

BEGIN_MESSAGE_MAP(CIMGKJY2020072101View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CIMGKJY2020072101View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_DOWN_SAMPLING, &CIMGKJY2020072101View::OnDownSampling)
	ON_COMMAND(ID_UP_SAMPLING, &CIMGKJY2020072101View::OnUpSampling)
	ON_COMMAND(ID_QUANTIZATION, &CIMGKJY2020072101View::OnQuantization)
END_MESSAGE_MAP()

// CIMGKJY2020072101View 생성/소멸

CIMGKJY2020072101View::CIMGKJY2020072101View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CIMGKJY2020072101View::~CIMGKJY2020072101View()
{
}

BOOL CIMGKJY2020072101View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CIMGKJY2020072101View 그리기

void CIMGKJY2020072101View::OnDraw(CDC* pDC)
{
	CIMGKJY2020072101Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	int i, j;
	unsigned char R, G, B;
	for (i = 0; i < pDoc->m_height; i++) {
		for (j = 0; j < pDoc->m_width; j++) {
			R = G = B = pDoc->m_InputImage[i * pDoc->m_width + j];
			pDC->SetPixel(j + 5, i + 5, RGB(R, G, B));
		}
	}
	// 축소된 영상 출력
	for (i = 0; i < pDoc->m_Re_height; i++) {
		for (j = 0; j < pDoc->m_Re_width; j++) {
			R = pDoc->m_OutputImage[i * pDoc->m_Re_width + j];
			G = B = R;
			pDC->SetPixel(j + pDoc->m_width + 10, i + 5, RGB(R, G, B));
		}
	}
}


// CIMGKJY2020072101View 인쇄


void CIMGKJY2020072101View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CIMGKJY2020072101View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CIMGKJY2020072101View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CIMGKJY2020072101View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CIMGKJY2020072101View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CIMGKJY2020072101View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CIMGKJY2020072101View 진단

#ifdef _DEBUG
void CIMGKJY2020072101View::AssertValid() const
{
	CView::AssertValid();
}

void CIMGKJY2020072101View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CIMGKJY2020072101Doc* CIMGKJY2020072101View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CIMGKJY2020072101Doc)));
	return (CIMGKJY2020072101Doc*)m_pDocument;
}
#endif //_DEBUG


// CIMGKJY2020072101View 메시지 처리기


void CIMGKJY2020072101View::OnDownSampling()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	// 메시지 박스 띄우기
	/*AfxMessageBox(L"000000000000000000000000");*/

	// TODO: Add your command handler code here
	CIMGKJY2020072101Doc* pDoc = GetDocument(); // Doc 클래스 참조
	ASSERT_VALID(pDoc);
	pDoc->onDownSampling(); // Doc 클래스에 OnDownSampling 함수 호출

	// 화면을 갱신하려고 onDraw 함수로 간다.
	Invalidate(TRUE); // 화면 갱신
}


void CIMGKJY2020072101View::OnUpSampling()
{
	CIMGKJY2020072101Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->onUpSampling();
	Invalidate(TRUE);
}


void CIMGKJY2020072101View::OnQuantization()
{
	// TODO: Add your command handler code here
	CIMGKJY2020072101Doc* pDoc = GetDocument(); // Doc 클래스 참조
	ASSERT_VALID(pDoc);
	pDoc->OnQuantization(); // Doc 클래스에 OnQuantization 함수 호출
	Invalidate(TRUE); // 화면 갱신
}
