
// RendDlg.cpp: archivo de implementación
//

#include "stdafx.h"
#include "Rend.h"
#include "RendDlg.h"
#include "afxdialogex.h"
#include <array>
#include "Tlhelp32.h"
#include "winbase.h"
#include "windows.h"
#include "NewStart.h"






#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cuadro de diálogo de CRendDlg



CRendDlg::CRendDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRendDlg::IDD, pParent)

	, m_archivos(0)
{
	
	m_Items = 0;
	m_min = true;
	m_left_ly = 0;
	m_left_time = 0;
	m_done_ly = 0;
	m_done_time = 0;
	m_error_ly = 0;
	m_error_time = 0;
	m_archivos = 0;
}

void CRendDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_LAY, m_ListLayer);
	DDX_Control(pDX, IDC_RUN_BTN, m_RUN_BTN);
	DDX_Control(pDX, IDC_AGAIN_BTN, m_again);
	DDX_Control(pDX, IDC_SOUND_CHECK, m_ONsound);
	DDX_Text(pDX, IDC_DN_LY_EDIT, m_done_ly);
	DDX_Text(pDX, IDC_LFT_LY_EDIT, m_left_ly);
	DDX_Text(pDX, IDC_DN_TIME_EDIT, m_done_time);
	DDX_Text(pDX, IDC_LFT_TIME_EDIT, m_left_time);
	DDX_Text(pDX, IDC_ERR_LY_EDIT, m_error_ly);
	DDX_Text(pDX, IDC_ERR_TIME_EDIT, m_error_time);
	DDX_Text(pDX, IDC_ARCHIVOS_EDIT, m_archivos);
}

BEGIN_MESSAGE_MAP(CRendDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_PATH_BTN, &CRendDlg::OnBnClickedPathBtn)
	ON_BN_CLICKED(IDC_RUN_BTN, &CRendDlg::OnBnClickedRunBtn)
	ON_BN_CLICKED(IDC_STOP_BTN, &CRendDlg::OnBnClickedStopBtn)
	ON_BN_CLICKED(IDC_UP_BTN, &CRendDlg::OnBnClickedUpBtn)
	ON_BN_CLICKED(IDC_DOWN_BTN, &CRendDlg::OnBnClickedDownBtn)
	ON_BN_CLICKED(IDC_AGAIN_BTN, &CRendDlg::OnBnClickedAgainBtn)
	ON_BN_CLICKED(IDC_DEL_BTN, &CRendDlg::OnBnClickedDelBtn)
	ON_BN_CLICKED(IDC_ST_EDIT_BTN, &CRendDlg::OnBnClickedStEditBtn)
	ON_BN_CLICKED(IDC_SAVE_BTN, &CRendDlg::OnBnClickedSaveBtn)
	ON_BN_CLICKED(IDC_SORT_BTN, &CRendDlg::OnBnClickedSortBtn2)
	ON_BN_CLICKED(IDC_SOUND_BTN, &CRendDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BAT_BTN, &CRendDlg::OnBnClickedBatBtn)
	ON_BN_CLICKED(IDC_TXT_BTN, &CRendDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_DEL_OK_BTN, &CRendDlg::OnBnClickedDelOkBtn)
END_MESSAGE_MAP()


// Controladores de mensaje de CRendDlg

BOOL CRendDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// Establecer el icono para este cuadro de diálogo. El marco de trabajo realiza esta operación
	//  automáticamente cuando la ventana principal de la aplicación no es un cuadro de diálogo
	HICON hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_REND_PR));
	SetIcon(hIcon, TRUE);
	//SetIcon(hIcon,FALSE);
	m_ONsound.SetCheck(1);
	SetDlgItemText(IDC_SOUND_EDIT,_T("D://R1_batch//AVISO.wav"));
	

	CMFCButton* pButtonAg = (CMFCButton* )GetDlgItem(IDC_AGAIN_BTN);	
	pButtonAg->SetIcon((HICON)LoadImage(AfxGetApp()->m_hInstance,
      MAKEINTRESOURCE(IDI_AG),
      IMAGE_ICON, 24,24, LR_COLOR));


	CMFCButton* pButtonDel = (CMFCButton* )GetDlgItem(IDC_DEL_BTN);	
	pButtonDel->SetIcon((HICON)LoadImage(AfxGetApp()->m_hInstance,
      MAKEINTRESOURCE(IDI_DELETE),
      IMAGE_ICON, 24,24, LR_COLOR));

	CMFCButton* pButtonUP = (CMFCButton* )GetDlgItem(IDC_UP_BTN);	
	pButtonUP->SetIcon((HICON)LoadImage(AfxGetApp()->m_hInstance,
      MAKEINTRESOURCE(IDI_UP),
      IMAGE_ICON, 24,24, LR_COLOR));

	CMFCButton* pButtonDN = (CMFCButton* )GetDlgItem(IDC_DOWN_BTN);	
	pButtonDN->SetIcon((HICON)LoadImage(AfxGetApp()->m_hInstance,
      MAKEINTRESOURCE(IDI_DOWN),
      IMAGE_ICON, 24,24, LR_COLOR));
	GetDlgItem(IDC_STOP_BTN)->EnableWindow(FALSE);
	
	
	CMFCButton* pButtonED = (CMFCButton* )GetDlgItem(IDC_ST_EDIT_BTN);	
	pButtonED->SetIcon((HICON)LoadImage(AfxGetApp()->m_hInstance,
      MAKEINTRESOURCE(IDI_EDIT),
      IMAGE_ICON, 24,24, LR_COLOR));

	CMFCButton* pButtonPL = (CMFCButton* )GetDlgItem(IDC_RUN_BTN);	
	pButtonPL->SetIcon((HICON)LoadImage(AfxGetApp()->m_hInstance,
      MAKEINTRESOURCE(IDI_PLAY),
      IMAGE_ICON, 24,24, LR_COLOR));

	CMFCButton* pButtonSTOP = (CMFCButton* )GetDlgItem(IDC_STOP_BTN);	
	pButtonSTOP->SetIcon((HICON)LoadImage(AfxGetApp()->m_hInstance,
      MAKEINTRESOURCE(IDI_STOP),
      IMAGE_ICON, 24,24, LR_COLOR));

	
	CMFCButton* pButtonExc = (CMFCButton* )GetDlgItem(IDC_PATH_BTN);	
	pButtonExc->SetIcon((HICON)LoadImage(AfxGetApp()->m_hInstance,
      MAKEINTRESOURCE(IDI_EXCEL),
      IMAGE_ICON, 24,24, LR_COLOR));

	CMFCButton* pButtonBat = (CMFCButton* )GetDlgItem(IDC_BAT_BTN);	
	pButtonBat->SetIcon((HICON)LoadImage(AfxGetApp()->m_hInstance,
      MAKEINTRESOURCE(IDI_BAT),
      IMAGE_ICON, 24,24, LR_COLOR));

	CMFCButton* pButtonTxt = (CMFCButton* )GetDlgItem(IDC_TXT_BTN);	
	pButtonTxt->SetIcon((HICON)LoadImage(AfxGetApp()->m_hInstance,
      MAKEINTRESOURCE(IDI_TXT),
      IMAGE_ICON, 24,24, LR_COLOR));



	CMFCButton* pButtonCanc = (CMFCButton* )GetDlgItem(IDCANCEL);	
	pButtonCanc->SetIcon((HICON)LoadImage(AfxGetApp()->m_hInstance,
      MAKEINTRESOURCE(IDI_CANCEL),
      IMAGE_ICON, 24,24, LR_COLOR));

	CMFCButton* pButtonDelOK = (CMFCButton* )GetDlgItem(IDC_DEL_OK_BTN);	
	pButtonDelOK->SetIcon((HICON)LoadImage(AfxGetApp()->m_hInstance,
      MAKEINTRESOURCE(IDI_DEL_OK),
      IMAGE_ICON, 24,24, LR_COLOR));

	CMFCButton* pButtonSrt = (CMFCButton* )GetDlgItem(IDC_SORT_BTN);	
	pButtonSrt->SetIcon((HICON)LoadImage(AfxGetApp()->m_hInstance,
      MAKEINTRESOURCE(IDI_SORT),
      IMAGE_ICON, 24,24, LR_COLOR));

	CMFCButton* pButtonSave = (CMFCButton* )GetDlgItem(IDC_SAVE_BTN);	
	pButtonSave->SetIcon((HICON)LoadImage(AfxGetApp()->m_hInstance,
      MAKEINTRESOURCE(IDI_SAVE),
      IMAGE_ICON, 24,24, LR_COLOR));

		CMFCButton* pButtonSnd = (CMFCButton* )GetDlgItem(IDC_SOUND_BTN);	
	pButtonSnd->SetIcon((HICON)LoadImage(AfxGetApp()->m_hInstance,
      MAKEINTRESOURCE(IDI_SOUND),
      IMAGE_ICON, 24,24, LR_COLOR));

	GetDlgItem(IDC_STOP_BTN)->EnableWindow(FALSE);

	m_ListLayer.SetExtendedStyle(LVS_SHOWSELALWAYS|
		LVS_EX_ONECLICKACTIVATE	| LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP|LVS_EX_DOUBLEBUFFER);
	m_ListLayer.InsertColumn(0, _T("Layer"), LVCFMT_LEFT, 170, 1);
	m_ListLayer.InsertColumn(1, _T("Start"), LVCFMT_LEFT, 50, 1);
	m_ListLayer.InsertColumn(2, _T("End"), LVCFMT_LEFT, 50, 1);
	m_ListLayer.InsertColumn(3, _T("Total"), LVCFMT_CENTER, 50, 1);
	m_ListLayer.InsertColumn(4, _T("Time"), LVCFMT_CENTER, 60, 1);
	m_ListLayer.InsertColumn(5, _T("Archivo"), LVCFMT_CENTER, 180, 1);
	m_ListLayer.InsertColumn(6, _T("Estado"), LVCFMT_CENTER, 80, 1);
	m_ListLayer.InsertColumn(7, _T(" "), LVCFMT_LEFT, 0, 1);
	
	m_ListLayer.GetHeaderCtrl()->EnableWindow(false);

	
	return TRUE;  // Devuelve TRUE  a menos que establezca el foco en un control
}

// Si agrega un botón Minimizar al cuadro de diálogo, necesitará el siguiente código
//  para dibujar el icono. Para aplicaciones MFC que utilicen el modelo de documentos y vistas,
//  esta operación la realiza automáticamente el marco de trabajo.

void CRendDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // Contexto de dispositivo para dibujo

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Centrar icono en el rectángulo de cliente
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Dibujar el icono
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// El sistema llama a esta función para obtener el cursor que se muestra mientras el usuario arrastra
//  la ventana minimizada.
HCURSOR CRendDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CRendDlg::OnBnClickedPathBtn()
{
	/*para abrir muchos excel files*/

TCHAR szFilters[]= _T("MyType Files (*xlsx)|*.xlsx||All Files (*.*)|*.*||");

CFileDialog fileDlg(TRUE, NULL, NULL,OFN_FILEMUSTEXIST | OFN_HIDEREADONLY|OFN_ALLOWMULTISELECT, szFilters);
fileDlg.m_ofn.nMaxFile = MAX_PATH;

	if( fileDlg.DoModal ()==IDOK )
	{
	
	POSITION pos = fileDlg.GetStartPosition();

	if(pos) {

	do {
		CString PathName = fileDlg.GetNextPathName(pos);

		
			AbrirExcelFile(PathName);
			m_archivos++;
			SetDlgItemInt(IDC_ARCHIVOS_EDIT,m_archivos);
		//		AbrirTxtFile(PathName);
		
		//		AgregarALista(PathName);

	} while(pos);

	}
	}

	
	
}

void CRendDlg::AgregarALista(CString path)
{
	/*lee el archivo bat*/
CFile myFile;
char buffer[1024];
DWORD dwRead;
CFileException fileException;
//CString str;
CString linea;
CString aux;
CString aux2;
int i =0;
int tam =1024;
int rend = 0;
int c=0;
std::array<CString, 100> m_archis;//para contar archivos

if ( !myFile.Open( path, CFile::modeRead, &fileException ) )
{
   TRACE( _T("Can't open file %s, error = %u\n"),
      path, fileException.m_cause );
}

do{
dwRead = myFile.Read(buffer,1024);

CString str = CString(buffer);


str.TrimLeft(_T("%\n"));

aux = str;
int ar =0;
while (AfxExtractSubString(linea,str, i++, _T('%')))
{
    if ((rend = linea.Find(_T("render"))!=-1))
	{
		
			m_Items++;
			m_left_ly++;
			CString arch = InsertarItem(linea);
			
			bool hay = false;
		
			if(m_archis.empty())
			{m_archis[0] = arch;}
			else
			{
					while(m_archis[ar]!=_T(""))
					{
						if(m_archis[ar]==arch)
						{
							hay = true;
							break;
						}
						ar++;
					}//while
				if(!hay)
				{
				m_archis[ar]=arch;
				m_archivos++;
				}//if hay
			}//else
		
	}//if render

	}//while %


}while (dwRead > 0);

SetDlgItemInt(IDC_LFT_LY_EDIT,m_left_ly);
SetDlgItemInt(IDC_ARCHIVOS_EDIT,m_archivos);
 myFile.Close();
	 
}


CString CRendDlg::InsertarItem(CString linea) /* saca los items de la linea que se saca del archivo bat*/
{
	/*insierta los items en CListCtrl*/
CString strText;
int nColumnCount = 4;
CString palabra;
std::array<CString, 20> m_Palabras;

int i= 0;
CString LY;
CString AR;
int FR = 0;
CString s;
CString e, t;
CString com;
com = linea;
com.Remove('\n');
com = com + (_T(" "));
	while (AfxExtractSubString(palabra,linea, i++, _T(' ')))
	{
		m_Palabras[i] = palabra;
	}

	LY = m_Palabras[11];
	AR = m_Palabras [16];
	s = m_Palabras[3];
	e = m_Palabras[5];
	FR = _ttoi(e)-_ttoi(s);
	t.Format(TEXT("%d"), FR);
	
			
			int k = m_ListLayer.InsertItem(LVIF_TEXT | LVIF_STATE, m_ListLayer.GetItemCount(), LY, 
				(i % 2) == 0 ? LVIS_SELECTED : 0, LVIS_SELECTED, 0, 0);

		
			m_ListLayer.SetItemText(k, 1, s);//start
			m_ListLayer.SetItemText(k, 2, e);//end
			m_ListLayer.SetItemText(k, 3, t);//total
			m_ListLayer.SetItemText(k, 4, _T("-"));//tiempo en bat no hay tiempos
			m_ListLayer.SetItemText(k, 5, AR);//archivo
			m_ListLayer.SetItemText(k, 6, _T("-"));//estado
			m_ListLayer.SetItemText(k, 7, com);//render cmd

return AR;
}

void CRendDlg::OnBnClickedRunBtn()
{
	CString param;
	
	if(Vacia())
		return;
	LPTSTR status  = new TCHAR[20];
	LPTSTR szData = new TCHAR[150];
//	COleDateTime time_start;

	m_rendering = 1;
	GetDlgItem(IDC_STOP_BTN)->EnableWindow(TRUE);
	GetDlgItem(IDC_RUN_BTN)->EnableWindow(FALSE);

	//CrearArchivo();

	for(int i=0; i<m_ListLayer.GetItemCount();i++)
	{
		m_ListLayer.GetItemText(i,6,status,20);
		CString st = status;

		/*se hace si no esta ya renderizando o ya se renderizo*/
	if((m_rendering ==1)&&(st!=_T("Error"))&&(st!=_T("OK")))
	{
		//LPTSTR szData = param.GetBuffer();
		COleDateTime time_start = COleDateTime::GetCurrentTime();
		m_ListLayer.GetItemText(i,7,szData,150);
		m_ListLayer.SetItemText(i,6,_T("Rendering.."));
		
		
		CString cs_tiempo = m_ListLayer.GetItemText(i,4);
	
		
		if (RunRender(NULL, szData)==0)
		{
		m_left_ly--;
		m_done_ly++;
		m_left_time = m_left_time - _ttoi(cs_tiempo);
		m_done_time = m_done_time + _ttoi(cs_tiempo);
		m_ListLayer.SetItemText(i,6,_T("OK"));
		
		SetDlgItemInt(IDC_LFT_LY_EDIT,m_left_ly);
		SetDlgItemInt(IDC_LFT_TIME_EDIT,m_left_time);
		SetDlgItemInt(IDC_DN_LY_EDIT,m_done_ly);
		SetDlgItemInt(IDC_DN_TIME_EDIT,m_done_time);

		//GrabarInforme(i, time_start);
		}
		else
		{
		m_error_ly++;
		m_error_time = m_error_time + _ttoi(cs_tiempo);
		m_ListLayer.SetItemText(i,6,_T("Error"));

		SetDlgItemInt(IDC_ERR_LY_EDIT,m_error_ly);
		SetDlgItemInt(IDC_ERR_TIME_EDIT,m_error_time);	
		//GrabarInforme(i, time_start);
		}


		}//if rendering





	}

m_rendering = 0;

//OrdenarErrores();
GetDlgItemText(IDC_SOUND_EDIT,szData,200);

if(m_ONsound.GetCheck()==0)
Beep(523, 3000);
else
::ShellExecute(AfxGetMainWnd()->m_hWnd, _T("open"), szData, NULL, NULL, SW_NORMAL); 
GetDlgItem(IDC_STOP_BTN)->EnableWindow(FALSE);
GetDlgItem(IDC_RUN_BTN)->EnableWindow(TRUE);
}

DWORD CRendDlg::RunRender(TCHAR *AppName, TCHAR *CmdLine)
{
 
	DWORD res;
    PROCESS_INFORMATION processInformation;
	DWORD nStatus;
	STARTUPINFO startupInfo = {0};
	//int st[3] = {0};
    memset(&processInformation, 0, sizeof(processInformation));
    memset(&startupInfo, 0, sizeof(startupInfo));
    startupInfo.cb = sizeof(startupInfo);
	
    BOOL result;
    TCHAR tempCmdLine[MAX_PATH * 2];  //Needed since CreateProcessW may change the contents of CmdLine
    if (CmdLine != NULL)
    {
        _tcscpy_s(tempCmdLine, MAX_PATH *2, CmdLine);
        result = ::CreateProcess(AppName, tempCmdLine, NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &startupInfo, &processInformation);
	}
    else
    {
        result = ::CreateProcess(AppName, CmdLine, NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &startupInfo, &processInformation);
    }

    if (result == 0)
    {
        wprintf(L"ERROR: CreateProcess failed!");
    }
    else
    {

while(true) 
	{
    nStatus= 
		MsgWaitForMultipleObjects(1, &processInformation.hProcess, FALSE, INFINITE, QS_ALLINPUT);
	if (nStatus == WAIT_OBJECT_0) {  
        break;
    }
    MSG msg;     // else process some messages while waiting...
    while( PeekMessage(&msg,NULL,0,0,PM_REMOVE) ){
        DispatchMessage( &msg );
    }
}  
		
GetExitCodeProcess (processInformation.hProcess, &res); 

        CloseHandle( processInformation.hProcess );
        CloseHandle( processInformation.hThread );
    }

	return res;
}






void CRendDlg::OnBnClickedStopBtn()
{
	
	CString name = _T("Render.exe");
	m_rendering = 0;
	GetDlgItem(IDC_RUN_BTN)->EnableWindow(TRUE);
	KillProcess();
	GetDlgItem(IDC_STOP_BTN)->EnableWindow(FALSE);
	
	
}
	
	
BOOL CRendDlg::KillProcess()  
{
	DWORD res;
    PROCESS_INFORMATION prInfo;
	CString CmdLine = _T("taskkill /IM Render.exe");
	STARTUPINFO stInfo = {0};
	int st[3] = {0};
    memset(&prInfo, 0, sizeof(prInfo));
    memset(&stInfo, 0, sizeof(stInfo));
    stInfo.cb = sizeof(stInfo);
	
    BOOL result;
    TCHAR tempCmdLine[MAX_PATH * 2];  
    _tcscpy_s(tempCmdLine, MAX_PATH *2, CmdLine);
	result = ::CreateProcess(NULL, tempCmdLine, NULL, NULL, FALSE,CREATE_NO_WINDOW, NULL, NULL, &stInfo, &prInfo);
 if (result == 0)
	 wprintf(L"ERROR: CreateProcess failed!");
  else
    {
     res = WaitForSingleObject( prInfo.hProcess, INFINITE );
	
		BOOL result = GetExitCodeProcess(prInfo.hProcess, &res);
        CloseHandle( prInfo.hProcess );
        CloseHandle( prInfo.hThread );
    }
 return result;
}

void CRendDlg::OnBnClickedSortBtn2()
{

OrdenarPorArchivo();
/*
//ordenar por tiempo, sin importar a que archivo pertenece
	LPTSTR cz_time  = new TCHAR[20];
		if(Vacia())
		return;
				
if(m_min)
{
for (int k = 0;k<m_ListLayer.GetItemCount();k++)
{
	m_ListLayer.GetItemText(k,4,cz_time,10);
	CString cs_time = cz_time;
	int min = _ttoi(cs_time);
	int i = k;
	for(i; i<m_ListLayer.GetItemCount();i++)
		{
			m_ListLayer.GetItemText(i,4,cz_time,10);
			CString t = cz_time;
			int num = _ttoi(t);
			if (min>num)
				{
					min= num;
					MoveRow(i,k);
				}
			
		}//for chico
	}//for grande
m_min = false;
}//if min
else
{
	for (int k = 0;k<m_ListLayer.GetItemCount();k++)
	{
	m_ListLayer.GetItemText(k,4,cz_time,10);
	CString s_time = cz_time;
	int max = _ttoi(s_time);
	int i = k;
	for(i; i<m_ListLayer.GetItemCount();i++)
		{
			m_ListLayer.GetItemText(i,4,cz_time,10);
			CString tm = cz_time;
			int num = _ttoi(tm);
			if (max<num)
				{
					max= num;
					MoveRow(i,k);
				}
			
		}//for chico
	}//for grande
m_min = true;
}
m_ListLayer.SetFocus();
m_ListLayer.SetItemState(0, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
m_ListLayer.SetSelectionMark(0);
*/
}

void CRendDlg::OnBnClickedUpBtn()
{
	if(Vacia())
		return;
	/*int from = m_ListLayer.GetSelectionMark();
	if ((from-1)>=0)
	MoveRow(from,from-1);*/

	for (int i = 0; i<m_ListLayer.GetItemCount() ;i++)
	{
		if (m_ListLayer.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
		{
			
			if ((i-1)<0) return;
			MoveRow(i,i-1);

		}

	}

}


void CRendDlg::OnBnClickedDownBtn()
{
	if(Vacia())
		return;
	/*int from = m_ListLayer.GetSelectionMark();
	if(from< m_ListLayer.GetItemCount() - 1)
	MoveRow(from, from+1);
	*/
	int total = m_ListLayer.GetItemCount();
	for (int i = total-1 ; i >=0 ;i--)
	{
		if (m_ListLayer.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
		{
			if(i+1> total-1)return;
			MoveRow(i, i+1);

		}

	}
}


void CRendDlg::OnBnClickedAgainBtn()
{
	if(Vacia())
		return;

int row = m_ListLayer.GetSelectionMark();
if(row < 0)   return;

	for (int i = 0; i<m_ListLayer.GetItemCount() ;i++)
	{
		if (m_ListLayer.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
		{
			CString tiempo = m_ListLayer.GetItemText(i,4);

			switch (GetStatus(i))
			{
			case 'r' : break;
			case 'k' : 
					m_left_ly++;
					m_done_ly--;
					m_left_time = m_left_time + _ttoi(tiempo);
					m_done_time = m_done_time - _ttoi(tiempo);
					m_ListLayer.SetItemText(i,6,_T("-"));
					break;
			case 'e' :
					m_error_ly--;
					m_error_time = m_error_time - _ttoi(tiempo);
					m_ListLayer.SetItemText(i,6,_T("-"));
					break;
			default: break;
			}


			}
		}

 SetDlgItemInt(IDC_LFT_LY_EDIT,m_left_ly);
 SetDlgItemInt(IDC_LFT_TIME_EDIT,m_left_time);
 SetDlgItemInt(IDC_DN_LY_EDIT,m_done_ly);
 SetDlgItemInt(IDC_DN_TIME_EDIT,m_done_time);
 SetDlgItemInt(IDC_ERR_LY_EDIT,m_error_ly);
 SetDlgItemInt(IDC_ERR_TIME_EDIT,m_error_time);
}



void CRendDlg::OnBnClickedDelBtn()
{
	if(Vacia()) return;

int row = m_ListLayer.GetSelectionMark();
if(row < 0)   return;
int nCount = m_ListLayer.GetItemCount();

	for (int i = nCount -1; i >=0 ;i--)
	{
		if (m_ListLayer.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
		{
			CString tiempo = m_ListLayer.GetItemText(i,4);
			switch(GetStatus(i))
			{
			case 'r' : break;
			case 'k' : 
				m_done_ly--;
				m_done_time = m_done_time - _ttoi(tiempo);
				m_Items--;
				m_ListLayer.DeleteItem(i);
				break;
			case 'e' : 
				m_error_ly--;
				m_error_time = m_error_time - _ttoi(tiempo);
				m_left_ly--;
				m_left_time = m_left_time - _ttoi(tiempo);
				m_Items--;
				m_ListLayer.DeleteItem(i);
				break;
			default :
				m_left_ly--;
				m_left_time = m_left_time - _ttoi(tiempo);
				m_Items--;
				m_ListLayer.DeleteItem(i);

			}

			//nCount--;
		}

	}

 ContarArchivos();
 SetDlgItemInt(IDC_LFT_LY_EDIT,m_left_ly);
 SetDlgItemInt(IDC_LFT_TIME_EDIT,m_left_time);
  SetDlgItemInt(IDC_DN_LY_EDIT,m_done_ly);
 SetDlgItemInt(IDC_DN_TIME_EDIT,m_done_time);
  SetDlgItemInt(IDC_ERR_LY_EDIT,m_error_ly);
 SetDlgItemInt(IDC_ERR_TIME_EDIT,m_error_time);
 
}


void CRendDlg::MoveRow(int from, int to)
{

	if((m_ListLayer.GetItemText(from,6) != _T("Rendering.."))&&(m_ListLayer.GetItemText(to,6) != _T("Rendering..")))
{
	
        CString LY,START,END,TIME, FR,AR,ST,CM;
        LY = m_ListLayer.GetItemText(from,0);
		START = m_ListLayer.GetItemText(from,1);
		END = m_ListLayer.GetItemText(from,2);
        FR = m_ListLayer.GetItemText(from,3);
		TIME = m_ListLayer.GetItemText(from,4);
		AR = m_ListLayer.GetItemText(from,5);
		ST = m_ListLayer.GetItemText(from,6);
		CM = m_ListLayer.GetItemText(from,7);

        m_ListLayer.DeleteItem(from);

        m_ListLayer.InsertItem(to,LY);
		m_ListLayer.SetItemText(to,1,START);
		m_ListLayer.SetItemText(to,2,END);
        m_ListLayer.SetItemText(to,3,FR);
		m_ListLayer.SetItemText(to,4,TIME);
		m_ListLayer.SetItemText(to,5,AR);
		m_ListLayer.SetItemText(to,6,ST);
		m_ListLayer.SetItemText(to,7,CM);

        m_ListLayer.SetFocus();
		m_ListLayer.SetItemState(to, LVIS_SELECTED | LVIS_FOCUSED,LVIS_SELECTED | LVIS_FOCUSED);
		m_ListLayer.SetSelectionMark(to);
    
}
}


void CRendDlg::OnBnClickedStEditBtn()
{
if(Vacia()) return;

int FR;
CString t,e,st,file,tm;

int row = m_ListLayer.GetSelectionMark();

if(m_ListLayer.GetItemText(row,6) == _T("Rendering.."))
	return;

CString cs_oldSt = m_ListLayer.GetItemText(row,1);
CString cs_oldEnd = m_ListLayer.GetItemText(row,2);
CString cs_oldTot = m_ListLayer.GetItemText(row,3);
CString cs_oldTime = m_ListLayer.GetItemText(row,4);
CString cs_oldFile = m_ListLayer.GetItemText(row,5);


CNewStart dlgSt;

dlgSt.m_newStart = cs_oldSt;
dlgSt.m_newEnd = cs_oldEnd;
dlgSt.m_newFile = cs_oldFile;

	if(dlgSt.DoModal()==IDOK)
	{

	
		//saco los datos del start y verifico si es valido
		st = dlgSt.m_newStart;
		int ks = _ttoi(st);
		if (ks == 0)
		st = _T("0");
		m_ListLayer.SetItemText(row,1,st);

		//saco los datos del end y verifico si es valido
		e = dlgSt.m_newEnd;
		int ke = _ttoi(e);
		if (ke == 0)
		e= _T("0");
		m_ListLayer.SetItemText(row,2,e);
		
		//saco los datos del file y verifico si es valido
		file = dlgSt.m_newFile;
		if (file.IsEmpty()) 
		file = cs_oldFile;
		

		if(cs_oldFile!=file)//para contar cantidad archivos
		{
			bool hay = false;
			for(int i = 0;i < m_ListLayer.GetItemCount();i++)
			{
				CString arch = m_ListLayer.GetItemText(i,5);
				if(file == arch)
				{
					hay = true;
					i=m_ListLayer.GetItemCount();
				}
			}
			
			if(!hay)
			{
				m_archivos++;
				SetDlgItemInt(IDC_ARCHIVOS_EDIT,m_archivos);
			}
		}

		m_ListLayer.SetItemText(row,5,file);
	//	CString EN = end;
	//	FR = _ttoi(EN)-_ttoi(st);
		
		FR = ke - ks;
		t.Format(TEXT("%d"), FR);
		m_ListLayer.SetItemText(row,3,t);

		//deduzco el tiempo
		int i_oldTot = _ttoi(cs_oldTot);
		int i_oldTime = _ttoi(cs_oldTime);
		int newTime = (FR*i_oldTime)/i_oldTot;
		tm.Format(TEXT("%d"), newTime);
		m_ListLayer.SetItemText(row,4,tm);		
		
		switch(GetStatus(row))
		{
			case 'k' : m_done_time = m_done_time-i_oldTime+newTime;
						break;
			case '-' : m_left_time = m_left_time-i_oldTime+newTime;
						break;
			case 'e' : m_left_time = m_left_time-i_oldTime+newTime;
								
		}


		//modificar la linea de comando

		CString linea = m_ListLayer.GetItemText(row,7);
		CString com = linea;
		CString newCode = _T("-s ")+st+_T(" -e ")+e;
		CString oldCode = _T("-s ")+cs_oldSt+_T(" -e ")+cs_oldEnd;
		com.Replace(oldCode,newCode);
		com.Replace(cs_oldFile,file);

		m_ListLayer.SetItemText(row,7,com);	

		 SetDlgItemInt(IDC_DN_TIME_EDIT,m_done_time);
		 SetDlgItemInt(IDC_LFT_TIME_EDIT,m_left_time);
	}	
}


BOOL CRendDlg::Vacia()
{
int cant = m_ListLayer.GetItemCount();
if (cant == 0) return TRUE;
else return FALSE;
}

void CRendDlg::OnBnClickedSaveBtn()
{
	if(Vacia()) return;
	CFileException fileException;



	TCHAR szFilter[] = TEXT ("Text Files (*.txt)\0*.txt\0")  \
                       TEXT ("All Files (*.*)\0*.*\0\0") ;


	CFileDialog filedialog(FALSE, _T("txt"), _T("*.txt"), /*OFN_EXPLORER | OFN_PATHMUSTEXIST |*/ OFN_HIDEREADONLY
  | OFN_OVERWRITEPROMPT, CString(szFilter));


 if (filedialog.DoModal() == IDOK)
 {
	
		CStdioFile file_object;
		CString pathname =filedialog.GetPathName();
	if ( !file_object.Open(pathname,CFile::modeCreate|CFile::modeWrite))
		 {
		   TRACE( _T("Can't open file %s, error = %u\n"),
				 pathname, fileException.m_cause );
		}
	
		LPTSTR item  = new TCHAR[150];
		CString str; 
		CString sValue;
		for(int i=0; i<m_ListLayer.GetItemCount();i++)
		{
			for(int j=0; j<=7;j++)
				{
				m_ListLayer.GetItemText(i,j,item,150);
				CString cs_item = item;
				str += cs_item;
				str += _T(" ");			
				}//for columna
			str+=_T("\n");
			
		}//for items

		
  file_object.WriteString(str); // field separator

  file_object.Close();
			
	 }//if archivo
 
}

void CRendDlg::AbrirExcelFile(CString pathName)
{

	CApplication app;
	CWorkbook oBook;
	CWorkbooks oBooks;
	CWorksheets oSheets;
	CWorksheet oSheet;
	CRange oRange;
	
	LPDISPATCH lpDisp;

	COleVariant vResult;
	COleVariant archivo;
  COleVariant
         covTrue ((short)TRUE),
         covFalse ((short)FALSE);
        //CovOptional ((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
        //CovOptional ((long)DISP_E_PARAMNOTFOUND, VT_ERROR), covWidth ((short)40);
         COleVariant covOptional ((long)DISP_E_PARAMNOTFOUND, VT_ERROR), covWidth ((short)40);




   if(!app.CreateDispatch(_T("Excel.Application")))
   {
      AfxMessageBox(_T("Cannot start Excel and get Application object."));
      return;
   }
   else
{

	oBooks.AttachDispatch (app.get_Workbooks ());
	lpDisp = oBooks.Open( pathName, 
                                 covOptional, covOptional, covOptional, covOptional, 
                                 covOptional, covOptional, covOptional, covOptional, 
                                 covOptional, covOptional, covOptional, covOptional, covOptional, covOptional);
	
   oBook.AttachDispatch (lpDisp);
  oSheets.AttachDispatch (oBook.get_Worksheets ());
  lpDisp = oSheets.get_Item(COleVariant((short)1));
 // lpDisp = oBook.get_ActiveSheet ();
  oSheet.AttachDispatch (lpDisp);

   oRange.AttachDispatch (oSheet.get_Cells ());
   oRange.AttachDispatch (oRange.get_Item (COleVariant ((long)4),
		COleVariant ((long)2)).pdispVal);
	archivo = oRange.get_Value (covOptional);
	CString szarchivo(archivo);


  for (int i = 1;i<=59;i ++)
  {
  CString linea;
  int j = 8;
    //Read the value of the cell
    oRange.AttachDispatch (oSheet.get_Cells ());
    oRange.AttachDispatch (oRange.get_Item (COleVariant ((long)i),
		COleVariant ((long)j)).pdispVal);
	vResult = oRange.get_Value (covOptional);
	CString szdata(vResult);
	
	if (szdata == _T("x"))
	{
	CString LY,ST,END,TOT,TIME,FX,FY,OF;	
			for (int j = 1;j<=16;j ++)
			 {
				oRange.AttachDispatch (oSheet.get_Cells ());
				 oRange.AttachDispatch (oRange.get_Item (COleVariant ((long)i),
				COleVariant ((long)j)).pdispVal);
				vResult = oRange.get_Value (covOptional);
			    CString szdata(vResult);
				switch (j)
				{
					case 2:		
								LY = szdata;
								break;
					case 3:		
								ST = szdata;
								break;
					case 4:		
								END= szdata;
								break;					
					case 5:		
								TOT= szdata;
								break;		
					case 7:	
								TIME = szdata;
								break;	
					case 9:	
								FX = szdata;
								break;	

					case 10:	FY= szdata;
								break;		

					case 11:	OF = szdata;
								break;

					default:	break;
				}//switch

		}//for j
			CString com = _T("render -s ")+ST +_T(" -e ")+END+_T(" -x ")+FX+_T(" -y ")+FY+_T(" -rl ")+LY+_T(" -of ")+OF+_T(" -n 0 ")+szarchivo +_T(" ");
			int k = m_ListLayer.InsertItem(LVIF_TEXT | LVIF_STATE, m_ListLayer.GetItemCount(), LY, 
				(i % 2) == 0 ? LVIS_SELECTED : 0, LVIS_SELECTED, 0, 0);

		
			m_ListLayer.SetItemText(k, 1, ST);
			m_ListLayer.SetItemText(k, 2, END);
			m_ListLayer.SetItemText(k, 3, TOT);
			m_ListLayer.SetItemText(k, 4, TIME);
			m_ListLayer.SetItemText(k, 5, szarchivo);
			m_ListLayer.SetItemText(k, 6, _T("-"));
			m_ListLayer.SetItemText(k, 7, com);
			m_Items++;
			m_left_ly++;
			m_left_time = m_left_time + _ttoi(TIME);
	} //if render
  }
  

 SetDlgItemInt(IDC_LFT_LY_EDIT,m_left_ly);
 SetDlgItemInt(IDC_LFT_TIME_EDIT,m_left_time);
	oBook.Save();
	oBooks.Close();
	oBooks.ReleaseDispatch();
	 
	 app.Quit( );
	 app.ReleaseDispatch();
  
   }//else
}

void CRendDlg::AbrirTxtFile(CString pathName)
{

CFileException fileException;
CStdioFile f;
CString archivo;
CString aux,linea;
std::array<CString, 35> m_items;
std::array<CString, 30> m_archis; //para contar archivos
	
	if ( !f.Open( pathName, CFile::modeRead, &fileException ) )
{
   TRACE( _T("Can't open file %s, error = %u\n"),
      pathName, fileException.m_cause );
}

while(1)
{
	if(!f.ReadString(archivo))
		break;

int i=0;

while (AfxExtractSubString(linea,archivo, i++, _T('\n')))
{
CString item;
m_Items++;
int j=0;
	while (AfxExtractSubString(item,linea, j++, _T(' ')))
	{
		m_items[j] = item;
		if (j>8) 
		{
		m_items[8]+=_T(" ");
		m_items[8]+=item;
		
		}
	}		
	if(m_items[7]==_T("Rendering.."))
		m_items[7]=_T("-");
	int k = m_ListLayer.InsertItem(LVIF_TEXT | LVIF_STATE, m_ListLayer.GetItemCount(), m_items[1], 
				(i % 2) == 0 ? LVIS_SELECTED : 0, LVIS_SELECTED, 0, 0);

			m_ListLayer.SetItemText(k, 1, m_items[2]);//start
			m_ListLayer.SetItemText(k, 2, m_items[3]);//end
			m_ListLayer.SetItemText(k, 3, m_items[4]);//total
			m_ListLayer.SetItemText(k, 4, m_items[5]);//time
			m_ListLayer.SetItemText(k, 5, m_items[6]);//archivo
			m_ListLayer.SetItemText(k, 6, m_items[7]);//status
			m_ListLayer.SetItemText(k, 7, m_items[8]);//render cmd
			

			if (m_items[7]=="-")
			{
			m_left_ly++;
			m_left_time = m_left_time + _ttoi(m_items[4]);
			}
			else
				{
					if (m_items[7]=="Error")
						{
						m_error_ly++;
						m_error_time = m_error_time + _ttoi(m_items[4]);
						}
						else
						{
						m_done_ly++;
						m_done_time = m_done_time + _ttoi(m_items[4]);
						}
				}
			if(m_archis.empty())m_archis[0] = m_items[6];
			else
			{
				bool hay = false;
				int ar = 0;
				while(m_archis[ar]!=_T(""))
				{
					if(m_archis[ar]==m_items[6])
					{
						hay = true;
						break;
					}
					ar++;
				}//while

				if(!hay)
				{
					m_archis[ar] = m_items[6];
				m_archivos++;
				}
			}//else


}

//}while (dwRead > 0);
}

 SetDlgItemInt(IDC_ARCHIVOS_EDIT,m_archivos);
 SetDlgItemInt(IDC_LFT_LY_EDIT,m_left_ly);
 SetDlgItemInt(IDC_LFT_TIME_EDIT,m_left_time);
 SetDlgItemInt(IDC_DN_LY_EDIT,m_done_ly);
 SetDlgItemInt(IDC_DN_TIME_EDIT,m_done_time);
 SetDlgItemInt(IDC_ERR_LY_EDIT,m_error_ly);
 SetDlgItemInt(IDC_ERR_TIME_EDIT,m_error_time);
 f.Close();
}







void CRendDlg::OnBnClickedButton1()/*el boton que abre para buscar el audio*/
{

CString pathName;
CString fileName;


TCHAR szFilters[]= _T("MyType Files (*.avi;*mp3;*wav)|*.avi;*.mp3;*.wav||All Files (*.*)|*.*||");

CFileDialog fileDlg(TRUE, NULL, NULL,OFN_FILEMUSTEXIST | OFN_HIDEREADONLY|OFN_ALLOWMULTISELECT, szFilters);


	if( fileDlg.DoModal ()==IDOK )
	{
      pathName = fileDlg.GetPathName();
	  SetDlgItemText(IDC_SOUND_EDIT,pathName);
	}
}


void CRendDlg::OnBnClickedBatBtn()
{

TCHAR szFilters[]= _T("MyType Files (*bat)|*.bat||All Files (*.*)|*.*||");

CFileDialog fileBatDlg(TRUE, NULL, NULL,OFN_FILEMUSTEXIST | OFN_HIDEREADONLY|OFN_ALLOWMULTISELECT, szFilters);
fileBatDlg.m_ofn.nMaxFile = MAX_PATH;

	if( fileBatDlg.DoModal ()==IDOK )
	{
     // pathName = fileDlg.GetPathName();
	
	POSITION pos = fileBatDlg.GetStartPosition();

	if(pos) {

		do {
			CString PathName = fileBatDlg.GetNextPathName(pos);

		
			AgregarALista(PathName);
		
		} while(pos);
	}//if pos
	}// modal
}


void CRendDlg::OnBnClickedButton2()/*para abrir el load de lo grabado*/
{
TCHAR szFilters[]= _T("MyType Files (*txt)|*.txt||All Files (*.*)|*.*||");

CFileDialog fileTxtDlg(TRUE, NULL, NULL,OFN_FILEMUSTEXIST | OFN_HIDEREADONLY|OFN_ALLOWMULTISELECT, szFilters);
fileTxtDlg.m_ofn.nMaxFile = MAX_PATH;

	if( fileTxtDlg.DoModal ()==IDOK )
	{
     // pathName = fileDlg.GetPathName();
	
	POSITION pos = fileTxtDlg.GetStartPosition();

	if(pos) {

	do {
		CString PathName = fileTxtDlg.GetNextPathName(pos);

		AbrirTxtFile(PathName);
		

	} while(pos);

	}
	}
	
}


char CRendDlg::GetStatus(int i)
{
CString status = m_ListLayer.GetItemText(i,6);
  if(status=="OK") return 'k';
  if(status=="Error")return 'e';
  if(status=="Rendering..")return 'r';
  else return '-';
}
/*
void CRendDlg::CrearArchivo(void)
{
	CFileException fileException;

	//CStdioFile file_object;

	COleDateTime t1 = COleDateTime::GetCurrentTime();
	CString date,hora;
	date.Format(TEXT("%d_%d_%d__"),t1.GetDay(),t1.GetMonth(),t1.GetYear());
	hora.Format(TEXT("%d_%d"),t1.GetHour(),t1.GetMinute());

	CString pathname = _T("H:\\R1_batch\\2_INFORMES\\")+date+hora+_T(".txt");

	if ( !m_informe.Open(pathname,CFile::modeCreate|CFile::modeWrite))
		 {
		   TRACE( _T("Can't open file %s, error = %u\n"),
				 pathname, fileException.m_cause );
		}
	

}

void CRendDlg::GrabarInforme(int ik,COleDateTime ts)
{
COleDateTime te = COleDateTime::GetCurrentTime();
CString date_st,hora_st,date_end,hora_end;
date_st.Format(TEXT("%d/%d/%d"),ts.GetDay(),ts.GetMonth(),ts.GetYear());
date_end.Format(TEXT("%d/%d/%d"),te.GetDay(),te.GetMonth(),te.GetYear());
hora_st.Format(TEXT("%d:%d"),ts.GetHour(),ts.GetMinute());
hora_end.Format(TEXT("%d:%d"),te.GetHour(),te.GetMinute());


CString ly = _T("Layer : ")+m_ListLayer.GetItemText(ik,0);
CString ar = _T("\r\nArchivo : ")+m_ListLayer.GetItemText(ik,5);
CString re = _T("\r\nRender : ")+m_ListLayer.GetItemText(ik,6);
CString emp = _T("\r\nEmpezó : ")+date_st+_T(" a las ")+hora_st;
CString term = _T("\r\nTerminó : ")+date_end+_T(" a las ")+hora_end;
CString str = _T("\r\n\r\n**********************************************************************************\r\n\r\n");

str = str +ly+ar+re+emp+term;



m_informe.WriteString(str);

}
*/

void CRendDlg::OrdenarErrores()
{
int ult = m_ListLayer.GetItemCount();
ult--;
for(int i=0; i<=ult;i++)
	{
		for(int i=0; i<=ult;i++)
		{
			if(GetStatus(i)=='e')
			{
				MoveRow(i,ult);
			}	
	
		}
	}
}


void CRendDlg::OnBnClickedDelOkBtn()
{
	int ult = m_ListLayer.GetItemCount();

	for(int i=0; i<ult;i++)
	{
		if(GetStatus(i)=='k')
			m_ListLayer.DeleteItem(i);
	}
	ContarArchivos();
}


void CRendDlg::OrdenarPorArchivo()
{
	//ordena por tiempo por cada archivo
if(Vacia())
		return;
				
if(m_min)
{
for (int k = 0;k<m_ListLayer.GetItemCount();k++)
{
	CString archivo = m_ListLayer.GetItemText(k,5);
	CString cs_time = m_ListLayer.GetItemText(k,4);
	int min = _ttoi(cs_time);
	int i = k;
		while(i<m_ListLayer.GetItemCount())
			{
			CString new_arch = m_ListLayer.GetItemText(i,5);
			if(new_arch!=archivo)
				break;
			else
			{
			CString t = m_ListLayer.GetItemText(i,4);
			int num = _ttoi(t);
			if (min>num)
				{
					min= num;
					MoveRow(i,k);
				}
			i++;
			}//else == archivos
		
		}//while(true);
	}//for grande
m_min = false;
}//if min
else
{
	for (int k = 0;k<m_ListLayer.GetItemCount();k++)
	{
	CString archivo = m_ListLayer.GetItemText(k,5);
	CString cs_time = m_ListLayer.GetItemText(k,4);
	int max = _ttoi(cs_time);
	int i = k;
	while(i<m_ListLayer.GetItemCount())
			{
			CString new_arch = m_ListLayer.GetItemText(i,5);
			if(new_arch!=archivo)
				break;
			else
			{
			CString t = m_ListLayer.GetItemText(i,4);
			int num = _ttoi(t);
			if (max<num)
				{
					max= num;
					MoveRow(i,k);
				}
			i++;
			}//else == archivos
		}//while 
	}//for grande
m_min = true;
}
m_ListLayer.SetFocus();
m_ListLayer.SetItemState(0, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
m_ListLayer.SetSelectionMark(0);
}

void CRendDlg::ContarArchivos()
{
	int ar =0;
	m_archivos = 0;
	std::array<CString, 30> m_archis;
	m_archis[ar] = m_ListLayer.GetItemText(0,5);
	m_archivos++;
	int count = m_ListLayer.GetItemCount();
	for(int i = 0;i < count;i++)
	{
		CString arch =  m_ListLayer.GetItemText(i,5);
		bool hay = false;
			
		while(m_archis[ar]!=_T(""))
		{
			
				if(m_archis[ar] ==arch)
				{
					hay = true;
					break;
				} 
			if(!hay)
			{
				m_archis[ar] = arch;
				m_archivos++;
			}
		}//while
	}//for

	SetDlgItemInt(IDC_ARCHIVOS_EDIT,m_archivos);
}
