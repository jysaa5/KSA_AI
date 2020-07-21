#pragma once


// CQuantizationDlg 대화 상자

class CQuantizationDlg : public CDialog
{
	DECLARE_DYNAMIC(CQuantizationDlg)

public:
	CQuantizationDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CQuantizationDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_QuantBit;
};
