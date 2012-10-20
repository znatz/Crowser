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
	bStruct			= AddNode(cBody);
	return;
}

void HtmlBody::Destruct(TAG* Root, UnicodeString Body)
{
	if (Body.Pos("<")==0 || Body=="")
	{
		Root = NULL;
		return;
	}
	UnicodeString frBody;
	UnicodeString temp;
	int tagCount;
	int endtagCount;

	while(Body.Pos("<")> 0 && Body!="")
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
						return;
						// FRIEND ONLY
					 }
			}
		else if (count==1)			// </tag> existed once
			{
				frBody = AfterTail(Body,endTag);
				Root->Friend	= AddNode(frBody);
				Body   = Within(Body,"<"+Root->TagString+">",endTag);
				Root->Next		= AddNode(Body);
				return;
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
				  Root->Next	=  AddNode(Body);
				  return;
				  // FRIEND AND NEXT EXISTED
			}
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





