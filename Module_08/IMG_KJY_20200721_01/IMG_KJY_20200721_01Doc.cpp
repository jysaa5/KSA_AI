
// IMG_KJY_20200721_01Doc.cpp: CIMGKJY2020072101Doc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "IMG_KJY_20200721_01.h"
#include "CDownSampleDlg.h" // 대화상자 사용을 위한 헤더 선언 //추가
#include "CUpSampleDlg.h" //추가
#include "CQuantizationDlg.h" //추가
#include "math.h" //수학 함수 사용을 위한 헤더 선언
#include "CConstantDlg.h" // 상수 입력 대화상자 사용을 위한 헤더 선언
#include "StressTransformDlg.h" //범위 강조 대화상자를 위한 헤더 선언
#endif

#include "IMG_KJY_20200721_01Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CIMGKJY2020072101Doc


IMPLEMENT_DYNCREATE(CIMGKJY2020072101Doc, CDocument)

BEGIN_MESSAGE_MAP(CIMGKJY2020072101Doc, CDocument)
//	ON_COMMAND(ID_SUM_CONSTANT, &CIMGKJY2020072101Doc::OnSumConstant)
END_MESSAGE_MAP()


// CIMGKJY2020072101Doc 생성/소멸

CIMGKJY2020072101Doc::CIMGKJY2020072101Doc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CIMGKJY2020072101Doc::~CIMGKJY2020072101Doc()
{
}

BOOL CIMGKJY2020072101Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CIMGKJY2020072101Doc serialization

void CIMGKJY2020072101Doc::Serialize(CArchive& ar)
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
void CIMGKJY2020072101Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CIMGKJY2020072101Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CIMGKJY2020072101Doc::SetSearchContent(const CString& value)
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

// CIMGKJY2020072101Doc 진단

#ifdef _DEBUG
void CIMGKJY2020072101Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CIMGKJY2020072101Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CIMGKJY2020072101Doc 명령

// 파일 입력 프로그램
BOOL CIMGKJY2020072101Doc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	CFile File; // 파일 객체 선언
	File.Open(lpszPathName, CFile::modeRead | CFile::typeBinary);
	// 파일 열기 대화상자에서 선택한 파일을 지정하고 읽기 모드 선택
	// 이 책에서는 영상의 크기 256*256, 512*512, 640*480만을 사용한다.
	if (File.GetLength() == 256 * 256) { // RAW 파일의 크기 결정
		m_height = 256;
		m_width = 256;
	}
	else if (File.GetLength() == 512 * 512) { // RAW 파일의 크기 결정
		m_height = 512;
		m_width = 512;
	}
	else if (File.GetLength() == 640 * 480) { // RAW 파일의 크기 결정
		m_height = 480;
		m_width = 640;
	}
	else {
		AfxMessageBox(L"Not Support Image Size"); // 해당 크기가 없는 경우
		return 0;
	} m_size = m_width *
		m_height; // 영상의 크기 계산
	m_InputImage = new unsigned char[m_size];
	// 입력 영상의 크기에 맞는 메모리 할당
	for (int i = 0; i < m_size; i++)
		m_InputImage[i] = 255; // 초기화
	File.Read(m_InputImage, m_size); // 입력 영상 파일 읽기
	File.Close();

	return TRUE;
}


// 파일 출력 프로그램
//BOOL CIMGKJY2020072101Doc::OnSaveDocument(LPCTSTR lpszPathName)
//{
//	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
//
//	CFile File; // 파일 객체 선언
//	//CFileDialog SaveDlg(FALSE, "raw", NULL, OFN_HIDEREADONLY);
//	// raw 파일을 다른 이름으로 저장하기 위한 대화상자 객체 선언
//	//CFileDialog SaveDlg(FALSE, NULL, "*.txt", OFN_OVERWRITEPROMPT, "TXT (*.txt)|*.txt||", this);
//  CFileDialog SaveDlg(FALSE);
//
//	if (SaveDlg.DoModal() == IDOK) {
//	
//		// DoModal 멤버 함수에서 저장하기 수행
//		File.Open(SaveDlg.GetPathName(), CFile::modeCreate | CFile::modeWrite);
//
//		// 파일 열기
//		// 파일 쓰기
//		File.Write(m_InputImage, m_size);
//		// 파일 닫기
//		File.Close();
//	}
//	return TRUE;
//}

// 영상 축소 프로그램
void CIMGKJY2020072101Doc::onDownSampling()
{
	int i, j;
	CDownSampleDlg dlg;
	//DoModal: 창이 무조건 뜨게 한다.
	if (dlg.DoModal() == IDOK) // 대화상자의 활성화 여부
	{
		m_Re_height = m_height / dlg.m_DownSampleRate;
		// 축소 영상의 세로 길이를 계산
		m_Re_width = m_width / dlg.m_DownSampleRate;
		// 축소 영상의 가로 길이를 계산
		m_Re_size = m_Re_height * m_Re_width;
		// 축소 영상의 크기를 계산
		m_OutputImage = new unsigned char[m_Re_size];
		// 축소 영상을 위한 메모리 할당
		for (i = 0; i < m_Re_height; i++) {
			for (j = 0; j < m_Re_width; j++) {
				m_OutputImage[i * m_Re_width + j]
					= m_InputImage[(i * dlg.m_DownSampleRate * m_width) + dlg.m_DownSampleRate * j];
				// 축소 영상을 생성
			}
		}
	}
}


// 영상 확대 프로그램
void CIMGKJY2020072101Doc::onUpSampling()
{
	int i, j;
	CUpSampleDlg dlg;
	if (dlg.DoModal() == IDOK) { // DoModal 대화상자의 활성화 여부
		m_Re_height = m_height * dlg.m_UpSampleRate;
		// 확대 영상의 세로 길이 계산
		m_Re_width = m_width * dlg.m_UpSampleRate;
		// 확대 영상의 가로 길이 계산
		m_Re_size = m_Re_height * m_Re_width;
		// 확대 영상의 크기 계산
		m_OutputImage = new unsigned char[m_Re_size];
		// 확대 영상을 위한 메모리 할당
		for (i = 0; i < m_Re_size; i++)
			m_OutputImage[i] = 0; // 초기화
		for (i = 0; i < m_height; i++) {
			for (j = 0; j < m_width; j++) {
				m_OutputImage[i * dlg.m_UpSampleRate * m_Re_width +
					dlg.m_UpSampleRate * j] = m_InputImage[i * m_width + j];
			} // 재배치하여 영상 확대
		}
	}
}


// 양자화 프로그램
void CIMGKJY2020072101Doc::OnQuantization()
{
	CQuantizationDlg dlg;
	if (dlg.DoModal() == IDOK)
		// 양자화 비트 수를 결정하는 대화상자의 활성화 여부
	{
		int i, j, value, LEVEL;
		double HIGH, * TEMP;
		m_Re_height = m_height;
		m_Re_width = m_width;
		m_Re_size = m_Re_height * m_Re_width;
		m_OutputImage = new unsigned char[m_Re_size];
		// 양자화 처리된 영상을 출력하기 위한 메모리 할당
		TEMP = new double[m_size];
		// 입력 영상 크기(m_size)와 동일한 메모리 할당
		LEVEL = 256; // 입력 영상의 양자화 단계(28=256)
		HIGH = 256.;
		value = (int)pow(2, dlg.m_QuantBit);
		// 양자화 단계 결정(예 : 24=16)
		for (i = 0; i < m_size; i++) {
			for (j = 0; j < value; j++) {
				if (m_InputImage[i] >= (LEVEL / value) * j &&
					m_InputImage[i] < (LEVEL / value) * (j + 1)) {
 					TEMP[i] = (double)(HIGH / value) * j; // 양자화 수행
				}
			}
		} for (i = 0
			;
			i < m_size;
			i++) {
			m_OutputImage[i] = (unsigned char)TEMP[i];
			// 결과 영상 생성
		}
	}
}


// 화소 값의 상수 덧셈 프로그램
void CIMGKJY2020072101Doc::OnSumConstant()
{
	CConstantDlg dlg; // 상수 값을 입력받는 대화상자
	int i;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	if (dlg.DoModal() == IDOK) {
		for (i = 0; i < m_size; i++) {
			if (m_InputImage[i] + dlg.m_Constant >= 255)
				m_OutputImage[i] = 255;
			// 출력 값이 255보다 크면 255 출력
			else
				m_OutputImage[i] = (unsigned char)(m_InputImage[i] + dlg.m_Constant);
			// 상수 값과 화소 값과의 덧셈
		}
	}
}


// 화소 값의 상수 뺄셈 프로그램
void CIMGKJY2020072101Doc::OnSubConstant()
{
	CConstantDlg dlg;
	int i;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	if (dlg.DoModal() == IDOK) {
		for (i = 0; i < m_size; i++) {
			if (m_InputImage[i] - dlg.m_Constant < 0)
				m_OutputImage[i] = 0; // 출력 값이 255보다 크면 255를 출력
			else
				m_OutputImage[i]
				= (unsigned char)(m_InputImage[i] - dlg.m_Constant);
			// 상수 값과 화소 값과의 뺄셈
		}
	}
}


// 화소 값의 곱셈 프로그램
void CIMGKJY2020072101Doc::OnMulConstant()
{
	CConstantDlg dlg;
	int i;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	if (dlg.DoModal() == IDOK) {
		for (i = 0; i < m_size; i++) {
			if (m_InputImage[i] * dlg.m_Constant > 255) {
				m_OutputImage[i] = 255;
			}
			// 곱의 값이 255보다 크면 255를 출력
			else if (m_InputImage[i] * dlg.m_Constant < 0)
			{
				m_OutputImage[i] = 0;
			}
			// 곱의 값이 0보다 작으면 0을 출력
			else
			{
				m_OutputImage[i] = (unsigned char)(m_InputImage[i] * dlg.m_Constant);
			}
			// 상수 값과 화소 값 곱셈
		}
	}
}


// 화소 값의 상수 나눗셈 프로그램
void CIMGKJY2020072101Doc::OnDivConstant()
{
	CConstantDlg dlg;
	int i;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	if (dlg.DoModal() == IDOK) {
		for (i = 0; i < m_size; i++) {
			if (m_InputImage[i] / dlg.m_Constant > 255)
			{
				m_OutputImage[i] = 255;
			}
			// 나눗셈의 값이 255보다 크면 255를 출력
			else if (m_InputImage[i] / dlg.m_Constant < 0)
			{
				m_OutputImage[i] = 0;
			}
			// 나눗셈의 값이 0보다 작으면 0을 출력
			else
			{
				m_OutputImage[i] = (unsigned char)(m_InputImage[i] / dlg.m_Constant);
			}
			// 상수 값과 화소 값 나눗셈
		}
	}
}


// 화소 값의 AND 프로그램
void CIMGKJY2020072101Doc::OnAndOperate()
{
	CConstantDlg dlg;
	int i;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	if (dlg.DoModal() == IDOK) {
		for (i = 0; i < m_size; i++) {
			// 비트 단위 AND 연산
			if ((m_InputImage[i] & (unsigned char)dlg.m_Constant) >= 255)
			{
				m_OutputImage[i] = 255;
			}
			else if ((m_InputImage[i] & (unsigned char)dlg.m_Constant) < 0)
			{
				m_OutputImage[i] = 0;
			}
			else
			{
				m_OutputImage[i] = (m_InputImage[i] & (unsigned char)dlg.m_Constant);
			}
		}
	}
}


// 화소 값의 OR 프로그램
void CIMGKJY2020072101Doc::OnOrOperate()
{
	CConstantDlg dlg;
	int i;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	if (dlg.DoModal() == IDOK) {
		for (i = 0; i < m_size; i++) {
			// 비트 단위 OR 연산
			if ((m_InputImage[i] | (unsigned char)dlg.m_Constant) >= 255) {
				m_OutputImage[i] = 255;
			}else if ((m_InputImage[i] | (unsigned char)dlg.m_Constant) < 0) {
				m_OutputImage[i] = 0;
			}
				else {
				m_OutputImage[i] = (m_InputImage[i] | (unsigned char) dlg.m_Constant);
			}
		}
	}
}


// 화소 값의 XOR 프로그램
void CIMGKJY2020072101Doc::OnXorOperate()
{
	CConstantDlg dlg;
	int i;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	if (dlg.DoModal() == IDOK) {
		for (i = 0; i < m_size; i++) {
			// 비트 단위 XOR 연산
			if ((m_InputImage[i] ^ (unsigned char)dlg.m_Constant) >= 255) {
				m_OutputImage[i] = 255;
			}else if ((m_InputImage[i] ^ (unsigned char)dlg.m_Constant) < 0) {
				m_OutputImage[i] = 0;
			}else {
				m_OutputImage[i] = (m_InputImage[i] ^ (unsigned char)dlg.m_Constant);
			}
		}
	}
}


// 영상을 반전시키는 프로그램
void CIMGKJY2020072101Doc::OnNegaTransform()
{
	int i;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	for (i = 0; i < m_size; i++)
		m_OutputImage[i] = 255 - m_InputImage[i]; // 영상 반전을 수행
}


// 감마 보정 프로그램
void CIMGKJY2020072101Doc::OnGammaCorrection()
{
	CConstantDlg dlg;
	int i;
	double temp;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	if (dlg.DoModal() == IDOK) {
		for (i = 0; i < m_size; i++) {
			temp = pow(m_InputImage[i], 1 / dlg.m_Constant);
			// 감마 값 계산
			if (temp < 0) {
				m_OutputImage[i] = 0;
			}
			else if (temp > 255) {
				m_OutputImage[i] = 255;
			}
			else {
				m_OutputImage[i] = (unsigned char)temp;
			}
		}
	}
}


// 영상의 이진 프로그램
void CIMGKJY2020072101Doc::OnBinarization()
{
	CConstantDlg dlg;
	int i;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	if (dlg.DoModal() == IDOK) {
		for (i = 0; i < m_size; i++) {
			if (m_InputImage[i] >= dlg.m_Constant) {
				m_OutputImage[i] = 255; // 임계 값보다 크면 255 출력
			}
			else {
				m_OutputImage[i] = 0; // 임계 값보다 작으면 0 출력
			}
		}
	}
}


// 범위를 강조하는 변환 프로그램
void CIMGKJY2020072101Doc::OnStressTransform()
{
	StressTransformDlg dlg;
	int i;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	if (dlg.DoModal() == IDOK) {
		for (i = 0; i < m_size; i++) {
			// 입력 값이 강조 시작 값과 강조 종료 값 사이에 위치하면 255 출력
			if (m_InputImage[i] >= dlg.m_StartPoint && m_InputImage[i] <= dlg.m_EndPoint)
			{
				m_OutputImage[i] = 255;
			}
			else {
				m_OutputImage[i] = m_InputImage[i];
			}
		}
	}
}


// 히스토그램 스트레칭의 프로그램
void CIMGKJY2020072101Doc::OnHistoStretch()
{
	int i;
	unsigned char LOW, HIGH, MAX, MIN;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	LOW = 0;
	HIGH = 255;
	MIN = m_InputImage[0]; // 최소값을 찾기 위한 초기값
	MAX = m_InputImage[0]; // 최대값을 찾기 위한 초기값
	// 입력 영상의 최소값 찾기
	for (i = 0; i < m_size; i++) {
		if (m_InputImage[i] < MIN) {
			MIN = m_InputImage[i];
		}
	}
	// 입력 영상의 최대값 찾기
	for (i = 0; i < m_size; i++) {
		if (m_InputImage[i] > MAX) {
			MAX = m_InputImage[i];
		}
	}
	m_OutputImage = new unsigned char[m_Re_size];
	// 히스토그램 stretch
	for (i = 0; i < m_size; i++) {
		m_OutputImage[i] = (unsigned char)((m_InputImage[i] - MIN) * HIGH / (MAX - MIN));
	}
}


// 앤드-인 탐색 프로그램
void CIMGKJY2020072101Doc::OnEndInSearch()
{
	int i;
	unsigned char LOW, HIGH, MAX, MIN;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	LOW = 0;
	HIGH = 255;
	MIN = m_InputImage[0];
	MAX = m_InputImage[0];
	for (i = 0; i < m_size; i++) {
		if (m_InputImage[i] < MIN) {
			MIN = m_InputImage[i];
		}
	}
	for (i = 0; i < m_size; i++) {
		if (m_InputImage[i] > MAX) {
			MAX = m_InputImage[i];
		}
	}
	m_OutputImage = new unsigned char[m_Re_size];

	for (i = 0; i < m_size; i++) {
		// 원본 영상의 최소값보다 작은 값은 0
		if (m_InputImage[i] <= MIN) {
			m_OutputImage[i] = 0;
		}
		// 원본 영상의 최대값보다 큰 값은 255
		else if (m_InputImage[i] >= MAX) {
			m_OutputImage[i] = 255;
		}
		else {
			m_OutputImage[i] = (unsigned char)((m_InputImage[i] - MIN) * HIGH / (MAX - MIN));

		}
	}
}

double m_HIST[256];
double m_Sum_Of_HIST[256];
unsigned char m_Scale_HIST[256];

// 히스토그램 프로그램
void CIMGKJY2020072101Doc::OnHistogram()
{
	// TODO: 여기에 구현 코드 추가.
	// 히스토그램의 값은 0~255
	// 히스토그램의 크기 값을 MAX=255로 정규화하여 출력
	// 히스트그램의 크기 : 256*256 지정

	int i, j, value;
	unsigned char LOW, HIGH;
	double MAX, MIN, DIF;

	m_Re_height = 256;
	m_Re_width = 256;
	m_Re_size = m_Re_height * m_Re_width;

	LOW = 0;
	HIGH = 255;

	// 초기화
	for (i = 0; i < 256; i++) {
		m_HIST[i] = LOW;
	}

	// 빈도 수 조사
	for (i = 0; i < m_size; i++) {
		value = (int)m_InputImage[i];
		m_HIST[value]++;
	}

	// 정규화
	MAX = m_HIST[0];
	MIN = m_HIST[0];

	for (i = 0; i < 256; i++) {
		if (m_HIST[i] > MAX) {
			MAX = m_HIST[i];
		}
	}

	for (i = 0; i < 256; i++) {

		if (m_HIST[i] < MIN) {
			MIN = m_HIST[i];
		}
	}

	DIF = MAX - MIN;
	// 정규화된 히스토그램

	for (i = 0; i < 256; i++) {
		m_Scale_HIST[i] = (unsigned char)((m_HIST[i] - MIN) * HIGH / DIF);
	}

	// 정규화된 히스토그램 출력
	m_OutputImage = new unsigned char[m_Re_size + (256 * 20)];

	for (i = 0; i < m_Re_size; i++) {
		m_OutputImage[i] = 255;
	}

	// 정규화된 히스토그램의 값은 출력 배열에 검은 점(0)으로 표현
	for (i = 0; i < 256; i++) {
		for (j = 0; j < m_Scale_HIST[i]; j++) {
			m_OutputImage[m_Re_width * (m_Re_height - j - 1) + i] = 0;
		}
	}

	// 히스토그램을 출력하고 그 아래 부분에 히스토그램의 색을 표시
	for (i = m_Re_height; i < m_Re_height + 5; i++) {
		for (j = 0; j < 256; j++) {
			m_OutputImage[m_Re_height * i + j] = 255;
		}
	}

	for (i = m_Re_height + 5; i < m_Re_height + 20; i++) {
		for (j = 0; j < 256; j++) {
			m_OutputImage[m_Re_height * i + j] = j;
		}
	}

	m_Re_height = m_Re_height + 20;
	m_Re_size = m_Re_height * m_Re_width;

}


// 히스토그램 평활화 프로그램
void CIMGKJY2020072101Doc::OnHistoEqual()
{
	// TODO: 여기에 구현 코드 추가.
	int i, value;
	unsigned char LOW, HIGH, Temp;
	double SUM = 0.0;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	LOW = 0;
	HIGH = 255;

	//초기화
	for (i = 0; i < 256; i++) {
		m_HIST[i] = LOW;
	}

	//빈도수 조사
	for (i = 0; i < m_size; i++) {
		value = (int)m_InputImage[i];
		m_HIST[value]++;
	}

	//누적 히스토그램 생성
	for (i = 0; i < 256; i++) {
		SUM += m_HIST[i];
		m_Sum_Of_HIST[i] = SUM;
	}

	m_OutputImage = new unsigned char[m_Re_size];

	//입력 영상을 평활화된 영상으로 출력
	for (i = 0; i < m_size; i++) {
		Temp = m_InputImage[i];
		m_OutputImage[i] = (unsigned char)(m_Sum_Of_HIST[Temp] * HIGH / m_size);
	}
}


// 히스토그램 명세화 프로그램
void CIMGKJY2020072101Doc::OnHistoSpec()
{

	int i, value, Dvalue, top, bottom, DADD;
	unsigned char* m_DTEMP, m_Sum_Of_ScHIST[256], m_TABLE[256];
	unsigned char LOW, HIGH, Temp, * m_Org_Temp;
	double m_DHIST[256], m_Sum_Of_DHIST[256], SUM = 0.0, DSUM = 0.0;
	double DMAX, DMIN;
	top = 255;
	bottom = top - 1;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	m_Org_Temp = new unsigned char[m_size];
	m_DTEMP = new unsigned char[m_size];
	CFile File;
	CFileDialog OpenDlg(TRUE);

	// 원하는 히스토그램이 있는 영상을 입력받음
	if (OpenDlg.DoModal() == IDOK) {

		//File.Open(OpenDlg.GetFileName(), CFile::modeRead);
		File.Open(OpenDlg.GetPathName(), CFile::modeRead);
		if (File.GetLength() == (unsigned)m_size) {
			m_DTEMP = new unsigned char[m_size];
			File.Read(m_DTEMP, m_size);
			File.Close();
		}
		else {
			AfxMessageBox(L"Image size not matched");
			// 같은 크기의 영상을 대상으로 함
			return;
		}
	}

	LOW = 0;
	HIGH = 255;
	// 초기화
	for (i = 0; i < 256; i++) {
		m_HIST[i] = LOW;
		m_DHIST[i] = LOW;
		m_TABLE[i] = LOW;
	}

	// 빈도 수 조사
	for (i = 0; i < m_size; i++) {
		value = (int)m_InputImage[i];
		m_HIST[value]++;
		Dvalue = (int)m_DTEMP[i];
		m_DHIST[Dvalue]++;
	}
	// 누적 히스토그램 조사
	for (i = 0; i < 256; i++) {
		SUM += m_HIST[i];
		m_Sum_Of_HIST[i] = SUM;
		DSUM += m_DHIST[i];
		m_Sum_Of_DHIST[i] = DSUM;
	}

	// 원본 영상의 평활화
	for (i = 0; i < m_size; i++) {
		Temp = m_InputImage[i];
		m_Org_Temp[i] = (unsigned char)(m_Sum_Of_HIST[Temp] * HIGH / m_size);
	}

	// 누적 히스토그램에서 최소값과 최대값 지정
	DMIN = m_Sum_Of_DHIST[0];
	DMAX = m_Sum_Of_DHIST[255];

	// 원하는 영상을 평활화
	for (i = 0; i < 256; i++) {
		m_Sum_Of_ScHIST[i] = (unsigned char)((m_Sum_Of_DHIST[i] - DMIN) * HIGH / (DMAX - DMIN));
	}
	// 룩업테이블을 이용한 명세화
	for (; ; ) {
		for (i = m_Sum_Of_ScHIST[bottom];
			i <= m_Sum_Of_ScHIST[top]; i++) {
			m_TABLE[i] = top;
		}

		top = bottom;
		bottom = bottom - 1;
		if (bottom < -1) {
			break;
		}
	}

	for (i = 0; i < m_size; i++) {
		DADD = (int)m_Org_Temp[i];
		m_OutputImage[i] = m_TABLE[DADD];
	}
}


// 엠보싱
void CIMGKJY2020072101Doc::OnEmbossing()
{
	int i, j;
	double EmboMask[3][3] = { {-1., 0., 0.}, {0., 0., 0.}, {0., 0., 1.} };

	//마스크 선택
	//double EmboMask[3][3] = { {0., 0., 0.}, {0., 1., 0.}, {0., 0., 0.} };
	//double EmboMask[3][3] = { {1., 1., 1.}, {1., -8., 1.}, {1., 1., 1.} };

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	m_tempImage = OnMaskProcess(m_InputImage, EmboMask);
	
	// OnMaskProcess 함수를 호출하여 회선을 처리를 한다.

	for (i = 0; i < m_Re_height; i++) {
		for (j = 0; j < m_Re_width; j++) {
		
			if (m_tempImage[i][j] > 255) {
				m_tempImage[i][j] = 255;
			}

			if (m_tempImage[i][j] < 0) {
				m_tempImage[i][j] = 0;
			}

		}
	}
	// 회선 처리 결과가 0~255 사이 값이 되도록 한다.
	// m_tempImage = OnScale(m_tempImage, m_Re_height, m_Re_width);
	// 정규화 함수를 사용할 때
	// 회선 처리 결과나 정규화 처리 결과는 2차원 배열 값이 되므로
	// 2차원 배열을 1차원 배열로 바꾸어 출력하도록 한다.

	for (i = 0; i < m_Re_height; i++) {
		for (j = 0; j < m_Re_width; j++) {
			m_OutputImage[i * m_Re_width + j] = (unsigned char)m_tempImage[i][j];
		}
	}


}


// 화소영역을 처리하는 함수
double** CIMGKJY2020072101Doc::OnMaskProcess(unsigned char* Target, double Mask[3][3])
{
	// 회선 처리가 일어나는 함수
	int i, j, n, m;
	double** tempInputImage, ** tempOutputImage, S = 0.0;

	tempInputImage = Image2DMem(m_height + 2, m_width + 2);
	// 입력 값을 위한 메모리 할당
	tempOutputImage = Image2DMem(m_height, m_width);
	// 출력 값을 위한 메모리 할당

	// 1차원 입력 영상의 값을 2차원 배열에 할당한다.
	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			tempInputImage[i + 1][j + 1] = (double)Target[i * m_width + j];
		}
	}

	// 회선 연산
	for (i = 0; i < m_height; i++) {
	
		for (j = 0; j < m_width; j++) {
			for (n = 0; n < 3; n++) {
			
				for (m = 0; m < 3; m++) {
				
					S += Mask[n][m] * tempInputImage[i + n][j + m];
				
				}
			} // 회선 마스크의 크기 만큼 이동하면서 값을 누적

			// 누적된 값을 출력 메모리 저장
			tempOutputImage[i][j] = S;
			S = 0.0; //다음 블록으로 이동하면 누적 값을 초기화
		}
	}
	// 결과 값 반환
	return tempOutputImage;
}


// 영상의 화소 값을 정규화시키는 함수
double** CIMGKJY2020072101Doc::OnScale(double **Target, int height, int width)
{
	// 정규화를 위한 함수
	int i, j;
	double min, max;

	min = max = Target[0][0];

	for (i = 0; i < height; i++) {

		for (j = 0; j < width; j++) {
		
			if (Target[i][j] <= min) {
				min = Target[i][j];
			}
		}
	
	}

	for (i = 0; i < height; i++) {

		for(j=0; j<width; j++){
		
			Target[i][j] = (Target[i][j] - min) * (255. / max);
		}
	}
	
	return Target;
}


// 화소 영역 처리 프로그램으로 간단히 하려고 1차원 배열을 2차원 배열로 할당하는 함수
double** CIMGKJY2020072101Doc::Image2DMem(int height, int width)
{
	// 2차원 메모리 할당을 위한 함수
	double** temp;
	int i, j;
	temp = new double* [height];
	for(i=0; i<height; i++){
		temp[i] = new double[width];
	}

	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {

			temp[i][j] = 0.0;
		}
	} // 할당된 2차원 메모리를 초기화

	return temp;
}


// 블러링 프로그램
void CIMGKJY2020072101Doc::OnBlurr()
{
	int i, j;
	double BlurrMask[3][3] = {{1./9., 1./9., 1./9.}, {1./9., 1./9., 1./9.}, {1./9., 1./9., 1./9.}};
	
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];
	m_tempImage = OnMaskProcess(m_InputImage, BlurrMask);
	//블러링 처리
	//m_tempImage = OnScale(m_tempImage, m_Re_height, m_Re_width);

	//정규화
	for (i = 0; i < m_Re_height; i++) {

		for (j = 0; j < m_Re_width; j++) {

			if (m_tempImage[i][j] > 255.) {
				m_tempImage[i][j] = 255.;
			}

			if (m_tempImage[i][j] < 0.) {
				m_tempImage[i][j] = 0.;
			}
		}
	}

	for (i = 0; i < m_Re_height; i++) {
		for (j = 0; j < m_Re_width; j++) {
			m_OutputImage[i * m_Re_width + j] = (unsigned char)m_tempImage[i][j];
		}
	}
	
}


// 가우시안 필터 처리
void CIMGKJY2020072101Doc::OnGaussianFilter()
{
	int i, j;
	double GaussianMask[3][3] = { {1./16., 1./8., 1./16.}, {1./8., 1./4., 1./8.}, {1./16., 1./8., 1./16.}};
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	m_tempImage = OnMaskProcess(m_InputImage, GaussianMask);

	// m_tempImage = OnScale(m_tempImage, m_Re_height, m_Re_width);
	for (i = 0; i < m_Re_height; i++) {
		for (j = 0; j < m_Re_width; j++) {
			if (m_tempImage[i][j] > 255.)
				m_tempImage[i][j] = 255.;
			if (m_tempImage[i][j] < 0.)
				m_tempImage[i][j] = 0.;
		}
	}
	for (i = 0; i < m_Re_height; i++) {
		for (j = 0; j < m_Re_width; j++) {
			m_OutputImage[i * m_Re_width + j]
				= (unsigned char)m_tempImage[i][j];
		}
	}
}


// 샤프닝 처리 프로그램
void CIMGKJY2020072101Doc::OnSharpening()
{
	int i, j;
	//double SharpeningMask[3][3] = {{-1., -1., -1.}, {-1., 9., -1.}, { -1., -1., -1. }};
	
	double SharpeningMask[3][3] = { {0., -1., 0.}, {-1., 5., -1.}, {0., -1., 0.} };
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	m_tempImage = OnMaskProcess(m_InputImage, SharpeningMask);
	
	// m_tempImage = OnScale(m_tempImage, m_Re_height, m_Re_width);

	for (i = 0; i < m_Re_height; i++) {
		for (j = 0; j < m_Re_width; j++) {
			if (m_tempImage[i][j] > 255.) {
				m_tempImage[i][j] = 255.;
			}
			if (m_tempImage[i][j] < 0.) {
				m_tempImage[i][j] = 0.;
			}
	    }
    }
    for (i = 0; i < m_Re_height; i++) {
	    for (j = 0; j < m_Re_width; j++) {
		 m_OutputImage[i * m_Re_width + j] = (unsigned char)m_tempImage[i][j];
	    }
    }
}


// 고주파 필터 샤프닝 처리 프로그램
void CIMGKJY2020072101Doc::OnHpfSharp()
{
	int i, j;
	double HpfSharpMask[3][3] = {{-1./9., -1./9., -1./9.}, {-1./9., 8./9., -1./9.}, {-1./9., -1./9., -1./9.}};
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	m_tempImage = OnMaskProcess(m_InputImage, HpfSharpMask);

	// m_tempImage = OnScale(m_tempImage, m_Re_height, m_Re_width);
	for (i = 0; i < m_Re_height; i++) {
		for (j = 0; j < m_Re_width; j++) {
			if (m_tempImage[i][j] > 255.) {
				m_tempImage[i][j] = 255.;
			}
			if (m_tempImage[i][j] < 0.) {
				m_tempImage[i][j] = 0.;
			}
		}
	}

	for (i = 0; i < m_Re_height; i++) {
		for (j = 0; j < m_Re_width; j++) {
			m_OutputImage[i * m_Re_width + j] = (unsigned char)m_tempImage[i][j];
		}
	}
}


// 저주파 필터 샤프닝 처리 프로그램
void CIMGKJY2020072101Doc::OnLpfSharp()
{
	CConstantDlg dlg; // 상수를 입력받으려고 대화상자 선언
	int i, j;
	int alpha = 0;
	double LpfSharpMask[3][3] = {{1. /9., 1./9., 1./9.}, {1./9., 1./9., 1./9.}, {1./9., 1./9., 1./9.}};
	
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];

	if (dlg.DoModal() == IDOK) {
		alpha = (int)dlg.m_Constant;
		// 대화상자를 이용하여 상수를 입력받는다.
	}
	m_tempImage = OnMaskProcess(m_InputImage, LpfSharpMask);

	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			m_tempImage[i][j] = (alpha * m_InputImage[i * m_width + j]) - (unsigned char)m_tempImage[i][j];
		}
	}

	// m_tempImage = OnScale(m_tempImage, m_Re_height, m_Re_width);
	for (i = 0; i < m_Re_height; i++) {
		for (j = 0; j < m_Re_width; j++) {
			if (m_tempImage[i][j] > 255.) {
				m_tempImage[i][j] = 255.;
			}
			if (m_tempImage[i][j] < 0.) {
				m_tempImage[i][j] = 0.;
			}
		}
	}
	for (i = 0; i < m_Re_height; i++) {
		for (j = 0; j < m_Re_width; j++) {
			m_OutputImage[i * m_Re_width + j] = (unsigned char)m_tempImage[i][j];
		}
	}
}


// 이동과 차분 처리 프로그램
void CIMGKJY2020072101Doc::OnDiffOperatorHor()
{
	int i, j;
	double DiffHorMask[3][3]
		= { {0., -1., 0.}, {0., 1., 0.}, {0., 0., 0.} };
	// 수평 필터 선택
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	m_tempImage = OnMaskProcess(m_InputImage, DiffHorMask);
	// m_tempImage = OnScale(m_tempImage, m_Re_height, m_Re_width);

	for (i = 0; i < m_Re_height; i++) {
		for (j = 0; j < m_Re_width; j++) {
			if (m_tempImage[i][j] > 255.) {
				m_tempImage[i][j] = 255.;
			}
			if (m_tempImage[i][j] < 0.) {
				m_tempImage[i][j] = 0.;
			}
		}
	}

	for (i = 0; i < m_Re_height; i++) {
		for (j = 0; j < m_Re_width; j++) {
			m_OutputImage[i * m_Re_width + j] = (unsigned char)m_tempImage[i][j];
		}
	}
}


// 유사 연산자 기법
void CIMGKJY2020072101Doc::OnHomogenOperator()
{
	int i, j, n, m;
	double max, ** tempOutputImage;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	m_tempImage = Image2DMem(m_height + 2, m_width + 2);
	
	tempOutputImage = Image2DMem(m_Re_height, m_Re_width);
	
	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			m_tempImage[i + 1][j + 1] = (double)m_InputImage[i * m_width + j];
		}
	}

	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			max = 0.0; // 블록이 이동할 때마다 최대값 초기화
			for (n = 0; n < 3; n++) {
				for (m = 0; m < 3; m++) {
					if (DoubleABS(m_tempImage[i + 1][j + 1] -
						m_tempImage[i + n][j + m]) >= max)
						// 블록의 가운데 값 - 블록의 주변 픽셀 값의 절대 값
						// 중에서 최대값을 찾는다.
						max = DoubleABS(m_tempImage[i + 1]
							[j + 1] - m_tempImage[i + n][j + m]);
				}
			}
			tempOutputImage[i][j] = max; // 찾은 최대값을 출력 값으로 지정
		}
	}
	
	for (i = 0; i < m_Re_height; i++) {
		for (j = 0; j < m_Re_width; j++) {
			if (tempOutputImage[i][j] > 255.)
				tempOutputImage[i][j] = 255.;
			if (tempOutputImage[i][j] < 0.)
				tempOutputImage[i][j] = 0.;
		}
	}
	
	for (i = 0; i < m_Re_height; i++) {
		for (j = 0; j < m_Re_width; j++) {
			m_OutputImage[i * m_Re_width + j]
				= (unsigned char)tempOutputImage[i][j];
		}
	}
}


// 유사 연산자 기법 - DouobleABS
double CIMGKJY2020072101Doc::DoubleABS(double X)
{
	// 실수의 절대 값 연산 함수
	if (X >= 0) {
		return X;
	}else {
		return -X;
	}
}


// 라플라시안 처리 프로그램
void CIMGKJY2020072101Doc::OnLaplacian()
{
	int i, j;
	double LaplacianMask[3][3] = { {0., 1., 0.}, {1., -4., 1.}, {0., 1., 0.} };
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	m_tempImage = OnMaskProcess(m_InputImage, LaplacianMask);
	// m_tempImage = OnScale(m_tempImage, m_Re_height, m_Re_width);

	for (i = 0; i < m_Re_height; i++) {
		for (j = 0; j < m_Re_width; j++) {
			if (m_tempImage[i][j] > 255.) {
				m_tempImage[i][j] = 255.;
			}
			if (m_tempImage[i][j] < 0.) {
				m_tempImage[i][j] = 0.;
			}
		}
	}
	for (i = 0; i < m_Re_height; i++) {
		for (j = 0; j < m_Re_width; j++) {
			m_OutputImage[i * m_Re_width + j] = (unsigned char)m_tempImage[i][j];
		}
	}
}


// 가장 인접한 이웃 화소 보간법
void CIMGKJY2020072101Doc::OnNearest()
{
	int i, j;
	int ZoomRate = 2; // 영상 확대 배율
	double** tempArray;
	m_Re_height = int(ZoomRate * m_height); // 확대된 영상의 높이
	m_Re_width = int(ZoomRate * m_width); // 확대된 영상의 너비
	m_Re_size = m_Re_height * m_Re_width;
	m_tempImage = Image2DMem(m_height, m_width);
	tempArray = Image2DMem(m_Re_height, m_Re_width);
	m_OutputImage = new unsigned char[m_Re_size];
	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			m_tempImage[i][j] = (double)m_InputImage[i * m_width + j];
		}
	}
	for (i = 0; i < m_Re_height; i++) {
		for (j = 0; j < m_Re_width; j++) {
			tempArray[i][j] = m_tempImage[i / ZoomRate][j / ZoomRate];
			// 이웃한 화소를 이용한 보간
		}
	}
	for (i = 0; i < m_Re_height; i++) {
		for (j = 0; j < m_Re_width; j++) {
			m_OutputImage[i * m_Re_width + j] = (unsigned char)tempArray[i][j];
		}
	}
}


// 양선형 보간법
void CIMGKJY2020072101Doc::OnBilinear()
{
	int i, j, point, i_H, i_W;
	unsigned char newValue;
	double ZoomRate = 2.0, r_H, r_W, s_H, s_W;
	double C1, C2, C3, C4;
	m_Re_height = (int)(m_height * ZoomRate); // 확대된 영상의 높이
	m_Re_width = (int)(m_width * ZoomRate); // 확대된 영상의 너비
	m_Re_size = m_Re_height * m_Re_width;
	m_tempImage = Image2DMem(m_height, m_width);
	m_OutputImage = new unsigned char[m_Re_size];
	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			m_tempImage[i][j] = (double)m_InputImage[i * m_width + j];
		}
	}

	for (i = 0; i < m_Re_height; i++) {
		for (j = 0; j < m_Re_width; j++) {
			r_H = i / ZoomRate;
			r_W = j / ZoomRate;
			i_H = (int)floor(r_H);
			i_W = (int)floor(r_W);
			s_H = r_H - i_H;
			s_W = r_W - i_W;
			if (i_H < 0 || i_H >= (m_height - 1) || i_W < 0
				|| i_W >= (m_width - 1))
			{
				point = i * m_Re_width + j;
				m_OutputImage[point] = 255;
			}
			else
			{
				C1 = (double)m_tempImage[i_H][i_W];
				C2 = (double)m_tempImage[i_H][i_W + 1];
				C3 = (double)m_tempImage[i_H + 1][i_W + 1];
				C4 = (double)m_tempImage[i_H + 1][i_W];
				newValue = (unsigned char)(C1 * (1 - s_H) * (1 - s_W)
					+ C2 * s_W * (1 - s_H) + C3 * s_W * s_H + C4 * (1 - s_W) * s_H);
				point = i * m_Re_width + j;
				m_OutputImage[point] = newValue;
			}
		}
	}
}


// 미디언 표현을 이용한 서브 샘플링 방법
void CIMGKJY2020072101Doc::OnMedianSub()
{
	int i, j, n, m, M = 2, index = 0; // M = 서브 샘플링 비율
	double* Mask, Value;
	Mask = new double[M * M]; // 마스크의 크기 결정

	m_Re_height = (m_height + 1) / M;
	m_Re_width = (m_width + 1) / M;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	m_tempImage = Image2DMem(m_height + 1, m_width + 1);

	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			m_tempImage[i][j] = (double)m_InputImage[i * m_width + j];
		}
	}

	for (i = 0; i < m_height - 1; i = i + M) {
		for (j = 0; j < m_width - 1; j = j + M) {
			for (n = 0; n < M; n++) {
				for (m = 0; m < M; m++) {
					Mask[n * M + m] = m_tempImage[i + n][j + m];
					// 입력 영상을 블록으로 잘라 마스크 배열에 저장
				}
			}
			
			OnBubleSort(Mask, M * M); // 마스크에 저장된 값을 정렬
			Value = Mask[(int)(M * M / 2)]; // 정렬된 값 중 가운데 값을 선택
			m_OutputImage[index] = (unsigned char)Value;
			
			// 가운데 값을 출력
			index++;
		}
	}
}


// 미디언 표현을 이용한 서브 샘플링 프로그램 - OnBubleSort
void CIMGKJY2020072101Doc::OnBubleSort(double* A, int MAX)
{
	// 데이터의 정렬을 처리하는 함수
	int i, j;
	for (i = 0; i < MAX; i++) {
		for (j = 0; j < MAX - 1; j++) {
			if (A[j] > A[j + 1]) {
				OnSwap(&A[j], &A[j + 1]);
			}
		}
	}
}


// 미디언 표현을 이용한 서브 샘플링 프로그램 - OnSwap
void CIMGKJY2020072101Doc::OnSwap(double* a, double* b)
{
	// 데이터 교환 함수
	double temp;
	temp = *a;
	*a = *b;
	*b = temp;
}


// 평균 표현을 이용한 서브 샘플링 프로그램
void CIMGKJY2020072101Doc::OnMeanSub()
{
	int i, j, n, m, M = 3, index = 0, k; // M = 서브 샘플링 비율
	double* Mask, Value, Sum = 0.0;
	Mask = new double[M * M];
	m_Re_height = (m_height + 1) / M;
	m_Re_width = (m_width + 1) / M;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	m_tempImage = Image2DMem(m_height + 1, m_width + 1);
	
	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			m_tempImage[i][j] = (double)m_InputImage[i * m_width + j];
		}
	}
	
	for (i = 0; i < m_height - 1; i = i + M) {
		for (j = 0; j < m_width - 1; j = j + M) {
			for (n = 0; n < M; n++) {
				for (m = 0; m < M; m++) {
					Mask[n * M + m] = m_tempImage[i + n][j + m];
				}
			}
			for (k = 0; k < M * M; k++) {
				Sum = Sum + Mask[k];
			}
			
			// 마스크에 저장된 값을 누적
			Value = (Sum / (M * M)); // 평균을 계산
			m_OutputImage[index] = (unsigned char)Value;
			// 평균값을 출력
			index++;
			Sum = 0.0;
		}
	}
}


// 이동 기하학 변환 프로그램
void CIMGKJY2020072101Doc::OnTranslation()
{
	int i, j;
	int h_pos = 30, w_pos = 130;
	double** tempArray;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	m_tempImage = Image2DMem(m_height, m_width);
	tempArray = Image2DMem(m_Re_height, m_Re_width);

	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			m_tempImage[i][j] = (double)m_InputImage[i * m_width + j];
		}
	}

	for (i = 0; i < m_height - h_pos; i++) {
		for (j = 0; j < m_width - w_pos; j++) {
			tempArray[i + h_pos][j + w_pos] = m_tempImage[i][j];
			// 입력 영상을 h_pos, w_pos만큼 이동
		}
	}
	for (i = 0; i < m_Re_height; i++) {
		for (j = 0; j < m_Re_width; j++) {
			m_OutputImage[i * m_Re_width + j] = (unsigned char)tempArray[i][j];
		}
	}
	delete[] m_tempImage;
	delete[] tempArray;
}


// 좌우 대칭 기하학 변환 프로그램
void CIMGKJY2020072101Doc::OnMirrorHor()
{
	int i, j;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];

	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			m_OutputImage[i * m_width + m_width - j - 1] = m_InputImage[i * m_width + j];
			// 입력 영상의 배열 값을 출력 영상을 위한
			// 배열의 수평축 뒷자리부터 저장
		}
	}
}


// 상하 대칭 기하학 변환 프로그램
void CIMGKJY2020072101Doc::OnMirrorVer()
{
	int i, j;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];

	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			m_OutputImage[(m_height - i - 1) * m_width + j] = m_InputImage[i * m_width + j];
			// 입력 영상의 값을 출력 영상을 위한 배열의 수직축 뒷자리부터 저장
		}
	}
}


// 영상의 회전 기하학 변환 프로그램
void CIMGKJY2020072101Doc::OnRotation()
{
	int i, j, CenterH, CenterW, newH, newW, degree = 45;
	// degree = 회전할 각도
	double Radian, PI, ** tempArray, Value;
	m_Re_height = m_height; // 회전된 영상의 높이
	m_Re_width = m_width; // 회전된 영상의 너비
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	PI = 3.14159265358979; // 회전각을 위한 PI 값
	Radian = (double)degree * PI / 180.0;
	// degree 값을 radian으로 변경
	CenterH = m_height / 2; // 영상의 중심 좌표
	CenterW = m_width / 2; // 영상의 중심 좌표
	m_tempImage = Image2DMem(m_height, m_width);
	tempArray = Image2DMem(m_Re_height, m_Re_width);
	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			m_tempImage[i][j] = (double)m_InputImage[i * m_width + j];
		}
	}

	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			// 회전 변환 행렬을 이용하여 회전하게 될 좌표 값 계산
			newH = (int)((i - CenterH) * cos(Radian)
				- (j - CenterW) * sin(Radian) + CenterH);
			newW = (int)((i - CenterH) * sin(Radian)
				+ (j - CenterW) * sin(Radian) + CenterW);
			if (newH < 0 || newH >= m_height) {
				// 회전된 좌표가 출력 영상을 위한 배열 값을 넘어갈 때
				Value = 0;
			}
			else if (newW <
				0
				|| newW >= m_width) {
				// 회전된 좌표가 출력 영상을 위한 배열 값을 넘어갈 때
				Value = 0;
			}
			else {
				Value = m_tempImage[newH][newW];
			} 
			tempArray[i][j] = Value;
		}
	}

	for (i = 0; i < m_Re_height; i++) {
		for (j = 0; j < m_Re_width; j++) {
			m_OutputImage[i * m_Re_width + j]
				= (unsigned char)tempArray[i][j];
		}
	}
	delete[] m_tempImage;
	delete[] tempArray;
}
