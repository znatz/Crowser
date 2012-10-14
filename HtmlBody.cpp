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
	bStruct  		= new TAG;
	bStruct->Next	= NULL;
	bStruct->Friend	= NULL;
	Destruct(bStruct,cBody);
}

void HtmlBody::SaveToFile(UnicodeString fn)
{
	StrStr->SaveToFile(fn);
}

void HtmlBody::Destruct(TAG* _bStruct, UnicodeString _cBody)
{
	TAG	*tempRoot	= new TAG;
	int tempPos;
	UnicodeString tempBody = _cBody;
	UnicodeString friendBody;
	tempRoot		= _bStruct;

do
	{
		// Fill all fields
		tempRoot->LStartPos    = tempBody.Pos("<");
		tempRoot->LEndPos      = tempBody.Pos(">");
		tempRoot->TagString	   = tempBody.SubString(tempRoot->LStartPos+1,tempRoot->LEndPos-tempRoot->LStartPos-1);
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

		  // !!!!!!!! TODO: if tempRoot->REndPos != _tempBody.length(); it means friendBody Existed
			if (tempRoot->REndPos < tempBody.Length())
			{
			  friendBody 	= tempBody.SubString(tempRoot->REndPos+1,tempBody.Length()-tempRoot->REndPos-1);
			  tempRoot->Friend	= new TAG;
			  tempRoot->Friend->Next=NULL;
			  tempRoot->Friend->Friend=NULL;
			  Destruct(tempRoot->Friend,friendBody);
			}
		  //_______________________________________________________________________________________
			 tempBody 			= tempBody.SubString(tempRoot->LEndPos+1,tempRoot->RStartPos-tempRoot->LEndPos-1);
		}
		else
		{
		  tempRoot->RStartPos	= tempBody.Length();
		  tempBody				= tempBody.SubString(tempRoot->LEndPos+1,tempRoot->RStartPos-tempRoot->LEndPos-1);
		 }
		 // Link to next
		 TAG	*tempList	= new TAG;
		 tempList->Next		= NULL;
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
