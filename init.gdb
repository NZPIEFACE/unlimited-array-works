set pagination off
set logging file gdb.txt
set logging on
set width 0
set height 0
set verbose off

file test.exe
break 99
run

set $ipx=0
set $end=24

while ($ipx < 32)
    print &array[i][j][k]
    print {i, j, k}
    continue
end


set logging off
quit
quit