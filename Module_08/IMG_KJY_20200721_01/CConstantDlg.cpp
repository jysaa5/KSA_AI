// CConstantDlg.cpp: 구현 파일
//

#include "pch.h"
#include "IMG_KJY_20200721_01.h"
#include "CConstantDlg.h"
#include "afxdialogex.h"


// CConstantDlg 대화 상자

IMPLEMENT_DYNAMIC(CConstantDlg, CDialogEx)

CConstantDlg::CConstantDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG4, pParent)
	, m_Constant(0)

{

}

CConstantDlg::~CConstantDlg()
{
}

void CConstantDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_EDIT1, m_Constant);
	DDX_Text(pDX, IDC_EDIT1, m_Constant);
	DDV_MinMaxDouble(pDX, m_Constant, 0, 255);
}


BEGIN_MESSAGE_MAP(CConstantDlg, CDialogEx)
	ON_COMMAND(ID_SUB_CONSTANT, &CConstantDlg::OnSubConstant)
	ON_COMMAND(ID_SUM_CONSTANT, &CConstantDlg::OnSumConstant)
	ON_COMMAND(ID_MUL_CONSTANT, &CConstantDlg::OnMulConstant)
	ON_COMMAND(ID_DIV_CONSTANT, &CConstantDlg::OnDivConstant)
	ON_COMMAND(ID_AND_OPERATE, &CConstantDlg::OnAndOperate)
	ON_COMMAND(ID_OR_OPERATE, &CConstantDlg::OnOrOperate)
	ON_COMMAND(ID_XOR_OPERATE, &CConstantDlg::OnXorOperate)
	ON_COMMAND(ID_NEGA_TRANSFORM, &CConstantDlg::OnNegaTransform)
	ON_COMMAND(ID_GAMMA_CORRECTION, &CConstantDlg::OnGammaCorrection)
	ON_COMMAND(ID_BINARIZATION, &CConstantDlg::OnBinarization)
END_MESSAGE_MAP()


// CConstantDlg 메시지 처리기


void CConstantDlg::OnSubConstant()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CConstantDlg::OnSumConstant()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CConstantDlg::OnMulConstant()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CConstantDlg::OnDivConstant()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CConstantDlg::OnAndOperate()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CConstantDlg::OnOrOperate()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CConstantDlg::OnXorOperate()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CConstantDlg::OnNegaTransform()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CConstantDlg::OnGammaCorrection()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CConstantDlg::OnBinarization()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}
