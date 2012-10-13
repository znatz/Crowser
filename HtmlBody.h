#ifndef HtmlBodyH
#define HtmlBodyH

#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>

struct cBodyStruct
{
	 cBodyStruct* next;
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
		// The length of the stream
		int bodySize;

	private:
		// Holdes the stringstream received from initiator
		TStringStream* StrStr;
};
#endif /* #ifndef Class1H */

