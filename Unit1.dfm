object Form1: TForm1
  Left = 0
  Top = 0
  BorderStyle = bsSizeToolWin
  Caption = 'Control_panel_v1.1'
  ClientHeight = 256
  ClientWidth = 1012
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Button1: TButton
    Left = 534
    Top = 0
    Width = 177
    Height = 33
    Caption = 'Servers_status_check'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Comic Sans MS'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 502
    Top = 39
    Width = 209
    Height = 34
    Caption = 'Get_defect_decrease_ratio'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Comic Sans MS'
    Font.Style = []
    ParentFont = False
    TabOrder = 1
    OnClick = Button2Click
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 237
    Width = 1012
    Height = 19
    Panels = <
      item
        Width = 50
      end>
  end
  object Button3: TButton
    Left = 502
    Top = 79
    Width = 209
    Height = 34
    Caption = 'Set_defect_decrease_ratio'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Comic Sans MS'
    Font.Style = []
    ParentFont = False
    TabOrder = 3
    OnClick = Button3Click
  end
  object DateTimePicker1: TDateTimePicker
    Left = 534
    Top = 0
    Width = 103
    Height = 27
    Date = 41059.000000000000000000
    Format = 'yyyy-MM-dd hh:nn:ss'
    Time = 41059.000000000000000000
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = []
    ParseInput = True
    ParentFont = False
    TabOrder = 4
  end
  object Button4: TButton
    Left = 502
    Top = 119
    Width = 209
    Height = 34
    Caption = 'Get_del_count'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Comic Sans MS'
    Font.Style = []
    ParentFont = False
    TabOrder = 5
    OnClick = Button4Click
  end
  object Headers: TPanel
    Left = 5
    Top = -2
    Width = 434
    Height = 30
    TabOrder = 6
    object Header_Get: TLabel
      Left = 145
      Top = 8
      Width = 19
      Height = 13
      Caption = 'GET'
    end
    object Header_Set: TLabel
      Left = 168
      Top = 8
      Width = 18
      Height = 13
      Caption = 'SET'
    end
    object Headers_Status: TLabel
      Left = 88
      Top = 8
      Width = 38
      Height = 13
      Caption = 'STATUS'
    end
    object Header_Del: TLabel
      Left = 264
      Top = 8
      Width = 18
      Height = 13
      Caption = 'DEL'
    end
    object Header_IP_ADDRESS: TCheckBox
      Left = 0
      Top = 7
      Width = 97
      Height = 17
      Caption = 'IP_ADDRESS'
      Checked = True
      State = cbChecked
      TabOrder = 0
      OnClick = Header_IP_ADDRESSClick
    end
  end
  object Memo1: TMemo
    Left = 717
    Top = 3
    Width = 185
    Height = 89
    TabOrder = 7
  end
  object ProgressBar1: TProgressBar
    Left = 0
    Top = 135
    Width = 150
    Height = 17
    Max = 0
    Smooth = True
    BarColor = clBlue
    BackgroundColor = clGray
    SmoothReverse = True
    Step = 1
    TabOrder = 8
  end
  object IdCmdTCPClient1: TIdCmdTCPClient
    Intercept = IdLogFile1
    OnWorkEnd = IdCmdTCPClient1WorkEnd
    ConnectTimeout = 0
    Host = '192.168.1.5'
    IPVersion = Id_IPv4
    Port = 3000
    ReadTimeout = -1
    CommandHandlers = <>
    ExceptionReply.Code = '500'
    ExceptionReply.Text.Strings = (
      'Unknown Internal Error')
    Left = 136
    Top = 328
  end
  object IdLogFile1: TIdLogFile
    Left = 552
    Top = 176
  end
  object Timer1: TTimer
    Enabled = False
    Interval = 1500
    OnTimer = Timer1Timer
    Left = 752
    Top = 112
  end
  object Timer2: TTimer
    Enabled = False
    Interval = 1500
    OnTimer = Timer2Timer
    Left = 792
    Top = 112
  end
  object Timer3: TTimer
    Enabled = False
    Interval = 2500
    OnTimer = Timer3Timer
    Left = 824
    Top = 112
  end
  object Timer4: TTimer
    Enabled = False
    Interval = 1500
    OnTimer = Timer4Timer
    Left = 856
    Top = 112
  end
  object Timer5: TTimer
    Enabled = False
    Interval = 1500
    OnTimer = Timer5Timer
    Left = 744
    Top = 176
  end
  object BindingsList1: TBindingsList
    Methods = <>
    OutputConverters = <>
    UseAppManager = True
    Left = 20
    Top = 5
  end
  object Timer7: TTimer
    Enabled = False
    Interval = 1500
    OnTimer = Timer7Timer
    Left = 824
    Top = 176
  end
  object Timer8: TTimer
    Enabled = False
    Interval = 1500
    OnTimer = Timer8Timer
    Left = 856
    Top = 176
  end
end
