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

void HtmlBody::Destruct(TAG* Root, UnicodeString Body)
{

	int tempPos;
	UnicodeString frBody;
do
	{
		// Fill all fields
		Root->RelatedPos   = cBody.Pos(Body);
		Root->LStartPos    = Body.Pos("<");
		Root->LEndPos      = Body.Pos(">");
		Root->TagString	   = Body.SubString(Root->LStartPos+1,Root->LEndPos-Root->LStartPos-1);

		// Find name in tag
		Root->NameEndPos   = Root->TagString.Pos(" ");
		if (Root->NameEndPos == 0)     	   // <tagname>
		{
			Root->TagName  = Root->TagString;
		}
		else							   // <tagname para=val>
		{
			Root->TagName  	= Root->TagString.SubString(1, Root->NameEndPos-1);
		}
		// Find string within the tag
		Root->RStartPos  = Body.Pos("</"+Root->TagName+">");
		if (Root->RStartPos!=0)
		{
		  Root->REndPos	= Root->RStartPos + Root->TagName.Length() + 2;

		  // !!!!!!!! TODO: if Root->REndPos != _Body.length(); it means frBody Existed
		  if (Root->REndPos < Body.Length())
			{
			  frBody 	= Body.SubString(Root->REndPos+1,Body.Length()-Root->REndPos-1);
			  if (frBody.Pos("<")!=0)
				{
				  TAG *newFd 	= new TAG;
				  newFd->Next	= NULL;
				  newFd->Friend	= NULL;
				  Destruct(newFd,frBody);
				  Root->Friend	= newFd;
				}
			}
		  //_______________________________________________________________________________________
			 Body 			= Body.SubString(Root->LEndPos+1,Root->RStartPos-Root->LEndPos-1);
		}
		else
		{
		  Root->RStartPos	= Body.Length();
		  Body				= Body.SubString(Root->LEndPos+1,Root->RStartPos-Root->LEndPos-1);
		 }
		 //________________________________


		 //________________________________
		 // Cut of the content before the <Tagname>
		 tempPos 	= Body.Length();
		 if (Body.Pos("<")!=0)
		 {
			Body 	= Body.SubString(Body.Pos("<"), tempPos-Body.Pos("<")-1);
		 // Link to next
		 TAG	*newRt	= new TAG;
		 newRt->Next	= NULL;
		 newRt->Friend	= NULL;
		 Root->Next		= newRt;
		 Root			= newRt;
         }

	}while(Body.Pos("<")!=0);
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
