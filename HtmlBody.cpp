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
	int tempPos;
	UnicodeString tempBody = cBody;
	tempRoot		= bStruct;

do
	{
		// Fill all fields
		tempRoot->LStartPos    = tempBody.Pos("<");
		tempRoot->LEndPos      = tempBody.Pos(">");
		tempRoot->TagString	   = tempBody.SubString(tempRoot->LStartPos,tempRoot->LEndPos-tempRoot->LStartPos-1);
		tempRoot->NameEndPos   = tempRoot->TagString.Pos(" ");
		// Fill tag name
		if (tempRoot->NameEndPos == 0)
		{
			tempRoot->TagName  	 = tempBody.SubString(tempRoot->LStartPos+1,tempRoot->LEndPos-tempRoot->LStartPos-1);
		}
		else
		{
			tempRoot->TagName  	 = tempBody.SubString(tempRoot->LStartPos+1,tempRoot->NameEndPos - tempRoot->LStartPos-1);
		}
		// Find what is inside the tag
		tempRoot->RStartPos  = tempBody.Pos("</"+tempRoot->TagName+">");
		if (tempRoot->RStartPos!=0)
		{
		  tempRoot->REndPos	= tempRoot->RStartPos + tempRoot->TagName.Length() + 2;
		  tempBody 			= tempBody.SubString(tempRoot->LEndPos+1,tempRoot->RStartPos-tempRoot->LEndPos-1);
		}
		else
		{
		  tempRoot->RStartPos	= tempBody.Length();
		  tempBody				= tempBody.SubString(tempRoot->LEndPos+1,tempRoot->RStartPos-tempRoot->LEndPos-1);
		 }
		 // Link to next
		 TAG	*tempList	= new TAG;
		 tempRoot->Next		= tempList;
		 tempRoot			= tempList;


	}while(tempBody.Pos("<")!=0);
}


/*
GET / HTTP/1.1
Host:localhost
Connection:close


*/

/*
    < : LS
    > : LE
    space inside <> : NameEnd
    </: RS
    > : RE
*/
