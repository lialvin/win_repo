
// PicCompDlg.h : ͷ�ļ�
//

#pragma once


// CPicCompDlg �Ի���
class CPicCompDlg : public CDialogEx
{
// ����
public:
	CPicCompDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PICCOMP_DLG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
