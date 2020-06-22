    
:: 文件名: make.cmd
echo off
mingw32-make tests
echo comppling -done
mingw32-make clean
echo delete .o file -done
 
::执行编译后的文件
tests.exe
echo test -done