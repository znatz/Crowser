#pragma hdrstop

#include "HtmlBody.h"
#include "StringFunctions.h"

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
	UnicodeString frBody;
	UnicodeString endTag;	// </ + tagname + >
do
	{
		// Fill all fields
		Root->RelatedPos   = cBody.Pos(Body);
		Root->LStartPos    = Body.Pos("<");
		Root->LEndPos      = Body.Pos(">");
		Root->TagString	   = Within(Body,"<",">");

		// Find name in tag
		Root->NameEndPos   = Root->TagString.Pos(" ");
		if (Root->NameEndPos == 0)     	   // <tagname>
		{
			Root->TagName  = Root->TagString;
		}
		else							   // <tagname para=val>
		{
			Root->TagName  = Within(Root->TagString,"<"," ");
		}
		// Find string within the tag
		endTag			 = "</"	+ Root->TagName + ">";
		Root->RStartPos  = Body.Pos(endTag);
		if (Root->RStartPos!=0)
		{
		  Root->REndPos	= Root->RStartPos + endTag.Length();

		  // !!!!!!!! TODO: if Root->REndPos != _Body.length(); it means frBody Existed
		  if (Root->REndPos < Body.Length())
			{
			  frBody   = AfterTail(Body,endTag);
			  if (frBody.Pos("<")!=0)
				{
				  TAG *newFd 	= new TAG;
				  newFd->Next	= NULL;
				  newFd->Friend	= NULL;
				  Destruct(newFd,frBody);
				  Root->Friend	= newFd;
				}
			}
			 Body	= Within(Body,Root->TagName,endTag);
		}
		else
		{
		  Root->RStartPos	= Body.Length();
		  Body	= AfterTail(Body,"<"+Root->TagString+">");
		 }
		 //________________________________


		 //________________________________
		 // Cut of the content before the <Tagname>
		 if (Body.Pos("<")!=0)
		 {
			Body = RemoveHead(Body,"<");
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
