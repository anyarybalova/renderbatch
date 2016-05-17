// NewStart.cpp: archivo de implementación
//

#include "stdafx.h"
#include "Rend.h"
#include "NewStart.h"
#include "afxdialogex.h"



// Cuadro de diálogo de CNewStart

IMPLEMENT_DYNAMIC(CNewStart, CDialog)

CNewStart::CNewStart(CWnd* pParent/*=NULL*/)
	: CDialog(CNewStart::IDD, pParent)
{
	m_newStart = _T("");
	m_newEnd = _T("");
	m_newFile = _T("");
}

CNewStart::~CNewStart()
{
}

void CNewStart::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_NEWST_EDIT, m_newStart);
	DDX_Text(pDX, IDC_NW_END_EDIT, m_newEnd);
	DDX_Text(pDX, IDC_NW_FILE_EDIT, m_newFile);
}

/*CString CNewStart::GetNewStart(void)
{
CString st;
GetDlgItemText(IDC_NEWST_EDIT,st);
return st;
}
*/
BEGIN_MESSAGE_MAP(CNewStart, CDialog)
END_MESSAGE_MAP()


// Controladores de mensajes de CNewStart


BOOL CNewStart::OnInitDialog()
{
	
	HICON m_hIcon; 
	m_hIcon = AfxGetApp()->LoadIcon(IDI_EDIT); 
	SetIcon(m_hIcon, FALSE);		
	CMFCButton* pButtonCanc = (CMFCButton* )GetDlgItem(IDCANCEL);	
	pButtonCanc->SetIcon((HICON)LoadImage(AfxGetApp()->m_hInstance,
    MAKEINTRESOURCE(IDI_CANCEL),
    IMAGE_ICON, 16,16, LR_COLOR));
	CDialog::OnInitDialog();

	CMFCButton* pButtonOK = (CMFCButton* )GetDlgItem(IDOK);	
	pButtonOK->SetIcon((HICON)LoadImage(AfxGetApp()->m_hInstance,
    MAKEINTRESOURCE(IDI_Accept),
    IMAGE_ICON, 16,16, LR_COLOR));

	

	return TRUE;  // return TRUE unless you set the focus to a control
}
