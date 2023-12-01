DSEG segment
    MESS DB "Hello,world",0DH,0AH,24H    ; MSG = Hello,world
DSEG ends

SSEG segment PARA STACK
         DW 256 DUP(?)    ;
SSEG ends


CSEG segment
          ASSUME CS:CSEG,DS:DSEG,SS:SSEG
    BEGIN:MOV    AX,DSEG
          MOV    DS,AX

          MOV    DX,OFFSET MESS

          MOV    AH,9
          INT    21H

          MOV    AH,4CH
          INT    21H
CSEG ends
END BEGIN