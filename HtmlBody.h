#ifndef HtmlBodyH
#define HtmlBodyH

#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>

struct TagProperty
{
	UnicodeString 	TagPara;
	UnicodeString 	TagVal;
	TagProperty    	*next;
};


struct Tag
{
	UnicodeString 	TagName;
	TagProperty*	TagPro;
};


struct BodyStruct
{
	 Tag 			BodyTag;
	 UnicodeString 	BodyIn;
	 BodyStruct* 	next;
};

class HtmlBody
{
	public:
		// Constructor and initiator
		HtmlBody();
		void SetBody(char*, int, int);
		// Save the stream to file
		void SaveToFile(UnicodeString fn);

		// Here is the string created from the stream strstr
		UnicodeString cBody;
		BodyStruct*	  cBodyStruct;
		// The length of the stream
		int bodySize;

	private:
		// Holdes the stringstream received from initiator
		TStringStream* StrStr;
		// Destruct body
		void Destruct();
};
#endif /* #ifndef Class1H */

