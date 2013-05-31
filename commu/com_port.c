/**
 * Copyright 2004 - 2007 Blue Bamboo International Inc. 
 *           All rights reserved.
 *
 *
 * Blue Bamboo PROPRIETARY/CONFIDENTIAL.
 *
 */
//#include "StdAfx.h"
#include <windows.h>
//#include <tchar.h>
#include <commctrl.h>
#include "includes.h"
#include "com_port.h"

BOOL Com_Port_Reset(HANDLE hFile)
{
	if (hFile == INVALID_HANDLE_VALUE)
		return FALSE;

	PurgeComm(hFile,PURGE_TXCLEAR);
	PurgeComm(hFile,PURGE_RXCLEAR);

	return TRUE;
}

BOOL Com_Port_Config(HANDLE hFile,EBaudrate eBaudrate,
		EDataBits eDataBits,
		EParity   eParity,
		EStopBits eStopBits)
{	
	DWORD err;
	BYTE Bbcd[28]={0x1c,0x00,0x00,0x00,0x80,0x25,0x00,0x00,
	               0x11,0x30,0x00,0x00,0x00,0x00,0x00,0x08,
				   0x00,0x02,0x08,0x03,0x00,0x11,0x13,0x00,
				   0x00,0x00,0x00,0x00};
	DCB					l_dcb;

	if (hFile == INVALID_HANDLE_VALUE)
		return FALSE;

	memcpy((BYTE *)&l_dcb,Bbcd,sizeof(l_dcb));
	err = SetCommState(hFile,&l_dcb);              
	if (!err)
	{
		//CloseHandle(idComDev);
	    return  FALSE;
	}

	if (!GetCommState(hFile,&l_dcb))
	{
		return FALSE;
	}
	// Set the new data
	//m_dcb.fParity  = 1;
	l_dcb.BaudRate = (DWORD)(eBaudrate);
	l_dcb.ByteSize = (BYTE)(eDataBits);
	l_dcb.Parity   = (BYTE)(eParity);
	l_dcb.StopBits = (BYTE)(eStopBits);

	// Determine if parity is used
	l_dcb.fParity  = (l_dcb.Parity != EParNone);

	// Set the new DCB structure
	if (!SetCommState(hFile,&l_dcb))
	{
		return FALSE;
	}	
	
	Com_Port_Reset(hFile);

	return TRUE;
}



int Com_Port_Connect(LPCTSTR pszParam,EBaudrate eBaudrate,HANDLE *pHandle)
{
	HANDLE hFile;
	COMMTIMEOUTS		CommTimeouts;
	DWORD err;

	hFile = CreateFile(pszParam,
						   GENERIC_READ|GENERIC_WRITE,0,
						   //GENERIC_READ|GENERIC_WRITE,FILE_SHARE_READ,
						   NULL,
						   OPEN_EXISTING,
						   0/*FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN*/,
						   //FILE_FLAG_OVERLAPPED,
						   NULL);
	err = GetLastError();
	if(hFile != INVALID_HANDLE_VALUE)
	{	
		CommTimeouts.ReadIntervalTimeout			=	100L;
		CommTimeouts.ReadTotalTimeoutMultiplier	=	0L;
		CommTimeouts.ReadTotalTimeoutConstant		=	30000L;
		CommTimeouts.WriteTotalTimeoutMultiplier	=	0L;
		CommTimeouts.WriteTotalTimeoutConstant	=	5000L;
		SetCommTimeouts(hFile, &CommTimeouts);	
		
		Com_Port_Config(hFile,eBaudrate,EData8,EParNone,EStop1);
		*pHandle=hFile;
		return 0;
	}
	return -1;
}
int Com_Port_Connect_By_Port_No(UINT uiPort,EBaudrate eBaudrate,HANDLE *pHandle)
{
	// Open the device
#if 0	
	TCHAR szBuf[MAX_PATH];
#else
	char szBuf[MAX_PATH];
#endif
	memset(szBuf,0,sizeof(szBuf));
	if(uiPort>9){
#if 0	
		wsprintf(szBuf,_TEXT("\\\\.\\COM%d"),uiPort);
#else		
		sprintf(szBuf,"\\\\.\\COM%d",uiPort);
#endif		
	}else{
#if 0	
		wsprintf(szBuf,_TEXT("COM%d"),uiPort);
#else
		sprintf(szBuf,"COM%d",uiPort);
#endif
	}
	return Com_Port_Connect(szBuf,eBaudrate,pHandle);
}

DWORD  Com_Port_Send(HANDLE hFile,LPCVOID pData,DWORD dwDataLen)
{
	DWORD dwWritten;

	if (hFile == INVALID_HANDLE_VALUE || dwDataLen<=0)
		return FALSE;

	dwWritten = 0;
	if(WriteFile(hFile, pData, dwDataLen, &dwWritten, NULL))
	{
		return dwWritten;
	}
	return -1;
}
DWORD  Com_Port_Recv(HANDLE hFile, LPVOID pData,DWORD dwDataLen, DWORD dwTimeOut)
{	
	DWORD dwReadLen;
    COMMTIMEOUTS		oldCommTimeouts,newCommTimeouts;
	BOOL bReadFileResult;

	if (hFile == INVALID_HANDLE_VALUE || pData == NULL || dwDataLen<=0)
		return -1;

	dwReadLen = 0;

#if 0
	if(WaitForSingleObject(hFile,dwTimeOut/*180000L*/)==WAIT_TIMEOUT)
	{
		return -1;
	}
	if(ReadFile(hFile,
			(LPBYTE)pData, 
			dwDataLen,
			&dwReadLen,NULL))
	{	
		return dwReadLen;
	}
#else
       ASSERT_MINE(GetCommTimeouts(hFile, &oldCommTimeouts));
       newCommTimeouts=oldCommTimeouts;
       newCommTimeouts.ReadTotalTimeoutConstant		=	dwTimeOut;
       ASSERT_MINE(SetCommTimeouts(hFile, &newCommTimeouts));	
#endif
       bReadFileResult=ReadFile(hFile,(LPBYTE)pData, dwDataLen,	&dwReadLen,NULL);
       SetCommTimeouts(hFile, &oldCommTimeouts);
       if(bReadFileResult)
       {
             return dwReadLen;
       }
	return -1;//*/
}

EBaudrate getBaudrate(int baudRate)
{
	switch(baudRate){
	case 110:
		return EBaud110;
	case 300:
		return EBaud300;
	case 600:
		return EBaud600;
	case 1200:
		return EBaud1200;
	case 2400:
		return EBaud2400;
	case 4800:
		return EBaud4800;
	case 9600:
		return EBaud9600;
	case 14400:
		return EBaud14400;
	case 19200:
		return EBaud19200;
	case 38400:
		return EBaud38400;
	case 56000:
		return EBaud56000;
	case 57600:
		return EBaud57600;
	case 115200:
		return EBaud115200;
	case 128000:
		return EBaud128000;
	case 256000:
		return EBaud256000;
	default:
		return EBaudUnknown;
	}
}
