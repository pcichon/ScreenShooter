echo Replace SDK_PATH before running
pause

"SDK_PATH\bin\adt.bat" -package -storetype pkcs12 -keystore test.p12 -storepass test -target ane ScreenShooter.ane extension.xml -swc ScreenShooter.swc -platform Windows-x86 library.swf ScreenShooter.dll