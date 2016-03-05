object fmAirMode: TfmAirMode
  Left = 0
  Top = 0
  Caption = #31354#27668#27169#24335
  ClientHeight = 588
  ClientWidth = 1158
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Visible = True
  PixelsPerInch = 96
  TextHeight = 13
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 1158
    Height = 588
    ActivePage = TabSheet1
    Align = alClient
    TabOrder = 0
    object TabSheet1: TTabSheet
      Caption = #35774#32622
      object Label3: TLabel
        Left = 1080
        Top = 40
        Width = 48
        Height = 13
        Caption = #26102#38388#38388#38548
      end
      object dcgMod: TDBCtrlGrid
        Left = 9
        Top = 40
        Width = 1065
        Height = 510
        DataSource = dm.dsAirModeMod
        PanelHeight = 51
        PanelWidth = 1048
        TabOrder = 0
        RowCount = 10
        object Label1: TLabel
          Left = 16
          Top = 11
          Width = 24
          Height = 13
          Caption = #22320#22336
        end
        object port: TLabel
          Left = 192
          Top = 11
          Width = 24
          Height = 13
          Caption = #31471#21475
        end
        object baudrate: TLabel
          Left = 312
          Top = 11
          Width = 36
          Height = 13
          Caption = #27874#29305#29575
        end
        object Label2: TLabel
          Left = 574
          Top = 11
          Width = 60
          Height = 13
          Caption = #27874#29305#29575#21442#25968
        end
        object DBEdit1: TDBEdit
          Left = 46
          Top = 8
          Width = 121
          Height = 21
          DataField = 'addr'
          DataSource = dm.dsAirModeMod
          TabOrder = 0
        end
        object DBComboBox1: TDBComboBox
          Left = 222
          Top = 8
          Width = 65
          Height = 21
          Style = csDropDownList
          DataField = 'port'
          DataSource = dm.dsAirModeMod
          Items.Strings = (
            '1'
            '2'
            '3'
            '4'
            '5'
            '6'
            '7'
            '8'
            '9'
            '10'
            '11'
            '12'
            '13'
            '14'
            '15'
            '16'
            '17'
            '18'
            '19'
            '20')
          TabOrder = 1
        end
        object DBComboBox2: TDBComboBox
          Left = 360
          Top = 8
          Width = 73
          Height = 21
          Style = csDropDownList
          DataField = 'baud_rate'
          DataSource = dm.dsAirModeMod
          Items.Strings = (
            '9600'
            '19200'
            '38400')
          TabOrder = 2
        end
        object passive: TDBCheckBox
          Left = 448
          Top = 8
          Width = 41
          Height = 17
          Caption = #20027#21160
          DataField = 'passive'
          DataSource = dm.dsAirModeMod
          TabOrder = 3
          ValueChecked = 'True'
          ValueUnchecked = 'False'
        end
        object dac: TDBCheckBox
          Left = 512
          Top = 8
          Width = 65
          Height = 17
          Caption = 'dac'
          DataField = 'dac'
          DataSource = dm.dsAirModeMod
          TabOrder = 4
          ValueChecked = 'True'
          ValueUnchecked = 'False'
        end
        object DBComboBox3: TDBComboBox
          Left = 640
          Top = 8
          Width = 89
          Height = 21
          Style = csDropDownList
          DataField = 'command_baud_rate'
          DataSource = dm.dsAirModeMod
          Items.Strings = (
            '9600'
            '19200'
            '38400')
          TabOrder = 5
        end
      end
      object dbnvMod: TDBNavigator
        Left = 0
        Top = 1
        Width = 324
        Height = 33
        DataSource = dm.dsAirModeMod
        VisibleButtons = [nbInsert, nbDelete, nbEdit, nbPost, nbCancel, nbRefresh]
        TabOrder = 1
      end
      object btnRun: TButton
        Left = 1080
        Top = 168
        Width = 75
        Height = 25
        Caption = #25191#34892
        TabOrder = 2
        OnClick = btnRunClick
      end
      object edtInterval: TMaskEdit
        Left = 1080
        Top = 59
        Width = 57
        Height = 21
        TabOrder = 3
        Text = '1'
      end
      object btnStop: TButton
        Left = 1080
        Top = 232
        Width = 75
        Height = 25
        Caption = #20572#27490
        Enabled = False
        TabOrder = 4
        OnClick = btnStopClick
      end
      object Button1: TButton
        Left = 1080
        Top = 320
        Width = 75
        Height = 25
        Caption = #21442#25968#37197#32622
        TabOrder = 5
        OnClick = Button1Click
      end
      object cbRunMode: TCheckBox
        Left = 1080
        Top = 104
        Width = 97
        Height = 17
        Caption = #27169#25311#36816#34892
        Checked = True
        State = cbChecked
        TabOrder = 6
      end
    end
    object TabSheet2: TTabSheet
      Caption = #25968#25454
      ImageIndex = 1
      object DBGrid1: TDBGrid
        Left = 0
        Top = 0
        Width = 161
        Height = 560
        Align = alLeft
        DataSource = dm.dsLog
        TabOrder = 0
        TitleFont.Charset = DEFAULT_CHARSET
        TitleFont.Color = clWindowText
        TitleFont.Height = -11
        TitleFont.Name = 'Tahoma'
        TitleFont.Style = []
      end
      object Panel1: TPanel
        Left = 161
        Top = 0
        Width = 989
        Height = 560
        Align = alClient
        TabOrder = 1
        object Panel2: TPanel
          Left = 1
          Top = 1
          Width = 987
          Height = 48
          Align = alTop
          TabOrder = 0
        end
        object DBGrid2: TDBGrid
          Left = 1
          Top = 49
          Width = 987
          Height = 510
          Align = alClient
          DataSource = dsDetail
          TabOrder = 1
          TitleFont.Charset = DEFAULT_CHARSET
          TitleFont.Color = clWindowText
          TitleFont.Height = -11
          TitleFont.Name = 'Tahoma'
          TitleFont.Style = []
        end
      end
    end
  end
  object Timer1: TTimer
    Enabled = False
    OnTimer = Timer1Timer
    Left = 448
    Top = 8
  end
  object dsDetail: TDataSource
    DataSet = qryDetail
    Left = 464
    Top = 136
  end
  object qryDetail: TADOQuery
    Connection = dm.dbConn
    Parameters = <
      item
        Name = 'logid'
        Attributes = [paSigned, paNullable]
        DataType = ftInteger
        Precision = 10
        Size = 4
        Value = Null
      end>
    SQL.Strings = (
      'select * from exec_detail where log_id = :logid')
    Left = 416
    Top = 112
  end
end
