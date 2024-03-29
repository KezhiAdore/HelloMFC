﻿
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
	ON_BN_CLICKED(IDB_BUTTON_CONFIRM,&CHelloMFCView::OnButtonConfirm)
	

	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CHelloMFCView 构造/析构

CHelloMFCView::CHelloMFCView() noexcept
{
	// TODO: 在此处添加构造代码
	confirm = new CButton();
	set_col = new CEdit();
	set_row = new CEdit();
	setting.top = 10;	//顶部设置栏顶部间隙
	setting.bottom = 40;	//顶部设置栏底部间隙
	setting.row_left = 100;	//行输入框左x坐标
	setting.row_right = 200;	//行输入框右x坐标
	setting.col_left = 300;	//列输入框左x坐标
	setting.col_right = 400;	//列输入框右x坐标
	setting.button_left = 450;	//确认按钮左x坐标
	setting.button_right = 500;	//确认按钮右x坐标
	setting.edge = 1;	//编辑框和边框的间距
	row_text.SetRect(0, setting.top, 100, setting.bottom);	//行编辑框的CRect
	col_text.SetRect(200, setting.top, 300, setting.bottom);	//列编辑框的CRect
	edit_temp.edit = new CEdit();	//编辑表格中内容时产生的临时编辑框
	edit_temp.edit->Create(ES_CENTER | ES_MULTILINE, CRect(0, 0, 0, 0), this, IDB_EDIT_TEMP);
}

CHelloMFCView::~CHelloMFCView()
{
	//销毁 new 动态分配的空间
	if (confirm != NULL)
		delete confirm;
	if (set_col != NULL)
		delete set_col;
	if (set_row != NULL)
		delete set_row;
	if (edit_temp.edit != NULL)
		delete edit_temp.edit;
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

	//获取当前窗口大小
	GetClientRect(&clint_rect);
	pDoc->m_sum_width = clint_rect.right - (pDoc->m_edge_right + pDoc->m_edge_left);
	pDoc->m_sum_height = clint_rect.bottom - (pDoc->m_edge_top + pDoc->m_edge_bottom);

	//绘制表格竖线
	for (int i = 0; i < pDoc->m_cell_col + 1; i++)
	{
		pDC->MoveTo(pDoc->m_edge_left + i * pDoc->m_sum_width / pDoc->m_cell_col, pDoc->m_edge_top);
		pDC->LineTo(pDoc->m_edge_left + i * pDoc->m_sum_width / pDoc->m_cell_col, pDoc->m_edge_top + pDoc->m_sum_height);
	}

	//绘制表格横线
	for (int i = 0; i < pDoc->m_cell_row + 1; i++)
	{
		pDC->MoveTo(pDoc->m_edge_left, pDoc->m_edge_top + i * pDoc->m_sum_height / pDoc->m_cell_row);
		pDC->LineTo(pDoc->m_edge_left + pDoc->m_sum_width, pDoc->m_edge_top + i * pDoc->m_sum_height / pDoc->m_cell_row);
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

	//将表数据填入表格中
	for (int i = 0; i < pDoc->m_cell_row; i++)
	{
		for (int j = 0; j < pDoc->m_cell_col; j++)
		{
			//将data数组中存储的int型数据转化为字符串
			CString str_show;
			str_show.Format(_T("%d"), pDoc->data[i][j]);

			//在表格中居中绘制文本
			pDC->DrawText(str_show, CRect(
				pDoc->m_edge_left + j * pDoc->m_sum_width / pDoc->m_cell_col+setting.edge,
				pDoc->m_edge_top + i * pDoc->m_sum_height / pDoc->m_cell_row+setting.edge,
				pDoc->m_edge_left + (j + 1) * pDoc->m_sum_width / pDoc->m_cell_col-setting.edge,
				pDoc->m_edge_top + (i + 1) * pDoc->m_sum_height / pDoc->m_cell_row-setting.edge), 
				DT_CENTER | DT_SINGLELINE | DT_VCENTER);
		}
	}
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

	//初始化按钮和文本框
	set_row->Create(ES_CENTER|ES_MULTILINE, CRect(setting.row_left,setting.top,setting.row_right,setting.bottom), this, IDB_EDIT_SETROW);
	set_col->Create(ES_CENTER, CRect(setting.col_left, setting.top, setting.col_right, setting.bottom), this, IDB_EDIT_SETCOL);
	set_row->LimitText(2);
	set_col->LimitText(2);
	confirm->Create(_T("确认"), BS_PUSHBUTTON, CRect(setting.button_left, setting.top, setting.button_right,setting.bottom), this, IDB_BUTTON_CONFIRM);
	

	//显示按钮和文本框
	set_row->ShowWindow(SW_SHOW);
	set_col->ShowWindow(SW_SHOW);
	confirm->ShowWindow(SW_SHOW);
	
}


void CHelloMFCView::OnButtonConfirm()
{

	//读取文本框中的输入，以字符串形式存储
	set_row->GetWindowTextW(str_row);
	set_col->GetWindowTextW(str_col);

	//对Doc中的行列信息数据进行修改
	CHelloMFCDoc* pDoc = GetDocument();
	pDoc->m_cell_row = _ttoi(str_row)?_ttoi(str_row):pDoc->m_cell_row;
	pDoc->m_cell_col = _ttoi(str_col)? _ttoi(str_col):pDoc->m_cell_col;

	//若有编辑框则将其关闭
	if (edit_temp.flag)
	{
		edit_temp.edit->GetWindowTextW(edit_temp.str);
		//判断输入是否合法
		if (_ttoi(edit_temp.str) == 0 && edit_temp.str.Compare(_T("0")))
			MessageBox(_T("error:请输入数字"));
		else
		{
			//若合法则将数据写入表数据中
			pDoc->data[edit_temp.row][edit_temp.col] = _ttoi(edit_temp.str);
			edit_temp.flag = 0;
		}
		//关闭临时编辑框
		edit_temp.edit->DestroyWindow();
	}

	//若行列超出当前数组大小，则对数组进行扩容
	//获取当前大小和改变之后大小的最大值
	int max_row = max(pDoc->m_cell_row, pDoc->data.size());
	int max_col = max(pDoc->m_cell_col, pDoc->data[0].size());
	
	//对数组进行扩容
	pDoc->data.resize(max_row);
	for (int i = 0; i < max_row; i++)
		pDoc->data[i].resize(max_col);

	//视图刷新显示
	Invalidate();
}


void CHelloMFCView::OnLButtonDown(UINT nFlags, CPoint point)
{

	CView::OnLButtonDown(nFlags, point);
	CHelloMFCDoc* pDoc = GetDocument();

	//每次点击生成新窗口时：1.将上次的输入写入doc；2.关闭之前的编辑窗口
	if (edit_temp.flag)
	{
		edit_temp.edit->GetWindowTextW(edit_temp.str);
		//判断输入是否合法
		if (_ttoi(edit_temp.str) == 0 && edit_temp.str.Compare(_T("0")))
			MessageBox(_T("error:请输入数字"));
		else
		{
			//若合法则将数据写入表数据中
			pDoc->data[edit_temp.row][edit_temp.col] = _ttoi(edit_temp.str);
			edit_temp.flag = 0;
			//Invalidate();
		}
	}
	edit_temp.edit->DestroyWindow();
	Invalidate();

	//若点击出现在表格外则无效
	if (point.x<pDoc->m_edge_left || point.x>pDoc->m_sum_width + pDoc->m_edge_left)
		return;
	if (point.y<pDoc->m_edge_top || point.y>pDoc->m_sum_height + pDoc->m_edge_top)
		return;
		
	//计算点击所在的行和列
	edit_temp.col = (point.x - pDoc->m_edge_left) / (pDoc->m_sum_width / pDoc->m_cell_col);
	edit_temp.row = (point.y - pDoc->m_edge_top) / (pDoc->m_sum_height / pDoc->m_cell_row);

	//计算编辑框所在竖直中点

	int edit_center = (pDoc->m_edge_top + edit_temp.row * pDoc->m_sum_height / pDoc->m_cell_row + pDoc->m_edge_top + (edit_temp.row + 1) * pDoc->m_sum_height / pDoc->m_cell_row - setting.edge) / 2;
	//在该单元格处生成编辑框
	edit_temp.edit->Create(ES_AUTOHSCROLL | ES_CENTER | ES_MULTILINE, CRect(pDoc->m_edge_left + edit_temp.col * pDoc->m_sum_width / pDoc->m_cell_col + setting.edge,
		edit_center - 10,
		pDoc->m_edge_left + (edit_temp.col + 1) * pDoc->m_sum_width / pDoc->m_cell_col - setting.edge,
		edit_center + 10), this, IDB_EDIT_TEMP);

	//读取该单元格的int类型数据转化为字符串以便于显示
	edit_temp.str.Format(_T("%d"), pDoc->data[edit_temp.row][edit_temp.col]);

	//将该单元格的数据显示在编辑框中
	edit_temp.edit->SetWindowTextW(edit_temp.str);

	//选中所有的字符串以便于编辑
	edit_temp.edit->SetFocus();
	edit_temp.edit->SetSel(0, -1);
	edit_temp.edit->ShowWindow(SW_SHOW);
	edit_temp.flag = 1;
}


//重写打印函数
void CHelloMFCView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: 在此添加专用代码和/或调用基类
	//CView::OnPrint(pDC, pInfo);

	CHelloMFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	//获取打印页面的水平和竖直像素值
	int page_width = pDC->GetDeviceCaps(HORZRES);
	int page_height = pDC->GetDeviceCaps(VERTRES);
	
	//规定页边距
	int page_edge = 10;

	//计算表格水平宽度
	int tab_width = page_width - 2 * page_edge;
	//计算表格竖直长度
	int tab_height = (page_height - 2 * page_edge) / 20 * pDoc->m_cell_row;
	
	//在打印机中重新绘制表格竖线
	for (int i = 0; i < pDoc->m_cell_col + 1; i++)
	{
		pDC->MoveTo(page_edge + i * tab_width / pDoc->m_cell_col, page_edge);
		pDC->LineTo(page_edge + i * tab_width / pDoc->m_cell_col, page_edge + tab_height);
	}

	//重新绘制表格横线
	for (int i = 0; i < pDoc->m_cell_row + 1; i++)
	{
		pDC->MoveTo(page_edge, page_edge + i * tab_height / pDoc->m_cell_row);
		pDC->LineTo(page_edge + tab_width, page_edge + i * tab_height / pDoc->m_cell_row);
	}

	//将表数据填入表格中
	for (int i = 0; i < pDoc->m_cell_row; i++)
	{
		for (int j = 0; j < pDoc->m_cell_col; j++)
		{
			//将data数组中存储的int型数据转化为字符串
			CString str_show;
			str_show.Format(_T("%d"), pDoc->data[i][j]);

			//在表格中居中绘制文本
			pDC->DrawText(str_show, CRect(
				page_edge + j * tab_width / pDoc->m_cell_col + setting.edge * 5,
				page_edge + i * tab_height / pDoc->m_cell_row + setting.edge * 5,
				page_edge + (j + 1) * tab_width / pDoc->m_cell_col - setting.edge * 5,
				page_edge + (i + 1) * tab_height / pDoc->m_cell_row - setting.edge * 5),
				DT_CENTER | DT_SINGLELINE | DT_VCENTER);
		}
	}
}
