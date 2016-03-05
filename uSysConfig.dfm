object fmSysConfig: TfmSysConfig
  Left = 0
  Top = 0
  Caption = #31995#32479#37197#32622
  ClientHeight = 450
  ClientWidth = 895
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
  object DBGrid1: TDBGrid
    Left = 0
    Top = 0
    Width = 337
    Height = 450
    Align = alLeft
    DataSource = dm.dsSysConfig
    ImeName = #20013#25991'('#31616#20307') - '#26497#28857#20116#31508
    TabOrder = 0
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'Tahoma'
    TitleFont.Style = []
    Columns = <
      item
        Expanded = False
        FieldName = 'item_name'
        Title.Caption = #35774#32622
        Width = 210
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'item_code'
        Visible = True
      end>
  end
  object DBGrid2: TDBGrid
    Left = 343
    Top = 0
    Width = 449
    Height = 169
    DataSource = dm.dsSysConfigDetail
    ImeName = #20013#25991'('#31616#20307') - '#26497#28857#20116#31508
    TabOrder = 1
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'Tahoma'
    TitleFont.Style = []
    Columns = <
      item
        Expanded = False
        FieldName = 'name'
        Title.Caption = #39033#30446
        Width = 107
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'value'
        Title.Caption = #20540
        Width = 150
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'code'
        Visible = True
      end>
  end
end
