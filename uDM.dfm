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
    Left = 624
    Top = 168
  end
  object dsSysConfig: TDataSource
    DataSet = tbSysConfig
    Left = 632
    Top = 232
  end
  object execLog: TADOTable
    Connection = dbConn
    CursorType = ctStatic
    Filter = '1=2'
    TableName = 'exec_log'
    Left = 320
    Top = 264
  end
  object dsLog: TDataSource
    DataSet = execLog
    Left = 328
    Top = 344
  end
end
