make
set disassembly-flavor intel
file ./proj3.out
set args < test_values

define hook-run
make
end

define hookpost-stepi
disassemble $eip-12,$eip+12
end
