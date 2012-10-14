#pragma hdrstop

#include "HtmlBody.h"

HtmlBody::HtmlBody()
{
	StrStr = new TStringStream();
	bodySize = 0;
}

void HtmlBody::SetBody(char* buff, int startPos,int endPos)
{
	StrStr->Write(&buff[startPos],endPos);
	cBody = StrStr->DataString;
	bodySize += endPos-startPos;
	Destruct();
}

void HtmlBody::SaveToFile(UnicodeString fn)
{
	StrStr->SaveToFile(fn);
}

void HtmlBody::Destruct()
{
	cBodyStruct 			= new BodyStruct;
	BodyStruct* tempRoot	= new BodyStruct;
	BodyStruct* tempList;
}
