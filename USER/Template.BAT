SET PATH=C:\MDK5\ARM\ARMCLANG\Bin;C:\Java\bin;C:\Java\jre\bin;E:\vs code\Microsoft VS Code\bin;e:\Program Files\Git\cmd;C:\Users\admin\AppData\Local\Programs\Python\Python36\Scripts\;C:\Users\admin\AppData\Local\Programs\Python\Python36\;E:\Tools\WinNT;E:\MSDev98\Bin;E:\Tools;c:\bin;C:\Users\admin\AppData\Local\Microsoft\WindowsApps;C:\Python27;E:\Mysql\mysql-8.0.13\bin;E:\PHP;E:\SQLite;E:\MQTT.fx\Fiddler;C:\Windows\System32;
SET ARMCC6_ASMOPT=--diag_suppress=9931
SET ARMCC6_CCOPT=--diag_suppress=9931
SET ARMCC6_LINKOPT=--diag_suppress=9931
SET CPU_TYPE=STM32F103ZE
SET CPU_VENDOR=STMicroelectronics
SET UV2_TARGET=Template
SET CPU_CLOCK=0x007A1200
"C:\MDK5\ARM\ARMCLANG\Bin\ArmAsm" --Via "..\obj\startup_stm32f10x_hd._ia"
"C:\MDK5\ARM\ARMCLANG\Bin\ArmClang.exe" @"..\obj\main.__i"
"C:\MDK5\ARM\ARMCLANG\Bin\ArmClang.exe" @"..\obj\delay.__i"
"C:\MDK5\ARM\ARMCLANG\Bin\ArmClang.exe" @"..\obj\sys.__i"
"C:\MDK5\ARM\ARMCLANG\Bin\ArmClang.exe" @"..\obj\usart.__i"
"C:\MDK5\ARM\ARMCLANG\Bin\ArmClang.exe" @"..\obj\led.__i"
"C:\MDK5\ARM\ARMCLANG\Bin\ArmClang.exe" @"..\obj\iic.__i"
"C:\MDK5\ARM\ARMCLANG\Bin\ArmClang.exe" @"..\obj\24c02.__i"
"C:\MDK5\ARM\ARMCLANG\Bin\ArmClang.exe" @"..\obj\oled.__i"
"C:\MDK5\ARM\ARMCLANG\Bin\ArmClang.exe" @"..\obj\lcd.__i"
"C:\MDK5\ARM\ARMCLANG\Bin\ArmClang.exe" @"..\obj\adc.__i"
"C:\MDK5\ARM\ARMCLANG\Bin\ArmClang.exe" @"..\obj\pwm.__i"
"C:\MDK5\ARM\ARMCLANG\Bin\ArmClang.exe" @"..\obj\key.__i"
"C:\MDK5\ARM\ARMCLANG\Bin\ArmClang.exe" @"..\obj\encoder.__i"
"C:\MDK5\ARM\ARMCLANG\Bin\ArmClang.exe" @"..\obj\usmart_str_1.__i"
"C:\MDK5\ARM\ARMCLANG\Bin\ArmClang.exe" @"..\obj\usmart_config_1.__i"
"C:\MDK5\ARM\ARMCLANG\Bin\ArmClang.exe" @"..\obj\usmart_1.__i"
"C:\MDK5\ARM\ARMCLANG\Bin\ArmLink" --Via "..\OBJ\Template.lnp"
"C:\MDK5\ARM\ARMCLANG\Bin\fromelf.exe" "..\OBJ\Template.axf" --i32combined --output "..\OBJ\Template.hex"
