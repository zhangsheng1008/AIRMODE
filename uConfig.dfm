object fmSysConfig: TfmSysConfig
  Left = 0
  Top = 0
  Caption = #31995#32479#37197#32622
  ClientHeight = 483
  ClientWidth = 877
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object DBGrid1: TDBGrid
    Left = 8
    Top = 31
    Width = 861
    Height = 442
    DataSource = dm.dsSysConfig
    TabOrder = 0
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'Tahoma'
    TitleFont.Style = []
  end
  object DBNavigator1: TDBNavigator
    Left = 8
    Top = 0
    Width = 240
    Height = 25
    DataSource = dm.dsSysConfig
    TabOrder = 1
  end
end
