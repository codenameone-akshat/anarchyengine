@echo off
echo Setting AC_ROOT variable.
setx AC_ROOT %cd%

echo Setting AC_SOURCE variable.
setx AC_SOURCE %cd%\Source

echo Setting the BOOST variable.
if "%BOOST%" == "" ( set /p boostpath="Enter Boost Full Path: " 
	setx BOOST %boostpath% ) else (	echo BOOST variable already set. )