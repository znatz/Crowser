#ifndef HtmlBodyH
#define HtmlBodyH

#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>

struct TAGPROPERTY
{
	UnicodeString 	TagPara;
	UnicodeString 	TagVal;
	TAGPROPERTY    	*next;
};


struct TAG
{
	UnicodeString 	TagName;
	UnicodeString 	TagString;
	TAGPROPERTY     *TagPro;
	//int RelatedPos;
	//int LStartPos;
	int NameEndPos;
	int LEndPos;
	int RStartPos;
	//int REndPos;
	TAG   			*Next;
	TAG				*Friend;
};


class HtmlBody
{
	public:
		// Constructor and initiator
		HtmlBody();
		void SetBody(char*, int, int);
		// Save the stream to file
		void SaveToFile(UnicodeString fn);
		void ExamBody();

		// Here is the string created from the stream strstr
		UnicodeString cBody;
		TAG*	  	  bStruct;
		// The length of the stream
		int bodySize;

	private:
		// Holdes the stringstream received from initiator
		TStringStream* StrStr;
		// Destruct body
		void Destruct(TAG*, UnicodeString);
		TAG *AddNode(UnicodeString);
};
#endif /* #ifndef Class1H */


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
