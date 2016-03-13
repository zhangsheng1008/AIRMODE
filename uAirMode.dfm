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
        object Label6: TLabel
          Left = 808
          Top = 8
          Width = 24
          Height = 13
          Caption = #21333#21495
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
        object DBEdit2: TDBEdit
          Left = 838
          Top = 8
          Width = 121
          Height = 21
          DataField = 'output_no'
          DataSource = dm.dsAirModeMod
          TabOrder = 6
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
        Top = 258
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
        Top = 289
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
      object Button2: TButton
        Left = 1080
        Top = 440
        Width = 75
        Height = 25
        Caption = 'Button2'
        TabOrder = 7
        Visible = False
        OnClick = Button2Click
      end
      object chkAnalyzer: TCheckBox
        Left = 1080
        Top = 136
        Width = 97
        Height = 17
        Caption = #36830#25509#20998#26512#20202
        TabOrder = 8
      end
      object chkPress: TCheckBox
        Left = 1080
        Top = 159
        Width = 97
        Height = 17
        Caption = #21387#21147
        TabOrder = 9
      end
      object chkTemp: TCheckBox
        Left = 1080
        Top = 182
        Width = 97
        Height = 17
        Caption = #28201#24230
        TabOrder = 10
      end
    end
    object TabSheet2: TTabSheet
      Caption = #25968#25454
      ImageIndex = 1
      object Panel1: TPanel
        Left = 0
        Top = 0
        Width = 1150
        Height = 560
        Align = alClient
        TabOrder = 0
        object Panel2: TPanel
          Left = 1
          Top = 1
          Width = 1148
          Height = 176
          Align = alTop
          TabOrder = 0
          object DBGrid3: TDBGrid
            Left = 1
            Top = 1
            Width = 784
            Height = 174
            Align = alLeft
            DataSource = dsAnalyzer
            Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgTitleClick, dgTitleHotTrack]
            TabOrder = 0
            TitleFont.Charset = DEFAULT_CHARSET
            TitleFont.Color = clWindowText
            TitleFont.Height = -11
            TitleFont.Name = 'Tahoma'
            TitleFont.Style = []
          end
          object btnExport: TButton
            Left = 1024
            Top = 136
            Width = 75
            Height = 25
            Caption = #23548#20986#25968#25454
            TabOrder = 1
          end
        end
        object tabResult: TTabControl
          Left = 1
          Top = 177
          Width = 1148
          Height = 382
          Align = alClient
          TabOrder = 1
          OnChange = tabResultChange
          object DBGrid2: TDBGrid
            Left = 4
            Top = 6
            Width = 1140
            Height = 372
            Align = alClient
            DataSource = dsDetail
            TabOrder = 0
            TitleFont.Charset = DEFAULT_CHARSET
            TitleFont.Color = clWindowText
            TitleFont.Height = -11
            TitleFont.Name = 'Tahoma'
            TitleFont.Style = []
            Columns = <
              item
                Expanded = False
                FieldName = 'addr'
                Width = 40
                Visible = True
              end
              item
                Expanded = False
                FieldName = 'passive'
                Width = 40
                Visible = True
              end
              item
                Expanded = False
                FieldName = 'dac'
                Width = 40
                Visible = True
              end
              item
                Expanded = False
                FieldName = 'baud_para'
                Width = 40
                Visible = True
              end
              item
                Expanded = False
                FieldName = 'port'
                Width = 40
                Visible = True
              end
              item
                Expanded = False
                FieldName = 'value_type'
                Width = 40
                Visible = True
              end
              item
                Expanded = False
                FieldName = 'v10'
                Width = 40
                Visible = True
              end
              item
                Expanded = False
                FieldName = 'v11'
                Width = 40
                Visible = True
              end
              item
                Expanded = False
                FieldName = 'v12'
                Width = 40
                Visible = True
              end
              item
                Expanded = False
                FieldName = 'v13'
                Width = 40
                Visible = True
              end
              item
                Expanded = False
                FieldName = 'v14'
                Width = 40
                Visible = True
              end
              item
                Expanded = False
                FieldName = 'v15'
                Width = 40
                Visible = True
              end
              item
                Expanded = False
                FieldName = 'v16'
                Width = 40
                Visible = True
              end
              item
                Expanded = False
                FieldName = 'v17'
                Width = 40
                Visible = True
              end
              item
                Expanded = False
                FieldName = 'v18'
                Width = 40
                Visible = True
              end
              item
                Expanded = False
                FieldName = 'v19'
                Width = 40
                Visible = True
              end
              item
                Expanded = False
                FieldName = 'v20'
                Width = 40
                Visible = True
              end
              item
                Expanded = False
                FieldName = 'v21'
                Width = 40
                Visible = True
              end
              item
                Expanded = False
                FieldName = 'v22'
                Width = 40
                Visible = True
              end
              item
                Expanded = False
                FieldName = 'v23'
                Width = 40
                Visible = True
              end
              item
                Expanded = False
                FieldName = 'v24'
                Width = 40
                Visible = True
              end
              item
                Expanded = False
                FieldName = 'v25'
                Width = 40
                Visible = True
              end
              item
                Expanded = False
                FieldName = 'v26'
                Width = 40
                Visible = True
              end
              item
                Expanded = False
                FieldName = 'v27'
                Width = 40
                Visible = True
              end
              item
                Expanded = False
                FieldName = 'v28'
                Width = 40
                Visible = True
              end
              item
                Expanded = False
                FieldName = 'v29'
                Width = 40
                Visible = True
              end>
          end
        end
      end
    end
    object TabSheet3: TTabSheet
      Caption = 'EEPROM'
      ImageIndex = 2
      object dbcgEEProm: TDBCtrlGrid
        Left = 16
        Top = 47
        Width = 1009
        Height = 466
        AllowDelete = False
        AllowInsert = False
        DataSource = dm.dsEEProm
        PanelHeight = 466
        PanelWidth = 992
        TabOrder = 0
        RowCount = 1
        object DBText1: TDBText
          Left = 32
          Top = 40
          Width = 65
          Height = 17
          DataField = 'addr'
          DataSource = dm.dsEEProm
        end
        object DBMemo1: TDBMemo
          Left = 416
          Top = 8
          Width = 377
          Height = 433
          DataField = 'return_info'
          DataSource = dm.dsEEProm
          TabOrder = 0
        end
        object DBMemo2: TDBMemo
          Left = 799
          Top = 8
          Width = 186
          Height = 433
          DataField = 'result'
          DataSource = dm.dsEEProm
          TabOrder = 1
        end
        object DBMemo3: TDBMemo
          Left = 184
          Top = 8
          Width = 226
          Height = 433
          DataField = 'command'
          DataSource = dm.dsEEProm
          TabOrder = 2
        end
      end
      object btnEEProm: TButton
        Left = 16
        Top = 16
        Width = 97
        Height = 25
        Caption = #35835#21462'EEPRom'
        TabOrder = 1
        OnClick = btnEEPromClick
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
    CursorType = ctStatic
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
      
        'select t1.addr, t1.passive, t1.dac, t1.baud_para, t1.port, t2.va' +
        'lue_type, t2.v10, t2.v11, t2.v12, t2.v13, t2.v14, t2.v15, t2.v16' +
        ', t2.v17, t2.v18, t2.v19,'
      
        't2.v20, t2.v21, t2.v22, t2.v23, t2.v24, t2.v25, t2.v26, t2.v27, ' +
        't2.v28, t2.v29    '
      #9'from exec_detail t1, gather_data t2 '
      #9'where t1.id=t2.detail_id '
      #9'and t1.log_id = :logid'
      #9'and t1.insert_time > GETDATE() - 1'
      '')
    Left = 416
    Top = 112
    object qryDetailaddr: TWideStringField
      FieldName = 'addr'
      Size = 10
    end
    object qryDetailpassive: TWideStringField
      FieldName = 'passive'
      Size = 10
    end
    object qryDetaildac: TWideStringField
      FieldName = 'dac'
      Size = 10
    end
    object qryDetailbaud_para: TWideStringField
      FieldName = 'baud_para'
      Size = 10
    end
    object qryDetailport: TWideStringField
      FieldName = 'port'
      Size = 10
    end
    object qryDetailvalue_type: TWideStringField
      FieldName = 'value_type'
      Size = 10
    end
    object qryDetailv10: TIntegerField
      FieldName = 'v10'
    end
    object qryDetailv11: TIntegerField
      FieldName = 'v11'
    end
    object qryDetailv12: TIntegerField
      FieldName = 'v12'
    end
    object qryDetailv13: TIntegerField
      FieldName = 'v13'
    end
    object qryDetailv14: TIntegerField
      FieldName = 'v14'
    end
    object qryDetailv15: TIntegerField
      FieldName = 'v15'
    end
    object qryDetailv16: TIntegerField
      FieldName = 'v16'
    end
    object qryDetailv17: TIntegerField
      FieldName = 'v17'
    end
    object qryDetailv18: TIntegerField
      FieldName = 'v18'
    end
    object qryDetailv19: TIntegerField
      FieldName = 'v19'
    end
    object qryDetailv20: TIntegerField
      FieldName = 'v20'
    end
    object qryDetailv21: TIntegerField
      FieldName = 'v21'
    end
    object qryDetailv22: TIntegerField
      FieldName = 'v22'
    end
    object qryDetailv23: TIntegerField
      FieldName = 'v23'
    end
    object qryDetailv24: TIntegerField
      FieldName = 'v24'
    end
    object qryDetailv25: TIntegerField
      FieldName = 'v25'
    end
    object qryDetailv26: TIntegerField
      FieldName = 'v26'
    end
    object qryDetailv27: TIntegerField
      FieldName = 'v27'
    end
    object qryDetailv28: TIntegerField
      FieldName = 'v28'
    end
    object qryDetailv29: TIntegerField
      FieldName = 'v29'
    end
  end
  object qryAnalyzer: TADOQuery
    Connection = dm.dbConn
    Parameters = <>
    SQL.Strings = (
      
        'select insert_time, analyzer_data, pressure_data, temp_data,humi' +
        '_data from analyzer_data where insert_time > getdate()-1')
    Left = 472
    Top = 64
  end
  object dsAnalyzer: TDataSource
    DataSet = qryAnalyzer
    Left = 624
    Top = 104
  end
  object Timer2: TTimer
    OnTimer = Timer2Timer
    Left = 656
    Top = 16
  end
end
