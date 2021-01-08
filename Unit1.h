//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TShape *tlo;
        TImage *paddle1;
        TImage *paddle2;
        TTimer *leftToUp;
        TTimer *leftToDown;
        TTimer *rightToDown;
        TTimer *rightToUp;
        TImage *ball;
        TTimer *TimerBall;
        TLabel *point;
        TLabel *score;
        TLabel *bounces;
        TButton *nextRoundB;
        TButton *newGameB;
        void __fastcall leftToDownTimer(TObject *Sender);
        void __fastcall leftToUpTimer(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall FormKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall rightToUpTimer(TObject *Sender);
        void __fastcall rightToDownTimer(TObject *Sender);
        void __fastcall TimerBallTimer(TObject *Sender);
        void __fastcall newGameBClick(TObject *Sender);
        void __fastcall nextRoundBClick(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
