object fmComponentConfig: TfmComponentConfig
  Left = 0
  Top = 0
  Caption = #32452#20214#21450#21629#20196#37197#32622
  ClientHeight = 786
  ClientWidth = 1108
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  FormStyle = fsMDIChild
  OldCreateOrder = False
  Visible = True
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 446
    Top = 20
    Width = 26
    Height = 13
    Caption = 'name'
    FocusControl = DBEdit1
  end
  object Label2: TLabel
    Left = 648
    Top = 21
    Width = 20
    Height = 13
    Caption = 'port'
    FocusControl = DBEdit2
  end
  object Label3: TLabel
    Left = 900
    Top = 21
    Width = 50
    Height = 13
    Caption = 'baud_rate'
    FocusControl = DBEdit3
  end
  object Label4: TLabel
    Left = 446
    Top = 349
    Width = 42
    Height = 13
    Caption = 'write_tpl'
    FocusControl = DBEdit4
  end
  object Label5: TLabel
    Left = 446
    Top = 491
    Width = 40
    Height = 13
    Caption = 'read_tpl'
    FocusControl = DBEdit5
  end
  object Label6: TLabel
    Left = 446
    Top = 536
    Width = 32
    Height = 13
    Caption = 'rpara1'
    FocusControl = DBEdit6
  end
  object Label7: TLabel
    Left = 600
    Top = 538
    Width = 32
    Height = 13
    Caption = 'rpara2'
    FocusControl = DBEdit7
  end
  object Label10: TLabel
    Left = 446
    Top = 392
    Width = 36
    Height = 13
    Caption = 'wpara1'
    FocusControl = DBEdit10
  end
  object Label11: TLabel
    Left = 596
    Top = 395
    Width = 36
    Height = 13
    Caption = 'wpara2'
    FocusControl = DBEdit11
  end
  object Label12: TLabel
    Left = 746
    Top = 392
    Width = 36
    Height = 13
    Caption = 'wpara3'
  end
  object Label14: TLabel
    Left = 900
    Top = 352
    Width = 36
    Height = 13
    Caption = 'interval'
    FocusControl = DBEdit14
  end
  object dbComponet: TDBGrid
    Left = 8
    Top = 39
    Width = 409
    Height = 282
    TabOrder = 0
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'Tahoma'
    TitleFont.Style = []
    Columns = <
      item
        Expanded = False
        FieldName = 'type'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'name'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'port'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'baud_rate'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'stop_bits'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'byte_size'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'parity'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'fparity'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'component_code'
        Visible = True
      end>
  end
  object DBNavigator1: TDBNavigator
    Left = 8
    Top = 8
    Width = 240
    Height = 25
    TabOrder = 1
  end
  object DBGrid1: TDBGrid
    Left = 8
    Top = 368
    Width = 409
    Height = 217
    TabOrder = 2
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'Tahoma'
    TitleFont.Style = []
    Columns = <
      item
        Expanded = False
        FieldName = 'desc'
        Width = 179
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'times'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'interval'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'type'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'command_type'
        Visible = True
      end>
  end
  object DBNavigator2: TDBNavigator
    Left = 8
    Top = 337
    Width = 240
    Height = 25
    TabOrder = 3
  end
  object btnSend: TButton
    Left = 8
    Top = 591
    Width = 75
    Height = 25
    Caption = #21457#36865#27979#35797
    TabOrder = 4
  end
  object memoLog: TMemo
    Left = 8
    Top = 622
    Width = 897
    Height = 156
    Lines.Strings = (
      '')
    TabOrder = 5
  end
  object DBEdit1: TDBEdit
    Left = 446
    Top = 39
    Width = 134
    Height = 21
    DataField = 'name'
    TabOrder = 6
  end
  object DBEdit2: TDBEdit
    Left = 648
    Top = 37
    Width = 134
    Height = 21
    DataField = 'port'
    TabOrder = 7
  end
  object DBEdit3: TDBEdit
    Left = 900
    Top = 37
    Width = 134
    Height = 21
    DataField = 'baud_rate'
    TabOrder = 8
  end
  object DBEdit4: TDBEdit
    Left = 446
    Top = 368
    Width = 434
    Height = 21
    DataField = 'write_tpl'
    TabOrder = 9
  end
  object DBEdit5: TDBEdit
    Left = 446
    Top = 507
    Width = 284
    Height = 21
    DataField = 'read_tpl'
    TabOrder = 10
  end
  object DBEdit6: TDBEdit
    Left = 446
    Top = 552
    Width = 134
    Height = 21
    DataField = 'rpara1'
    TabOrder = 11
  end
  object DBEdit7: TDBEdit
    Left = 600
    Top = 554
    Width = 134
    Height = 21
    DataField = 'rpara2'
    TabOrder = 12
  end
  object DBEdit10: TDBEdit
    Left = 446
    Top = 411
    Width = 134
    Height = 21
    DataField = 'wpara1'
    TabOrder = 13
  end
  object DBEdit11: TDBEdit
    Left = 596
    Top = 411
    Width = 134
    Height = 21
    DataField = 'wpara2'
    TabOrder = 14
  end
  object DBEdit14: TDBEdit
    Left = 900
    Top = 368
    Width = 134
    Height = 21
    DataField = 'interval'
    TabOrder = 15
  end
  object DBCheckBox1: TDBCheckBox
    Left = 446
    Top = 448
    Width = 67
    Height = 17
    Caption = 'checksum'
    DataField = 'checksum'
    TabOrder = 16
    ValueChecked = 'True'
    ValueUnchecked = 'False'
  end
  object Button1: TButton
    Left = 952
    Top = 680
    Width = 75
    Height = 25
    Caption = #36864#20986
    TabOrder = 17
    OnClick = Button1Click
  end
  object DBMemo1: TDBMemo
    Left = 746
    Top = 411
    Width = 343
    Height = 174
    DataField = 'wpara3'
    TabOrder = 18
  end
end
