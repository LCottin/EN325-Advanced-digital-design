#!/bin/sh

# 
# Vivado(TM)
# runme.sh: a Vivado-generated Runs Script for UNIX
# Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
# 

if [ -z "$PATH" ]; then
  PATH=/opt/xilinx/vivado/2018.2/SDK/2018.2/bin:/opt/xilinx/vivado/2018.2/Vivado/2018.2/ids_lite/ISE/bin/lin64:/opt/xilinx/vivado/2018.2/Vivado/2018.2/bin
else
  PATH=/opt/xilinx/vivado/2018.2/SDK/2018.2/bin:/opt/xilinx/vivado/2018.2/Vivado/2018.2/ids_lite/ISE/bin/lin64:/opt/xilinx/vivado/2018.2/Vivado/2018.2/bin:$PATH
fi
export PATH

if [ -z "$LD_LIBRARY_PATH" ]; then
  LD_LIBRARY_PATH=/opt/xilinx/vivado/2018.2/Vivado/2018.2/ids_lite/ISE/lib/lin64
else
  LD_LIBRARY_PATH=/opt/xilinx/vivado/2018.2/Vivado/2018.2/ids_lite/ISE/lib/lin64:$LD_LIBRARY_PATH
fi
export LD_LIBRARY_PATH

HD_PWD='/net/e/fpouget001/SE/EN325-Advanced-digital-design/Partie-1/2_Hardware/Etape_7/vivado/vivado.runs/impl_1'
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
EAStep vivado -log PGCD_uart.vdi -applog -m64 -product Vivado -messageDb vivado.pb -mode batch -source PGCD_uart.tcl -notrace


