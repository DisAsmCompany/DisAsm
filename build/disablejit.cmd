REM http://msdn.microsoft.com/en-us/library/2ac5yxx6(v=VS.90).aspx
REM http://msdn.microsoft.com/en-us/library/5hs4b7a6(v=VS.90).aspx
REG DELETE "HKLM\Software\Microsoft\Windows NT\CurrentVersion\AeDebug" /v Debugger /f
REG DELETE "HKLM\Software\Wow6432Node\Microsoft\Windows NT\CurrentVersion\AeDebug" /v Debugger /f
REG DELETE "HKLM\Software\Microsoft\.NETFramework" /v DbgManagedDebugger /f
REG DELETE "HKLM\Software\Wow6432Node\Microsoft\.NETFramework" /v DbgManagedDebugger /f
REG ADD "HKLM\SOFTWARE\Microsoft\.NETFramework" /v DbgJITDebugLaunchSetting  /t REG_DWORD /d 1 /f
