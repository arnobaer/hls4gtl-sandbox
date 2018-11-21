source {./config/config.tcl}

open_project $project
open_solution $solution

#set flow {syn}
set rtl {vhdl}
set format {ip_catalog}

export_design -rtl $rtl -format $format
