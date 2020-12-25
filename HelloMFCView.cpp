
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

}

CHelloMFCView::~CHelloMFCView()
{
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
	//绘制表格竖线
	for (int i = 0; i < pDoc->m_cell_col + 1; i++)
	{
		pDC->MoveTo(pDoc->m_edge_width + float(i) / pDoc->m_cell_col * pDoc->m_sum_width, pDoc->m_edge_height);
		pDC->LineTo(pDoc->m_edge_width + float(i) / pDoc->m_cell_col * pDoc->m_sum_width, pDoc->m_edge_height + pDoc->m_sum_height);
	}

	//绘制表格横线
	for (int i = 0; i < pDoc->m_cell_row + 1; i++)
	{
		pDC->MoveTo(pDoc->m_edge_width, pDoc->m_edge_height + float(i) / pDoc->m_cell_row * pDoc->m_sum_height);
		pDC->LineTo(pDoc->m_edge_width + pDoc->m_sum_width, pDoc->m_edge_height + float(i) / pDoc->m_cell_row * pDoc->m_sum_height);
	}
	CRect rect(20, 20, 200, 100);
	CString strwidth = CString("hello world");
	pDC->DrawText(strwidth, rect, 0);
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
