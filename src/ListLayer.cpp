// ListLayer.cpp: archivo de implementación
//

#include "stdafx.h"
#include "Rend.h"
#include "ListLayer.h"
#include <array>

// CListLayer

IMPLEMENT_DYNAMIC(CListLayer, CListCtrl)

CListLayer::CListLayer(int k, CString LY, CString AR, int FR)
{
	m_fila = k;
	m_Layer = LY;
	m_Archivo = AR;
	m_frames = FR;
}

CListLayer::CListLayer(CString linea, int k)
{
	CString l;
	CString s;
	CString palabra;
	CString e;
	CString aux;
	int i =0;
	int c,iE(0);
	std::array<CString, 20> m_Palabras;
	m_fila = k;
	m_frames = 0;
	
	l =linea;

	m_Command = linea;
	aux =linea;
	m_Command.Remove('\n');
	m_Command = m_Command + (_T(" "));
	//m_Command.SetAt(c,' ');
	while (AfxExtractSubString(palabra,linea, i++, _T(' ')))
	{
		m_Palabras[i] = palabra;
	}

	m_Layer = m_Palabras[11];
	m_Archivo = m_Palabras [17];
	s = m_Palabras[3];
	e = m_Palabras[5];
	m_frames = _ttoi(e)-_ttoi(s);

	
	
}


CListLayer::~CListLayer()
{
}

void CListLayer::SetStatus(int i)
{
 if (i==259)
	 m_Status = "OK";
 else 
	 m_Status = "Error";
}

BOOL CListLayer::MoveRow(int from, int to)
{
	CString auxLY;
	CString auxFR;
	CString auxAR;
	CString auxST;

	//Can't move to the same place, or from or to a negative index
	if(from == to || from < 0 || to < 0)
		return FALSE;
	//copiar cosas del TO
	auxLY = GetItemText(to, 0);
	auxFR = GetItemText(to, 1);
	auxAR = GetItemText(to, 2);
	auxST = GetItemText(to, 3);

	//copiar cosas del FROM a TO
	SetItemText(to,0,GetItemText(from,0));
	SetItemText(to,1,GetItemText(from,1));
	SetItemText(to,2,GetItemText(from,2));
	SetItemText(to,3,GetItemText(from,3));

	return FALSE;
}

BOOL CListLayer::CopyRow(int from, int to)
{	
	//Can't move to the same place, or from or to a negative index
	if(from == to || from < 0 || to < 0)
		return FALSE;
	//Copy the row to the new index
	InsertItem(to, GetItemText(from, 0));
	//If row has been inserted before original
	//increment the original
	if(from > to)
		from++;
	//Loop through subitems
/*	for(int i = 1; i < GetColumnCount(); i++)
	{
		SetItemText(to, i, GetItemText(from, i));
	}
	*/
	return TRUE;
}

BEGIN_MESSAGE_MAP(CListLayer, CListCtrl)
END_MESSAGE_MAP()



// Controladores de mensajes de CListLayer


