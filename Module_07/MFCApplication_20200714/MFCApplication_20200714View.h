
// MFCApplication_20200714View.h: CMFCApplication20200714View 클래스의 인터페이스
//

#pragma once


class CMFCApplication20200714View : public CView
{
protected: // serialization에서만 만들어집니다.
	CMFCApplication20200714View() noexcept;
	DECLARE_DYNCREATE(CMFCApplication20200714View)

// 특성입니다.
public:
	CMFCApplication20200714Doc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	
	virtual void Copy2Array(DWORD* pArr, CImage& Img);
	virtual void CopyFromArray(CImage& Img, DWORD* pArr);
	virtual void SelectOneColor(DWORD* pArr, int nWidth, int nHeight, int nIdxRGB);
	virtual void Color2Gray(CImage& Img, char* pArr);
	virtual void CopyGray2Image(CImage& Img, char* pArr);

protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CMFCApplication20200714View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // MFCApplication_20200714View.cpp의 디버그 버전
inline CMFCApplication20200714Doc* CMFCApplication20200714View::GetDocument() const
   { return reinterpret_cast<CMFCApplication20200714Doc*>(m_pDocument); }
#endif

