
// HelloMFCDoc.h: CHelloMFCDoc 类的接口
//


#pragma once


class CHelloMFCDoc : public CDocument
{
protected: // 仅从序列化创建
	CHelloMFCDoc() noexcept;
	DECLARE_DYNCREATE(CHelloMFCDoc)

// 特性
public:
	int m_edge_width;
	int m_edge_height;
	int m_sum_width;
	int m_sum_height;
	int m_cell_col;
	int m_cell_row;

// 操作
public:

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CHelloMFCDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
