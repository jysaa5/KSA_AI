#pragma once


// StressTransformDlg 대화 상자

class StressTransformDlg : public CDialog
{
	DECLARE_DYNAMIC(StressTransformDlg)

public:
	StressTransformDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~StressTransformDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG5 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_StartPoint;
	int m_EndPoint;
	afx_msg void OnStressTransform();
};
