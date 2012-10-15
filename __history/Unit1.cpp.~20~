//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "Unit1.h"
//---------------------------------------------------------------------------

#include "RequestHeader.h"
#include "ResponseHeader.h"
#include "HtmlBody.h"
//---------------------------------------------------------------------------
#include <winsock2.h>
#include <WS2tcpip.h>
#include <IPHlpApi.h>
//---------------------------------------------------------------------------
#define DEFAULT_PORT "80"
#define BUFFLEN 1024
#pragma comment (lib, "ws2_32.lib")
//---------------------------------------------------------------------------

#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
int  			iResult;
UnicodeString 	msg;
UnicodeString 	filename;
ResponseHeader 	RspHdr("");
HtmlBody 		Content;

void ConnectIt();
void Report(int, UnicodeString);

//---------------------------------------------------------------------------
TFm *Fm;
//---------------------------------------------------------------------------
__fastcall TFm::TFm(TComponent* Owner)
	: TForm(Owner)
{
	RqstHdr->Text = "";
	Output->Text  = "";
	Err->Text	  = "";
	BodyEdt->Text = "";
	BodyREdit->SelText	  = "";
	BodyREdit->Text		  = "";
}
//---------------------------------------------------------------------------
void __fastcall TFm::SbClick(TObject *Sender)
{
	Fm->Err->Text		=	"";
	Fm->Output->Text	=	"";
	Fm->BodyEdt->Text	=	"";
	Fm->Err->Text		=	"";
	UnicodeString str 	= 	Input->Text;

	randomize();


	ConnectIt();
}

//---------------------------------------------------------------------------
void Report(int iR, UnicodeString ms)
{
	if (iR==0)
	{
		Fm->Err->Text=Fm->Err->Text + ms + " OK\r\n";// + ENDOFLINE ;
	}
	else
	{
		Fm->Err->Text = Fm->Err->Text + ms + " " + IntToStr(iR) + "\r\n";// ENDOFLINE;
	}
}


//---------------------------------------------------------------------------
void ConnectIt()
{
// Initiate WSAData
	WSADATA wsadata;
	iResult = WSAStartup(0x0202,&wsadata);
	msg = "WSAStartup";
	Report(iResult,msg);
// Initiate addrinfo
	struct addrinfo *result,hints;
	ZeroMemory(&hints,sizeof(hints));
	hints.ai_family=AF_UNSPEC;
	hints.ai_socktype=SOCK_STREAM;
	hints.ai_protocol=IPPROTO_TCP;
// Retrieve addrinfo
	const char* IPAddress = AnsiString(Fm->Input->Text).c_str();
	iResult = getaddrinfo(IPAddress,DEFAULT_PORT,&hints,&result);
	msg = "Address info";
	Report(iResult,msg);
// Retrieve socket
	int iSocket = socket (result->ai_family,result->ai_socktype,result->ai_protocol);
	msg = "Socket initiated";
	Report(iSocket,msg);
// Connect to server
	iResult = connect(iSocket, result->ai_addr, (int)result->ai_addrlen);
	msg = "Connection";
	Report(iResult,msg);
// Free up addrinfo
	freeaddrinfo(result);
// Send request header
	RequestHeader RqHdr(Fm->RqstHdr->Text);
	iResult = send(iSocket, RqHdr.HdrToSent, BUFFLEN,0);
	msg = "Bytes sent";
	Report(iResult,msg);
// Receive data
	char* recvbuff = new char[BUFFLEN];
	int totalRecvBytes = 0;
	do
	{
		iResult = recv(iSocket, recvbuff, BUFFLEN, 0);
		if (iResult>0)
		{
			Fm->Output->Text = Fm->Output->Text + UnicodeString(recvbuff).SubString(0,iResult);
			totalRecvBytes += iResult;

				if (totalRecvBytes==iResult)
				{
					  // RspHdr get the buffer, calculate the length, create the header
					  RspHdr.SetResponseHeader(recvbuff);
					  // Content get the buffer, create the first part of content
					  // Starting from the end of the header.
					  Content.SetBody(recvbuff,RspHdr.HdrLen,iResult-RspHdr.HdrLen);

					  Report(RspHdr.cSize," The lenth of the content is");
					  Report(1, " The date is " + RspHdr.cDate);
					  Report(RspHdr.HdrLen,"Total Bytes of header");
				}
				else
				{
					   Content.SetBody(recvbuff,0,iResult);
				}

		}
		else if (iResult==0)
		{
			msg = "Receiving bytes ...";
			Report(iResult,msg);
			closesocket(iSocket);
			WSACleanup();
			msg = "Total bytes received.";
			Report(totalRecvBytes,msg);
		} ;

	} while (iResult > 0);

	if (iResult<0)
	{
		msg = "Error";
		Report(iResult,msg);
		closesocket(iSocket);
		WSACleanup();
	};

if (RspHdr.cType==".html")
{
	/* Fill RichEdit with text.
	   Select the necessary part.
	   Change the selected part to what you want*/
	Fm->BodyREdit->SelText=Content.cBody;
	Fm->BodyREdit->SelStart = 100;
	Fm->BodyREdit->SelLength = 300;
	TTextAttributes* textAttrib = Fm->BodyREdit->SelAttributes;
	textAttrib->Color = StringToColor(clBlue);
	Fm->BodyREdit->SelAttributes = textAttrib;

	// Try to destruct body here
	Report(4444,Content.bStruct->Next->Next->Friend->Next->TagName);
	TAG* iterate;
	for (iterate=Content.bStruct; iterate!=NULL; iterate=iterate->Next) {
		Report(0,"Inside "+iterate->TagName+" Tag: " + iterate->TagString);
		if (iterate->Friend!=NULL) {
			TAG* p;
			for (p=iterate->Friend; p!= NULL; p = p->Friend) {
				Report (1,p->TagName);
				TAG* ip;
				for (ip=p; ip!=NULL; ip=ip->Next) {
                    Report(2, ip->TagName);
				}
			}
		}
	}
}

// Save the content or not according to the type of the content
if (RspHdr.cType!=".html")
{
	filename = IntToStr(rand()) + RspHdr.cType;
	Content.SaveToFile(filename);
}


// Close connection
	msg = "The End";
	Report(iResult,msg);
	closesocket(iSocket);
	WSACleanup();
 //--------------------------


}
//---------------------------------------------------------------------------

void __fastcall TFm::Button1Click(TObject *Sender)
{
	if (RspHdr.cType!=".html") {
	TImage* Image2 = new TImage(Fm);
	Image2->Parent = Fm;
   	Image2->Left = 600;
	Image2->Top  = 200;
	Image2->Picture->LoadFromFile(filename);
	}
	else {Report(0, "Not an image file.");  }
}

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
