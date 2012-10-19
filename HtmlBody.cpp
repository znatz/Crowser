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
	if (Body=="")
	{
		Root = NULL;
		return;
	}
	UnicodeString frBody;
	UnicodeString temp;
	int tagCount;
	int endtagCount;

	while(Body.Pos("<")&& Body!="")
	{
		Body = RemoveHead(Body,"<");
		Root->TagString	= Within(Body,"<",">");
		// Find tag name
		Root->NameEndPos = Root->TagString.Pos(" ");
		if (Root->NameEndPos == 0 || Root->NameEndPos > Body.Pos(">"))
			{
			Root->TagName = Root->TagString;
			}
		else if (Root->NameEndPos<Body.Pos(">"))
			{
			   Root->TagName = Within("<"+Root->TagString,"<"," ");
			}
		//______________
		UnicodeString endTag = "</" + Root->TagName + ">";
		int count = CountPart(Body,endTag);
		// whether </tag> existed
		if (count == 0 ) 			// </tag> not existed
			{
				// whether < existed
				if ( CountPart(Body,"<")<=1 ) 	   // < not existed
					 {
						TAG	*endRode	= new TAG;
						endRode->Next	= NULL;
						endRode->Friend	= NULL;
						Root->Next		= endRode;
						Root			= endRode;
						Body 			= "";
						return;
					 }
				else       						   // < existed  , only friends existed
					 {
						frBody = AfterTail(Body,"<"+Root->TagString+">");
						Root->Friend   = AddNode(frBody);
						// FRIEND ONLY
					 }
			}
		else if (count==1)			// </tag> existed once
			{
				frBody = AfterTail(Body,endTag);
				Root->Friend	= AddNode(frBody);
				Body   = Within(Body,"<"+Root->TagString+">",endTag);
				// FRIEND AND NEXT EXISTED
			}
		else if (count>1)  			// </tag> existed more than one time
			{
				 // find out the index of </tag> that match
				 int index = 0;
				 do
				 {
					index++;
					temp = WithinTails(Body,"<"+Root->TagName,endTag,index);
					tagCount = CountPart(temp,"<"+Root->TagName);
					endtagCount = CountPart(temp,endTag);
				  }	while(tagCount!=endtagCount);
				  frBody = AfterNTail(Body,endTag,index);
				  Root->Friend	=  AddNode(frBody);
				  Body   = WithinTails(Body,"<"+Root->TagName+">",endTag,index);
				  // FRIEND AND NEXT EXISTED
			}
		TAG	*endRode	= new TAG;
		endRode->Next	= NULL;
		endRode->Friend	= NULL;
		Root->Next		= endRode;
		Root			= endRode;
	}
}

TAG * HtmlBody::AddNode(UnicodeString str)
{
	if (str=="" || str.Pos("<")==0)
	{
		return NULL;
	}
	TAG *newNode 	= new TAG;
	newNode->Next	= NULL;
	newNode->Friend	= NULL;
	Destruct(newNode,str);
	return		newNode;
}







/*
	int duplicate = 0;
 //	int count 	  = 1;
	int index	  = 1;
	UnicodeString temp = "";
	UnicodeString startTag="";
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
		if (Root->RStartPos!=0)          	// </tagname> existed
		{
			duplicate = CountPart(Body,"<"+Root->TagName);
			if (duplicate==1)                                  // 1 means no dupliate
			{
				if (EPos(Body,endTag)< Body.Length())
				{
					frBody	= AfterTail(Body,endTag);
					TAG *newFd 	= new TAG;
					newFd->Next	= NULL;
					newFd->Friend	= NULL;
					Destruct(newFd,frBody);
					Root->Friend	= newFd;
				}
				Body = Within(Body,"<"+Root->TagString+">",endTag);
			}
			if (duplicate>1)            // duplicate <tagname>
			{
			while (index<=duplicate)
			 {   // ??????
				 startTag = UnicodeString("<"+Root->TagName);
				 temp = WithinTails(Body,startTag,endTag,index);  // any <tagname> between <tagname> and </tagname>
				 if (CountPart(temp,startTag)-CountPart(temp,endTag)>0)   // if <tagname <tagname </tagname>
				 {
					index++;
				 }
				 if  (CountPart(temp,startTag)-CountPart(temp,endTag)==0)
				 {
					frBody = AfterNTail(Body,endTag,CountPart(temp,endTag)+1);
							if (frBody!="\r\n")
							{
								TAG *newFd 	= new TAG;
								newFd->Next	= NULL;
								newFd->Friend	= NULL;
								Destruct(newFd,frBody);
								Root->Friend	= newFd;
							}
					Body = WithinTails(Body,"<"+Root->TagString+">",endTag,CountPart(temp,endTag)+1);

				 }
			 }
			// count = 1;
			 }
		  }
		  else if (Root->RStartPos==0) 		// </tagname> nonexisted
		 {
			   Body	= AfterTail(Body,"<"+Root->TagString+">");
		  }
		 //___________________________________________________
		 Root->REndPos	= Root->RStartPos + endTag.Length();

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

*/
