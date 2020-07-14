
// MFCApplication_20200714View.cpp: CMFCApplication20200714View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFCApplication_20200714.h"
#endif

#include "MFCApplication_20200714Doc.h"
#include "MFCApplication_20200714View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication20200714View

IMPLEMENT_DYNCREATE(CMFCApplication20200714View, CView)

BEGIN_MESSAGE_MAP(CMFCApplication20200714View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMFCApplication20200714View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CMFCApplication20200714View 생성/소멸

CMFCApplication20200714View::CMFCApplication20200714View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMFCApplication20200714View::~CMFCApplication20200714View()
{
}

BOOL CMFCApplication20200714View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMFCApplication20200714View 그리기
// 화면에 뿌려주는 함수
DWORD dwImg[1000 * 1000];
char cImg[1000 * 1000];
// 초기화: 전역변수는 초기화가 가능하다.
char cImg2[10000 * 28 * 28] = {0,};


void CMFCApplication20200714View::OnDraw(CDC* pDC)
{
	//CMFCApplication20200714Doc* pDoc = GetDocument();
	//ASSERT_VALID(pDoc);
	//if (!pDoc)
	//	return;

	//컬러영상 명도 영상 변환/RGB 선택 영상 실습
	//CMFCApplication20200714Doc* pDoc = GetDocument();
	//ASSERT_VALID(pDoc);
	//if (!pDoc) {
	//	return;
	//}

	//CImage Image;
	//HRESULT hResult = Image.Load(_T("pp.jpg"));

	//if (!FAILED(hResult)) {
	//	Copy2Array((DWORD*)dwImg, Image);
	//	// 0, 1, 2
	//	//SelectOneColor(dwImg, Image.GetWidth(), Image.GetHeight(), 2);
	//	//CopyFromArray(Image, dwImg);
	//	Color2Gray(Image, cImg);
	//	CopyGray2Image(Image, cImg);
	//	Image.BitBlt(pDC->m_hDC, 0, 0);
	//}

	//MNIST 특징 추출
	//FILE* fp;
	//fopen_s(&fp, "train-images.idx3-ubyte", "rb");
	//fread(cImg, 16, 1, fp);
	//fread(cImg, 28 * 28 * 10, 1, fp);
	//for (int k = 0; k < 10; k++) {
	//	for (int j = 0; j < 28; j++) {
	//		for (int i = 0; i < 28; i++) {
	//			pDC->SetPixel(i + 28 * k, j, RGB(cImg[k * 28 * 28 + j * 28 + i], cImg[k * 28 * 28 + j * 28 + i], cImg[k * 28 * 28 + j * 28 + i]));
	//		}
	//	}
	//}

	//fclose(fp);


	// MNIST 특징 추출: 마스크 만들기(LBP만들기)
	FILE* fp;
	fopen_s(&fp, "train-images.idx3-ubyte", "rb");
	fread(cImg, 16, 1, fp);
	fread(cImg, 28 * 28 * 10, 1, fp);
	for (int k = 0; k < 10; k++) {
		for (int j = 1; j < 27; j++) {
			for (int i = 1; i < 27; i++) {
				
				int m = 0;
				unsigned char val = 0;

				// 마스크 정의
				for (int sj = -1; sj < 2; sj++) {
					for (int si = -1; si < 2; si++) {
					
						if(sj !=0 && si != 0){
						
							if (cImg[k * 28 * 28 + j * 28 + i] <= cImg[k * 28 * 28 + (j + sj) * 28 + i + si]) {
								val |= 1<< m;
							}
							else if(sj==0 && si==0) {
								m--;
							}

							m++;
						}

						cImg2[k * 28 * 28 + j * 28 + i] = val;
					}
				}




				
				//pDC->SetPixel(i + 28 * k, j, RGB(cImg[k * 28 * 28 + j * 28 + i], cImg[k * 28 * 28 + j * 28 + i], cImg[k * 28 * 28 + j * 28 + i]));
			}
		}
	}

	for (int k = 0; k < 10; k++) {
		for (int j = 1; j < 27; j++) {
			for (int i = 1; i < 27; i++) {

				pDC->SetPixel(i + 28 * k, j, RGB(cImg[k * 28 * 28 + j * 28 + i], cImg[k * 28 * 28 + j * 28 + i], cImg[k * 28 * 28 + j * 28 + i]));
			}
		}
	}
	
	fclose(fp);





	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


//컬러영상 명도 영상 변환/RGB 선택 영상 실습
void CMFCApplication20200714View::Copy2Array(DWORD* pArr, CImage& Img) {

	for (int j = 0; j < Img.GetHeight(); j++) {
		for (int i = 0; i < Img.GetWidth(); i++) {
			pArr[j * Img.GetWidth() + i] = Img.GetPixel(i, j);
		}
	}
}

void CMFCApplication20200714View::CopyFromArray(CImage& Img, DWORD* pArr) {
	for (int j = 0; j < Img.GetHeight(); j++) {
		for (int i = 0; i < Img.GetWidth(); i++) {
			Img.SetPixel(i, j, pArr[j * Img.GetWidth() + i]);
		}
	}
}

void CMFCApplication20200714View::SelectOneColor(DWORD* pArr, int nWidth, int nHeight, int nIdxRGB) {
	for (int j = 0; j < nHeight; j++) {
		for (int i = 0; i < nWidth; i++) {
			pArr[j * nWidth + i] = pArr[j * nWidth + i] & 0xFF << (8 * nIdxRGB);
		}
	}
}

void CMFCApplication20200714View::Color2Gray(CImage& Img, char* pArr) {
	for (int j = 0; j < Img.GetHeight(); j++) {
		for (int i = 0; i < Img.GetWidth(); i++) {
			COLORREF rgb = Img.GetPixel(i, j);
			pArr[j * Img.GetWidth() + i] = (GetRValue(rgb) * 30 + GetGValue(rgb) * 59 + GetBValue(rgb) * 11) / 100;
		}
	}

}



void CMFCApplication20200714View::CopyGray2Image(CImage& Img, char* pArr) {
	for (int j = 0; j < Img.GetHeight(); j++) {
		for (int i = 0; i < Img.GetWidth(); i++) {
			char val = pArr[j * Img.GetWidth() + i];
			Img.SetPixel(i, j, RGB(val, val, val));
		}
	}

}



// CMFCApplication20200714View 인쇄

void CMFCApplication20200714View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMFCApplication20200714View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMFCApplication20200714View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMFCApplication20200714View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CMFCApplication20200714View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCApplication20200714View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCApplication20200714View 진단

#ifdef _DEBUG
void CMFCApplication20200714View::AssertValid() const
{
	CView::AssertValid();
}

void CMFCApplication20200714View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCApplication20200714Doc* CMFCApplication20200714View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication20200714Doc)));
	return (CMFCApplication20200714Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCApplication20200714View 메시지 처리기
