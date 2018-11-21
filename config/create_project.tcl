source {./config/config.tcl}

delete_project $project
open_project $project
set_top $top
add_files src/top.cpp
add_files -tb src/top_tb.cpp

open_solution $solution
set_part $part
create_clock -period $clock_ns -name default
