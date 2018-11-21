source {./config/config.tcl}

open_project $project
open_solution $solution

set trace_level {port}
set rtl {vhdl}
set tool {xsim}
set ldflags {}

cosim_design -trace_level $trace_level -rtl $rtl -tool $tool -ldflags $ldflags -argv $argv
