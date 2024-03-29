﻿
// HelloMFCDoc.cpp: CHelloMFCDoc 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "HelloMFC.h"
#endif

#include "HelloMFCDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CHelloMFCDoc

IMPLEMENT_DYNCREATE(CHelloMFCDoc, CDocument)

BEGIN_MESSAGE_MAP(CHelloMFCDoc, CDocument)
END_MESSAGE_MAP()


// CHelloMFCDoc 构造/析构

CHelloMFCDoc::CHelloMFCDoc() noexcept
{
	// TODO: 在此添加一次性构造代码
	m_edge_top = 50;	//表格顶部间隙
	m_edge_bottom = 5;	//表格底部间隙
	m_edge_left = 10;	//表格左边间隙
	m_edge_right = 10;	//表格右边间隙
	m_sum_height = 250;	//表格总高度（任意）
	m_sum_width = 1000;	//表格总宽度（任意）
	m_cell_col = 8;	//表格列数（初始）
	m_cell_row = 5;	//表格行数（初始）
	data.resize(m_cell_row);	//表格数据（vector二维数组，可动态扩容）
	for (int i = 0; i < m_cell_row; i++)
		data[i].resize(m_cell_col);
}

CHelloMFCDoc::~CHelloMFCDoc()
{
	
}

BOOL CHelloMFCDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CHelloMFCDoc 序列化

void CHelloMFCDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CHelloMFCDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CHelloMFCDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CHelloMFCDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CHelloMFCDoc 诊断

#ifdef _DEBUG
void CHelloMFCDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CHelloMFCDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CHelloMFCDoc 命令
