//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Graphics.hpp>
//---------------------------------------------------------------------------
class TFm : public TForm
{
__published:	// IDE-managed Components
	TEdit *Input;
	TButton *Button1;
	TButton *Sb;
	TButton *BtnConSz;
	TMemo *Output;
	TMemo *Err;
	TMemo *BodyEdt;
	TMemo *RqstHdr;
	TLabel *RqstLabel;
	TLabel *ErrLabel;
	TLabel *RspLabel;
	TLabel *BodyLabel;
	TRichEdit *BodyREdit;
	void __fastcall SbClick(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TFm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFm *Fm;
//---------------------------------------------------------------------------
#endif
