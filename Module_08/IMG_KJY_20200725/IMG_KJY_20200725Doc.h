
// IMG_KJY_20200725Doc.h: CIMGKJY20200725Doc 클래스의 인터페이스
//


#pragma once


class CIMGKJY20200725Doc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CIMGKJY20200725Doc() noexcept;
	DECLARE_DYNCREATE(CIMGKJY20200725Doc)

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CIMGKJY20200725Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);

	/*RAW 파일*/
	// Pointer for input image
	unsigned char* m_InputImage;
	unsigned char* m_OutputImage;


	/*BMP 파일*/
	// bmp파일의 이미지 내용 저장
	unsigned char* m_inImg;
	// bmp이미지 출력용 배열
	unsigned char* m_outImg;
	// 비트맵 파일 헤드 구조체
	BITMAPFILEHEADER dibHf;
	// 비트맵 영상헤드 구조체
	BITMAPINFOHEADER dibHi;
	// 팔레트 정보 구조체 배열
	RGBQUAD palRGB[256];
	// 가상변수로 구현화
	//virtual ~CIMGKJY20200725Doc();


	/*공통 사용*/
	// Width of input image
	int m_width;
	// Height of input image
	int m_height;
	// Total size of input image
	int m_size;

	int m_Re_width;
	int m_Re_height;
	int m_Re_size;

	void OnFrameSum();
	void OnFrameAnd();
	void OnNegaTransform();
	void OnFrameComb();

	// AND 결과
	unsigned char* and_result1;
	unsigned char* and_result2;
	
	// sum 결과
	unsigned char* sum_result;
	void OnFrameComb01();
};
