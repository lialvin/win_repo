
// PicCompDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PicComp.h"
#include "PicCompDlg.h"
#include "afxdialogex.h"
#include <vector>
#include <string>


#include <math.h>
#include <opencv2/opencv.hpp> // ��Ҫ���� _DEBUG ǰ��
#include <opencv2\imgproc\imgproc.hpp> 
#include <opencv2\imgproc\types_c.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/* 
#pragma comment(lib,"opencv_core231.lib")
#pragma comment(lib,"opencv_highgui231.lib")
#pragma comment(lib,"opencv_calib3d231.lib")
#pragma comment(lib,"opencv_contrib231.lib")

#pragma comment(lib,"opencv_features2d231.lib")
#pragma comment(lib,"opencv_flann231.lib")
#pragma comment(lib,"opencv_gpu231.lib")
#pragma comment(lib,"opencv_highgui231.lib")
#pragma comment(lib,"opencv_imgproc231.lib")
#pragma comment(lib,"opencv_legacy231.lib")
#pragma comment(lib,"opencv_ml231.lib")
#pragma comment(lib,"opencv_objdetect231.lib")
#pragma comment(lib,"opencv_ts231.lib")
#pragma comment(lib,"opencv_video231.lib")
*/
FILE  * g_merge_fp;

 int test_pic(const char *  picfile,int size  );
// CPicCompDlg �Ի���

 void FindDirFileNoFormat(std::string dir, std::vector<std::string> &filePath);
 ULONGLONG  GetFileSize(std::string filePath);


 CPicCompDlg *   g_pThisPicDlg = NULL;
CPicCompDlg::CPicCompDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PICCOMP_DLG, pParent)
	, m_strPicDir(_T(""))
	, m_edt3msize(0)
	, m_edt2msize(0)
	, m_edt1msize(0)
	, m_f3mscale(0)
	, m_f2mscale(0)
	, m_f1mscale(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	g_pThisPicDlg = this;
}

void CPicCompDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDT_DIR, m_strPicDir);
	DDX_Text(pDX, IDC_EDT3M, m_edt3msize);
	DDX_Text(pDX, IDC_EDT2M, m_edt2msize);
	DDX_Text(pDX, IDC_EDT1M, m_edt1msize);
	DDX_Text(pDX, IDC_EDT3SCALE, m_f3mscale);
	DDX_Text(pDX, IDC_EDT2SCALE, m_f2mscale);
	DDX_Text(pDX, IDC_EDT1SCALE, m_f1mscale);
}

BEGIN_MESSAGE_MAP(CPicCompDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_PIC, &CPicCompDlg::OnBnClickedBtnPic)
	ON_BN_CLICKED(IDC_BTN_FILEMERGE, &CPicCompDlg::OnBnClickedBtnFilemerge)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CPicCompDlg ��Ϣ�������

BOOL CPicCompDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

//using namespace cv;



int test_pic2(const char *  picfile, int size)
{
	IplImage *src = 0;			//Դͼ��ָ��
	IplImage *dst = 0;			//Ŀ��ͼ��ָ��
	float scale = 0.4;		    //���ű���Ϊ0.618��
	CvSize dst_cvsize;			//Ŀ��ͼ��ߴ�
	if (strstr(picfile, ".jpg") || strstr(picfile, ".JPG"))
	{
	}
	else
	{
		return 0;
	}
	if (size > g_pThisPicDlg->m_edt3msize * 1000) //2000
	{
		scale = g_pThisPicDlg->m_f3mscale;

	}

	else if (size > g_pThisPicDlg->m_edt2msize * 1000) //
	{
		scale = g_pThisPicDlg->m_f2mscale;
	}
	else if (size > g_pThisPicDlg->m_edt1msize * 1000) //
	{
		scale = g_pThisPicDlg->m_f1mscale;
	}
	else
		return 0;

	if (scale>0.9999 || scale< 0.1)
		return 0;
	
	if (picfile != NULL)
	{
		//src = cv::cvLoadImage(picfile, -1);
		//��������д�������Ҫ�򿪵�ͼƬ�������˳�������ע�͵�����һ�У�
		//return -1;
	}
	else
	{
		//src = cvLoadImage("tiger.jpg");    //���빤��Ŀ¼���ļ���Ϊ��tiger.jpg����ͼƬ��
	}

	dst_cvsize.width = src->width * scale;		//Ŀ��ͼ��Ŀ�ΪԴͼ����scale��
	dst_cvsize.height = src->height * scale;	//Ŀ��ͼ��ĸ�ΪԴͼ��ߵ�scale��

	dst = cvCreateImage(dst_cvsize, src->depth, src->nChannels);	//����Ŀ��ͼ��
	//cvResize(src, dst, CV_INTER_LINEAR);	//����Դͼ��Ŀ��ͼ��
	
											//cvNamedWindow( "src",   CV_WINDOW_AUTOSIZE );	//����������ʾԴͼ��Ĵ���
											//cvNamedWindow( "dst",   CV_WINDOW_AUTOSIZE );	//����������ʾĿ��ͼ��Ĵ���


											//cvShowImage( "src", src );		��ʾԴͼ��
											//cvShowImage( "dst", dst );		//��ʾĿ��ͼ��

											//cvWaitKey(-1);		//�ȴ��û���Ӧ

	cvReleaseImage(&src);	//�ͷ�Դͼ��ռ�õ��ڴ�

	//cvSaveImage(picfile, dst);

	cvReleaseImage(&dst);	//�ͷ�Ŀ��ͼ��ռ�õ��ڴ�
							//cvDestroyWindow( "src" );	//���ٴ��ڡ�src��
							//cvDestroyWindow( "dst" );	//���ٴ��ڡ�dst��
							//void cvDestroyAllWindows(void);

	return 0;
}

int test_pic(const char *  picfile,int size  )
{
	
	cv::Mat src;
	cv::Mat dst;
    //IplImage *src = 0;			//Դͼ��ָ��
    //IplImage *dst = 0;			//Ŀ��ͼ��ָ��
    float scale = 0.4;		    //���ű���Ϊ0.618��
    //CvSize dst_cvsize;			//Ŀ��ͼ��ߴ�

	if(strstr(picfile,".jpg") || strstr(picfile,".JPG"))
	{
	}
	else
	{
		return 0;
	}
	if(size > g_pThisPicDlg->m_edt3msize*1000) //2000
	{
		scale =g_pThisPicDlg->m_f3mscale;	
		
	}
	
	else if(size > g_pThisPicDlg->m_edt2msize*1000) //
	{
		scale = g_pThisPicDlg->m_f2mscale;	
	}
	else if(size > g_pThisPicDlg->m_edt1msize*1000) //
	{
		scale = g_pThisPicDlg->m_f1mscale;	
	}
	else 
		return 0;
	
	if(scale>0.9999||scale< 0.1 )
		return 0;
	
    // the first command line parameter must be image file name 
    if ( picfile !=NULL  )
    {	
		src = cv::imread(picfile);
		if (src.empty()) {
			throw("Faild open file.");
		}
    }
    else
    {
        src = cv::imread("tiger.jpg");  //���빤��Ŀ¼���ļ���Ϊ��tiger.jpg����ͼƬ��
    }
 
	int width = static_cast<float>(src.cols*scale);
	//������Ҫ���������С��Ŀ�ȣ�src.colsΪԭͼ��Ŀ�ȣ�����80%��õ���Ҫ�Ĵ�С����ǿ��ת����float��
	int height = static_cast<float>(src.rows*scale);
	//������Ҫ���������С��ĸ߶ȣ�src.colsΪԭͼ��ĸ߶ȣ�����80%��õ���Ҫ�Ĵ�С����ǿ��ת����float��

	cv::resize(src, dst, cv::Size(width, height), cv::INTER_AREA);
	cv::imwrite(picfile, dst);
	
    return 0;
}

void CPicCompDlg::OnBnClickedBtnPic()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	char szPicDir[100] = {""};	
	this->UpdateData();
	CW2A  szIpObj(m_strPicDir);
	strcpy_s(szPicDir, szIpObj);
	g_pThisPicDlg=this;
	std::vector<std::string> filePath;
	FindDirFileNoFormat(szPicDir, filePath);
	//visit(szPicDir,1);  
}

//����Ŀ¼�����е��ļ���
void FindFolder(std::string dir, std::vector<std::string> &folderPath)
{
	CFileFind fileFinder;
	CString filePath = CString(dir.c_str()) + _T("\\*.*");

	BOOL bFinished = fileFinder.FindFile(filePath);
	while (bFinished)  //ÿ��ѭ����Ӧһ�����Ŀ¼
	{
		bFinished = fileFinder.FindNextFile();
		if (fileFinder.IsDirectory() && !fileFinder.IsDots())  //fileFinder.IsDots()ʶ��"."�ļ���".."�ļ�
		{
			CString filePath = fileFinder.GetFilePath();			
			std::string filep = CT2A(filePath);
			folderPath.push_back(filep);			
			filePath.ReleaseBuffer();
		}
	}

	fileFinder.Close();
}

//����Ŀ¼�����е��ļ�(������Ŀ¼��Ŀ¼)	
void FindDirFileNoFormat(std::string dir, std::vector<std::string> &filePath)
{
	CFileFind fileFinder;
	CString path = CString(dir.c_str()) + _T("\\*.*");

	BOOL bFinished = fileFinder.FindFile(path);
	while (bFinished)  //ÿ��ѭ����Ӧһ�����Ŀ¼
	{
		bFinished = fileFinder.FindNextFile();
		if (fileFinder.IsDirectory() || fileFinder.IsDots())  //fileFinder.IsDots()ʶ��"."�ļ���".."�ļ�
		{
			continue;
		}
		else
		{
			CString findPath = fileFinder.GetFilePath();
			std::string filep = CT2A(findPath);
			long fileSize = GetFileSize(filep);
			test_pic(filep.c_str(), fileSize);
			filePath.push_back(filep);
			findPath.ReleaseBuffer();
		}
	}

	fileFinder.Close();
}

//����Ŀ¼�����е��ļ�(����Ŀ¼��Ŀ¼)	
void FindAllFileNoFormat(std::string dir, std::vector<std::string> &filePath)
{
	CFileFind fileFinder;
	CString path = CString(dir.c_str()) + _T("\\*.*");

	BOOL bFinished = fileFinder.FindFile(path);
	while (bFinished)  //ÿ��ѭ����Ӧһ�����Ŀ¼
	{
		bFinished = fileFinder.FindNextFile();

		// ���� . �� .. ; �������������ѭ���У�����
		if (fileFinder.IsDots())
		{
			continue;
		}

		//
		if (fileFinder.IsDirectory())
		{
			CString findPath = fileFinder.GetFilePath();
			std::string subdir = CT2A(findPath);  //findPath.GetBuffer();
			FindAllFileNoFormat(subdir, filePath);
			findPath.ReleaseBuffer();
		}
		else
		{
			CString findPath = fileFinder.GetFilePath();
			std::string filep = CT2A(findPath);
			filePath.push_back(filep);
			findPath.ReleaseBuffer();
		}
	}

	fileFinder.Close();
}

// ����Ŀ¼��ĳһ�����ļ� (������Ŀ¼��Ŀ¼)
void FindDirFile(std::string dir, std::string format, std::vector<std::string> &filePath)
{
	CFileFind fileFinder;
	CString path = CString(dir.c_str()) + _T("\\*") + CString(format.c_str());

	BOOL bFinished = fileFinder.FindFile(path);
	while (bFinished)  //ÿ��ѭ����Ӧһ�����Ŀ¼
	{
		bFinished = fileFinder.FindNextFile();
		if (fileFinder.IsDirectory() && !fileFinder.IsDots())  //fileFinder.IsDots()ʶ��"."�ļ���".."�ļ�
		{
			continue;
		}
		else
		{
			CString findPath = fileFinder.GetFilePath();
			std::string filep = CT2A(findPath);
			filePath.push_back(filep);
			findPath.ReleaseBuffer();
		}
	}

	fileFinder.Close();
}

ULONGLONG  GetFileSize(std::string filePath)
{
	CFileStatus status;
	CString filep(filePath.c_str());
	CFile::GetStatus(filep, status);
	ULONGLONG lSizeOfFile;
	lSizeOfFile = status.m_size;
	return lSizeOfFile;
}
//�õ��ļ�·���ĸ�ʽ��׺
std::string GetPathFormat(std::string filePath)
{
	std::string format = filePath;
	size_t p = filePath.find_last_of('.');
	if (p == -1)
	{
		return std::string();
	}
	format.erase(0, p);
	return format;
}

// ����Ŀ¼��ĳһ�����ļ� (����Ŀ¼��Ŀ¼)	
void FindDirAllFileEx(std::string dir, std::vector<std::string> &format, std::vector<std::string>& filePath)
{
	CFileFind fileFinder;
	CString path = CString(dir.c_str()) + _T("\\*.*");

	BOOL bFinished = fileFinder.FindFile(path);
	while (bFinished)  //ÿ��ѭ����Ӧһ�����Ŀ¼
	{
		bFinished = fileFinder.FindNextFile();

		// ���� . �� .. ; �������������ѭ���У�����
		if (fileFinder.IsDots())
		{
			continue;
		}

		if (fileFinder.IsDirectory())
		{
			CString findPath = fileFinder.GetFilePath();
			std::string subdir = CT2A(findPath); //.GetBuffer();
			FindDirAllFileEx(subdir, format, filePath);
			findPath.ReleaseBuffer();
		}
		else
		{
			//��ȡ�ļ�����
			CString findPath = fileFinder.GetFilePath();
			
			std::string file = CT2A(findPath); //.GetBuffer();
			std::string postfix = GetPathFormat(file);

			bool flag = false;
			for (auto it : format)
			{
				if (_stricmp(it.c_str(), postfix.c_str()) == 0)
				{
					flag = true;
					break;
				}
			}

			if (flag)
			{
				filePath.push_back(file);
			}

			findPath.ReleaseBuffer();
		}
	}

	fileFinder.Close();
}


/*
��δ��װopencv����������opencv���������

 �½�һ���հ���Ŀ��win32����̨��Ŀ���������-ѡ��-VC++Ŀ¼��������ͼ��ʾ�����Ŀ¼��
 ��ִ���ļ�Ŀ¼
 F:\opencv\build\x86\vc9\bin
 ���ļ�
 F:\opencv\build\x86\vc9\lib
�����ļ�
 F:\opencv\build\include
 ��opecv dll������ debugĿ¼��
*/
int g_nRecNum;
int  FileMerge(const char *  picfile,int size)
{
	
	char 	sFileheadRecord[512]; /*��ȡ�ļ�ͷ*/ 
	char 	sFileRecord[512];     /*��ȡ�ļ�����*/
	char  * pPos=NULL;
	memset(sFileRecord, 0x00, sizeof(sFileRecord));
	memset(sFileheadRecord, 0x00, sizeof(sFileheadRecord));

	FILE  * lrp_fp;
	fopen_s(&lrp_fp ,picfile, "r");
	

	if (fgets (sFileheadRecord, 496, lrp_fp) == NULL)
	{	
 		fclose (lrp_fp);
 		return -1;
	}
	if(g_nRecNum==1)
	{
		fprintf( g_merge_fp,"%s",sFileheadRecord);
	}

	if(fgets (sFileRecord, 496, lrp_fp)==NULL)
	{
		return -1;
	}
	
	if(g_nRecNum==1)
	{
		fprintf( g_merge_fp,"%s",sFileRecord);
	}

	/*ȡͷ�жϼ�¼��*/
	memset(sFileRecord,0,sizeof(sFileRecord));
	while( fgets (sFileRecord, 496, lrp_fp) != NULL )
	{
		pPos = strstr(sFileRecord,"|");
		fprintf( g_merge_fp,"%d%s",g_nRecNum, pPos);
		
		memset(sFileRecord,0,sizeof(sFileRecord));
		g_nRecNum++;
	}
	return 0;
}

void CPicCompDlg::OnBnClickedBtnFilemerge()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	char szPicDir[100] = {""};	
	this->UpdateData();
	CW2A  szIpObj(m_strPicDir);
	strcpy_s(szPicDir, szIpObj);
	g_pThisPicDlg=this;
	g_nRecNum=1;
	fopen_s(&g_merge_fp , "D://abc.txt","w");
	//visit_comm(szPicDir,1,FileMerge);  		
	fclose(g_merge_fp);
}
// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CPicCompDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CPicCompDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

