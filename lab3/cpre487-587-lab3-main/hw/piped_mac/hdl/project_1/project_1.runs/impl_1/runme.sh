#!/bin/sh

# 
# Vivado(TM)
# runme.sh: a Vivado-generated Runs Script for UNIX
# Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
# 

if [ -z "$PATH" ]; then
  PATH=/remote/Xilinx/2020.1/Vitis/2020.1/bin:/remote/Xilinx/2020.1/Vivado/2020.1/ids_lite/ISE/bin/lin64:/remote/Xilinx/2020.1/Vivado/2020.1/bin
else
  PATH=/remote/Xilinx/2020.1/Vitis/2020.1/bin:/remote/Xilinx/2020.1/Vivado/2020.1/ids_lite/ISE/bin/lin64:/remote/Xilinx/2020.1/Vivado/2020.1/bin:$PATH
fi
export PATH

if [ -z "$LD_LIBRARY_PATH" ]; then
  LD_LIBRARY_PATH=
else
  LD_LIBRARY_PATH=:$LD_LIBRARY_PATH
fi
export LD_LIBRARY_PATH

HD_PWD='/home/tjfriedl/Desktop/cpre_487/lab3/cpre487-587-lab3-main/hw/piped_mac/hdl/project_1/project_1.runs/impl_1'
cd "$HD_PWD"

HD_LOG=runme.log
/bin/touch $HD_LOG

ISEStep="./ISEWrap.sh"
EAStep()
{
     $ISEStep $HD_LOG "$@" >> $HD_LOG 2>&1
     if [ $? -ne 0 ]
     then
         exit
     fi
}

# pre-commands:
/bin/touch .init_design.begin.rst
EAStep vivado -log piped_mac.vdi -applog -m64 -product Vivado -messageDb vivado.pb -mode batch -source piped_mac.tcl -notrace


