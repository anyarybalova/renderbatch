
// RendDlg.h: archivo de encabezado
//

#pragma once
#include "CApplication.h"
#include "CRange.h"
#include "CWorkbook.h"
#include "CWorkbooks.h"
#include "CWorksheet.h"
#include "CWorksheets.h"
#include "afxcmn.h"
#include <list>
#include "afxwin.h"



// Cuadro de di�logo de CRendDlg
class CRendDlg : public CDialog
{
// Construcci�n
public:
	CRendDlg(CWnd* pParent = NULL);	// Constructor est�ndar
	

// Datos del cuadro de di�logo
	enum { IDD = IDD_REND_DIALOG };
//	std::list<CListLayer*> m_Lista;

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// Compatibilidad con DDX/DDV

private:
	int m_Items;
	int m_rendering;
	CBitmap again;
	BOOL m_min;
	CStdioFile m_informe;
	
// Implementaci�n
protected:
	HICON m_hIcon;
	CListCtrl *listLayer;
	// Funciones de asignaci�n de mensajes generadas
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	

public:
	afx_msg void OnBnClickedPathBtn();
	CListCtrl m_ListLayer;
	void AgregarALista(CString path);
	CString InsertarItem(CString linea);
	DWORD RunRender(TCHAR *App,TCHAR *Arg);
	void AbrirExcelFile(CString pathName);
	void AbrirTxtFile(CString pathName);
	char GetStatus(int i);
	int GetTime(int i);
	//void GrabarInforme(int i,COleDateTime time_start);
	//void CrearArchivo();
	afx_msg void OnBnClickedRunBtn();
	void OrdenarErrores();
	void OrdenarPorArchivo();
	void ContarArchivos();

	BOOL KillProcess(); 
	void MoveRow(int from,int to);
	BOOL Vacia();
	CButton m_RUN_BTN;
	afx_msg void OnBnClickedStopBtn();
	afx_msg void OnBnClickedUpBtn();
	afx_msg void OnBnClickedDownBtn();
	afx_msg void OnBnClickedAgainBtn();
	afx_msg void OnBnClickedDelBtn();
	afx_msg void OnBnClickedStEditBtn();
	CButton m_again;
	
	afx_msg void OnBnClickedSaveBtn();
	
	afx_msg void OnBnClickedSortBtn2();

	afx_msg void OnBnClickedButton1();
	CButton m_ONsound;
	afx_msg void OnBnClickedBatBtn();
	afx_msg void OnBnClickedButton2();
	int m_left_ly;
	int m_left_time;
	int m_done_ly;
	int m_done_time;
	int m_error_ly;
	int m_error_time;
	afx_msg void OnBnClickedDelOkBtn();
	int m_archivos;
};
