// StressTransformDlg.cpp: 구현 파일
//

#include "pch.h"
#include "IMG_KJY_20200721_01.h"
#include "StressTransformDlg.h"
#include "afxdialogex.h"


// StressTransformDlg 대화 상자

IMPLEMENT_DYNAMIC(StressTransformDlg, CDialog)

StressTransformDlg::StressTransformDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG5, pParent)
	, m_StartPoint(0)
	, m_EndPoint(0)
{

}

StressTransformDlg::~StressTransformDlg()
{
}

void StressTransformDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_StartPoint);
	DDX_Text(pDX, IDC_EDIT2, m_EndPoint);
	DDV_MinMaxInt(pDX, m_EndPoint, 0, 255);
}


BEGIN_MESSAGE_MAP(StressTransformDlg, CDialog)
	ON_COMMAND(ID_STRESS_TRANSFORM, &StressTransformDlg::OnStressTransform)
END_MESSAGE_MAP()


// StressTransformDlg 메시지 처리기


void StressTransformDlg::OnStressTransform()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}
