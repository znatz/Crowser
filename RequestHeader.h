#ifndef RequestHeaderH
#define RequestHeaderH

#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>

class RequestHeader
{

	public:
		RequestHeader(UnicodeString);

		UnicodeString UStrReqHdr;
		const char* HdrToSent;


};

#endif /* #ifndef RequestHeaderH */

