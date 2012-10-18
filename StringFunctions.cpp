//---------------------------------------------------------------------------

#pragma hdrstop

#include "StringFunctions.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


// Return the position for the Nth str in body. Body: str str str str ...
int Search(UnicodeString body, UnicodeString part,int index)
{
	UnicodeString bodyCopy = body;
	int position 		   = 1;//body.Pos(part);
	int partL 			   = part.Length();
	int posCopy			   = position;
	int count			   = 0;
	while(count!= index-1)
	{
		count++;
		if (posCopy!=0) {
			bodyCopy.Delete(posCopy,partL);
			position+=partL;
			posCopy = bodyCopy.Pos(part);
		}
	}
	position += bodyCopy.Pos(part);
	return position - 1;
}

// Return the count duplicated str in body.
int CountPart(UnicodeString body,UnicodeString part)
{
	int count=0;
	UnicodeString bodyCopy = body;
	while (bodyCopy.Pos(part)!=0)
	{
		 bodyCopy = bodyCopy.Delete(bodyCopy.Pos(part),part.Length());
		 count++;
	}
	return count;
}

// Return the str with in head and tail. Body: headstrtail
UnicodeString Within(UnicodeString body,UnicodeString head, UnicodeString tail)
{
	UnicodeString temp = body;
	if (head!=tail)
	{
		temp = temp.SubString(body.Pos(head)+head.Length(), body.Pos(tail)-body.Pos(head)-head.Length());
	}
	else if (head==tail)
	{
		temp = temp.Delete(1,temp.Pos(head)-1);
		temp = temp.Delete(1,head.Length());
		temp = temp.Delete(temp.Pos(tail),temp.Length()-temp.Pos(tail)+1);
	}
	return temp;
}

// Return the position of the ending char of part in body.
int EPos(UnicodeString body, UnicodeString part)
{
	return body.Pos(part)+ part.Length()-1;
}

// Return str after the tail. tailstr
UnicodeString AfterTail(UnicodeString body, UnicodeString tail)
{
	return body.SubString(EPos(body,tail)+1,body.Length()-EPos(body,tail));
}

// Return str after head and before the Nth tail.
UnicodeString WithinTails(UnicodeString body,UnicodeString head, UnicodeString tail, int tailIndex)
{
	UnicodeString temp = body;
	if (CountPart(body,tail)==0)
	{
		temp = body;
	}
	else if (CountPart(body,tail)==1)
	{
		temp = Within(body,head,tail);
	 }
	 else if (CountPart(body, tail)>1)
	 {
		temp = body.SubString(body.Pos(head)+head.Length(), Search(body,tail,tailIndex)-body.Pos(head)-head.Length() );
	  }
	  return temp;
}

// Remove chars before head. charshead.
UnicodeString RemoveHead(UnicodeString body,UnicodeString head)
{
	UnicodeString temp = body;
	return temp.Delete(1, temp.Pos(head)-1);
}

// Remove chars after the Nth tail.
UnicodeString AfterNTail(UnicodeString body, UnicodeString tail, int index)
{
	UnicodeString temp = body;
	while(index>=1)
	{
		temp = AfterTail(temp,tail);
		index--;
	}
	return temp;
}
