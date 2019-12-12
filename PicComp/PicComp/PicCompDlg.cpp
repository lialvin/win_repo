
// PicCompDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PicComp.h"
#include "PicCompDlg.h"
#include "afxdialogex.h"
#include <vector>
#include <string>


#include <math.h>
#include <opencv2/opencv.hpp> // 需要放在 _DEBUG 前面
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
// CPicCompDlg 对话框

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


// CPicCompDlg 消息处理程序

BOOL CPicCompDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

//using namespace cv;



int test_pic2(const char *  picfile, int size)
{
	IplImage *src = 0;			//源图像指针
	IplImage *dst = 0;			//目标图像指针
	float scale = 0.4;		    //缩放倍数为0.618倍
	CvSize dst_cvsize;			//目标图像尺寸
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
		//如果命令行传递了需要打开的图片就无须退出，所以注释掉下面一行！
		//return -1;
	}
	else
	{
		//src = cvLoadImage("tiger.jpg");    //载入工作目录下文件名为“tiger.jpg”的图片。
	}

	dst_cvsize.width = src->width * scale;		//目标图像的宽为源图象宽的scale倍
	dst_cvsize.height = src->height * scale;	//目标图像的高为源图象高的scale倍

	dst = cvCreateImage(dst_cvsize, src->depth, src->nChannels);	//构造目标图象
	//cvResize(src, dst, CV_INTER_LINEAR);	//缩放源图像到目标图像
	
											//cvNamedWindow( "src",   CV_WINDOW_AUTOSIZE );	//创建用于显示源图像的窗口
											//cvNamedWindow( "dst",   CV_WINDOW_AUTOSIZE );	//创建用于显示目标图像的窗口


											//cvShowImage( "src", src );		显示源图像
											//cvShowImage( "dst", dst );		//显示目标图像

											//cvWaitKey(-1);		//等待用户响应

	cvReleaseImage(&src);	//释放源图像占用的内存

	//cvSaveImage(picfile, dst);

	cvReleaseImage(&dst);	//释放目标图像占用的内存
							//cvDestroyWindow( "src" );	//销毁窗口“src”
							//cvDestroyWindow( "dst" );	//销毁窗口“dst”
							//void cvDestroyAllWindows(void);

	return 0;
}

int test_pic(const char *  picfile,int size  )
{
	
	cv::Mat src;
	cv::Mat dst;
    //IplImage *src = 0;			//源图像指针
    //IplImage *dst = 0;			//目标图像指针
    float scale = 0.4;		    //缩放倍数为0.618倍
    //CvSize dst_cvsize;			//目标图像尺寸

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
        src = cv::imread("tiger.jpg");  //载入工作目录下文件名为“tiger.jpg”的图片。
    }
 
	int width = static_cast<float>(src.cols*scale);
	//定义想要扩大或者缩小后的宽度，src.cols为原图像的宽度，乘以80%则得到想要的大小，并强制转换成float型
	int height = static_cast<float>(src.rows*scale);
	//定义想要扩大或者缩小后的高度，src.cols为原图像的高度，乘以80%则得到想要的大小，并强制转换成float型

	cv::resize(src, dst, cv::Size(width, height), cv::INTER_AREA);
	cv::imwrite(picfile, dst);
	
    return 0;
}

void CPicCompDlg::OnBnClickedBtnPic()
{
	// TODO: 在此添加控件通知处理程序代码
	char szPicDir[100] = {""};	
	this->UpdateData();
	CW2A  szIpObj(m_strPicDir);
	strcpy_s(szPicDir, szIpObj);
	g_pThisPicDlg=this;
	std::vector<std::string> filePath;
	FindDirFileNoFormat(szPicDir, filePath);
	//visit(szPicDir,1);  
}

//查找目录下所有的文件夹
void FindFolder(std::string dir, std::vector<std::string> &folderPath)
{
	CFileFind fileFinder;
	CString filePath = CString(dir.c_str()) + _T("\\*.*");

	BOOL bFinished = fileFinder.FindFile(filePath);
	while (bFinished)  //每次循环对应一个类别目录
	{
		bFinished = fileFinder.FindNextFile();
		if (fileFinder.IsDirectory() && !fileFinder.IsDots())  //fileFinder.IsDots()识别"."文件和".."文件
		{
			CString filePath = fileFinder.GetFilePath();			
			std::string filep = CT2A(filePath);
			folderPath.push_back(filep);			
			filePath.ReleaseBuffer();
		}
	}

	fileFinder.Close();
}

//查找目录下所有的文件(不遍历目录的目录)	
void FindDirFileNoFormat(std::string dir, std::vector<std::string> &filePath)
{
	CFileFind fileFinder;
	CString path = CString(dir.c_str()) + _T("\\*.*");

	BOOL bFinished = fileFinder.FindFile(path);
	while (bFinished)  //每次循环对应一个类别目录
	{
		bFinished = fileFinder.FindNextFile();
		if (fileFinder.IsDirectory() || fileFinder.IsDots())  //fileFinder.IsDots()识别"."文件和".."文件
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

//查找目录下所有的文件(遍历目录的目录)	
void FindAllFileNoFormat(std::string dir, std::vector<std::string> &filePath)
{
	CFileFind fileFinder;
	CString path = CString(dir.c_str()) + _T("\\*.*");

	BOOL bFinished = fileFinder.FindFile(path);
	while (bFinished)  //每次循环对应一个类别目录
	{
		bFinished = fileFinder.FindNextFile();

		// 跳过 . 和 .. ; 否则会陷入无限循环中！！！
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

// 查找目录下某一类型文件 (不遍历目录的目录)
void FindDirFile(std::string dir, std::string format, std::vector<std::string> &filePath)
{
	CFileFind fileFinder;
	CString path = CString(dir.c_str()) + _T("\\*") + CString(format.c_str());

	BOOL bFinished = fileFinder.FindFile(path);
	while (bFinished)  //每次循环对应一个类别目录
	{
		bFinished = fileFinder.FindNextFile();
		if (fileFinder.IsDirectory() && !fileFinder.IsDots())  //fileFinder.IsDots()识别"."文件和".."文件
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
//得到文件路径的格式后缀
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

// 查找目录下某一类型文件 (遍历目录的目录)	
void FindDirAllFileEx(std::string dir, std::vector<std::string> &format, std::vector<std::string>& filePath)
{
	CFileFind fileFinder;
	CString path = CString(dir.c_str()) + _T("\\*.*");

	BOOL bFinished = fileFinder.FindFile(path);
	while (bFinished)  //每次循环对应一个类别目录
	{
		bFinished = fileFinder.FindNextFile();

		// 跳过 . 和 .. ; 否则会陷入无限循环中！！！
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
			//获取文件类型
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
在未安装opencv电脑上运行opencv程序的设置

 新建一个空白项目（win32控制台项目）点击工具-选项-VC++目录，按照下图提示，添加目录：
 可执行文件目录
 F:\opencv\build\x86\vc9\bin
 库文件
 F:\opencv\build\x86\vc9\lib
包含文件
 F:\opencv\build\include
 把opecv dll拷贝到 debug目录下
*/
int g_nRecNum;
int  FileMerge(const char *  picfile,int size)
{
	
	char 	sFileheadRecord[512]; /*读取文件头*/ 
	char 	sFileRecord[512];     /*读取文件内容*/
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

	/*取头判断记录数*/
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
	// TODO: 在此添加控件通知处理程序代码
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
// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CPicCompDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CPicCompDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

