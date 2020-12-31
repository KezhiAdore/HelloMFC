
// HelloMFCView.cpp: CHelloMFCView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "HelloMFC.h"
#endif

#include "HelloMFCDoc.h"
#include "HelloMFCView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHelloMFCView

IMPLEMENT_DYNCREATE(CHelloMFCView, CView)

BEGIN_MESSAGE_MAP(CHelloMFCView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CHelloMFCView 构造/析构

CHelloMFCView::CHelloMFCView() noexcept
{
	// TODO: 在此处添加构造代码
	confirm = new CButton();
	set_col = new CEdit();
	set_row = new CEdit();
	setting.top = 10;
	setting.bottom = 40;
	setting.row_left = 100;
	setting.row_right = 200;
	setting.col_left = 300;
	setting.col_right = 400;
	setting.button_left = 450;
	setting.button_right = 500;
	setting.edge = 1;
	row_text.SetRect(0, setting.top, 100, setting.bottom);
	col_text.SetRect(200, setting.top, 300, setting.bottom);
}

CHelloMFCView::~CHelloMFCView()
{
	if (confirm!=NULL)
		delete confirm;
	if (set_col!=NULL)
		delete set_col;
	if (set_row != NULL)
		delete set_row;
}

BOOL CHelloMFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CHelloMFCView 绘图

void CHelloMFCView::OnDraw(CDC* pDC)
{
	CHelloMFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码

	//获取当前窗口大小
	GetClientRect(&clint_rect);
	pDoc->m_sum_width = clint_rect.right - (pDoc->m_edge_right + pDoc->m_edge_left);
	pDoc->m_sum_height = clint_rect.bottom - (pDoc->m_edge_top + pDoc->m_edge_bottom);

	//绘制表格竖线
	for (int i = 0; i < pDoc->m_cell_col + 1; i++)
	{
		pDC->MoveTo(pDoc->m_edge_left + float(i) / pDoc->m_cell_col * pDoc->m_sum_width, pDoc->m_edge_top);
		pDC->LineTo(pDoc->m_edge_left + float(i) / pDoc->m_cell_col * pDoc->m_sum_width, pDoc->m_edge_top + pDoc->m_sum_height);
	}

	//绘制表格横线
	for (int i = 0; i < pDoc->m_cell_row + 1; i++)
	{
		pDC->MoveTo(pDoc->m_edge_left, pDoc->m_edge_top + float(i) / pDoc->m_cell_row * pDoc->m_sum_height);
		pDC->LineTo(pDoc->m_edge_left + pDoc->m_sum_width, pDoc->m_edge_top + float(i) / pDoc->m_cell_row * pDoc->m_sum_height);
	}

	//输出设置栏字符“行数设置 列数设置”
	pDC->DrawText(CString("行数设置"), row_text, DT_CENTER);
	pDC->DrawText(CString("列数设置"), col_text, DT_CENTER);

	//绘制文本框row_set
	pDC->MoveTo(setting.row_left- setting.edge, setting.top-setting.edge);
	pDC->LineTo(setting.row_right+ setting.edge, setting.top-setting.edge);
	pDC->LineTo(setting.row_right + setting.edge, setting.bottom + setting.edge);
	pDC->LineTo(setting.row_left - setting.edge, setting.bottom + setting.edge);
	pDC->LineTo(setting.row_left - setting.edge, setting.top - setting.edge);
	
	//绘制文本框col_set
	pDC->MoveTo(setting.col_left - setting.edge, setting.top - setting.edge);
	pDC->LineTo(setting.col_right + setting.edge, setting.top - setting.edge);
	pDC->LineTo(setting.col_right + setting.edge, setting.bottom + setting.edge);
	pDC->LineTo(setting.col_left - setting.edge, setting.bottom + setting.edge);
	pDC->LineTo(setting.col_left - setting.edge, setting.top - setting.edge);
	
}


// CHelloMFCView 打印

BOOL CHelloMFCView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CHelloMFCView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CHelloMFCView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CHelloMFCView 诊断

#ifdef _DEBUG
void CHelloMFCView::AssertValid() const
{
	CView::AssertValid();
}

void CHelloMFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CHelloMFCDoc* CHelloMFCView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHelloMFCDoc)));
	return (CHelloMFCDoc*)m_pDocument;
}
#endif //_DEBUG


// CHelloMFCView 消息处理程序

void CHelloMFCView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类

	//初始化按钮和文本框
	set_row->Create(ES_LEFT, CRect(setting.row_left,setting.top,setting.row_right,setting.bottom), this, IDB_EDIT_SETROW);
	set_col->Create(ES_LEFT, CRect(setting.col_left, setting.top, setting.col_right, setting.bottom), this, IDB_EDIT_SETCOL);
	confirm->Create(_T("确认"), BS_PUSHBUTTON, CRect(setting.button_left, setting.top, setting.button_right,setting.bottom), this, IDB_BUTTON_CONFIRM);
	

	//显示按钮和文本框
	set_row->ShowWindow(SW_SHOW);
	set_col->ShowWindow(SW_SHOW);
	confirm->ShowWindow(SW_SHOW);
	

}
