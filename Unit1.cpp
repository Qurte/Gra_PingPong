//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
int x = -8;
int y = -8;
int numberOfBallBounces = 0;
int numberOfFirstPlayerPoints = 0;
int numberOfSecondPlayerPoints = 0;
int numberToSpeedUp = 10;

void loss ()
{
     Form1->TimerBall->Enabled = false;
     Form1->ball->Visible = false;
     Form1->score->Caption = IntToStr(numberOfFirstPlayerPoints) + ":" +  IntToStr(numberOfSecondPlayerPoints);
     Form1->score->Visible = true;
     Form1->bounces->Caption = "Ilosc odbic: " + IntToStr(numberOfBallBounces);
     Form1->bounces->Visible = true;

     Form1->nextRoundB->Visible = true;
     Form1->newGameB->Visible = true;
}
void speedUpTheBall ()
{
        if (x > 0) x += 6;
        if (x < 0) x -= 6;
        if (y > 0) y += 5;
        if (y < 0) y -= 5;

        Form1->point->Caption = "Pilka przyspieszyla";
        Form1->point->Visible = true;
        Application->ProcessMessages(); Sleep(500);
        Form1->point->Visible = false;
}
void positionSetting ()
{
    Form1->paddle1->Left = Form1->tlo->Left + 30;
    Form1->paddle2->Left = Form1->tlo->Width - 30;
    Form1->paddle1->Top = Form1->tlo->Height /2;
    Form1->paddle2->Top = Form1->tlo->Height /2;
    Form1->point->Left = Form1->tlo->Width/2 - Form1->point->Width/2;
    Form1->score->Left = Form1->tlo->Width/2 - Form1->score->Width/2;
    Form1->bounces->Left = Form1->tlo->Width/2 - Form1->bounces->Width/2;
    Form1->nextRoundB->Left = Form1->tlo->Width/2 - Form1->nextRoundB->Width/2;
    Form1->newGameB->Left = Form1->tlo->Width/2 - Form1->newGameB->Width/2;
}
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------


void __fastcall TForm1::leftToDownTimer(TObject *Sender)
{
   if (paddle1->Top + paddle1->Height < tlo->Height - 10) paddle1->Top +=10;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::leftToUpTimer(TObject *Sender)
{
     if (paddle1->Top > 10) paddle1->Top -=10;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
     if (Key == 0x41) leftToUp->Enabled = true;
     if (Key == 0x5A) leftToDown->Enabled = true;
     if (Key == VK_UP) rightToUp->Enabled = true;
     if (Key == VK_DOWN) rightToDown->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
     if (Key == 0x41) leftToUp->Enabled = false;
     if (Key == 0x5A) leftToDown->Enabled = false;
     if (Key == VK_UP) rightToUp->Enabled = false;
     if (Key == VK_DOWN) rightToDown->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::rightToUpTimer(TObject *Sender)
{
  if (paddle2->Top > 10) paddle2->Top -=10;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::rightToDownTimer(TObject *Sender)
{
   if (paddle2->Top + paddle2->Height < tlo->Height - 10) paddle2->Top +=10;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::TimerBallTimer(TObject *Sender)
{
  ball->Left += x;
  ball->Top += y;

  //odbicie od górnej sciany
  if (ball->Top <= tlo->Top + 10) y = -y;
  // odbicie od dolnej sciany
  if (ball->Top + ball->Height + 10 >= tlo->Height) y = -y;

  // Przegrana pierwszego
  if (ball->Left <= paddle1->Left)
  {

     numberOfSecondPlayerPoints++;
     point->Caption = "Wygrana gracza po prawej  >";
     point->Visible = true;
     loss();

  }  //uderzenie paletki 1
  else if (ball->Top + ball->Height/2 >= paddle1->Top && ball->Top + ball->Height/2 <= paddle1->Top + paddle1->Height
      && ball->Left < paddle1->Left + paddle1->Width + 10)
      {
        x = -x;
        numberOfBallBounces++;
        if ((ball->Top + ball->Height/2 > paddle1->Top + paddle1->Height/2 - 20)
             && ball->Top +ball->Height/2 < paddle1->Top + paddle1->Height/2 + 20)
             {
               speedUpTheBall ();
             }
      }
  //Przegrana drugiego
  if (ball->Left > paddle2->Left)
  {
     numberOfFirstPlayerPoints++;
     point->Caption = "<  Wygrana gracza po lewej";
     point->Visible = true;
     loss();
  }    // uderzenie paletki 2
  else if (ball->Top + ball->Height/2 >= paddle2->Top && ball->Top + ball->Height/2 <= paddle2->Top + paddle2->Height
      && ball->Left + ball->Width > paddle2->Left -10)
      {
        x = -x;
        numberOfBallBounces++;
        if ( numberOfBallBounces >= numberToSpeedUp)
        {
            speedUpTheBall ();
            numberToSpeedUp += 10;
        }
        if ((ball->Top + ball->Height/2 > paddle2->Top + paddle2->Height/2 - 20)
             && ball->Top +ball->Height/2 < paddle2->Top + paddle2->Height/2 + 20)
             {
                speedUpTheBall();
             }
      }

}
//---------------------------------------------------------------------------
void __fastcall TForm1::newGameBClick(TObject *Sender)
{
   score->Visible = false;
   point->Visible = false;
   bounces->Visible = false;
   nextRoundB->Visible = false;
   ball->Left = 800;
   ball->Top  = 300;
   ball->Visible = true;
   newGameB->Visible = false;
   numberOfBallBounces = 0;
   numberOfFirstPlayerPoints = 0;
   numberOfSecondPlayerPoints = 0;
   numberToSpeedUp = 10;
   TimerBall->Enabled = true;

   positionSetting ();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::nextRoundBClick(TObject *Sender)
{
        score->Visible = false;
        point->Visible = false;
        bounces->Visible = false;
        nextRoundB->Visible = false;
        newGameB->Visible = false;
        ball->Left = 800;
        ball->Top  = 300;
        ball->Visible = true;
        numberOfBallBounces = 0;
        numberToSpeedUp = 10;
        TimerBall->Enabled = true;
        positionSetting ();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
  Application->MessageBox("Witaj w grze PingPong."
             "\n\nLewy gracz steruje wciskajac klawisze A oraz Z"
             "\nPrawy gracz steruje wciskaj¹c klawisze strza³ek w góre i w dó³"
             "\n\nDla urozmaicenia zabawy: \nKiedy odbijesz pi³kê na srodku paletki, wówczas zmienisz jej k¹t odbicia i pi³ka przyspieszy. "
             "\nIm d³u¿ej odbijasz, tym pi³ka szybciej przemieszcza siê. \nMo¿esz dowolnie zmienia pole gry \n\nMi³ej zabawy! "
             ,"Gra w PingPonga", MB_OK);
    numberOfBallBounces = 0;
    numberOfFirstPlayerPoints = 0;
    numberOfSecondPlayerPoints = 0;
    numberToSpeedUp = 10;

    point->Caption = "Witamy w grze PingPong";
    point->Visible = true;

    positionSetting ();
}
//---------------------------------------------------------------------------
