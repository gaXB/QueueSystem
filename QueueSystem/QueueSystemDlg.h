
// QueueSystemDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "atlcomtime.h"

typedef   unsigned char   teamType;
typedef   unsigned char   uint8;
typedef struct 
{
	unsigned char B1;
	unsigned char B2;
	unsigned char B3;
	unsigned char B4;   //���
	unsigned char B5;
	unsigned char B6;
	unsigned char B7;
	unsigned char B8;
	unsigned char B9;
	unsigned char Reset;
}ONETEMDATE;
#define    TEAMNUM   11
#define    RESETNUM  (TEAMNUM-1)
// CQueueSystemDlg �Ի���
class CQueueSystemDlg : public CDialogEx
{
// ����
public:
	CQueueSystemDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_QUEUESYSTEM_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();

public:
	ONETEMDATE CurrentTeam;
    teamType CTeam[TEAMNUM]; 
	teamType CResetTeam[TEAMNUM]; 
	teamType CResultTeam[TEAMNUM*100][TEAMNUM]; 
	CListCtrl m_list;
	int m_Page;
	void RefListView(void);
	int DealQueue(void);
	int m_NumEmp;
	afx_msg void OnBnClickedButtonNext();
	afx_msg void OnBnClickedButtonLast();
	COleDateTime m_ColeDate;
	int m_SetYear;
	int m_SetMonth;
	int m_SetDay;
};
