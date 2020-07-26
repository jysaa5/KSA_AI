
// IMG_KJY_20200725View.cpp: CIMGKJY20200725View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "IMG_KJY_20200725.h"
#endif

#include "IMG_KJY_20200725Doc.h"
#include "IMG_KJY_20200725View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
//이미지 가로 바이트 길이는 4바이트의 배수
#define WIDTHBYTES(bits) (((bits)+31)/32*4);    
#endif


// CIMGKJY20200725View

IMPLEMENT_DYNCREATE(CIMGKJY20200725View, CView)

BEGIN_MESSAGE_MAP(CIMGKJY20200725View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CIMGKJY20200725View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_FRAME_SUM, &CIMGKJY20200725View::OnFrameSum)
	ON_COMMAND(ID_FRAME_AND, &CIMGKJY20200725View::OnFrameAnd)

	ON_COMMAND(ID_NEGA_TRANSFORM, &CIMGKJY20200725View::OnNegaTransform)
	ON_COMMAND(ID_FRAME_COMB, &CIMGKJY20200725View::OnFrameComb)
END_MESSAGE_MAP()

// CIMGKJY20200725View 생성/소멸

CIMGKJY20200725View::CIMGKJY20200725View() noexcept
{
	BmInfo = (BITMAPINFO*)malloc(sizeof(BITMAPINFO) + 256 * sizeof(RGBQUAD));

	for (int i = 0; i < 256; i++){
		BmInfo->bmiColors[i].rgbRed = BmInfo->bmiColors[i].rgbGreen = BmInfo->bmiColors[i].rgbReserved = 0;
	}




}

CIMGKJY20200725View::~CIMGKJY20200725View()
{
	if (BmInfo) {
		delete BmInfo;
	}
}

BOOL CIMGKJY20200725View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CIMGKJY20200725View 그리기

void CIMGKJY20200725View::OnDraw(CDC *pDC)
{
	CIMGKJY20200725Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	/*RAW 파일 그리기*/
	// raw 파일 열기 출력
	int i, j;
	unsigned char R, G, B;

	if (pDoc->m_InputImage != NULL && pDoc->dibHf.bfType != 0x4D42) {

		for (i = 0; i < pDoc->m_height; i++) {
			for (j = 0; j < pDoc->m_width; j++) {
				R = G = B = pDoc->m_InputImage[i * pDoc->m_width + j];
				pDC->SetPixel(j + 5, i + 5, RGB(R, G, B));
			}
		}
	}

	// raw 파일 결과 출력
	if (pDoc->m_OutputImage != NULL && pDoc->dibHf.bfType != 0x4D42) {
		for (i = 0; i < pDoc->m_Re_height; i++) {
			for (j = 0; j < pDoc->m_Re_width; j++) {
				R = pDoc->m_OutputImage[i * pDoc->m_Re_width + j];
				G = B = R;
				pDC->SetPixel(j + pDoc->m_width + 10, i + 5, RGB(R, G, B));
			}
		}
	}


	/*BMP 파일 그리기*/
	//BmInfo;
	int height;
	int width;
	int rwsize;

	// bmp 파일 읽기
	if (pDoc->m_inImg == NULL) {
		return;
	}

	//24비트 비트맵 파일의 영상출력
	if (pDoc->dibHi.biBitCount == 24) {

		height = pDoc->dibHi.biHeight;
		width = pDoc->dibHi.biWidth;
		rwsize = WIDTHBYTES(pDoc->dibHi.biBitCount * pDoc->dibHi.biWidth);
		BmInfo->bmiHeader = pDoc->dibHi;
		SetDIBitsToDevice(pDC->GetSafeHdc(), 0, 0, width, height, 0, 0, 0, height, pDoc->m_inImg, BmInfo, DIB_RGB_COLORS);

	}
	else {
		//8비트 컬러일 경우
		int index;
		rwsize = WIDTHBYTES(pDoc->dibHi.biBitCount * pDoc->dibHi.biWidth);

		//팔레트를 읽어들이며 반복출력
		for (int i = 0; i < pDoc->dibHi.biHeight; i++) {

			for (int j = 0; j < pDoc->dibHi.biWidth; j++) {
				index = pDoc->m_inImg[i * rwsize + j];
				BYTE R = pDoc->palRGB[index].rgbRed;
				BYTE G = pDoc->palRGB[index].rgbGreen;
				BYTE B = pDoc->palRGB[index].rgbBlue;

				//pDC->SetPixel(j,i,RGB(R,G,B));
				//영상 반전출력

				pDC->SetPixel(j, pDoc->dibHi.biHeight - i - 1, RGB(R, G, B));
			}

		}
	}


	// 결과 영상 출력
	if (pDoc->m_outImg == NULL) {
		return;
	}

	//24비트 비트맵 파일의 영상출력
	if (pDoc->dibHi.biBitCount == 24) {

		height = pDoc->dibHi.biHeight;
		width = pDoc->dibHi.biWidth;
		rwsize = WIDTHBYTES(pDoc->dibHi.biBitCount * pDoc->dibHi.biWidth);
		BmInfo->bmiHeader = pDoc->dibHi;
		SetDIBitsToDevice(pDC->GetSafeHdc(), 0, 0, width, height, 0, 0, 0, height, pDoc->m_inImg, BmInfo, DIB_RGB_COLORS);

	}else {
		//8비트 컬러일 경우
		int index;
		rwsize = WIDTHBYTES(pDoc->dibHi.biBitCount * pDoc->dibHi.biWidth);

		//팔레트를 읽어들이며 반복출력
		for (int i = 0; i < pDoc->dibHi.biHeight; i++) {

			for (int j = 0; j < pDoc->dibHi.biWidth; j++) {
				index = pDoc->m_outImg[i * rwsize + j];
				BYTE R = pDoc->palRGB[index].rgbRed;
				BYTE G = pDoc->palRGB[index].rgbGreen;
				BYTE B = pDoc->palRGB[index].rgbBlue;

				//pDC->SetPixel(j,i,RGB(R,G,B));
				//영상 반전출력

				pDC->SetPixel(j, pDoc->dibHi.biHeight - i - 1, RGB(R, G, B));
			}

		}
	}
}

// CIMGKJY20200725View 인쇄


void CIMGKJY20200725View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CIMGKJY20200725View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CIMGKJY20200725View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CIMGKJY20200725View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CIMGKJY20200725View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CIMGKJY20200725View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CIMGKJY20200725View 진단

#ifdef _DEBUG
void CIMGKJY20200725View::AssertValid() const
{
	CView::AssertValid();
}

void CIMGKJY20200725View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CIMGKJY20200725Doc* CIMGKJY20200725View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CIMGKJY20200725Doc)));
	return (CIMGKJY20200725Doc*)m_pDocument;
}
#endif //_DEBUG


// CIMGKJY20200725View 메시지 처리기


void CIMGKJY20200725View::OnFrameSum()
{
	CIMGKJY20200725Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnFrameSum();
	Invalidate(TRUE);
}


void CIMGKJY20200725View::OnFrameAnd()
{
	CIMGKJY20200725Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnFrameAnd();
	Invalidate(TRUE);
}



void CIMGKJY20200725View::OnNegaTransform()
{
	CIMGKJY20200725Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnNegaTransform();
	Invalidate(TRUE);
}


void CIMGKJY20200725View::OnFrameComb()
{
	CIMGKJY20200725Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnFrameComb();
	Invalidate(TRUE);
}
