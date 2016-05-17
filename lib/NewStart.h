#pragma once
#include "afxwin.h"
#include "RendDlg.h"


// Cuadro de di�logo de CNewStart

class CNewStart : public CDialog
{
	DECLARE_DYNAMIC(CNewStart)

public:
	CNewStart(CWnd* pParent=NULL);   // Constructor est�ndar
	virtual ~CNewStart();
	CString GetNewStart();



// Datos del cuadro de di�logo
	enum { IDD = IDD_START_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX/DDV

	DECLARE_MESSAGE_MAP()
public:

	CString m_newStart;
	virtual BOOL OnInitDialog();
	CString m_newEnd;
	CString m_newFile;
};