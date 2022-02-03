ml /W2 /c /coff /Cx /Zi /D_VXD_ /DBLD_COFF /DIS_32 /DMASM6 /DDEBUG  /Fo%2 %1
editbin %2 -section:_EBSS=.bss$1 -section:INITCODE=.CRT$XCA -section:INITEND=.CRT$XCZ
