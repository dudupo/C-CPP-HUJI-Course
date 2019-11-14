#!/bin/bash
for i in ./in/01/*.tst
do
  echo $i
  ./tools/HardwareSimulator.bat $i
done
