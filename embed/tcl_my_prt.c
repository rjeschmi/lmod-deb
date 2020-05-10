#include <tcl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * The sLiteral argument *must* be a string literal; the incantation with
 * sizeof(sLiteral "") will fail to compile otherwise.
 */
#define TclNewLiteralStringObj(objPtr, sLiteral) \
    (objPtr) = Tcl_NewStringObj( (sLiteral), (int) (sizeof(sLiteral "") - 1))

static char* resultStr = NULL;
static int   rlen      = 0;

int setResultsObjCmd(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[])
{
  int      len;
  Tcl_Obj *objPtr;
  int i;
  if (objc != 2) {
    Tcl_WrongNumArgs(interp, 1, objv, "value");
    return TCL_ERROR;
  }
  objPtr = objv[1];

  char * str  = Tcl_GetStringFromObj(objPtr, &len);
  if (str[0] == '\0')
    {
      fprintf(stderr,"Result string has zero length\n");
      return TCL_ERROR;
    }

  if (len > rlen) 
    {
      free(resultStr);
      rlen      = len + 1;
      resultStr = (char *) malloc(rlen*sizeof(char));
    }
  memcpy(&resultStr[0], str, len);
  resultStr[len] = '\0';
  return TCL_OK;
}

int Tcl_AppInit(Tcl_Interp* interp)
{
  if (Tcl_Init(interp) == TCL_ERROR)
    return TCL_ERROR;
  Tcl_CreateObjCommand(interp,"setResults", setResultsObjCmd, (ClientData) NULL, (Tcl_CmdDeleteProc *) NULL);
  return TCL_OK;
}

int main(int argc, char **argv)
{
  int        status;
  char       *script = argv[1];
  Tcl_Obj    *argvPtr;
  Tcl_FindExecutable(script);

  Tcl_Interp *interp = Tcl_CreateInterp();

  if (interp == NULL) {
    fprintf(stderr,"Cannot create TCL interpreter\n");
    exit(-1);
  }

  if (Tcl_AppInit(interp) != TCL_OK)
    return TCL_ERROR;

  Tcl_SetVar2Ex(interp, "argv0", NULL, Tcl_NewStringObj(script,-1), TCL_GLOBAL_ONLY);
  argc -= 2;
  argv += 2;
  Tcl_SetVar2Ex(interp, "argc", NULL, Tcl_NewIntObj(argc), TCL_GLOBAL_ONLY);
  argvPtr = Tcl_NewListObj(0, NULL);
  while (argc--) 
    Tcl_ListObjAppendElement(NULL, argvPtr, Tcl_NewStringObj(*argv++, -1));
  Tcl_SetVar2Ex(interp, "argv", NULL, argvPtr, TCL_GLOBAL_ONLY);


  if ((status = Tcl_EvalFile(interp, script)) != TCL_OK)
    {
      Tcl_Channel chan = Tcl_GetStdChannel(TCL_STDERR);
      if (chan)
	{
	  Tcl_Obj *options = Tcl_GetReturnOptions(interp, status);
	  Tcl_Obj *keyPtr, *valuePtr;

	  TclNewLiteralStringObj(keyPtr, "-errorinfo");
	  Tcl_IncrRefCount(keyPtr);
	  Tcl_DictObjGet(NULL, options, keyPtr, &valuePtr);
	  Tcl_DecrRefCount(keyPtr);

	  if (valuePtr) 
	    Tcl_WriteObj(chan, valuePtr);
	  Tcl_WriteChars(chan, "\n", 1);
	  Tcl_DecrRefCount(options);
	}
      return TCL_ERROR;
    }

  fprintf(stderr,"len: %d, resultStr: \"%s\"\n",strlen(resultStr), resultStr);

  exit(0);
}

