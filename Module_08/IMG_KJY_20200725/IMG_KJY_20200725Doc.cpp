
// IMG_KJY_20200725Doc.cpp: CIMGKJY20200725Doc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "IMG_KJY_20200725.h"
#endif

#include "IMG_KJY_20200725Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
// 추가, 영상의 가로줄은 4바이트의 배수
#define WIDTHBYTES(bits) (((bits)+31)/32*4)
#endif

// CIMGKJY20200725Doc

IMPLEMENT_DYNCREATE(CIMGKJY20200725Doc, CDocument)

BEGIN_MESSAGE_MAP(CIMGKJY20200725Doc, CDocument)
END_MESSAGE_MAP()


// CIMGKJY20200725Doc 생성/소멸

CIMGKJY20200725Doc::CIMGKJY20200725Doc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CIMGKJY20200725Doc::~CIMGKJY20200725Doc()
{
}

BOOL CIMGKJY20200725Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CIMGKJY20200725Doc serialization

void CIMGKJY20200725Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CIMGKJY20200725Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CIMGKJY20200725Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CIMGKJY20200725Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CIMGKJY20200725Doc 진단

#ifdef _DEBUG
void CIMGKJY20200725Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CIMGKJY20200725Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CIMGKJY20200725Doc 명령


BOOL CIMGKJY20200725Doc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	// CFile에서 처리
	// 파일을 읽어들이면 이 클래스 형식으로 저장.
	CFile hFile;

	// 파일 열기
	hFile.Open(lpszPathName, CFile::modeRead | CFile::typeBinary);
	// dibHf에 파일헤더를 읽어들인다.
	hFile.Read(&dibHf, sizeof(BITMAPFILEHEADER));

	/*RAW*/
	// raw 파일로 열기
	if (dibHf.bfType != 0x4D42) {
		if (hFile.GetLength() == 256 * 256) { // RAW 파일의 크기 결정
			m_height = 256;
			m_width = 256;
		}
		else if (hFile.GetLength() == 512 * 512) { // RAW 파일의 크기 결정
			m_height = 512;
			m_width = 512;
		}
		else if (hFile.GetLength() == 640 * 480) { // RAW 파일의 크기 결정
			m_height = 480;
			m_width = 640;
		}
		else {
			AfxMessageBox(L"Not Support Image Size"); // 해당 크기가 없는 경우
			return 0;
		} 
		
		m_size = m_width * m_height; // 영상의 크기 계산
		m_InputImage = new unsigned char[m_size];
		// 입력 영상의 크기에 맞는 메모리 할당
		for (int i = 0; i < m_size; i++) {
			m_InputImage[i] = 255; // 초기화
		}
		hFile.Read(m_InputImage, m_size); // 입력 영상 파일 읽기
		hFile.Close(); // 파일 닫기
		return TRUE;
	
	}else {

		// 이 파일이 BMP파일인지 검사 
		//if (dibHf.bfType != 0x4D42)
		//{
		//	// 프로젝트 생성시 유니코드를 사용하게 할 경우
		//	AfxMessageBox(L"Not BMP File");
		//	return FALSE;
		//}

		/*BMP*/
		// 영상정보의 header를 읽기
		hFile.Read(&dibHi, sizeof(BITMAPINFOHEADER));

		// 8비트, 24비트가 아닐 경우
		if (dibHi.biBitCount != 8 && dibHi.biBitCount != 24)
		{
			AfxMessageBox(L"Gray/True Color Possible");
			return FALSE;
		}


		if (dibHi.biBitCount == 8) {
			//8비트의 경우 팔레트를 생성해 주어야 한다. 총 256가지 색이므로 그 길이만큼 읽어들임
			hFile.Read(palRGB, sizeof(RGBQUAD) * 256);
		}

		//메모리 할당
		int ImgSize;

		if (dibHi.biBitCount == 8)
		{
			//이미지의 크기는 파일 총 길이에서, 두 헤드와 팔레트의 사이즈를 제외
			ImgSize = hFile.GetLength() - sizeof(BITMAPFILEHEADER) - sizeof(BITMAPINFOHEADER) - 256 * sizeof(RGBQUAD);

			// 컬러영상
		}
		else if (dibHi.biBitCount == 24) {
			ImgSize = hFile.GetLength() - sizeof(BITMAPFILEHEADER) - sizeof(BITMAPINFOHEADER);
		}

		//이미지를 저장, 출력할 배열생성.
		m_inImg = new unsigned char[ImgSize];
		m_outImg = NULL;
		hFile.Read(m_inImg, ImgSize);
		hFile.Close();

		//이미지의 길이정보
		m_height = dibHi.biHeight;
		m_width = dibHi.biWidth;
		m_size = m_height * m_width;

		return TRUE;
	}
}

 
BOOL CIMGKJY20200725Doc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// 파일 객체 선언
	CFile hFile;

	/*RAW 파일 저장*/
	CFileDialog SaveDlg(FALSE);
	
	// raw 파일을 다른 이름으로 저장하기 위한 대화상자 객체 선언
	if (SaveDlg.DoModal() == IDOK) {
		//DoModal 멤버 함수에서 저장하기 수행
		// 파일 열기
		hFile.Open(SaveDlg.GetPathName(), CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);
		// 파일 쓰기
		//hFile.Write(m_OutputImage, m_size);
		//// 파일 닫기
		//hFile.Close();

		//정보저장
		hFile.Write(&dibHf, sizeof(BITMAPFILEHEADER));
		hFile.Write(&dibHi, sizeof(BITMAPINFOHEADER));
		if (dibHi.biBitCount == 8)
			hFile.Write(palRGB, sizeof(RGBQUAD) * 256);

		if (m_outImg)
			hFile.Write(m_outImg, dibHi.biSizeImage);
		else
			hFile.Write(m_inImg, dibHi.biSizeImage);
		hFile.Close();
	}
	
	return TRUE;

	/*BMP 파일 저장*/
	//if (!hFile.Open(lpszPathName, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary)) {

	//	return FALSE;
	//}
	////정보저장

	//hFile.Write(&dibHf, sizeof(BITMAPFILEHEADER));
	//hFile.Write(&dibHi, sizeof(BITMAPINFOHEADER));

	//if (dibHi.biBitCount == 8) {
	//	hFile.Write(palRGB, sizeof(RGBQUAD) * 256);
	//}

	//hFile.Write(m_inImg, dibHi.biSizeImage);
	//hFile.Close();

	//return TRUE;

}


void CIMGKJY20200725Doc::OnFrameSum()
{
	CFile File;
	CFileDialog OpenDlg(TRUE);
	int i;
	unsigned char* temp1;
	unsigned char* temp2;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_outImg = new unsigned char[m_Re_size];

	if (OpenDlg.DoModal() == IDOK) {
		File.Open(OpenDlg.GetPathName(), CFile::modeRead | CFile::typeBinary);

		if (File.GetLength() == (unsigned)m_width * m_height) {
			temp1 = new unsigned char[m_Re_size];
			temp2 = new unsigned char[m_Re_size];
			File.Read(temp1, m_Re_size);
			File.Close();

			// 영상 상하 반전
			// 입력 영상의 배열 값을 출력 영상을 위한 배열의 수평축 뒷자리부터 저장
			for (i = 0; i < m_height; i++) {
				for (int j = 0; j < m_width; j++) {
					temp2[(m_height - i - 1) * m_width + j] = temp1[i * m_width + j];
				}
			}

			// 입력 값 저장을 위한 배열 선언
			// 프레임 간에 픽셀 대 픽셀로 덧셈연산 실행
			for (i = 0; i < m_Re_size; i++) {
				if (m_inImg[i] + temp2[i] > 255) {
					m_outImg[i] = 255;
				}else {
					m_outImg[i] = m_inImg[i] + temp2[i];
				}
			}
		}else {
			AfxMessageBox(L"Image size not matched");
			//영상의 크기가 다를 때는 처리하지 않음
			return;
		}
	}


}


void CIMGKJY20200725Doc::OnFrameAnd()
{
	CFile File;
	CFileDialog OpenDlg(TRUE);
	int i;
	unsigned char* temp1;
	unsigned char* temp2;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_outImg = new unsigned char[m_Re_size];

	if (OpenDlg.DoModal() == IDOK) {
		File.Open(OpenDlg.GetPathName(), CFile::modeRead | CFile::typeBinary);

		if (File.GetLength() == (unsigned)m_width * m_height) {
			temp1 = new unsigned char[m_Re_size];
			temp2 = new unsigned char[m_Re_size];
			File.Read(temp1, m_Re_size);
			File.Close();

			// 영상 상하 반전
			// 입력 영상의 배열 값을 출력 영상을 위한 배열의 수평축 뒷자리부터 저장
			for (i = 0; i < m_height; i++) {
				for (int j = 0; j < m_width; j++) {
					temp2[(m_height -i - 1)*m_width+j] = temp1[i * m_width + j];
				}
			}

			// 프레임 간에 픽셀 대 픽셀로 AND 연산 실행
			for (i = 0; i < m_Re_size; i++) {
				m_outImg[i] = (unsigned char)(m_inImg[i] & temp2[i]);
			}
		}else {
			AfxMessageBox(L"Image size not matched");
			return;
		}
	}
}


// 영상 반전
void CIMGKJY20200725Doc::OnNegaTransform()
{
	int i;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	for (i = 0; i < m_size; i++) {
		m_OutputImage[i] = 255 - m_InputImage[i]; // 영상 반전을 수행
	}
}

/*영상 합성*/
void CIMGKJY20200725Doc::OnFrameComb()
{
	CFile File1;
	CFile File2;
	CFileDialog OpenDlg(TRUE);
	int i;
	unsigned char* temp1;
	unsigned char* temp2;
	unsigned char* temp, * masktemp, maskvalue;
	unsigned char maskvalue1;
	unsigned char maskvalue2;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	// 컬러영상 사이즈
//	int image_size = dibHi.biSizeImage;
	int image_size = 512*512*3;

	m_outImg = new unsigned char[m_Re_size];
	
	unsigned char* result1;
	unsigned char* result2;

	unsigned char* firstImg;
	firstImg = new unsigned char[m_Re_size];
	firstImg = m_inImg;

	temp1 = NULL;
	temp2 = NULL;
	temp = NULL;
	masktemp = NULL;
	result1 = NULL;
	result2 = NULL;


	/*입력 영상 AND 마스크 연산*/
	AfxMessageBox(L"입력 영상의 마스크 영상을 입력하시오");

	if (OpenDlg.DoModal() == IDOK) { // 입력 영상의 마스크 영상
		File2.Open(OpenDlg.GetPathName(), CFile::modeRead | CFile::typeBinary);
	
		temp1 = new unsigned char[m_Re_size];
		temp2 = new unsigned char[m_Re_size];
		File2.Read(temp1, m_Re_size);
		File2.Close();
		int index = 0;

		// 영상 상하 반전
		// 입력 영상의 배열 값을 출력 영상을 위한 배열의 수평축 뒷자리부터 저장
		for (i = 0; i < m_height; i++) {
			for (int j = 0; j < m_width; j++) {
				temp2[(m_height - i - 1) * m_width + j] = temp1[i * m_width + j];
			}
		}

		and_result1 = new unsigned char[image_size];
		unsigned char* result_R = new unsigned char[m_Re_size];
		unsigned char* result_G = new unsigned char[m_Re_size];
		unsigned char* result_B = new unsigned char[m_Re_size];

		//and_result2 = new unsigned char[m_Re_size];
		// 프레임 간에 픽셀 대 픽셀로 AND 연산 실행




		if (dibHi.biBitCount == 8) {
			for (i = 0; i < m_Re_size; i++) {
				index = firstImg[i];
				and_result1[i] = (palRGB[index].rgbRed & temp2[i]);
			}
		}
		else {

			for (i = 0; i < m_Re_size; i++) {
				// 영상의 최대값에서 마스크 영상의 값을 뺀다.

				index = firstImg[i];
				result_R[i] = palRGB[index].rgbRed & temp2[i];
				result_G[i] = palRGB[index].rgbGreen & temp2[i];
				result_B[i] = palRGB[index].rgbBlue & temp2[i];
				and_result1[i] = result_R[i] + result_G[i] + result_B[i];
			}
		}
	}



	/*합성할 영상 AND 마스크 연산*/
	AfxMessageBox(L"합성할 영상을 입력하시오");

	if (OpenDlg.DoModal() == IDOK) { // 합성할 영상을 입력
		File1.Open(OpenDlg.GetPathName(), CFile::modeRead | CFile::typeBinary);
		// dibHf에 파일헤더를 읽어들인다.
		File1.Read(&dibHf, sizeof(BITMAPFILEHEADER));

		/*BMP*/
		// 영상정보의 header를 읽기
		File1.Read(&dibHi, sizeof(BITMAPINFOHEADER));

		// 8비트, 24비트가 아닐 경우
		if (dibHi.biBitCount != 8 && dibHi.biBitCount != 24)
		{
			AfxMessageBox(L"Gray/True Color Possible");
			return;
		}

		if (dibHi.biBitCount == 8) {
			//8비트의 경우 팔레트를 생성해 주어야 한다. 총 256가지 색이므로 그 길이만큼 읽어들임
			File1.Read(palRGB, sizeof(RGBQUAD) * 256);
		}

		//메모리 할당
		int ImgSize;

		if (dibHi.biBitCount == 8)
		{
			//이미지의 크기는 파일 총 길이에서, 두 헤드와 팔레트의 사이즈를 제외
			ImgSize = File1.GetLength() - sizeof(BITMAPFILEHEADER) - sizeof(BITMAPINFOHEADER) - 256 * sizeof(RGBQUAD);

			// 컬러영상
		}
		else if (dibHi.biBitCount == 24) {
			ImgSize = File1.GetLength() - sizeof(BITMAPFILEHEADER) - sizeof(BITMAPINFOHEADER);
		}

		//이미지를 저장, 출력할 배열생성.

		temp = new unsigned char[m_size];
		File1.Read(temp, ImgSize);
		//File.Close();

		//이미지의 길이정보
		//m_height = dibHi.biHeight;
		//m_width = dibHi.biWidth;
		//m_size = m_height * m_width;

		//File.Read(temp, m_size);
		//if ((unsigned)m_width * m_height != File.GetLength()) {
		//	AfxMessageBox(L"Image size not matched");
		//	// 영상의 크기가 같을 때
		//	return;
		//}
		
		File1.Close();
		and_result2 = new unsigned char[m_Re_size];
		for (i = 0; i < m_Re_size; i++) {

			maskvalue2 = 255 - temp2[i];
			and_result2[i] = ((unsigned char)temp[i] & (unsigned char)maskvalue2);
		}

	}// 입력 영상, 합성할 영상, 마스크 영상의 크기가 같아야 한다.



	/*전체 OR 연산*/
	for (i = 0; i < m_Re_size; i++) {
		m_outImg[i] = ((unsigned char) and_result1[i] | (unsigned char)and_result2[i]);
	// 입력 영상과 마스크 영상은 AND 연산을 하고, 합성할 영상은
	// (255-마스크 영상) 값과 AND 연산을 실행한 후 두 값을 더한다.
	}

}


void CIMGKJY20200725Doc::OnFrameComb01()
{
	CFile File;
	CFileDialog OpenDlg(TRUE);
	int i;
	unsigned char* temp, * masktemp, maskvalue;
	masktemp = NULL;
	maskvalue = NULL;
	temp = NULL;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];

	AfxMessageBox(L"합성할 영상을 입력하시오");
	if (OpenDlg.DoModal() == IDOK) { // 합성할 영상을 입력
		File.Open(OpenDlg.GetPathName(), CFile::modeRead);
		temp = new unsigned char[m_size];
		File.Read(temp, m_size);
	
		if ((unsigned)m_width * m_height != File.GetLength()) {
			AfxMessageBox(L"Image size not matched");
			// 영상의 크기가 같을 때
			return;
		}
			File.Close();
	}// 입력 영상, 합성할 영상, 마스크 영상의 크기가 같아야 한다.

	AfxMessageBox(L"입력 영상의 마스크 영상을 입력하시오");
	if (OpenDlg.DoModal() == IDOK) { // 입력 영상의 마스크 영상
		File.Open(OpenDlg.GetPathName(), CFile::modeRead);
		masktemp = new unsigned char[m_size];
		File.Read(masktemp, m_size);
		File.Close();
	}
	for (i = 0; i < m_size; i++) {
		maskvalue = 255 - masktemp[i];
		// 영상의 최대값에서 마스크 영상의 값을 뺀다.
		m_OutputImage[i] = (m_InputImage[i] & masktemp[i]) | (temp[i] & maskvalue);
		// 입력 영상과 마스크 영상은 AND 연산을 하고, 합성할 영상은
		// (255-마스크 영상) 값과 AND 연산을 실행한 후 두 값을 더한다.
	}
}
