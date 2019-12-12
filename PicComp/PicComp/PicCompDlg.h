
// PicCompDlg.h : 头文件
//

#pragma once


// CPicCompDlg 对话框
class CPicCompDlg : public CDialogEx
{
// 构造
public:
	CPicCompDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PICCOMP_DLG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
public:
	afx_msg void OnPaint();

	afx_msg void OnBnClickedBtnPic();
	CString m_strPicDir;
	int m_edt3msize;
	int m_edt2msize;
	int m_edt1msize;
	float m_f3mscale;
	float m_f2mscale;
	float m_f1mscale;
	afx_msg void OnBnClickedBtnFilemerge();

	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
