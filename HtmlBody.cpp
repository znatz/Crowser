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
	bStruct  		= new TAG;
	TAG	*tempRoot	= new TAG;
	TAG	*tempList;
	int tempPos;
	UnicodeString tempBody = cBody;
//do
//	{
		bStruct->LStartPos 	= tempBody.Pos("<");
		bStruct->NameEndPos	= tempBody.Pos(" ");
		bStruct->LEndPos    = tempBody.Pos(">");
		bStruct->TagName 	= tempBody.SubString(bStruct->LStartPos+1,bStruct->NameEndPos-1);
		bStruct->RStartPos  = tempBody.Pos("</"+bStruct->TagName+">");
		if (bStruct->RStartPos!=0)
		{
		  bStruct->REndPos	= bStruct->RStartPos + bStruct->TagName.Length() + 2;
		}
//	}while();
}
