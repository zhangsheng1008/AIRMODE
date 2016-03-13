object dm: Tdm
  OldCreateOrder = False
  OnCreate = DataModuleCreate
  Height = 545
  Width = 891
  object dbConn: TADOConnection
    CommandTimeout = 5
    ConnectionString = 
      'Provider=SQLNCLI11.1;Integrated Security=SSPI;Persist Security I' +
      'nfo=False;User ID="";Initial Catalog=airmode;Data Source=ZSLABTO' +
      'P-PC\SQLEXPRESS;Initial File Name="";Server SPN="";'
    ConnectionTimeout = 30
    LoginPrompt = False
    Provider = 'SQLNCLI11.1'
    Left = 56
    Top = 16
  end
  object dsAirModeMod: TDataSource
    DataSet = tbAirModeMod
    Left = 128
    Top = 16
  end
  object tbAirModeMod: TADOTable
    Connection = dbConn
    CursorType = ctStatic
    TableName = 'module_config'
    Left = 128
    Top = 88
  end
  object tbSysConfig: TADOTable
    Connection = dbConn
    TableName = 'sys_config'
    Left = 760
    Top = 16
  end
  object dsSysConfig: TDataSource
    DataSet = tbSysConfig
    Left = 760
    Top = 80
  end
  object execLog: TADOTable
    Connection = dbConn
    CursorType = ctStatic
    Filter = '1=2'
    TableName = 'exec_log'
    Left = 248
    Top = 16
  end
  object dsLog: TDataSource
    DataSet = execLog
    Left = 248
    Top = 88
  end
  object tbEEProm: TADOTable
    Connection = dbConn
    CursorType = ctStatic
    TableName = 'eeprom_data'
    Left = 616
    Top = 232
  end
  object tbAnalyzer: TADOTable
    Connection = dbConn
    TableName = 'analyzer_data'
    Left = 608
    Top = 320
  end
  object dsEEProm: TDataSource
    DataSet = tbEEProm
    Left = 680
    Top = 240
  end
  object dsAnalyzer: TDataSource
    DataSet = tbAnalyzer
    Left = 688
    Top = 320
  end
  object CmdEEPromClear: TADOCommand
    CommandText = 'delete from eeprom_data;'
    Connection = dbConn
    Prepared = True
    Parameters = <>
    Left = 240
    Top = 312
  end
end
