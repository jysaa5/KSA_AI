
// IMG_KJY_20200725View.h: CIMGKJY20200725View 클래스의 인터페이스
//

#pragma once


class CIMGKJY20200725View : public CView
{
protected: // serialization에서만 만들어집니다.
	CIMGKJY20200725View() noexcept;
	DECLARE_DYNCREATE(CIMGKJY20200725View)

// 특성입니다.
public:
	CIMGKJY20200725Doc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CIMGKJY20200725View();
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
public:
	// 비트맵 영상 헤드 선언
	BITMAPINFO* BmInfo;
	afx_msg void OnFrameSum();
	afx_msg void OnFrameAnd();
	afx_msg void OnNegaTransform();
	afx_msg void OnFrameComb();
	afx_msg void OnFrameComb01();
};

#ifndef _DEBUG  // IMG_KJY_20200725View.cpp의 디버그 버전
inline CIMGKJY20200725Doc* CIMGKJY20200725View::GetDocument() const
   { return reinterpret_cast<CIMGKJY20200725Doc*>(m_pDocument); }
#endif

