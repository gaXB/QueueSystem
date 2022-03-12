
// QueueSystemDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "QueueSystem.h"
#include "QueueSystemDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CQueueSystemDlg 对话框




CQueueSystemDlg::CQueueSystemDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CQueueSystemDlg::IDD, pParent)
	, m_Page(0)
	, m_NumEmp(7)
	, m_ColeDate(COleDateTime::GetCurrentTime())
	, m_SetYear(0)
	, m_SetMonth(0)
	, m_SetDay(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CQueueSystemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_list);
	DDX_Text(pDX, IDC_EDIT1, m_Page);
	DDV_MinMaxInt(pDX, m_Page, 0, 99);
	DDX_Text(pDX, IDC_EDIT2, m_NumEmp);
	DDV_MinMaxInt(pDX, m_NumEmp, 7, 9);
	DDX_Text(pDX, IDC_EDIT3, m_ColeDate);
	DDX_Text(pDX, IDC_EDIT4, m_SetYear);
	DDV_MinMaxInt(pDX, m_SetYear, 2000, 2200);
	DDX_Text(pDX, IDC_EDIT5, m_SetMonth);
	DDV_MinMaxInt(pDX, m_SetMonth, 1, 12);
	DDX_Text(pDX, IDC_EDIT6, m_SetDay);
	DDV_MinMaxInt(pDX, m_SetDay, 1, 31);
}

BEGIN_MESSAGE_MAP(CQueueSystemDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CQueueSystemDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, &CQueueSystemDlg::OnBnClickedButtonNext)
	ON_BN_CLICKED(IDC_BUTTON_LAST, &CQueueSystemDlg::OnBnClickedButtonLast)
END_MESSAGE_MAP()

uint8 SearchNum(uint8* pData, uint8 value)
{
	for (int i = 0; i < TEAMNUM; i++)
	{
		if (value == pData[i])
		{
			return i;		
		}else{}
	}

	return RESETNUM;
}
// CQueueSystemDlg 消息处理程序

BOOL CQueueSystemDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标


	//标题所需字段
	CString head[]={
   
   TEXT("序号"),TEXT("时间"),TEXT("9点"), TEXT("9点半"),TEXT(" 10点半"),TEXT("11点"), TEXT("晚班"),  TEXT("休息")};

	CString name[]={
   
   TEXT("李白"),TEXT("鲁班"),TEXT("韩信"),
					TEXT("亚索"),TEXT("达摩"),TEXT("小明")};
	
	//插入列标题
	m_list.InsertColumn(0,head[0],LVCFMT_LEFT, 100);
	m_list.InsertColumn(1,head[1],LVCFMT_LEFT, 150);
	m_list.InsertColumn(2,head[2],LVCFMT_LEFT, 100);
	m_list.InsertColumn(3,head[3],LVCFMT_LEFT, 100);
	m_list.InsertColumn(4,head[4],LVCFMT_LEFT, 100);
	m_list.InsertColumn(5,head[5],LVCFMT_LEFT, 100);
	m_list.InsertColumn(6,head[6],LVCFMT_LEFT, 300);
	m_list.InsertColumn(7,head[7],LVCFMT_LEFT, 100);

	// TODO: 在此添加额外的初始化代码
		CurrentTeam.B1 = 1;
	CurrentTeam.B2 = 1;
	CurrentTeam.B3 = 1;
	CurrentTeam.B4 = 1;

	CurrentTeam.B5 = 1;

	DealQueue();

	//插入正文内容
	CString str;
	for(int i=0;i<TEAMNUM;i++){
   
   
	//	CString str;
	//  str.Format(TEXT("张三_%d"),i);
	//	str.Format(TEXT("name[i]_%d"),i);

		//确定行数
		str.Format(L"第%d天",i+1);
		m_list.InsertItem(i,str);
		
		//设置列内容
		int j=0;
		int age=23;
		m_list.SetItemText(i,++j,TEXT("3月22日"));//怎么设置int
		//if ()
		//m_list.SetItemText(i,++j,TEXT("男"));

	}
	//设置风格样式
	//LVS_EX_GRIDLINES 网格
	//LVS_EX_FULLROWSELECT 选中整行
	m_list.SetExtendedStyle(m_list.GetExtendedStyle() 
	| LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	m_SetYear = m_ColeDate.GetYear();
	m_SetMonth = m_ColeDate.GetMonth();
	m_SetDay = m_ColeDate.GetDay();
	UpdateData(FALSE);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CQueueSystemDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CQueueSystemDlg::OnPaint()
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
HCURSOR CQueueSystemDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CQueueSystemDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
	RefListView();
}

CString GetAName(uint8* pData, uint8 len)
{
	CString str = L"";
	CString str1;
	for (int i= 0; i < len; i++)
	{
		if (pData[i] != 0)
		{
			str1.Format(L"A%d", pData[i]);
			if (str == L"")
			{
				str = str1;
			}
			else
			{
				str = str+L"和"+ str1;
			}
		}
	}

	return str;
}
void CQueueSystemDlg::RefListView(void)
{
			//插入正文内容
	CString str;

	int nYear,nMonth,nDay;


//CTime t = CTime::GetCurrentTime(); 
	


	UpdateData(TRUE);
	int mDayNum = m_Page*10;
	UpdateData(FALSE);
	DealQueue();
	for(int i=0;i<11;i++)
	{

	//	COleDateTime time1(1977,4,16,2,2,2); //COleDataTime--->CTime
		//SYSTEMTIME systime;
		//VariantTimeToSystemTime(m_ColeDate, &systime);
		CTime t(m_SetYear, m_SetMonth, m_SetDay,0,0,0);
		//CTime t = m_ColeDate;
		//m_ColeDate
	    mDayNum = m_Page*TEAMNUM+i;
		t += CTimeSpan(mDayNum, 0, 0, 0 );    //该函数第一个参数为相差的天数  
		nYear = t.GetYear();
		nMonth = t.GetMonth();
		nDay = t.GetDay();
	//	CString str;
	//  str.Format(TEXT("张三_%d"),i);
	//	str.Format(TEXT("name[i]_%d"),i);
		
		//设置列内容
		int j=0;
		str.Format(L"%d年%d月%d日", nYear,nMonth,nDay);
		m_list.SetItemText(i,++j,str);//怎么设置int
		
		//CResultTeam[mDayNum][i]
		str = GetAName(&CResultTeam[mDayNum][0], 1);
		m_list.SetItemText(i,++j,str);
		str = GetAName(&CResultTeam[mDayNum][1], 1);
		m_list.SetItemText(i,++j,str);
		str = GetAName(&CResultTeam[mDayNum][2], 1);
		m_list.SetItemText(i,++j,str);
		str = GetAName(&CResultTeam[mDayNum][3], 1);
		m_list.SetItemText(i,++j,str);
		str = GetAName(&CResultTeam[mDayNum][4], 6);
		m_list.SetItemText(i,++j,str);
		str = GetAName(&CResultTeam[mDayNum][RESETNUM], 1);
		m_list.SetItemText(i,++j,str);
	}
}


int CQueueSystemDlg::DealQueue(void)
{
	if (m_NumEmp == 7)
	{
		CTeam[0] = 1;
		CTeam[1] = 2;
		CTeam[2] = 3;
		CTeam[3] = 0;
		CTeam[4] = 4;
		CTeam[5] = 5;
		CTeam[6] = 6;
		CTeam[7] = 0;
		CTeam[8] = 0;
		CTeam[9] = 0;
		CTeam[10] = 7;

		CResetTeam[0] = 7;
		CResetTeam[1] = 1;
		CResetTeam[2] = 4;
		CResetTeam[3] = 2;
		CResetTeam[4] = 5;
		CResetTeam[5] = 3;
		CResetTeam[6] = 6;
		CResetTeam[7] = 0;
		CResetTeam[8] = 0;
		CResetTeam[9] = 0;
		CResetTeam[10] = 0;
	}
	else if (m_NumEmp == 8)
	{
		CTeam[0] = 2;
		CTeam[1] = 3;
		CTeam[2] = 4;
		CTeam[3] = 5;
		CTeam[4] = 6;
		CTeam[5] = 7;
		CTeam[6] = 8;
		CTeam[7] = 0;
		CTeam[8] = 0;
		CTeam[9] = 0;
		CTeam[10] = 1;

		CResetTeam[0] = 1;
		CResetTeam[1] = 2;
		CResetTeam[2] = 6;
		CResetTeam[3] = 3;
		CResetTeam[4] = 7;
		CResetTeam[5] = 4;
		CResetTeam[6] = 8;
		CResetTeam[7] = 5;
		CResetTeam[8] = 0;
		CResetTeam[9] = 0;
		CResetTeam[10] = 0;
	}
	else
	{
		CTeam[0] = 2;
		CTeam[1] = 3;
		CTeam[2] = 4;
		CTeam[3] = 5;
		CTeam[4] = 6;
		CTeam[5] = 7;
		CTeam[6] = 8;
		CTeam[7] = 9;
		CTeam[8] = 0;
		CTeam[9] = 0;
		CTeam[10] = 1;

		CResetTeam[0] = 1;
		CResetTeam[1] = 2;
		CResetTeam[2] = 6;
		CResetTeam[3] = 3;
		CResetTeam[4] = 7;
		CResetTeam[5] = 4;
		CResetTeam[6] = 8;
		CResetTeam[7] = 5;
		CResetTeam[8] = 9;
		CResetTeam[9] = 0;
		CResetTeam[10] = 0;
	}
	memcpy(&CResultTeam[0][0], CTeam, TEAMNUM);
	teamType lastRest = 1;
	int iBan;
	int iDay;
	bool NoRestflg;
	for (iDay = 1; iDay < TEAMNUM*100; iDay++)
	{
		memcpy(&CResultTeam[iDay][0], &CTeam[0], TEAMNUM);
		if (CTeam[RESETNUM] != 0)
		{
			lastRest = CTeam[RESETNUM];
			NoRestflg = 0;
		}
		else
		{//没人休息
			NoRestflg = 1;
		}
		
		CResultTeam[iDay][RESETNUM] = CResetTeam[iDay%TEAMNUM];   //本次休息的人

		if (CResultTeam[iDay][RESETNUM] != 0)
		{//如果本次有人休息，则找到上次休息的人顶
			iBan = SearchNum(CTeam, CResultTeam[iDay][RESETNUM]);

			if (iBan == RESETNUM || lastRest == 0)
			{//错误
				while(1){}
			}
			else{}

			CResultTeam[iDay][iBan] = lastRest;
			if (NoRestflg)
			{//上次没人休息，把他上 的那个班清0
				iBan = SearchNum(CTeam, lastRest);

				if (iBan == RESETNUM)
				{//错误
					while(1){}
				}
				else{}
				CResultTeam[iDay][iBan] = 0;
			}
		}
		else if(NoRestflg == 0)
		{//如果本次mei有人休息，而上次有人休息，则让他上第3班或者下午班
			if (CResultTeam[iDay][3] == 0)
			{
				CResultTeam[iDay][3] = lastRest;
			}
			else if (CResultTeam[iDay][RESETNUM] == 0)
			{
				CResultTeam[iDay][RESETNUM-1] = lastRest;
			}
			else
			{
				while(1){}
			}
		}
		else{}

		memcpy(&CTeam[0], &CResultTeam[iDay][0], TEAMNUM);
	}
	return 0;
}


void CQueueSystemDlg::OnBnClickedButtonNext()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_Page = m_Page+1;
	if (m_Page >99)
	{
		m_Page = 99;
	}
	UpdateData(FALSE);
	RefListView();
}


void CQueueSystemDlg::OnBnClickedButtonLast()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_Page > 0)
	{
		m_Page = m_Page-1;
	}
	UpdateData(FALSE);
	RefListView();
}
