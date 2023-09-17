#include "interpreter.h"
#include "myHeader.h"
#include "picoc.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
extern char literal;
extern char buf[BUFSIZE];
extern char DebugBar[];
void UnixSetupFunc()
{    
}
char * PlatformReadFile(char * FileName);


void Clineno (struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) 
{
    ReturnValue->Val->Integer = Parser->Line;
}

void irand (struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) 
{
    ReturnValue->Val->Integer = rand();
}
void picocexit (struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) 
{
     printf("picoc Exiting\n\n");
    
}


void Sleep(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
   int sval=Param[0]->Val->Integer;
   delay(sval);
}
extern int nwatches;
extern char watches[20][33];
void sprint(char *);
void sendc(char  it);
void ssend(char * what);
void send(char * it);
void sendln(char * it);
extern char toConsole;
int lastpos=-1,lastline=-1;
void CurLinePrint(struct ParseState * Parser)
{
        int i=1;
        char SavetoConsole=toConsole;
        toConsole=0;
        char fbuf[433];
        int line=Parser->Line;
        int pos=Parser->CharacterPos;
        PlatformReadFile(Parser->FileName); 
        sendContent("<tr>");
        char * ps,*cp;
        cp=(char *)&buf;ps=strchr(cp,10);
        while (ps!=0)
        {
          if (i==line)
          {
            *ps=0;
            //Ssend(cp);sprintf((char *)&fbuf,"line=%d & pos=%d strlen is %d \nnextline=%s \nlastpos=%d lastline=%d\n",line,pos,strlen(cp),(char *)ps+1,lastpos,lastline);Ssend((char *)&fbuf);
            if (pos+3>=strlen(cp) && strlen(cp)>=3) { line++;pos=0; } // if pos is at EOL then we are really going to execute the next program line
          }
          if (lastline==line && lastpos==pos) {line++;pos=0;}
          if (i==line)
          {
            int j;
            lastpos=pos;lastline=line;
            if (pos>0 && pos<strlen(cp)) pos++;
            snprintf((char *)&fbuf,432,"<td style=\"FONT-SIZE:14px; COLOR:#000000; LINE-HEIGHT:10px; FONT-FAMILY:Courier\">");
            literal=1;sendContent((char *)&fbuf);literal=0;
            snprintf((char *)&fbuf,432,"%4d:%3d  >",i,pos);
            sendContent((char *)&fbuf);
            char fst[433],snd[433];
            strncpy((char *)&fst,(char *)cp,432);
            if (pos==0) fst[pos]=0;
            else fst[pos]=0;
            strncpy((char *)&snd,(char *)(cp+pos+1),432);
            literal=2;
            sendContent((char *)&fst);
            literal=0;
            ssend("<span class=\"text1\">");
            if (pos==0) {fst[0]=*(cp+pos);fst[1]=0;}
            else {fst[0]=*(cp+pos);fst[1]=0;}
            literal=2;
            sendContent((char *)&fst);
            literal=0;
            ssend("</span>");
            literal=2;
            sendContent((char *)&snd);//sendContent("<br>");
            literal=0;
            sendContent("</td>");
            *ps++=10;break;
          }
          else {
            i++;
            cp=++ps;
            ps=strchr(cp,10); }
        }
        if (nwatches>0)
        { 
          literal=1;
          sendContent("<td style=\"FONT-SIZE:14px; COLOR:#000000; LINE-HEIGHT:10px; FONT-FAMILY:Courier\">");
          literal=0;
          for (int i=0;i<nwatches;i++)
          {
            struct Value *VariableValue = NULL;
            int rslt;
            char * Ident=(char *)&watches[i][0];
            char asCharPointer=0;
            char asIntPointer=0;
            char asAddress=0;
            if (strncmp(Ident,"(char *)",8)==0)  { Ident+=8;asCharPointer=1; }
            if (strncmp(Ident,"(int *)",7)==0)  { Ident+=7;asIntPointer=1; }
            char * mycp=TableStrRegister(Ident);
            //if (VariableDefined((char *)&cln[1]))
            {
                if (TopStackFrame!=NULL) rslt=TableGet(&TopStackFrame->LocalTable,mycp,&VariableValue,NULL,NULL,NULL);
                if (rslt==0) rslt=TableGet(&GlobalTable,mycp,&VariableValue,NULL,NULL,NULL);
            }
            if (rslt!=0) {
              if (i>0) sendContent(" | "); 
              if (asCharPointer)
              {
                sendContent("*(char *)");
              sprint(Ident);
              sprint(" : ");
                snprintf((char *)&fbuf,432,"%s",(char *)VariableValue->Val->Pointer);
                sendContent((char *)&fbuf);                
              }
              else if (asIntPointer)
              {
                sendContent("*(int*)");
              sprint(Ident);
              sprint(" : ");
                snprintf((char *)&fbuf,432,"%d",*(int *)(VariableValue->Val->Pointer));
                sendContent((char *)&fbuf);                
              }
              else {
                
              sprint(Ident);
              sprint(" : ");
              PrintValue(VariableValue);
              }
            }
            else {
              if (i>0) sendContent(" | ");snprintf((char *)&fbuf,432,"%s not defined",(char *)&watches[i][0]);
              sendContent((char *)&fbuf); 
            }         
          }
          sendContent("</td></tr>");toConsole=SavetoConsole;
        }
        else sendContent("</td></tr>");toConsole=SavetoConsole;
       
     }


void prntLines(struct ParseState * Parser)
{
  int i=1;
  Ssend("In prntLines\n");
  char fbuf[433];fbuf[0]=0;
  int line=Parser->Line;
  PlatformReadFile(Parser->FileName); 
  char * ps,*cp;cp=(char *)&buf;ps=strchr(cp,10);
  while (ps!=0)
  {
      *ps=0;
      snprintf((char *)&fbuf,432,"%4d >%s\n",i,(char *)cp);
  //    printf("%s",(char *)&fbuf);
      send((char *)&fbuf);
      *ps++=10;cp=ps;i++;ps=strchr(cp,10);    
  }
  if (*cp!=0) {
      snprintf((char *)&fbuf,432,"%4d >%s\n",i,(char *)cp);
      printf((char *)&fbuf);
      send((char *)&fbuf);
  }
  Ssend("Sending </textarea><table ...\n");
  send("</textarea><table frame=\"vsides\"  rules=\"cols\" cellpadding=\"2\">");
}
void LinePrint(char * src,int line,int col)
{
        printf("Entered PrintLine");
        char * strt=(char *)buf;
        int i=1;
        char work[128];
        int dn=0;
        strncpy((char *)buf,src,BUFSIZE-1);
        printf("\r\n");
        sendln("\r\n");

        char *where=strchr(strt,'\n');
        while (dn==0 && where !=(void *)0)
        {
        where=strchr(strt,'\n');
                if (where!=0)
                {
                        *where=0;
                        sprintf((char *)&work,"%4d %s\r\n",i++,strt);
                        printf("%s",(char *)&work);
                        send((char *)&work);
                        if (line==i-1) // printed the line being executed
                        {
                                        int j; for (j=0;j<col+5;j++) printf(" ");
                                        printf("^\r\n");
                        }
                        strt=where;
                        strt++;
                }
                else
                {
                        //dn=1;
                        if (strlen(strt)!=0) { sprintf((char *)&work,"%4d %s\r\n",i,strt);printf((char *)&work);send((char *)&work); }
                }

        }
}



extern char * Prompt;


/* list of all library functions and their prototypes */
struct LibraryFunction UnixFunctions[] =
{
    { Clineno,      "int lineno();" },
    { picocexit,    "void picocexit();" },
    { Sleep,       "void  Sleep(int);" },
    { NULL,         NULL }
};

void PlatformLibraryInit()
{
    IncludeRegister("picoc_unix.h", &UnixSetupFunc, &UnixFunctions[0], NULL);
}
