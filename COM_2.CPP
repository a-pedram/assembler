/*
This programm is Assembler that make assembly programming very easy and
more comfortable
*/
# define numofline 200
# define numoflinetxtcom 200
# define numofadress 100

# define AX   0
# define CX   1
# define DX   2
# define BX   3
# define SP   4
# define BP   5
# define SI   6
# define DI   7

# define ES   0
# define CS   1
# define SS   2
# define DS   3

# define BXSI 0
# define BXDI 1
# define BPSI 2
# define BPDI 3
# define aSI  4
# define aDI  5
# define aBP  6
# define ADR  6
# define aBX  7

# define AL   0
# define CL   1
# define DL   2
# define BL   3
# define AH   4
# define CH   5
# define DH   6
# define BH   7

# define rEG  1
# define REG  2
# define ADRREG 3
# define BYTPTR 4
# define DIGIT  5
# define WORPTR 6
# define SEGREG 7

# define ADD  0x0
# define OR   0x8
# define ADC 0x10
# define SBB 0x18
# define AND 0x20
# define SUB 0x28
# define XOR 0x30
# define CMP 0x38
# define MOV 0x50

# define ROL  0x0
# define ROR  0x8
# define RCL 0x10
# define RCR 0x18
# define SHL 0x20
# define SHR 0x28
# define SAR 0x30
/*
The "USUAL" command includes commands like : add,sub,xor,or,cmp,etc...
The "UNUSUAL" command includes lea,les,lds
The "ELSE" command includes test,xchg
The "ONEPARAM" command includes commands like int
*/
# define USUAL     1
# define UNUSUAL   2
# define ELSE      3
# define ONEPARAM  4
# define MoV       5
# define ABYTE     6
# define RETAOT    7
# define IN        8
# define OUT       9
# define SHORJUMP 10
# define DB	  11
# define DW	  12
# define JMP	  13

# include<stdio.h>
# define BEEP printf("%c",7)
# define ASMFILE "d:\source.asm"


void adressing( void );
void coding( void );
void cls( void );
void close(int file);
char cmpstr( char *v1, char *v2);
int  constorlable(char *argument,int *lenconst);
int  decdigit(char *argument,int *lendigit);
int  digit(char *argument,int *lendigit);
char getchrfil( int num);
int  hexdigit(char *argument,int *lendigit);
long int isadress(char *argument,int *lendigit);
int  len(char *str);
void locate(char x,char y);
int  make(char *v,int atribute);
void makecode(int surchcode,int nbyte);
int  open(char *file,char h);
int  parametr(char *argument);
void parametr2(char *argument,int *p1,int *vp1,int *p2,int *vp2);
void putchr(char chr);
void print(char *str);
void putchrfil(char *file,int v,int ted);
void putfile(void);
void readfile( void );
void readobjectfile( void );
void readtxtfile( void );
void readcodefile(void);
int  registr(char *argument,int *vc);
int  testcommand(char *argument);
char *findstr(char *str,char *cmp);



char obj[ numofline ][40];
char txtcom1[ numoflinetxtcom ][9]; //                                10                                                20                                                30                                                40                                                50
char code1[ numoflinetxtcom ]={6,7,0xe,0x16,0x17,0x1e,0x1f,0x26,0x27,0x2e,0x2f,0x36,0x37,0x3e,0x3f,0x90,0x98,0x99,0x9b,0x9c,0x9d,0x9e,0x9f,0xa4,0xa5,0xa6,0xa7,0xaa,0xab,0xac,0xad,0xae,0xaf,0xc3,0xcb,0xce,0xcf,0xd7,0xf0,0xf2,0xf3,0xf4,0xf5,0xf8,0xf9,0xfa,0xfb,0xfc,0xfd};
char *adress[numofadress];
char outcode[400];
char txtlabel[100][11];
int  adrlabel[100];
char *pointadr[100];
int  placjmp[100];
int  maxcode;
int  byte1,byte2,byte3,byte4,byte5,byte6,byte7;
int  vp,vp3=0;
int  digitflag=0;
int  howcommand;
int  codenum=0;
int  linenum=-1;
int  numjmp;
int  lj=-1;
int  maxline;
/****************************************************************************
*****************************************************************************
******T  H  I  S    I  S    M  A  I  N    O  F    P  R  O  G  R  A  M********
*****************************************************************************
****************************************************************************/

void main(void)
{
 int i,ii,jj;
 cls();

 readfile();
 coding();
 adressing();
 putfile();

  for(jj =0; jj<=5;jj++){
	 for (ii=0;ii<=20;ii++)
			  putchr(obj[jj][ii]);
	 print("\n\r$");
		  }
   for (ii=0;ii<=10;ii++)
			  printf("%d ",obj[ii][0]);
printf("\n%s = %d",pointadr[0],placjmp[0]);
printf("\n%s = %d",pointadr[1],placjmp[1]);
printf("\n%s = %d",pointadr[2],placjmp[2]);
printf("\n MAXCODE = %d",codenum);
printf("\nTXTLAB = ,%s, = %d" ,txtlabel[0],adrlabel[0]);
printf("\nTXTLAB = ,%s, = %d" ,txtlabel[1],adrlabel[1]);
printf("\nTXTLAB = ,%s, = %d" ,txtlabel[2],adrlabel[2]);
printf("\nTXTLAB = ,%s, = %d" ,txtlabel[3],adrlabel[3]);
}

/****************************************************************************
*****************************************************************************
**********************E  N  D    O  F    M  A  I  N**************************
*****************************************************************************
****************************************************************************/


/***************************************************************************
**************THIS IS READFILE AND READFILE FUNCTIONS***********************
****************************************************************************/
void readfile( void )
{

 readtxtfile();

  //readcodefile();
 readobjectfile();
}



void readobjectfile( void )
{
 int i=0,j=0;
 int li=0;
 int halat=1,halat1=-1,halat2=-1,halat3=0;
 char c;
 int opn;
 opn =open(ASMFILE,0);
  do {
    c=getchrfil(opn);
    //putchr(c);
    switch (c){
       case  10:
	      break;
       case  13:
	      break;
       case -1 :
	      break;
       case 9  :
	      break;
       case '@':
	      if (halat1== 1 || halat2== 1){if (halat==1){
			     obj[j][i] = c;
			     i++;
			     }}
		      else{
			     halat3 = 1;
			     li = 0;
			     i = 0;
			     obj[j][i] = '@';
			     lj++ ;
			     j++;
			     }
	      break;
       case ':':
	      if (halat1== 1 || halat2== 1){if (halat==1){
			     obj[j][i] = c;
			     i++;
			     }}
		      else
			     halat3 = 0 ;
	      break;
       case ';' :
	      if (halat == 1){
		    j++;
		    i=0;
		    }
	      break;

       case ' ':
	      if (halat1== 1 || halat2== 1)if (halat==1){
			     obj[j][i] = c;
			     i++;
			     }
	      break;

       case '%':
	      halat=-halat;
	      break;

       case '"':
	    if (halat==1){
		   halat2=(-1 * (halat2));
		   obj[j][i] = c;
		   i++;
		   }
	    break;
       case 39 :
	    if (halat==1){
		   halat1= (-1 * (halat1));
		   obj[j][i] = c;
		   i++;
		   }
	    break;

def:     default:
	      if (halat3 == 1) {
			if (li < 11){
				txtlabel[lj][li] = c;
				li++;
				}
	      break;
	      }
	      if (halat == 1) {
	      if(c >= 65 & c<=90)c += 32;
	      obj[j][i] = c;
	      i++;
	      }

	}
 }while(c != -1);
 printf("  mobj=%d",j);
 maxline=j;
 close(opn);
}


void readcodefile(void)
{
 int opn,i=0;
 opn = open("cod.h",0);
 do{
      code1[i] = getchrfil(opn);
      i++;
 } while( code1[i-1] != -1);
 close (opn);
}

void readtxtfile(void)
{
char c;
 int opn,i=0,j=0;
 opn = open("text.h",0);
 do{
   begin:
     c = getchrfil(opn);
     if ( c == ';')
	    {j++;
	     i=0;
	      goto begin;}
     if ( c== 10 || c== 13) goto begin ;
     if ( c== -1) break;
     txtcom1[j][i]=c;
     i++;
 } while( c != -1);
 close(opn);
}

/***************************************************************************
*****************END OF READFILE AND READFILE FUNCTIONS*********************
****************************************************************************/

void adressing(void){
int i,j,b2;
for(i=0; i<= numjmp;i++){
       for(j =0 ;j<= lj;j++){
	     if (cmpstr(pointadr[i],&txtlabel[j][0])==1){
			b2 = adrlabel[j]-placjmp[i]-2;
			if( b2 < 0) b2 = b2 + 256;
			if(b2 >= 0 && b2 <= 256 ){outcode[placjmp[i]+1] = b2;
				    if(outcode[placjmp[i]]==0xe9){
						outcode[placjmp[i]]==0xeb;
						outcode[placjmp[i]+1] = b2;}
				    printf("\n/////////////////////////");
				    printf("\n%s  %s  %d  %d",pointadr[i],&txtlabel[j][0],adrlabel[j],j);}

					}
			}
  }
}



void coding( void)
{
int i=0,l=0,lb=0;
for (linenum=0;linenum<=maxline;linenum++){
start:
maxcode = codenum;
/////////////////////////////////////////////////////////////////////////////
if( obj[linenum][0] == '@' ){
			 printf("\nCODENUM = %d",lb);
			 l=lb;
			 adrlabel[l] = codenum;
			 l++;
			 lb++;
			 continue;
			 }
  for(i=0;i<50;++i){
	if( cmpstr(&obj[linenum][0],&txtcom1[i][0])==1 ){
			   outcode[codenum] = code1[i];
			   codenum++;
			   continue           ;
			   }
	if ( txtcom1[i][0] == 0 ) break;
		    }
/////////////////////////////////////////////////////////////////////////////
if(findstr(&obj[linenum][0],"push")==&obj[linenum][0]){
				howcommand = ABYTE;
				makecode(0x50,3);
				continue;
				}
if(findstr(&obj[linenum][0],"pop")==&obj[linenum][0]){
				howcommand = ABYTE;
				makecode(0x58,3);
				continue;
				}
if(findstr(&obj[linenum][0],"inc")==&obj[linenum][0]){
				howcommand = ABYTE;
				makecode(0x40,3);
				continue;
				}
if(findstr(&obj[linenum][0],"dec")==&obj[linenum][0]){
				howcommand = ABYTE;
				makecode(0x48,3);
				continue;
				}
if(findstr(&obj[linenum][0],"add")==&obj[linenum][0]){
				howcommand = USUAL;
				makecode(0x00,3);
				continue;
				}
if(findstr(&obj[linenum][0],"or")==&obj[linenum][0]){
				howcommand = USUAL;
				makecode(0x08,2);
				continue;
				}
if(findstr(&obj[linenum][0],"adc")==&obj[linenum][0]){
				howcommand = USUAL;
				makecode(0x10,3);
				continue;
				}
if(findstr(&obj[linenum][0],"sbb")==&obj[linenum][0]){
				howcommand = USUAL;
				makecode(0x18,3);
				continue;
				}
if(findstr(&obj[linenum][0],"and")==&obj[linenum][0]){
				howcommand = USUAL;
				makecode(0x20,3);
				continue;
				}
if(findstr(&obj[linenum][0],"sub")==&obj[linenum][0]){
				howcommand = USUAL;
				makecode(0x28,3);
				continue;
				}
if(findstr(&obj[linenum][0],"xor")==&obj[linenum][0]){
				howcommand = USUAL;
				makecode(0x30,3);
				continue;
				}
if(findstr(&obj[linenum][0],"cmp")==&obj[linenum][0]){
				makecode(0x38,3);
				howcommand = USUAL;
				continue;
				}
if(findstr(&obj[linenum][0],"mov")==&obj[linenum][0]){
				howcommand = MoV;
				makecode(0x88,3);
				continue;
				}
if(findstr(&obj[linenum][0],"test")==&obj[linenum][0]){
				howcommand = ELSE;
				makecode(0x84,4);
				continue;
				}
if(findstr(&obj[linenum][0],"xchg")==&obj[linenum][0]){
				howcommand = ELSE;
				makecode(0x87,4);
				continue;
				}
if(findstr(&obj[linenum][0],"lea")==&obj[linenum][0]){
			       howcommand = UNUSUAL;
			       makecode(0x8d,3);
			       continue;
			       }
if(findstr(&obj[linenum][0],"les")==&obj[linenum][0]){
			       howcommand = UNUSUAL;
			       makecode(0xc4,3);
			       continue;
			       }
if(findstr(&obj[linenum][0],"lds")==&obj[linenum][0]){
			       howcommand = UNUSUAL;
			       makecode(0xc5,3);
			       continue;
			       }
if(findstr(&obj[linenum][0],"int")==&obj[linenum][0]){
			       howcommand = ONEPARAM;
			       makecode(0xcd,3);
			       continue;
			       }
/*if(findstr(&obj[linenum][0],"aam")==&obj[linenum][0]){
			       howcommand = ONEPARAM;
			       makecode(0xd4,linenum,&codenum,3);
			       }
if(findstr(&obj[linenum][0],"aad")==&obj[linenum][0]){
			       howcommand = ONEPARAM;
			       makecode(0xd5,linenum,&codenum,3);
			       }*/


if(findstr(&obj[linenum][0],"rol")==&obj[linenum][0]){
				makecode(0x38,3);
				howcommand=RETAOT;
				continue;
				}
if(findstr(&obj[linenum][0],"ror")==&obj[linenum][0]){
				howcommand=RETAOT;
				makecode(0x88,3);
				continue;
				}
if(findstr(&obj[linenum][0],"rcl")==&obj[linenum][0]){
				howcommand=RETAOT;
				makecode(0x84,3);
				continue;
				}
if(findstr(&obj[linenum][0],"rcr")==&obj[linenum][0]){
				howcommand=RETAOT;
				makecode(0x86,3);
				continue;
				}
if(findstr(&obj[linenum][0],"shr")==&obj[linenum][0]){
			       howcommand=RETAOT;
			       makecode(0x8d,3);
			       continue;
			       }
if(findstr(&obj[linenum][0],"shl")==&obj[linenum][0]){
			       howcommand=RETAOT;
			       makecode(0xc4,3);
			       continue;
			       }
if(findstr(&obj[linenum][0],"sar")==&obj[linenum][0]){
			       howcommand=RETAOT;
			       makecode(0xc5,3);
			       continue;
			       }
if(findstr(&obj[linenum][0],"ina")==&obj[linenum][0]){
			       howcommand = IN;
			       makecode(0xe4,2);
			       continue;
			       }
if(findstr(&obj[linenum][0],"out")==&obj[linenum][0]){
			       howcommand = OUT;
			       makecode(0xe6,3);
			       continue;
			       }
if(findstr(&obj[linenum][0],"jo")==&obj[linenum][0]){
			       howcommand = SHORJUMP;
			       makecode(0x70,2);
			       continue;
			       }
if(findstr(&obj[linenum][0],"jno")==&obj[linenum][0]){
			       howcommand = SHORJUMP;
			       makecode(0x71,3);
			       continue;
			       }
if(findstr(&obj[linenum][0],"jb")==&obj[linenum][0]){
			       howcommand = SHORJUMP;
			       makecode(0x72,2);
			       continue;
			       }
if(findstr(&obj[linenum][0],"jnb")==&obj[linenum][0]){
			       howcommand = SHORJUMP;
			       makecode(0x73,3);
			       continue;
			       }
if(findstr(&obj[linenum][0],"jz")==&obj[linenum][0]){
			       howcommand = SHORJUMP;
			       makecode(0x74,2);
			       continue;
			       }
if(findstr(&obj[linenum][0],"jnz")==&obj[linenum][0]){
			       howcommand = SHORJUMP;
			       makecode(0x75,3);
			       continue;
			       }
if(findstr(&obj[linenum][0],"jbe")==&obj[linenum][0]){
			       howcommand = SHORJUMP;
			       makecode(0x76,3);
			       continue;
			       }
if(findstr(&obj[linenum][0],"ja")==&obj[linenum][0]){
			       howcommand = SHORJUMP;
			       makecode(0x77,2);
			       continue;
			       }
if(findstr(&obj[linenum][0],"js")==&obj[linenum][0]){
			       howcommand = SHORJUMP;
			       makecode(0x78,2);
			       continue;
			       }
if(findstr(&obj[linenum][0],"jns")==&obj[linenum][0]){
			       howcommand = SHORJUMP;
			       makecode(0x79,3);
			       continue;
			       }
if(findstr(&obj[linenum][0],"jpe")==&obj[linenum][0]){
			       howcommand = SHORJUMP;
			       makecode(0x7a,3);
			       continue;
			       }
if(findstr(&obj[linenum][0],"jpo")==&obj[linenum][0]){
			       howcommand = SHORJUMP;
			       makecode(0x7b,3);
			       continue;
			       }
if(findstr(&obj[linenum][0],"jl")==&obj[linenum][0]){
			       howcommand = SHORJUMP;
			       makecode(0x7c,2);
			       continue;
			       }
if(findstr(&obj[linenum][0],"jge")==&obj[linenum][0]){
			       howcommand = SHORJUMP;
			       makecode(0x7d,3);
			       continue;
			       }
if(findstr(&obj[linenum][0],"jle")==&obj[linenum][0]){
			       howcommand = SHORJUMP;
			       makecode(0x7e,3);
			       continue;
			       }
if(findstr(&obj[linenum][0],"jg")==&obj[linenum][0]){
			       howcommand = SHORJUMP;
			       makecode(0x7f,2);
			       continue;
			       }
if(findstr(&obj[linenum][0],"db")==&obj[linenum][0]){
			       howcommand = DB;
			       makecode(0x00,2);
			       continue;
			       }
if(findstr(&obj[linenum][0],"dw")==&obj[linenum][0]){
			       howcommand = DW;
			       makecode(0x00,2);
			       continue;
			       }
if(findstr(&obj[linenum][0],"jmp")==&obj[linenum][0]){
			       howcommand = JMP;
			       makecode(0xe9,3);
			       continue;
			       }


 }
printf("Erorr$%d",linenum);
}




void putfile(void){

int out;
//out=make("sampl.com",0);
//close(out);
out =open("com.com",1);
putchrfil(outcode,out,maxcode);
close(out);
printf("maxcode=%d",maxcode);
}





void makecode(int surchcode,int nbyte){
int e,*l;
//if ( surchcode == 0xcd ){
 //		     byte1=0xcd;
   //		     e = digit(&obj[linenum][nbyte],l);
  //		     if(e<256) byte2 = e;
    //		     goto sec;
      //		     }
outcode[codenum]=surchcode+parametr(&obj[linenum][nbyte]);
sec:
codenum++;

if(byte1 !=-1) outcode[codenum-1] = byte1;
if(byte2 !=-1){outcode[codenum]=byte2;codenum++;}
if(byte3 !=-1){outcode[codenum]=byte3;codenum++;}
if(byte4 !=-1){outcode[codenum]=byte4;codenum++;}
if(byte5 !=-1){outcode[codenum]=byte5;codenum++;}
if(byte6 !=-1){outcode[codenum]=byte6;codenum++;}
}


int parametr(char *argument)
{
int *p1,*p2,*vp1,*vp2;
int var1,var2,var3,var4;
int com;
p1 = &var1;
p2 = &var2;
vp1 = &var3;
vp2 = &var4;
int *vc,*lendigit,*n;
*vc=0;
byte1=-1;
byte2=-1;
byte3=-1;
byte4=-1;
byte5=-1;
byte6=-1;
byte7=-1;
if (cmpstr(argument,"ax")==1) return(AX);
if (cmpstr(argument,"cx")==1) return(CX);
if (cmpstr(argument,"dx")==1) return(DX);
if (cmpstr(argument,"bx")==1) return(BX);
if (cmpstr(argument,"sp")==1) return(SP);
if (cmpstr(argument,"bp")==1) return(BP);
if (cmpstr(argument,"si")==1) return(SI);
if (cmpstr(argument,"di")==1) return(DI);
//register  int  double  char  long  float  short  if  for  while  do  switch
//return  case  default  auto  static  extern  break  continue  class  struct
//else  near  pascal  unsigned  new  operator  private  friend  public  union
//protected  asm  unsigned  far  template  catch  delete  try  throw  virtual
//goto  this  inline
parametr2( argument, p1, vp1, p2, vp2);

///////////////////////////////////////////////////////////////////////////
if( howcommand == RETAOT ){

		   printf("\n *vp1 =%d           *vp2=%d      *p2=%d\n",*vp1,*vp2,*p2);
		   if( *vp2 == BYTPTR && *p2==1 ){
				    byte1= 0xd0;
				    byte2= testcommand(argument-3)  + *p1;
				   return(0);}
		   if( *vp2 == BYTPTR && digitflag==1){// && *vp1==rEG){
				    byte1= 0xd2;
				    byte2= testcommand(argument-3)  + *p1;
				   return(0);}
		   if( *vp2 == WORPTR && *p2==1 ){
				    byte1= 0xd1;
				    byte2= testcommand(argument-3)  + *p1;
				   return(0);}
		   if( *vp2 == WORPTR && digitflag==1){
				    byte1= 0xd3;
				    byte2= testcommand(argument-3)  + *p1;
				   return(0);}

		   if( *vp1 == rEG && *vp2==DIGIT && *p2==1 ){
				    byte1= 0xd0;
				    byte2= testcommand(argument-3)+ *p1+0xc0;
				   return(0);}
		   if( *vp1 == rEG && *vp2==rEG && *p2==CL){// && *vp1==rEG){
				    byte1= 0xd2;
				    byte2= testcommand(argument-3)+ *p1+0xc0;
				   return(0);}
		   if( *vp1 == REG && *vp2==DIGIT && *p2==1 ){
				    byte1= 0xd1;
				    byte2= testcommand(argument-3)+ *p1+0xc0;
				   return(0);}
		   if( *vp1 == REG && *vp2==rEG && *p2==CL){
				    byte1= 0xd3;
				    byte2= testcommand(argument-3)+ *p1+0xc0;
				   return(0);}

		   }

/////////////////////////////////////////////////////////////////////////////
if( howcommand == USUAL ){
			if( *vp1==ADRREG && *vp2==rEG ){
					     byte2= *p2 * 0x8 + *p1;
					     return(0);
						  }
			if( *vp1==ADRREG && *vp2==REG ){
					       byte2= *p2 * 0x8 + *p1;
					       return(1);
						  }
			if( *vp1==rEG && *vp2==ADRREG ){
					       byte2= *p1 * 0x8 + *p2;
					       return(2);
						  }
			if( *vp1==REG && *vp2==ADRREG ){
					       byte2= *p1 * 0x8 + *p2;
					       return(3);
						  }
			if( *vp1==REG && *vp2==REG ){
					       byte2= *p2 * 0x8 + *p1 + 0xc0;
					       return(1);
						  }
			if( *vp1==rEG && *vp2==rEG ){
					       byte2= *p2 * 0x8 + *p1 + 0xc0;
					       return(0);
					       }
			if( vp3 == BYTPTR) {
					  byte1 = 0x80;
					  byte2= *p1 + testcommand(argument-3);
					  if( *p1 == ADR){
						  byte5= *p2;
						  goto exit;}
					  if(byte2 < 0x80) byte4 = *p2; else byte5= *p2;
				      exit:
					  return(1);
					  }
				if( vp3 == WORPTR) {
					  byte1 = 0x81;
					  byte2= *p1 + testcommand(argument-3);
					  if( *p1 == ADR){
							byte5 = *p2 % 256;
							byte6 = *p2 / 256;
							//printf("\n{{{ %d }}}",*p2);
							goto exit2;}
					  if(byte2 < 0x80){ byte4 = *p2 % 256;
							 byte5 = *p2 / 256;}
							 else //byte5= *p2;
							  { byte5 = *p2 % 256;
							    byte6 = *p2 / 256;}

						exit2:
					   return(1);
					    }
			if( *vp2 == DIGIT && *vp1 == rEG){
				      if(*p2 < 256){
					  byte1 = 0x80;
					  byte2 = testcommand(argument-3)+ *p1 + 0xc0;
					  byte3 = *p2;
					  return(0);}
					  }

			 if( *vp2 == DIGIT && *vp1==REG){
						       byte1 = 0x81;
						       byte2 = testcommand(argument-3)+ *p1 + 0xc0;
						       byte3 = *p2 % 256;
						       byte4 = *p2 / 256;
						       return(0);
						     }

			 }
////////////////////////////////////////////////////////////////////////////
if( howcommand == MoV){
			 if( *vp2 == DIGIT&& *vp1==rEG){
						       byte1 = 0xb0 + *p1;
						       if(*p2 < 256) byte2 = *p2;
						       return(0);
						       }
			if( *vp2 == DIGIT && *vp1==REG){
				       byte1 = 0xb8 + *p1;
				       byte2 = *p2 % 256;
				       byte3 = *p2 / 256;
				       return(0);
						    }
			if( *vp1==ADRREG && *vp2==rEG ){
					     byte2= *p2 * 0x8 + *p1;
					     return(0);
						  }
			if( *vp1==ADRREG && *vp2==REG ){
					       byte2= *p2 * 0x8 + *p1;
					       return(1);
						  }
			if( *vp1==rEG && *vp2==ADRREG ){
					       byte2= *p1 * 0x8 + *p2;
					       return(2);
						  }
			if( *vp1==REG && *vp2==ADRREG ){
					       byte2= *p1 * 0x8 + *p2;
					       return(3);
						  }
			if( vp3==BYTPTR) {
					       if( *p1 == ADR){
					       byte5= *p2;
					       goto mexit;}
					if(byte2 < 0x80) byte4 = *p2;
						 else byte5= *p2;

					mexit:
					 byte1 = 0xc6;
					 byte2= *p1;
					 return(0);
					}
			if( vp3==WORPTR) {
					 if( *p1 == ADR){
						byte5 = *p2 % 256;
						byte6 = *p2 / 256;
						 goto mexit2;}
					 if(byte2 < 0x80){ byte4 = *p2 % 256;
						  byte5 = *p2 / 256;}
						else //byte5= *p2;
						  { byte5 = *p2 % 256;
						    byte6 = *p2 / 256;}

					 mexit2:
					 byte1 = 0xc7;
					  byte2= *p1;
					  return(0);
					   }
if( *vp1==ADRREG && *vp2==SEGREG ){
		  byte2= *p2 * 0x8 + *p1 ;
		  return(4);
		  }
if( *vp1==SEGREG && *vp2==ADRREG ){
		  byte2= *p1 * 0x8 + *p2 ;
		  return(6);
		  }
if( *vp1 == REG && *vp2== SEGREG ){
		  byte2= *p2 * 0x8 + *p1 +0xc0 ;
		  return(4);
		  }
if( *vp1 == SEGREG && *vp2== REG ){
		  byte2= *p1 * 0x8 + *p2 +0xc0 ;
		  return(6);
		  }

		    }
/////////////////////////////////////////////////////////////////////////////
if( howcommand == UNUSUAL){
			if( *vp1==REG && *vp2==ADRREG ){
				  byte2= *p1 * 0x8 + *p2;
				  return(0);
				  }
			if( *vp1==REG && *vp2==REG ){
				  byte2= *p2 * 0x8 + *p1 + 0xc0;
				  return(1);
				  }
			   }
/////////////////////////////////////////////////////////////////////////////
if( howcommand == ELSE ){
			if( *vp1==REG && *vp2==ADRREG ){
					       byte2= *p1 * 0x8 + *p2;
					       return(0);
						  }
			if( *vp1==REG && *vp2==REG ){
					       if( *p2 == AX){
							  byte1 = 0x90 + *p1;
							  return(0);
							  }
					       byte2= *p2 * 0x8 + *p1 + 0xc0;
					       return(0);
						  }
			}
/////////////////////////////////////////////////////////////////////////////
if ( howcommand == ONEPARAM){
			    if(*vp2 == DIGIT && *p2 < 256 && *vp1 == 0){
						  byte2 = *p2;
						  return(0);
						  }
			    }
/////////////////////////////////////////////////////////////////////////////
if ( howcommand == IN){
			 if(*vp2==DIGIT && *p2<256 && *vp1==rEG && *p1==AL){
						  byte2 = *p2;
						  return(0);
						  }
			 if(*vp2==DIGIT && *p2<256 && *vp1==REG && *p1==AX){
						  byte2 = *p2;
						  return(1);
						  }
			    }
			if(*vp1==rEG && *p1==AL && *vp2 == REG && *p2==DX){
						  byte1=0xec;
						  return(0);
						  }
			if(*vp1==REG && *p1==AX && *vp2 == REG && *p2==DX){
						  byte1=0xed;
						  return(0);
						  }
/////////////////////////////////////////////////////////////////////////////
if ( howcommand == OUT){
		       int dg,*lendigit;
		       dg = digit(argument,lendigit);
		       if(dg<256 && (findstr(argument,",al")==argument+ *lendigit)){
						byte1 = 0xe6;
						byte2 = dg;
						return(0); }
		       if(dg < 256 && (findstr(argument,",ax")==argument+ *lendigit)){
						byte1 = 0xe7;
						byte2 = dg;
						return(1); }
		       if(*vp2==rEG && *p2==AL && *vp1 == REG && *p1==DX){
						  byte1=0xee;
						  return(0);
						  }
		       if(*vp2==REG && *p2==AX && *vp1 == REG && *p1==DX){
						  byte1=0xef;
						  return(0);
						  }

			   }
////////////////////////////////////////////////////////////////////////////
if(howcommand == SHORJUMP){
			byte2=0;
			pointadr[numjmp] = argument;
			placjmp[numjmp] = codenum;
			numjmp++;
			return(0);
			}
///////////////////////////////////////////////////////////////////////////
if(howcommand == DB ){
		  printf("{{{{{{%c}}}}",*argument);
		  if ( *argument == '"'){
			   int i=1;
			   do{
			     outcode[codenum]=*(argument+i);
			     codenum++;
			     i++;
			     }while (*(argument+i) !='"');
			     codenum--;
			     return(*(argument+i-1));
		      }

		  if( *vp2 == DIGIT){
			 if(*p2 < 256){
			     byte1=*p2;
			     return(0);
			     }
			     }
				  }
//////////////////////////////////////////////////////////////////////////
if(howcommand == DW ){
		  if( *vp2 == DIGIT){
			     byte1= *p2 %256;
			     byte2= *p2 /256;
			     return(0);

			   }
		      }
////////////////////////////////////////////////////////////////////////////
if(howcommand == JMP){
			byte2=0;
			byte3=0;
			pointadr[numjmp] = argument;
			placjmp[numjmp] = codenum;
			numjmp++;
			return(0);
		  }
/*if( *vp2 == DIGIT&& *vp1==rEG){
		  if(testcommand(argument-3) == MOV){
				       byte1 = 0xb0 + *p1;
				       if(*p2 < 256) byte2 = *p2;
				       return(0);
						    }

if( *vp2 == DIGIT && *vp1==0){
		  printf("%c",7);
		  if( *p2< 256){
			      byte2 = *p2;
			      }
			      return(0);
			      }
		  byte1 = 0x80;
		  byte2 = testcommand(argument-3)+ *p1 + 0xc0;
		  if(*p2 < 256) byte3 = *p2;
		  return(0);
		  }
if( *vp2 == DIGIT && *vp1==REG){
		  if(testcommand(argument-3) == MOV){
				       byte1 = 0xb8 + *p1;
				       byte2 = *p2 % 256;
				       byte3 = *p2 / 256;
				       return(0);
						    }
		    }
if( *vp1==ADRREG && *vp2==rEG ){
		  byte2= *p2 * 0x8 + *p1;
		  return(0);
		  }
if( *vp1==ADRREG && *vp2==REG ){
		  byte2= *p2 * 0x8 + *p1;
		  if (howcommand == CHG) return(1);
		  if (howcommand == ELSE)return(0);
		  return(0);
		  }
if( *vp1==rEG && *vp2==ADRREG ){
		  byte2= *p1 * 0x8 + *p2;
		  if (howcommand == CHG) return(2);
		  return(0);
		  }
if( *vp1==REG && *vp2==ADRREG ){
		  byte2= *p1 * 0x8 + *p2;
		  if (howcommand == CHG) return(3);
		  if (howcommand == ELSE)return(1);
		  return(0);
		  }


if( *vp1==REG && *vp2==REG ){
		  byte2= *p2 * 0x8 + *p1 + 0xc0;
		  if (howcommand == NOTCHG){
				byte2= *p1 * 0x8 + *p2 + 0xc0;
				return(0);}
		  if (howcommand == CHG) return(1);
		  if (howcommand == ELSE)return(1);
		  return(0);}
if( *vp1==rEG && *vp2==rEG ){
		  byte2= *p2 * 0x8 + *p1 + 0xc0;
		  return(0);}
if( *vp1==ADRREG && *vp2==SEGREG ){
		  byte2= *p2 * 0x8 + *p1 ;
		  if (howcommand == CHG) return(4);
		  return(0);}
if( *vp1==SEGREG && *vp2==ADRREG ){
		  byte2= *p1 * 0x8 + *p2 ;
		   if (howcommand == CHG) return(6);
		   return(0);}
if( *vp1 == REG && *vp2== SEGREG ){
		  byte2= *p2 * 0x8 + *p1 +0xc0 ;
		  if (howcommand == CHG)return(4);
		  return(0);}
if( *vp1 == SEGREG && *vp2== REG ){
		  byte2= *p1 * 0x8 + *p2 +0xc0 ;
		  if (howcommand == CHG) return(6);
		  return(0);}
if( *vp2==BYTPTR) {
		  byte1 = 0x80;
		  byte2= *p1 + testcommand(argument-3);
		  if( *p1 == ADR){
				byte5= *p2;
				goto exit;}
		  if(byte2 < 0x80) byte4 = *p2; else byte5= *p2;

	 exit:
		if(testcommand(argument-3) == MOV){
					  byte1 = 0xc6;
					  byte2= *p1;
					  return(0);}
		if (howcommand == CHG) return(1);
		 return(0);
		   }
if( *vp2==WORPTR) {
		 byte1 = 0x81;
		 byte2= *p1 + testcommand(argument-3);


		if( *p1 == ADR){
				byte5 = *p2 % 256;
				byte6 = *p2 / 256;
				goto exit2;}
	       if(byte2 < 0x80){ byte4 = *p2 % 256;
				    byte5 = *p2 / 256;}
					 else byte5= *p2;
				  { byte5 = *p2 % 256;
				    byte6 = *p2 / 256;}

	 exit2:
		if(testcommand(argument-3) == MOV){
					  byte1 = 0xc7;
					  byte2= *p1;
					  return(0);}
		if (howcommand == CHG)return(1);
		  return(0);
		   }
  */
}


int testcommand(char *argument){
if(findstr(argument,"add")==argument) return(ADD);
if(findstr(argument,"xor")==argument) return(XOR);
if(findstr(argument,"or")==argument+1)return(OR );
if(findstr(argument,"adc")==argument) return(ADC);
if(findstr(argument,"sbb")==argument) return(SBB);
if(findstr(argument,"and")==argument) return(AND);
if(findstr(argument,"sub")==argument) return(SUB);
if(findstr(argument,"cmp")==argument) return(CMP);
if(findstr(argument,"mov")==argument) return(MOV);
if(findstr(argument,"rol")==argument) return(ROL);
if(findstr(argument,"ror")==argument) return(ROR);
if(findstr(argument,"rcl")==argument) return(RCL);
if(findstr(argument,"rcr")==argument) return(RCR);
if(findstr(argument,"shl")==argument) return(SHL);
if(findstr(argument,"shr")==argument) return(SHR);
if(findstr(argument,"sar")==argument) return(SAR);

}



void parametr2(char *argument,int *p1,int *vp1,int *p2,int *vp2){
char *newargument;
int *lendigit;
int dg;
*vp1=0;
*vp2=0;
*p1 =0;
*p2 =0;
vp3 = 0;
digitflag = 0;
newargument = argument;
if (findstr(argument,"byteptr[")==argument){
				  argument = argument+7;
				  vp3 = BYTPTR;
				  }
if (findstr(argument,"wordptr[")==argument){
				  argument = argument+7;
				  vp3 = WORPTR;
				  }

if (findstr(argument,"al,")==argument){
				  newargument = argument+2;
				  *p1 = AL ;
				  *vp1 = rEG;
				  goto param2;
				  }
if (findstr(argument,"cl,")==argument){
				  newargument = argument+2;
				  *p1 = CL ;
				  *vp1 = rEG;
				  goto param2;
				  }
if (findstr(argument,"dl,")==argument){
				  newargument = argument+2;
				  *p1 = DL ;
				  *vp1 = rEG;
				  goto param2;
				  }
if (findstr(argument,"bl,")==argument){
				  newargument = argument+2;
				  *p1 = BL ;
				  *vp1 = rEG;
				  goto param2;
				  }
if (findstr(argument,"ah,")==argument){
				  newargument = argument+2;
				  *p1 = AH ;
				  *vp1 = rEG;
				  goto param2;
				  }
if (findstr(argument,"ch,")==argument){
				  newargument = argument+2;
				  *p1 = CH ;
				  *vp1 = rEG;
				  goto param2;
				  }
if (findstr(argument,"dh,")==argument){
				  newargument = argument+2;
				  *p1 = DH ;
				  *vp1 = rEG;
				  goto param2;
				  }
if (findstr(argument,"bh,")==argument){
				  newargument = argument+2;
				  *p1 = BH ;
				  *vp1 = rEG;
				  goto param2;
				  }

if (findstr(argument,"ax,")==argument){
				  newargument = argument+2;
				  *p1 = AX ;
				  *vp1 = REG;
				  goto param2;
				  }
if (findstr(argument,"cx,")==argument){
				  newargument = argument+2;
				  *p1 = CX ;
				  *vp1 = REG;
				  goto param2;
				  }
if (findstr(argument,"dx,")==argument){
				  newargument = argument+2;
				  *p1 = DX ;
				  *vp1 = REG;
				  goto param2;
				  }
if (findstr(argument,"bx,")==argument){
				  newargument = argument+2;
				  *p1 = BX ;
				  *vp1 = REG;
				  goto param2;
				  }
if (findstr(argument,"sp,")==argument){
				  newargument = argument+2;
				  *p1 = SP ;
				  *vp1 = REG;
				  goto param2;
				  }
if (findstr(argument,"bp,")==argument){
				  newargument = argument+2;
				  *p1 = BP ;
				  *vp1 = REG;
				  goto param2;
				  }
if (findstr(argument,"si,")==argument){
				  newargument = argument+2;
				  *p1 = SI ;
				  *vp1 = REG;
				  goto param2;
				  }
if (findstr(argument,"di,")==argument){
				  newargument = argument+2;
				  *p1 = DI ;
				  *vp1 = REG;
				  goto param2;
				  }

if (findstr(argument,"es,")==argument){
				  newargument = argument+2;
				  *p1 = ES ;
				  *vp1 = SEGREG;
				  goto param2;
				  }
if (findstr(argument,"cs,")==argument){
				  newargument = argument+2;
				  *p1 = CS ;
				  *vp1 = SEGREG;
				  goto param2;
				  }
if (findstr(argument,"ss,")==argument){
				  newargument = argument+2;
				  *p1 = SS ;
				  *vp1 = SEGREG;
				  goto param2;
				  }
if (findstr(argument,"ds,")==argument){
				  newargument = argument+2;
				  *p1 = DS ;
				  *vp1 = SEGREG;
				  goto param2;
				  }

if (findstr(argument,"[bx+si],")==argument){
			 *p1 = BXSI;
			 *vp1 = ADRREG;
			 newargument = argument + 7;
			 goto param2;}
if (findstr(argument,"[bx+di],")==argument){
			 *p1 = BXDI;
			 *vp1 = ADRREG;
			 newargument = argument + 7 ;
			 goto param2;}
if (findstr(argument,"[bp+si],")==argument){
			 *p1 = BPSI;
			 *vp1 = ADRREG;
			 newargument = argument + 7;
			 goto param2;}
if (findstr(argument,"[bp+di],")==argument){
			 *p1 = BPDI;
			 *vp1 = ADRREG;
			 newargument = argument + 7 ;
			 goto param2;}
if (findstr(argument,"[si],")==argument){
			 *p1 = aSI;
			 *vp1 = ADRREG;
			 newargument = argument + 4 ;
			 goto param2;}
if (findstr(argument,"[di],")==argument){
			 *p1 = aDI;
			 *vp1 = ADRREG;
			 newargument = argument + 4;
			 goto param2;}
if (findstr(argument,"[bx],")==argument){
			 *p1 = aBX;
			 *vp1 = ADRREG;
			 newargument = argument + 4;
			 goto param2;}

if(findstr(argument,"[bx+si+")==argument||findstr(argument,"[bx+si-")==argument){
			byte3= digit(argument+7,lendigit);
			newargument = argument + 8 + *lendigit;
			*p1=BXSI+0x40+ vp;
			*vp1 = ADRREG;
			goto param2;}
if (findstr(argument,"[bx+di+")==argument||findstr(argument,"[bx+di-")==argument){
			byte3= digit(argument+7,lendigit);
			newargument = argument + 8 + *lendigit;
			*p1= BXDI + 0x40 +  vp;
			*vp1 = ADRREG;
			goto param2;}
if (findstr(argument,"[bp+si+")==argument||findstr(argument,"[bp+si-")==argument){
			byte3= digit(argument+7,lendigit);
			newargument = argument + 8+ *lendigit;
			*p1= BPSI + 0x40 + vp;
			*vp1 = ADRREG;
			goto param2;}
if (findstr(argument,"[bp+di+")==argument||findstr(argument,"[bp+di-")==argument){
			byte3= digit(argument+7,lendigit);
			newargument = argument + 8 + *lendigit;
			*p1= BPDI + 0x40 + vp;
			*vp1 = ADRREG;
			goto param2;}
if (findstr(argument,"[si+")==argument||findstr(argument,"[si-")==argument){
			byte3= digit(argument+4,lendigit);
			newargument = argument + 5 + *lendigit;
			*p1= aSI + 0x40 + vp;
			*vp1 = ADRREG;
			goto param2;}
if (findstr(argument,"[di+")==argument||findstr(argument,"[di-")==argument){
			byte3= digit(argument+4,lendigit);
			newargument = argument + 5 + *lendigit;
			*p1= aDI + 0x40 + vp;
			*vp1 = ADRREG;
			goto param2;}
if (findstr(argument,"[bp+")==argument||findstr(argument,"[di-")==argument){
			byte3= digit(argument+4,lendigit);
			newargument = argument + 5 + *lendigit;
			*p1=aBP+0x40+ vp;
			*vp1 = ADRREG;
			goto param2;}
if (findstr(argument,"[bx+")==argument||findstr(argument,"[bx-")==argument){
			byte3= digit(argument+4,lendigit);
			newargument = argument + 5 + *lendigit;
			*p1=aBX+0x40+ vp;
			*vp1 = ADRREG;
			goto param2;}
if (findstr(argument,"[")==argument){
			 int qe;
			 qe=digit((argument +1),lendigit);
			 newargument = argument + 2 + *lendigit;
			 //printf("\n\n%s\n\n",newargument);
			 if (qe != -1){
				     *p1 = ADR;
				     *vp1 =ADRREG;
				     byte3= qe % 256;
				     byte4= (qe - byte3) / 256;
				     goto param2;
				     }
				     }


param2:

if (findstr(argument,",al")==newargument){
				  *p2 = AL;
				  *vp2 = rEG;
				  return;
				  }
if (findstr(argument,",cl")==newargument){
				  *p2 = CL ;
				  *vp2 = rEG;
				  return;
				  }
if (findstr(argument,",dl")==newargument){
				  *p2 = DL ;
				  *vp2 = rEG;
				  return;
				  }
if (findstr(argument,",bl")==newargument){
				  *p2 = BL ;
				  *vp2 = rEG;
				  return;
				  }
if (findstr(argument,",ah")==newargument){
				  *p2 = AH ;
				  *vp2 = rEG;
				  return;
				  }
if (findstr(argument,",ch")==newargument){
				  *p2 = CH ;
				  *vp2 = rEG;
				  return;
				  }
if (findstr(argument,",dh")==newargument){
				  *p2 = DH ;
				  *vp2 = rEG;
				  return;
				  }
if (findstr(argument,",bh")==newargument){
				  *p2 = BH ;
				  *vp2 = rEG;
				  return;
				  }

if (findstr(argument,",ax")==newargument){
				  *p2 = AX ;
				  *vp2 = REG;
				  return;
				  }
if (findstr(argument,",cx")==newargument){
				  *p2 = CX ;
				  *vp2 = REG;
				  return;
				  }
if (findstr(argument,",dx")==newargument){
				  *p2 = DX ;
				  *vp2 = REG;
				  return;
				  }
if (findstr(argument,",bx")==newargument){
				  *p2 = BX ;
				  *vp2 = REG;
				  return;
				  }
if (findstr(argument,",sp")==newargument){
				  *p2 = SP ;
				  *vp2 = REG;
				  return;
				  }
if (findstr(argument,",bp")==newargument){
				  *p2 = BP ;
				  *vp2 = REG;
				  return;
				  }
if (findstr(argument,",si")==newargument){
				  *p2 = SI ;
				  *vp2 = REG;
				  return;
				  }
if (findstr(argument,",di")==newargument){
				  *p2 = DI ;
				  *vp2 = REG;
				  return;
				  }
if (findstr(argument,",es")==newargument){
				  *p2 = ES ;
				  *vp2 = SEGREG;
				  return;
				  }
if (findstr(argument,",cs")==newargument){
				  *p2 = CS ;
				  *vp2 = SEGREG;
				  return;
				  }
if (findstr(argument,",ss")==newargument){
				  *p2 = SS ;
				  *vp2 = SEGREG;
				  return;
				  }
if (findstr(argument,",ds")==newargument){
				  *p2 = DS ;
				  *vp2 = SEGREG;
				  return;
				  }

if (findstr(argument,",[bx+si]")==newargument){
			 *p2 = BXSI;
			 *vp2 = ADRREG;
			 return;}
if (findstr(argument,",[bx+di]")==newargument){
			 *p2 = BXDI;
			 *vp2 = ADRREG;
			 return;}
if (findstr(argument,",[bp+si]")==newargument){
			 *p2 = BPSI;
			 *vp2 = ADRREG;
			 return;}
if (findstr(argument,",[bp+di]")==newargument){
			 *p2 = BPDI;
			 *vp2 = ADRREG;
			 return;}
if (findstr(argument,",[si]")==newargument){
			 *p2 = aSI;
			 *vp2 = ADRREG;
			 return;}
if (findstr(argument,",[di]")==newargument){
			 *p2 = aDI;
			 *vp2 = ADRREG;
			 return;}
if (findstr(argument,",[bx]")==newargument){
			 *p2 = aBX;
			 *vp2 = ADRREG;
			 return;}
if(findstr(argument,",[bx+si+")==newargument||findstr(argument,",[bx+si-")==newargument){
			byte3= digit(newargument+8,lendigit);
			*p2=BXSI+0x40+ vp;
			*vp2 = ADRREG;
			return;}
if (findstr(argument,",[bx+di+")==newargument||findstr(argument,",[bx+di-")==newargument){
			byte3= digit(newargument+8,lendigit);
			*p2= BXDI + 0x40 +  vp;
			*vp2 = ADRREG;
			return;}
if (findstr(argument,",[bp+si+")==newargument||findstr(argument,",[bp+si-")==newargument){
			byte3= digit(newargument+8,lendigit);
			*p2= BPSI + 0x40 + vp;
			*vp2 = ADRREG;
			return;}
if (findstr(argument,",[bp+di+")==newargument||findstr(argument,",[bp+di-")==newargument){
			byte3= digit(newargument+8,lendigit);
			*p2= BPDI + 0x40 + vp;
			*vp2 = ADRREG;
			return;}
if (findstr(argument,",[si+")==newargument||findstr(argument,",[si-")==newargument){
			byte3= digit(newargument+5,lendigit);
			*p2= aSI + 0x40 + vp;
			*vp2 = ADRREG;
			return;}
if (findstr(argument,",[di+")==newargument||findstr(argument,",[di-")==newargument){
			byte3= digit(newargument+5,lendigit);
			*p2= aDI + 0x40 + vp;
			*vp2 = ADRREG;
			return;}
if (findstr(argument,",[bp+")==newargument||findstr(argument,",[di-")==newargument){
			byte3= digit(newargument+5,lendigit);
			*p2=BXSI+0x40+ vp;
			*vp2 = ADRREG;
			return;}
if (findstr(argument,",[bx+")==newargument||findstr(argument,",[bx-")==newargument){
			byte3= digit(argument+5,lendigit);
			*p2=BXSI+0x40+ vp;
			*vp2 = ADRREG;
			return;}
if (findstr(argument,",[")==newargument){
			 int qe;
			 qe=digit((newargument +2),lendigit);
			 if (qe != -1){
				     *p2 = ADR;
				     *vp2 = ADRREG;
				     byte3= qe % 256;
				     byte4= (qe - byte3) / 256;
				     return;
				     }
				     }

if (*newargument == ',') dg = digit(newargument+1,lendigit);
				else
				    dg = digit(newargument,lendigit);
if (digitflag==0){
		  *vp2 = DIGIT;
		  *p2 = dg;
		  return;
		  } else printf("%c---- %d ---",7,dg);
}



int registr(char *argument,int *vc){
*vc=1;
if (cmpstr(argument,"ax")==1) return(AX);
if (cmpstr(argument,"cx")==1) return(CX);
if (cmpstr(argument,"dx")==1) return(DX);
if (cmpstr(argument,"bx")==1) return(BX);
if (cmpstr(argument,"sp")==1) return(SP);
if (cmpstr(argument,"bp")==1) return(BP);
if (cmpstr(argument,"si")==1) return(SI);
if (cmpstr(argument,"di")==1) return(DI);
*vc=0;
if (cmpstr(argument,"ah")==1) return(AH);
if (cmpstr(argument,"ch")==1) return(CH);
if (cmpstr(argument,"dh")==1) return(DH);
if (cmpstr(argument,"bh")==1) return(BH);
if (cmpstr(argument,"al")==1) return(AL);
if (cmpstr(argument,"cl")==1) return(CL);
if (cmpstr(argument,"dl")==1) return(DL);
if (cmpstr(argument,"bl")==1) return(BL);

return(-1);
}

int digit(char *argument,int *lendigit){
long int dgt,t;
int vaz;
vaz = *lendigit;
vp = 0;
t = isadress(argument,lendigit);
if (t != -1){
	dgt = t;
	goto nextwork;}
if( (*argument=='0') && ((*(argument+1)) == 'x') ){
				dgt=hexdigit(argument+2,lendigit);
				goto nextwork;}
if( ( (*argument ) >47) & (( *argument ) < 58) )
				dgt=decdigit(argument,lendigit);
nextwork:
if(*(argument-1)=='[') return(dgt);
if(*(argument-1)==',') return(dgt);
if((*(argument-1)=='+') & (dgt < 128)) return(dgt);

if((*(argument-1)=='-') & (dgt <= 128)) return(256-dgt);
if((*(argument-1)=='+') & (dgt >=  128)) {
					 vp = 0x40;
					 byte4 =dgt/256;
					 return( dgt % 256);}
if((*(argument-1)=='-') & (dgt > 128)) {
					 vp = 0x40;
					 dgt = 0xffff - dgt + 1;
					 byte4 =dgt/256;
					 return( dgt % 256);}

return(dgt);
//return(constorlable(argument,lendigit));
}

long int isadress(char *argument,int *lendigit){
int i;
for(i=0 ; i<= numjmp;i++){

		if(findstr(argument,&txtlabel[i][0])==argument){
			     *lendigit = len(&txtlabel[i][0]);
			     return(adrlabel[i]+256);}
		  }

return(-1);

}

int decdigit(char *argument,int *lendigit){
char strdgt[9],*cargument;
int i=1,a=1,b;
int sum=0;
cargument=argument;
do{
   strdgt[i]= (*cargument)-48;
   i++;
   cargument++;
     }while((*cargument)!=']'&(*cargument)!=','& (*cargument)!=0 & i!=10);
i--;
*lendigit = i;
do {
  b=( a * strdgt[i]);
  if( (strdgt[i]+0)< 0 || (strdgt[i]+0) > 10)digitflag = 1;
  sum=sum+b;
  a *=10;
  i--;
}while(i!= 0);

return(sum);
}


int hexdigit(char *argument,int *lendigit){
char strdgt[9],*cargument;
int i=1,a=1,b;
int sum=0;
cargument=argument;
do{
   if((*cargument) >= 'a' && (*cargument) <= 'f') strdgt[i]=(*cargument)-87;
				else strdgt[i]= (*cargument)-48;
   i++;
   cargument++;
     }while((*cargument)!=']'&(*cargument)!=','& (*cargument)!=0 & i!=10);
i--;
*lendigit = i + 2;
do {
  b=( a * strdgt[i]);
  if( (strdgt[i]+0)< 0 || (strdgt[i]+0) > 15) digitflag = 1;
  sum=sum+b;
  a *=16;
  i--;
}while(i!= 0);
return(sum);
}

int constorlable(char *argument,int *lenconst){
}




/****************************************************************************
	    EEEEEEEE         NN        N         DDDD
	    E                N N       N         D   DDD
	    E                N  N      N         D      DD
	    E                N   N     N         D        D
	    EEEEEE           N    N    N         D        D
	    E                N     N   N         D        D
	    E                N      N  N         D      DD
	    E                N       N N         D   DDD
	    EEEEEEEE         N        NN         DDDD
****************************************************************************/


/****************************************************************************
THIS FUNTION OPENS A FILE FOR INPUT OR OUTPUT OR BOTH THEM AND RETURN THE HEADER
****************************************************************************/
int open(char *file,char h)
{
asm{
    mov  dx,file
    mov  ah,0x3d
    mov  al,h
    int  21h
    jnc  exitf
    mov  ax,0xffff
    }
exitf:
}
/****************E N D   O F  T H I S   F U N C T I O N*********************/



/****************************************************************************
*******THIS FUNCTION GET A CHARACTER FROM A FILE THAT NUM POINTED IT*********
****************************************************************************/
char getchrfil( int num)
{
int byte, *pbyte;
pbyte= &byte;

asm{
    mov  bx,num
    mov  cx,1
    mov  ah,0x3f
    mov  dx,pbyte
    int  0x21

    cmp  ax,0000
    jnz  exitfun
    }
byte=-1;
exitfun:
return(byte);
}
/****************E N D   O F  T H I S   F U N C T I O N*********************/



/****************************************************************************
**********THIS FUNCTION IS A PRINT COMMAND WITH DOS INTERRUPT****************
****************************************************************************/
void print(char *str)
{
asm{
   mov ah,9
   mov dx,str
   int 21h
   }
}


/****************************************************************************
****************THIS FUNCTION CLEARS SCREEN AND PUT CURSER IN 0,0************
****************************************************************************/
void cls(void)
{
asm{
    xor al,al
    xor cx,cx
    mov dh,24
    mov dl,79
    mov bh,7
    mov ah,6
    int 10h
    }
locate(0,0);
}
/****************E N D   O F  T H I S   F U N C T I O N*********************/


/****************************************************************************
********************THIS FUNCTION  PUT CURSER IN x , y***********************
****************************************************************************/
void locate(char x,char y)
{
asm {
    mov dl,y
    mov dh,x
    mov bh,0
    mov ah,2
    int 10h
    }
}
/****************E N D   O F  T H I S   F U N C T I O N*********************/

int make(char *v,int atribute)
{
asm{
    mov ah,0x3c
    mov dx,v
    mov cx,atribute
    int 0x21
    }
}

void putchr(char chr)
{
asm{
    mov ah,2
    mov dl,chr
    int 21h
    }
}
/****************************************************************************
***********************THIS FUNTION CLOSES A FILE****************************
****************************************************************************/
void close( int file)
{
asm{
    mov  bx,file
    mov  ah,0x3e
    int  21h
    }

}
/****************E N D   O F  T H I S   F U N C T I O N*********************/



void putchrfil(char *file,int v,int ted)
{
asm{
    mov ah,0x40
    mov cx,ted
    mov bx,v
    mov dx,file
    int 21h
    }
}

char *findstr( char *v1, char *v2){
register int i,lencmp,l;
int l1;
char ch;
l=len(v2);
l1=len(v1);
lencmp=l1-l;
for(i=0;i<=lencmp;++i){
    ch=*(v1+l);
    *(v1+l)=0;
    if (cmpstr(v1,v2)==1){
		  *(v1+l)=ch;
		  return(v1);
		  }
    *(v1+l)=ch;
    v1++;
    }
    return(0);
}




int len(char *str)
{
int lenth=0;
do{
   str++ ;
   lenth++;
   }while(*str != 0);
return(lenth);
}

char cmpstr( char *v1, char *v2){

do{
   if (*v1 != *v2) return(0);
   v1++;
   v2++;
  }while(*v1 !=0 || *v2 !=0);
return(1);

}