source {./config/config.tcl}

open_project $project
open_solution $solution

set compiler {gcc}
set ldflags {}
set cflags {-clean}

csim_design -compiler $compiler -ldflags $ldflags $cflags -argv $argv
