./build/make -j16

#./build/spike -d --pc=0x93000000  ++/home/yuchengchen/vfbackup/vf/keys/bbl0 ++load_rom ++load_files=/home/yuchengchen/vfbackup/vf/keys/root_key.vbpubk__0x95600000,/home/yuchengchen/vfbackup/vf/keys/firmware.vblock__0x95601000,/home/yuchengchen/vfbackup/vf/keys/bbl1__0x95603000,/home/yuchengchen/vfbackup/vf/keys/firmware_v2.vblock__0x95701000,/home/yuchengchen/vfbackup/vf/keys/bbl1__0x95703000,/home/yuchengchen/vfbackup/vf/device/sw/lib/gptk.bin__0x90000000  ++chip_config=nc_1__f_1000__xlen_64__isa_rv64imafdc  ++shift_file=0x13000000 ++mems=0x80000000:0x000d0000,0x800e0000:0x1ff20000 ++load_flash=0x93000000 ++chrome_rom
./build/spike -d --pc=0x93000000  ++/home/yuchengchen/vfbackup/vf/keys/bbl0 ++load_rom ++load_files=/home/yuchengchen/vfbackup/vf/keys/root_key.vbpubk__0x95600000,/home/yuchengchen/vfbackup/vf/keys/firmware.vblock__0x95601000,/home/yuchengchen/vfbackup/vf/keys/bbl1__0x95603000,/home/yuchengchen/vfbackup/vf/keys/firmware_v2.vblock__0x95701000,/home/yuchengchen/vfbackup/vf/keys/bbl1__0x95703000,/home/yuchengchen/vfbackup/vf/device/sw/lib/gptk.bin__0x90000000  ++chip_config=nc_1__f_1000__xlen_64__isa_rv64imafdc  ++shift_file=0x13000000 ++mems=0x90000000:0x10000000,0x80000000:0x20000000 ++load_flash=0x93000000 
#./spike --pc=0x80000000 -m0x90000000:0x10000000,0x80000000:0x20000000 ++/home/yuchengchen/vf/device/sw/bbl/build/bbl0 ++load_rom ++chrome_rom ++load_files=/home/yuchengchen/vf/keys/root_key.vbpubk__0x95600000,/home/yuchengchen/vf/keys/firmware.vblock__0x95601000,/home/yuchengchen/vf/device/sw/bbl/build/bbl1__0x95603000,/home/yuchengchen/vf/keys/firmware_v2.vblock__0x95701000,/home/yuchengchen/vf/device/sw/bbl/build/bbl1__0x95703000,/home/yuchengchen/vf/device/sw/lib/gptk.bin__0x90000000  ++chip_config=nc_1__f_1000__xlen_64__isa_rv64imafdc   ++mems=0x90000000:0x10000000,0x80000000:0x20000000 ++load_to_flash
