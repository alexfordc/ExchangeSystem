// ExchangeSystem_v4.cpp: 定义控制台应用程序的入口点。
//


#include <iostream>
#include <string>
#include "ThostFtdcMdApi.h"
#include "ThostFtdcTraderApi.h"
#include "ThostFtdcUserApiDataType.h"
#include "ThostFtdcUserApiStruct.h"
#include "CustomMdSpi.h"
#include "CustomTradeSpi.h"
using namespace std;

#pragma comment (lib, "thostmduserapi.lib")
#pragma comment (lib, "thosttraderapi.lib")

CThostFtdcMdApi *pUserApi = nullptr;
int requestId = 0;
int CONTRACTSNUM = 4;
char *CONTRACTS[4];
char gTradeFrontAddr[] = "tcp://180.168.146.187:10031";
TThostFtdcBrokerIDType BROKERID = "9999";
TThostFtdcInvestorIDType USERID;
TThostFtdcPasswordType PASSWORD;
TThostFtdcInstrumentIDType g_pTradeInstrumentID;//所交易的合约代码
CThostFtdcTraderApi *g_pTradeUserApi;//交易接口指针

int main()
{
	cout << "请输入投资人ID：";
	cin >> USERID;
	cout << "请输入密码：";
	cin >> PASSWORD;
	
	//行情接口初始化
	cout << "初始化行情..." << endl;
	pUserApi = CThostFtdcMdApi::CreateFtdcMdApi();
	CustomMdSpi* pUserSpi = new CustomMdSpi;
	pUserApi->RegisterSpi(pUserSpi);
	pUserApi->RegisterFront(gTradeFrontAddr);
	pUserApi->Init();
	//pUserApi->Join();
	
	//初始化交易接口
	cout << "初始化交易接口..." << endl;
	g_pTradeUserApi = CThostFtdcTraderApi::CreateFtdcTraderApi();
	CustomTradeSpi *pTradeSpi = new CustomTradeSpi;
	g_pTradeUserApi->RegisterSpi(pTradeSpi);
	g_pTradeUserApi->SubscribePublicTopic(THOST_TERT_RESTART);
	g_pTradeUserApi->SubscribePrivateTopic(THOST_TERT_RESTART);
	g_pTradeUserApi->RegisterFront(gTradeFrontAddr);
	g_pTradeUserApi->Init();

	pUserApi->Join();
	
	return 0;
}

