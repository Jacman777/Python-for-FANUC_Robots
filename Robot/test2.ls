/PROG  TEST2
/ATTR
OWNER		= MNEDITOR;
COMMENT		= "";
PROG_SIZE	= 783;
CREATE		= DATE 00-04-08  TIME 08:57:58;
MODIFIED	= DATE 25-02-28  TIME 19:21:54;
FILE_NAME	= ;
VERSION		= 0;
LINE_COUNT	= 13;
MEMORY_SIZE	= 1119;
PROTECT		= READ_WRITE;
TCD:  STACK_SIZE	= 0,
      TASK_PRIORITY	= 50,
      TIME_SLICE	= 0,
      BUSY_LAMP_OFF	= 0,
      ABORT_REQUEST	= 0,
      PAUSE_REQUEST	= 0;
DEFAULT_GROUP	= 1,*,*,*,*;
CONTROL_CODE	= 00000000 00000000;
LOCAL_REGISTERS	= 0,0,0;
/MN
   1:  F[5:Comm established]=(OFF) ;
   2:  F[6:End recording]=(OFF) ;
   3:   ;
   4:  CALL RUNPY("script name"='LOGBYSOCKETRO.PY',"pythonID R[]"=1) ;
   5:   ;
   6:  WAIT (F[5:Comm established])    ;
   7:   ;
   8:J P[1] 30% FINE    ;
   9:J P[2] 60% FINE    ;
  10:J P[3] 100% FINE    ;
  11:J P[1] 100% FINE    ;
  12:  F[6:End recording]=(ON) ;
  13:  //CALL ABORTPY("pythonID"=1) ;
/POS
P[1]{
   GP1:
	UF : 0, UT : 1,	
	J1=    15.145 deg,	J2=   -36.399 deg,	J3=    -3.976 deg,
	J4=     -.143 deg,	J5=   -88.918 deg,	J6=     -.423 deg
};
P[2]{
   GP1:
	UF : 0, UT : 1,	
	J1=     -.000 deg,	J2=   -26.385 deg,	J3=    -3.976 deg,
	J4=     -.143 deg,	J5=   -88.918 deg,	J6=     -.423 deg
};
P[3]{
   GP1:
	UF : 0, UT : 1,	
	J1=    18.252 deg,	J2=   -49.045 deg,	J3=    -3.977 deg,
	J4=     -.143 deg,	J5=   -88.918 deg,	J6=     -.423 deg
};
/END
