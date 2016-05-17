#pragma once


// CListLayer

class CListLayer : public CListCtrl
{
	DECLARE_DYNAMIC(CListLayer)

public:
	CListLayer(CString linea, int i);
	CListLayer(int k, CString LY, CString AR, int i);
	virtual ~CListLayer();
	enum { IDD = IDC_LIST_LAY};
	CString GetLayer()
	{return m_Layer;}
	CString GetFile()
	{return m_Archivo;}
	int GetFrames()
	{return m_frames;}
	CString GetCommand()
	{return m_Command;}
	int GetFila()
	{return m_fila;}
	void SetStatus(int i);
	BOOL MoveRow(int from, int to);
	BOOL CopyRow(int from, int to);

protected:
	DECLARE_MESSAGE_MAP()

private:
	int m_fila;
	CString m_Layer;
	int m_frames;
	CString m_Archivo;
	CString m_Command;
	CString m_Status;
};


