
// Rend.h: archivo de encabezado principal para la aplicaci�n PROJECT_NAME
//

#pragma once


#ifndef __AFXWIN_H__
	#error "incluir 'stdafx.h' antes de incluir este archivo para PCH"
#endif

#include "resource.h"		// S�mbolos principales


// CRendApp:
// Consulte la secci�n Rend.cpp para obtener informaci�n sobre la implementaci�n de esta clase
//

class CRendApp : public CWinApp
{
public:
	CRendApp();

// Reemplazos
public:
	virtual BOOL InitInstance();

// Implementaci�n

	DECLARE_MESSAGE_MAP()
};

extern CRendApp theApp;