
// Rend.h: archivo de encabezado principal para la aplicación PROJECT_NAME
//

#pragma once


#ifndef __AFXWIN_H__
	#error "incluir 'stdafx.h' antes de incluir este archivo para PCH"
#endif

#include "resource.h"		// Símbolos principales


// CRendApp:
// Consulte la sección Rend.cpp para obtener información sobre la implementación de esta clase
//

class CRendApp : public CWinApp
{
public:
	CRendApp();

// Reemplazos
public:
	virtual BOOL InitInstance();

// Implementación

	DECLARE_MESSAGE_MAP()
};

extern CRendApp theApp;