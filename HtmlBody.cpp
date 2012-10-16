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

}

void HtmlBody::SaveToFile(UnicodeString fn)
{
	StrStr->SaveToFile(fn);
}

void HtmlBody::ExamBody()
{
	bStruct  		= new TAG;
	bStruct->Next	= NULL;
	bStruct->Friend	= NULL;
	Destruct(bStruct,cBody);

}

void HtmlBody::Destruct(TAG* tempRoot, UnicodeString tempBody)
{

	int tempPos;
	UnicodeString friendBody;
do
	{
		// Fill all fields
		tempRoot->RelatedPos   = cBody.Pos(tempBody);
		tempRoot->LStartPos    = tempBody.Pos("<");
		tempRoot->LEndPos      = tempBody.Pos(">");
		tempRoot->TagString	   = tempBody.SubString(tempRoot->LStartPos+1,tempRoot->LEndPos-tempRoot->LStartPos-1);
		tempRoot->NameEndPos   = tempRoot->TagString.Pos(" ");
		// Fill tag name
		if (tempRoot->NameEndPos == 0)
		{
			tempRoot->TagName  	 = tempRoot->TagString;
		}
		else
		{
			// TODO : Have to sovle this problem:  string string <tagname para> the space
			// The lenght of the substring need NOT minus 1, becuase the "<"  has been removed before calculated.
			tempRoot->TagName  	 = tempRoot->TagString.SubString(1, tempRoot->NameEndPos-1);
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
			  if (friendBody.Pos("<")!=0)
				{
				  TAG *tempFriend = new TAG;
				  tempFriend->Next=NULL;
				  tempFriend->Friend=NULL;
				  Destruct(tempFriend,friendBody);
				  tempRoot->Friend=tempFriend;
				}
			}
		  //_______________________________________________________________________________________
			 tempBody 			= tempBody.SubString(tempRoot->LEndPos+1,tempRoot->RStartPos-tempRoot->LEndPos-1);
		}
		else
		{
		  tempRoot->RStartPos	= tempBody.Length();
		  tempBody				= tempBody.SubString(tempRoot->LEndPos+1,tempRoot->RStartPos-tempRoot->LEndPos-1);
		 }
		 //________________________________


		 //________________________________
		 // Cut of the content before the <Tagname>
		 tempPos 	= tempBody.Length();
		 if (tempBody.Pos("<")!=0)
		 {
			tempBody 	= tempBody.SubString(tempBody.Pos("<"), tempPos-tempBody.Pos("<")-1);

		 // Link to next
		 TAG	*tempList	= new TAG;
		 tempList->Next		= NULL;
		 tempList->Friend	= NULL;
		 tempRoot->Next		= tempList;
		 tempRoot			= tempList;
         }

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
