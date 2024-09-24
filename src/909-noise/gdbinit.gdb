# set $executable convenience variable to elf name
python
from os.path import basename
gdb.set_convenience_variable(
    "executable",
    basename(gdb.current_progspace().filename)
)
end

define init_remote_debug
    target remote localhost:3333
    monitor reset halt
    monitor reset init
    set remote hardware-breakpoint-limit 4
    set remote hardware-watchpoint-limit 2
    load
end

define rebuild
    detach
    eval "make %s", $executable
    eval "file %s", $executable
    init_remote_debug
    continue
end

document rebuild
Detach from target, rebuild excecutable, and restart debugging.
end

init_remote_debug
b main
continue
