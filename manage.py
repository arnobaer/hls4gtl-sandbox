#!/usr/bin/env python

from xml.dom import minidom

import argparse
import logging
import shutil
import subprocess
import sys, os

class Default:
    vivado_hls = 'vivado_hls'
    project = 'hls_impl'
    solution = 'solution1'

def csynth_report(filename):
    """Prints csynth report (latency)."""
    doc = minidom.parse(filename)
    node = doc.getElementsByTagName('PerformanceEstimates')[0]
    items = [
        # XML tag, expected value
        ['Best-caseLatency', 0],
        ['Average-caseLatency', 0],
        ['Worst-caseLatency', 0],
        ['Interval-min', 1],
        ['Interval-max', 1],
    ]
    logging.info("Latency report:")
    for item in items:
        value = node.getElementsByTagName(item[0])[0].firstChild.nodeValue
        if int(value) != item[1]:
            logging.warning("{}: {} [expected: {}]".format(item[0], value, item[1]))
        else:
            logging.info("{}: {}".format(item[0], value))

def check_call(args):
    """Call system command, handles OSErrors (file not found)."""
    try:
        return subprocess.check_call(args)
    except OSError as e:
        # Catching error 2 (file not found).
        # Usually occures if vivado is not sourced.
        if e.errno == os.errno.ENOENT:
            logging.error(format(e))
            logging.error("executable '%s' not found", args[0])
            sys.exit(1)

def cmd_clean(args):
    """Clear command, removes project implementation."""
    if os.path.isdir(Default.project):
        shutil.rmtree(Default.project)
        logging.info("removed implementation %s", Default.project)

def cmd_auto_create_project(args):
    if not os.path.isdir(Default.project):
        context='config/create_project.tcl'
        command = [args.vivado_hls, context]
        check_call(command)

def cmd_csim(args):
    cmd_auto_create_project(args)
    context='config/csim.tcl'
    testvectors = auto_testvectors(args)
    command = [args.vivado_hls, context]
    command.extend(testvectors)
    check_call(command)

def cmd_csynth(args):
    cmd_auto_create_project(args)
    context='config/csynth.tcl'
    command = [args.vivado_hls, context]
    check_call(command)
    csynth_report(os.path.join(Default.project, Default.solution, 'syn/report/csynth.xml'))

def cmd_cosim(args):
    cmd_auto_create_project(args)
    context='config/cosim.tcl'
    command = [args.vivado_hls, context]
    check_call(command)

def cmd_export(args):
    cmd_auto_create_project(args)
    context='config/export.tcl'
    command = [args.vivado_hls, context]
    check_call(command)

def parse_args():
    parser = argparse.ArgumentParser()
    subparsers = parser.add_subparsers(dest='command')

    clear_parser = subparsers.add_parser('clean', help="remove project/solution")
    clear_parser.set_defaults(func=cmd_clean)

    csim_parser = subparsers.add_parser('csim', help="run C simulation")
    csim_parser.set_defaults(func=cmd_csim)

    csynth_parser = subparsers.add_parser('csynth', help="run C synthesis")
    csynth_parser.set_defaults(func=cmd_csynth)

    cosim_parser = subparsers.add_parser('cosim', help="run co-simulation")
    cosim_parser.set_defaults(func=cmd_cosim)

    export_parser = subparsers.add_parser('export', help="run export IP core")
    export_parser.set_defaults(func=cmd_export)

    parser.add_argument('--vivado-hls', metavar='<exec>', default=Default.vivado_hls, help="Xilinx Vivado HLS executable, default is '{}'".format(Default.vivado_hls))

    return parser.parse_args()

def main():
    args = parse_args()
    logging.basicConfig(format='%(levelname)s: %(message)s', level=logging.INFO)
    args.func(args)
    sys.exit()

if __name__ == '__main__':
    main()
