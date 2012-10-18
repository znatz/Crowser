//---------------------------------------------------------------------------

#ifndef StringFunctionsH
#define StringFunctionsH
//---------------------------------------------------------------------------
#endif

#include <vcl.h>
#pragma hdrstop

int Search(UnicodeString, UnicodeString,int);
int CountPart(UnicodeString,UnicodeString)  ;
int EPos(UnicodeString , UnicodeString )  ;

UnicodeString Within(UnicodeString ,UnicodeString , UnicodeString )  ;
UnicodeString WithinTails(UnicodeString,UnicodeString, UnicodeString, int);
UnicodeString AfterTail(UnicodeString, UnicodeString);
UnicodeString AfterNTail(UnicodeString, UnicodeString, int);
UnicodeString RemoveHead(UnicodeString,UnicodeString);


