//---------------------------------------------------------------------------
//-dqwd
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include <Inifiles.hpp>
#include <IdSync.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

class update_c : public TThread
{
private:
protected:
	void __fastcall Execute();
public:
	__fastcall update_c(bool CreateSuspended);
};
//---------------------------------------------------------------------------
#endif

__fastcall update_c::update_c(bool CreateSuspended)
	: TThread(CreateSuspended)
{
}
//---------------------------------------------------------------------------
void __fastcall update_c::Execute()
{
ShowMessage("213");
}
//---------------------------------------------------------------------------




UnicodeString Temp_result;
bool checked = true;
int Server_IPs_count = 0;
TIniFile *SettingsINI = new TIniFile(ExtractFileDir(Application->ExeName) + "\\settings.ini");

TStringList *Server_IPs = new TStringList;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
Form1->ProgressBar1->Max = 0;
for(int i = 0; i < Server_IPs->Count; i++)
{
if (((TCheckBox*)Form1->FindComponent("CheckBox" + IntToStr(i)))->Checked == true)
{
Form1->ProgressBar1->Max = Form1->ProgressBar1->Max + 1;
}
}
Form1->ProgressBar1->Position = 0;
checked = true;
Form1->Button1->Enabled = false;
Form1->Button2->Enabled = false;
Form1->Button3->Enabled = false;
Form1->Button4->Enabled = false;

Form1->StatusBar1->Panels->Items[0]->Text = "Starting Status Check";
Server_IPs_count = 0;
while (Server_IPs_count < Server_IPs->Count)
{
Application->ProcessMessages();
if (Server_IPs_count >= Server_IPs->Count) {
break;
}
//Application->ProcessMessages();
if (((TCheckBox*)Form1->FindComponent("CheckBox" + IntToStr(Server_IPs_count)))->Checked == true)
{

if (checked == true) {
checked = false;
((TLabel*)FindComponent("Label" + IntToStr(Server_IPs_count)))->Caption = "";
try
{
if (Form1->IdCmdTCPClient1->Connected() == true) {
Form1->IdCmdTCPClient1->Disconnect();
}
Form1->IdCmdTCPClient1->Connect(Server_IPs->Strings[Server_IPs_count], 3000);
Form1->Timer2->Enabled = true;
}

catch (EIdException *Error)
{
ShowMessage("For Server IP Address " + Server_IPs->Strings[Server_IPs_count] + " occured the next ERROR: " + Error->Message);
Form1->Timer2->Enabled = false;
Form1->ProgressBar1->Position = Form1->ProgressBar1->Position + 1;
checked = true;
((TLabel*)FindComponent("Label" + IntToStr(Server_IPs_count)))->Color = clRed;
((TLabel*)FindComponent("Label" + IntToStr(Server_IPs_count)))->Font->Color = clWhite;
((TLabel*)FindComponent("Label" + IntToStr(Server_IPs_count)))->Caption = "Stopped";
Server_IPs_count++;
}
}

}
else
{
Server_IPs_count++;
}
}

Form1->Button1->Enabled = true;
Form1->Button2->Enabled = true;
Form1->Button3->Enabled = true;
Form1->Button4->Enabled = true;
}

//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
Form1->ProgressBar1->Max = 0;
for(int i = 0; i < Server_IPs->Count; i++)
{
if (((TCheckBox*)Form1->FindComponent("CheckBox" + IntToStr(i)))->Checked == true)
{
Form1->ProgressBar1->Max = Form1->ProgressBar1->Max + 1;
}
}
Form1->ProgressBar1->Position = 0;
checked = true;
Form1->Memo1->Clear();
Form1->Button1->Enabled = false;
Form1->Button2->Enabled = false;
Form1->Button3->Enabled = false;
Form1->Button4->Enabled = false;

Form1->StatusBar1->Panels->Items[0]->Text = "Starting GET";
Server_IPs_count = 0;
while (Server_IPs_count < Server_IPs->Count)
{
Application->ProcessMessages();
if (Server_IPs_count >= Server_IPs->Count) {
break;
}
//Application->ProcessMessages();
if (((TCheckBox*)Form1->FindComponent("CheckBox" + IntToStr(Server_IPs_count)))->Checked == true)
{

if (checked == true) {
checked = false;
((TEdit*)Form1->FindComponent("Edit" + IntToStr(Server_IPs_count)))->Text = "";
try
{
Form1->IdCmdTCPClient1->LastCmdResult->Clear();
if (Form1->IdCmdTCPClient1->Connected() == true) {
Form1->IdCmdTCPClient1->Disconnect();
}
Form1->IdCmdTCPClient1->Connect(Server_IPs->Strings[Server_IPs_count], 3000);


Form1->Timer5->Enabled = true;
}

catch (EIdException *Error)
{
ShowMessage("For Server IP Address " + Server_IPs->Strings[Server_IPs_count] + " occured the next ERROR: " + Error->Message);
Form1->Timer5->Enabled = false;
Form1->Timer1->Enabled = false;
Form1->ProgressBar1->Position = Form1->ProgressBar1->Position + 1;
checked = true;
((TEdit*)Form1->FindComponent("Edit" + IntToStr(Server_IPs_count)))->Text = "ERROR";
Server_IPs_count++;
}
}

}
else
{
Server_IPs_count++;
}
}

Form1->Button1->Enabled = true;
Form1->Button2->Enabled = true;
Form1->Button3->Enabled = true;
Form1->Button4->Enabled = true;
}
//---------------------------------------------------------------------------




void __fastcall TForm1::FormCreate(TObject *Sender)
{
if (ForceDirectories(ExtractFileDir(Application->ExeName) + "\\connection_logs\\") == true)
	  {
	  Form1->IdLogFile1->Filename = ExtractFileDir(Application->ExeName) + "\\connection_logs\\" + Date().FormatString("yyyymmdd") + ".log";
	  Form1->IdLogFile1->Active = true;
	  }


Form1->DateTimePicker1->Format = "yyyy-MM-dd hh:nn:ss";
Form1->DateTimePicker1->Date = Date();

Form1->IdCmdTCPClient1->ConnectTimeout = 7000;
Form1->IdCmdTCPClient1->ReadTimeout = 7000;
Form1->StatusBar1->Panels->Items[0]->Width = Form1->StatusBar1->Width;

SettingsINI->ReadSectionValues("Server_IPs", Server_IPs);
if (Server_IPs->Count != 0) {
for (int Server_IPs_count = 0; Server_IPs_count < Server_IPs->Count; Server_IPs_count++) {
if (Server_IPs->Strings[Server_IPs_count].Pos("=") != Server_IPs->Strings[Server_IPs_count].Length()) {
Server_IPs->Strings[Server_IPs_count] = Server_IPs->Strings[Server_IPs_count].SubString(Server_IPs->Strings[Server_IPs_count].Pos("=") + 1, Server_IPs->Strings[Server_IPs_count].Length() - Server_IPs->Strings[Server_IPs_count].Pos("="));

TPanel *Panel = new TPanel(Form1);
Panel->Name = "Panel" + IntToStr(Server_IPs_count);
Panel->Left = 5;
Panel->Top = Form1->Headers->Height + Panel->Height*Server_IPs_count;
Panel->Visible = true;
Panel->Enabled = true;
Panel->Parent = Form1;
Panel->Alignment = taCenter;
Panel->Font->Size = 12;
Panel->Caption = "";
Panel->AutoSize = true;

TCheckBox *CheckBox = new TCheckBox(Form1);
CheckBox->Name = "CheckBox" + IntToStr(Server_IPs_count);
CheckBox->Left = 0;
CheckBox->Top = Panel->Height/2 - CheckBox->Height/2;//10 + (CheckBox->Height + 15)*Server_IPs_count;
CheckBox->Visible = true;
CheckBox->Enabled = true;
CheckBox->Parent = (TPanel*)FindComponent("Panel" + IntToStr(Server_IPs_count));
CheckBox->Alignment = taCenter;
CheckBox->Font->Size = 12;
CheckBox->Checked = true;
CheckBox->Width = 145;
CheckBox->Caption = Server_IPs->Strings[Server_IPs_count];

TLabel *Label = new TLabel(Form1);
Label->Name = "Label" + IntToStr(Server_IPs_count);
Label->Left = 5 + CheckBox->Width;
Label->Top = Panel->Height/2 - Label->Height/2 - 2;
Label->Visible = true;
Label->Enabled = true;
Label->Parent = (TPanel*)FindComponent("Panel" + IntToStr(Server_IPs_count));
Label->Alignment = taCenter;
Label->Font->Size = 12;
Label->Width = 145;
Label->Caption = "Not defined";

TEdit *Edit = new TEdit(Form1);
Edit->Name = "Edit" + IntToStr(Server_IPs_count);
Edit->Left = 40 + CheckBox->Width + Label->Width;
Edit->Top = Panel->Height/2 - Edit->Height/2 - 3;
Edit->Visible = true;
Edit->Enabled = true;
Edit->Parent = (TPanel*)FindComponent("Panel" + IntToStr(Server_IPs_count));
Edit->Alignment = taRightJustify;
Edit->Font->Size = 12;
Edit->Width = 40;
Edit->NumbersOnly = true;
Edit->MaxLength = 3;
Edit->Font->Size = 10;
Edit->Text = "";
Edit->ReadOnly = true;

TEdit *Edit2 = new TEdit(Form1);
Edit2->Name = "Edit_set" + IntToStr(Server_IPs_count);
Edit2->Left = 40 + CheckBox->Width + Label->Width + Edit->Width + 10;
Edit2->Top = Panel->Height/2 - Edit2->Height/2 - 3;
Edit2->Visible = true;
Edit2->Enabled = true;
Edit2->Parent = (TPanel*)FindComponent("Panel" + IntToStr(Server_IPs_count));
Edit2->Alignment = taRightJustify;
Edit2->Font->Size = 12;
Edit2->Width = 40;
Edit2->NumbersOnly = true;
Edit2->MaxLength = 3;
Edit2->Font->Size = 10;
Edit2->Text = "";

TEdit *Edit3 = new TEdit(Form1);
Edit3->Name = "Edit_del_count" + IntToStr(Server_IPs_count);
Edit3->Left = 40 + CheckBox->Width + Label->Width + Edit->Width + Edit2->Width + 20;
Edit3->Top = Panel->Height/2 - Edit3->Height/2 - 3;
Edit3->Visible = true;
Edit3->Enabled = true;
Edit3->Parent = (TPanel*)FindComponent("Panel" + IntToStr(Server_IPs_count));
Edit3->Alignment = taRightJustify;
Edit3->Font->Size = 12;
Edit3->Width = 40;
Edit3->NumbersOnly = true;
Edit3->MaxLength = 3;
Edit3->Font->Size = 10;
Edit3->Text = "";
Edit3->ReadOnly = true;

Form1->DateTimePicker1->Left = ((TPanel*)Form1->FindComponent("Panel" + IntToStr(Server_IPs_count)))->Left + ((TPanel*)Form1->FindComponent("Panel" + IntToStr(Server_IPs_count)))->Width + 225;

Form1->ProgressBar1->Height = 20;
Form1->ProgressBar1->Width = ((TPanel*)Form1->FindComponent("Panel" + IntToStr(Server_IPs_count)))->Left + ((TPanel*)Form1->FindComponent("Panel" + IntToStr(Server_IPs_count)))->Width + 225;
Form1->ProgressBar1->Top = ((TPanel*)Form1->FindComponent("Panel" + IntToStr(Server_IPs_count)))->Top + ((TPanel*)Form1->FindComponent("Panel" + IntToStr(Server_IPs_count)))->Height + 10;

Form1->StatusBar1->Top = Form1->ProgressBar1->Top + Form1->ProgressBar1->Height + 5;
}
else
{
Server_IPs->Delete(Server_IPs_count);
Server_IPs_count--;
}
}
Form1->Headers->Width = 408;

Form1->Header_IP_ADDRESS->Width = 100;
Form1->Header_IP_ADDRESS->Left = ((TCheckBox*)Form1->FindComponent("CheckBox0"))->Left + 5;

Form1->Headers_Status->Width = 145;
Form1->Headers_Status->Left = Form1->Header_IP_ADDRESS->Width + 75;

Form1->Header_Get->Width = 40;
Form1->Header_Get->Left =  35 + Header_IP_ADDRESS->Width + Form1->Headers_Status->Width;

Form1->Header_Set->Width = 40;
Form1->Header_Set->Left =  45 + Header_IP_ADDRESS->Width + Form1->Headers_Status->Width + Form1->Header_Get->Width;

Form1->Header_Del->Width = 40;
Form1->Header_Del->Left =  55 + Header_IP_ADDRESS->Width + Form1->Headers_Status->Width + Form1->Header_Get->Width + Form1->Header_Set->Width;

Form1->AutoSize = true;
}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
Form1->ProgressBar1->Max = 0;
for(int i = 0; i < Server_IPs->Count; i++)
{
if (((TCheckBox*)Form1->FindComponent("CheckBox" + IntToStr(i)))->Checked == true)
{
Form1->ProgressBar1->Max = Form1->ProgressBar1->Max + 1;
}
}
Form1->ProgressBar1->Position = 0;
checked = true;
Form1->Button1->Enabled = false;
Form1->Button2->Enabled = false;
Form1->Button3->Enabled = false;
Form1->Button4->Enabled = false;

Form1->StatusBar1->Panels->Items[0]->Text = "Starting GET";
Server_IPs_count = 0;
while (Server_IPs_count < Server_IPs->Count)
{
Application->ProcessMessages();
if (Server_IPs_count >= Server_IPs->Count) {
break;
}
//Application->ProcessMessages();
if (((TCheckBox*)Form1->FindComponent("CheckBox" + IntToStr(Server_IPs_count)))->Checked == true)
{

if (checked == true) {
checked = false;
((TEdit*)Form1->FindComponent("Edit" + IntToStr(Server_IPs_count)))->Text = "";
try
{
Form1->IdCmdTCPClient1->LastCmdResult->Clear();
if (Form1->IdCmdTCPClient1->Connected() == true) {
Form1->IdCmdTCPClient1->Disconnect();
}
Form1->IdCmdTCPClient1->Connect(Server_IPs->Strings[Server_IPs_count], 3000);


Form1->Timer7->Enabled = true;
}

catch (EIdException *Error)
{
ShowMessage("For Server IP Address " + Server_IPs->Strings[Server_IPs_count] + " occured the next ERROR: " + Error->Message);
Form1->Timer7->Enabled = false;
Form1->Timer3->Enabled = false;
Form1->ProgressBar1->Position = Form1->ProgressBar1->Position + 1;
checked = true;
((TEdit*)Form1->FindComponent("Edit" + IntToStr(Server_IPs_count)))->Text = "ERROR";
Server_IPs_count++;
}
}

}
else
{
Server_IPs_count++;
}
}

Form1->Button1->Enabled = true;
Form1->Button2->Enabled = true;
Form1->Button3->Enabled = true;
Form1->Button4->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
Form1->ProgressBar1->Max = 0;
for(int i = 0; i < Server_IPs->Count; i++)
{
if (((TCheckBox*)Form1->FindComponent("CheckBox" + IntToStr(i)))->Checked == true)
{
Form1->ProgressBar1->Max = Form1->ProgressBar1->Max + 1;
}
}
Form1->ProgressBar1->Position = 0;
checked = true;
Form1->Memo1->Clear();
Form1->Button1->Enabled = false;
Form1->Button2->Enabled = false;
Form1->Button3->Enabled = false;
Form1->Button4->Enabled = false;

Form1->StatusBar1->Panels->Items[0]->Text = "Starting GET";
Server_IPs_count = 0;
while (Server_IPs_count < Server_IPs->Count)
{
Application->ProcessMessages();
if (Server_IPs_count >= Server_IPs->Count) {
break;
}
//Application->ProcessMessages();
if (((TCheckBox*)Form1->FindComponent("CheckBox" + IntToStr(Server_IPs_count)))->Checked == true)
{

if (checked == true) {
checked = false;
((TEdit*)Form1->FindComponent("Edit_del_count" + IntToStr(Server_IPs_count)))->Text = "";
try
{
Form1->IdCmdTCPClient1->LastCmdResult->Clear();
if (Form1->IdCmdTCPClient1->Connected() == true) {
Form1->IdCmdTCPClient1->Disconnect();
}
Form1->IdCmdTCPClient1->Connect(Server_IPs->Strings[Server_IPs_count], 3000);


Form1->Timer8->Enabled = true;
}

catch (EIdException *Error)
{
ShowMessage("For Server IP Address " + Server_IPs->Strings[Server_IPs_count] + " occured the next ERROR: " + Error->Message);
Form1->Timer8->Enabled = false;
Form1->Timer4->Enabled = false;
Form1->ProgressBar1->Position = Form1->ProgressBar1->Position + 1;
checked = true;
((TEdit*)Form1->FindComponent("Edit_del_count" + IntToStr(Server_IPs_count)))->Text = "ERROR";
Server_IPs_count++;
}
}

}
else
{
Server_IPs_count++;
}
}

Form1->Button1->Enabled = true;
Form1->Button2->Enabled = true;
Form1->Button3->Enabled = true;
Form1->Button4->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Header_IP_ADDRESSClick(TObject *Sender)
{
bool Checked = true;
if (Form1->Header_IP_ADDRESS->Checked == false) {
Checked = false;
}
else
{
Checked = true;

}
for (int Server_IPs_count = 0; Server_IPs_count < Server_IPs->Count; Server_IPs_count++) {
((TCheckBox*)Form1->FindComponent("CheckBox" + IntToStr(Server_IPs_count)))->Checked = Checked;
}
}
//---------------------------------------------------------------------------



void __fastcall TForm1::Timer1Timer(TObject *Sender)
{

Form1->Timer1->Enabled = false;
Temp_result = "";
Temp_result = Form1->IdCmdTCPClient1->LastCmdResult->Text->Text;
if (Temp_result.Pos("\r\n") != 0) {
((TEdit*)Form1->FindComponent("Edit" + IntToStr(Server_IPs_count)))->Text = Temp_result;
Form1->IdCmdTCPClient1->Disconnect(true);

Form1->ProgressBar1->Position = Form1->ProgressBar1->Position + 1;
Server_IPs_count++;
checked = true;

}
else
{
Form1->Timer1->Enabled = true;
}

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer2Timer(TObject *Sender)
{
Form1->Timer2->Enabled = false;
if (Form1->IdCmdTCPClient1->Connected() == true) {
((TLabel*)FindComponent("Label" + IntToStr(Server_IPs_count)))->Color = clGreen;
((TLabel*)FindComponent("Label" + IntToStr(Server_IPs_count)))->Font->Color = clWhite;
((TLabel*)FindComponent("Label" + IntToStr(Server_IPs_count)))->Caption = "Running";
Form1->ProgressBar1->Position = Form1->ProgressBar1->Position + 1;
Application->ProcessMessages();
Form1->IdCmdTCPClient1->Disconnect(true);

Server_IPs_count++;
checked = true;
}
else
{
Form1->Timer2->Enabled = true;
}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer3Timer(TObject *Sender)
{
Form1->Timer3->Enabled = false;
Temp_result = "";
Temp_result = Form1->IdCmdTCPClient1->LastCmdResult->Text->Text;
if (Temp_result.Pos("\r\n") != 0) {
((TEdit*)Form1->FindComponent("Edit" + IntToStr(Server_IPs_count)))->Text = Temp_result;

Form1->IdCmdTCPClient1->Disconnect(true);

Form1->ProgressBar1->Position = Form1->ProgressBar1->Position + 1;
Application->ProcessMessages();
Server_IPs_count++;
checked = true;
}
else
{
Form1->Timer3->Enabled = true;
}
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Timer4Timer(TObject *Sender)
{
Form1->Timer4->Enabled = false;
Temp_result = "";
Temp_result = Form1->IdCmdTCPClient1->LastCmdResult->Text->Text;
if (Temp_result.Pos("\r\n") != 0) {
if (Temp_result.Pos("Ok") != 0) {
Temp_result = "0";
}
((TEdit*)Form1->FindComponent("Edit_del_count" + IntToStr(Server_IPs_count)))->Text = Temp_result;

Form1->IdCmdTCPClient1->Disconnect(true);

Form1->ProgressBar1->Position = Form1->ProgressBar1->Position + 1;
Application->ProcessMessages();
Server_IPs_count++;
checked = true;
}
else
{
Form1->Timer4->Enabled = true;
}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer5Timer(TObject *Sender)
{
Form1->Timer5->Enabled = false;
if (Form1->IdCmdTCPClient1->Connected() == true) {
Form1->IdCmdTCPClient1->SendCmd("get_defect_count_ratio 1", 202, TEncoding::UTF8);
Form1->Timer1->Enabled = true;

}
else
{
Form1->Timer5->Enabled = true;
}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer7Timer(TObject *Sender)
{
Form1->Timer7->Enabled = false;
if (Form1->IdCmdTCPClient1->Connected() == true) {
Form1->IdCmdTCPClient1->SendCmd("set_defect_count_ratio " + ((TEdit*)Form1->FindComponent("Edit_set" + IntToStr(Server_IPs_count)))->Text, 203, TEncoding::UTF8);
Form1->Timer3->Enabled = true;
Application->ProcessMessages();
}
else
{
Form1->Timer7->Enabled = true;
}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer8Timer(TObject *Sender)
{
Form1->Timer8->Enabled = false;
if (Form1->IdCmdTCPClient1->Connected() == true) {
Form1->IdCmdTCPClient1->SendCmd("get_del_count " + Form1->DateTimePicker1->Date.FormatString("yyyymmdd"), 205, TEncoding::UTF8);
Form1->Timer4->Enabled = true;
Application->ProcessMessages();
}
else
{
Form1->Timer8->Enabled = true;
}


}
//---------------------------------------------------------------------------


void __fastcall TForm1::IdCmdTCPClient1WorkEnd(TObject *ASender, TWorkMode AWorkMode)

{
TIdSync::SynchronizeMethod(ShowMessage("11"));
}
//---------------------------------------------------------------------------

