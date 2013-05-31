/**
 * Copyright 2004 - 2007 Blue Bamboo International Inc. 
 *           All rights reserved.
 *
 *
 * Blue Bamboo PROPRIETARY/CONFIDENTIAL.
 *
 */
#pragma once

	typedef enum tagEBaudrate
	{
		EBaudUnknown = -1,			// Unknown
		EBaud110     = CBR_110,		// 110 bits/sec
		EBaud300     = CBR_300,		// 300 bits/sec
		EBaud600     = CBR_600,		// 600 bits/sec
		EBaud1200    = CBR_1200,	// 1200 bits/sec
		EBaud2400    = CBR_2400,	// 2400 bits/sec
		EBaud4800    = CBR_4800,	// 4800 bits/sec
		EBaud9600    = CBR_9600,	// 9600 bits/sec
		EBaud14400   = CBR_14400,	// 14400 bits/sec
		EBaud19200   = CBR_19200,	// 19200 bits/sec 
		EBaud38400   = CBR_38400,	// 38400 bits/sec
		EBaud56000   = CBR_56000,	// 56000 bits/sec
		EBaud57600   = CBR_57600,	// 57600 bits/sec
		EBaud115200  = CBR_115200,	// 115200 bits/sec
		EBaud128000  = CBR_128000,	// 128000 bits/sec
		EBaud256000  = CBR_256000,	// 256000 bits/sec
	}EBaudrate;
	// Data bits (5-8)
	typedef enum tagEDataBits
	{
		EDataUnknown = -1,			// Unknown
		EData5       =  5,			// 5 bits per byte
		EData6       =  6,			// 6 bits per byte
		EData7       =  7,			// 7 bits per byte
		EData8       =  8			// 8 bits per byte (default)
	}EDataBits;
	// Parity scheme
	typedef enum tagEParity
	{
		EParUnknown = -1,			// Unknown
		EParNone    = NOPARITY,		// No parity (default)
		EParOdd     = ODDPARITY,	// Odd parity
		EParEven    = EVENPARITY,	// Even parity
		EParMark    = MARKPARITY,	// Mark parity
		EParSpace   = SPACEPARITY	// Space parity
	}EParity;
	// Stop bits
	typedef enum tagEStopBits
	{
		EStopUnknown = -1,			// Unknown
		EStop1       = ONESTOPBIT,	// 1 stopbit (default)
		EStop1_5     = ONE5STOPBITS,// 1.5 stopbit
		EStop2       = TWOSTOPBITS	// 2 stopbits
	}EStopBits;
DWORD  Com_Port_Send(HANDLE hFile,LPCVOID pData,DWORD dwDataLen);
//int  Com_Port_Send(HANDLE hFile,const uint8 * pData,int dwDataLen);

DWORD  Com_Port_Recv(HANDLE hFile, LPVOID pData,DWORD dwDataLen, DWORD dwTimeOut);
//int  Com_Port_Recv(HANDLE hFile,  uint8* pData,int dwDataLen, int dwTimeOut);
//HANDLE Com_Port_Connect_By_Port_No(UINT uiPort,int eBaudrate);
int Com_Port_Connect_By_Port_No(UINT uiPort,EBaudrate eBaudrate,HANDLE *pHandle);
EBaudrate getBaudrate(int baudRate);
BOOL Com_Port_Reset(HANDLE hFile);
int setBaudRate(int fd,int baudRate);

