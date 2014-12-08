#include "string_ops.h"
#include "mem_ops.h"

#define array_elements(array) (sizeof(array) / sizeof *(array))

char  *ClearStr(char* charBuffer,int num) 
{
	char *tmp=(charBuffer + num);
	tmp[strlen(tmp)-2]='\0';
	return tmp;
}

// DFA to parse egg module
int parse_eggs(char** p, char** lex)
{
    char* marker;

    for (;;)
    {
    	*lex = *p;
    
	{
		char yych;

		yych = (char)**p;
		switch (yych) {
		case 0x00:	goto yy4;
		case ':':	goto yy2;
		default:	goto yy6;
		}
yy2:
		yych = (char)*(marker = ++*p);
		switch (yych) {
		case ':':	goto yy7;
		default:	goto yy3;
		}
yy3:

		{ continue; }

yy4:
		++*p;

		{ return END; }

yy6:
		yych = (char)*++*p;
		goto yy3;
yy7:
		yych = (char)*++*p;
		switch (yych) {
		case 'D':	goto yy10;
		case 'R':	goto yy11;
		case 'T':	goto yy9;
		default:	goto yy8;
		}
yy8:
		*p = marker;
		goto yy3;
yy9:
		yych = (char)*++*p;
		switch (yych) {
		case 'i':	goto yy65;
		default:	goto yy8;
		}
yy10:
		yych = (char)*++*p;
		switch (yych) {
		case 'e':	goto yy46;
		default:	goto yy8;
		}
yy11:
		yych = (char)*++*p;
		switch (yych) {
		case 'e':	goto yy12;
		default:	goto yy8;
		}
yy12:
		yych = (char)*++*p;
		switch (yych) {
		case 'f':	goto yy13;
		case 'g':	goto yy14;
		default:	goto yy8;
		}
yy13:
		yych = (char)*++*p;
		switch (yych) {
		case 'e':	goto yy32;
		default:	goto yy8;
		}
yy14:
		yych = (char)*++*p;
		switch (yych) {
		case 'e':	goto yy15;
		default:	goto yy8;
		}
yy15:
		yych = (char)*++*p;
		switch (yych) {
		case 'x':	goto yy16;
		default:	goto yy8;
		}
yy16:
		yych = (char)*++*p;
		switch (yych) {
		case '_':	goto yy17;
		default:	goto yy8;
		}
yy17:
		yych = (char)*++*p;
		switch (yych) {
		case 'M':	goto yy18;
		default:	goto yy8;
		}
yy18:
		yych = (char)*++*p;
		switch (yych) {
		case 'a':	goto yy19;
		default:	goto yy8;
		}
yy19:
		yych = (char)*++*p;
		switch (yych) {
		case 't':	goto yy20;
		default:	goto yy8;
		}
yy20:
		yych = (char)*++*p;
		switch (yych) {
		case 'c':	goto yy21;
		default:	goto yy8;
		}
yy21:
		yych = (char)*++*p;
		switch (yych) {
		case 'h':	goto yy22;
		default:	goto yy8;
		}
yy22:
		yych = (char)*++*p;
		switch (yych) {
		case ':':	goto yy23;
		default:	goto yy8;
		}
yy23:
		yych = (char)*++*p;
		switch (yych) {
		case ':':	goto yy24;
		default:	goto yy8;
		}
yy24:
		yych = (char)*++*p;
		switch (yych) {
		case '(':	goto yy25;
		default:	goto yy8;
		}
yy25:
		yych = (char)*++*p;
		switch (yych) {
		case ')':	goto yy8;
		default:	goto yy27;
		}
yy26:
		++*p;
		yych = (char)**p;
yy27:
		switch (yych) {
		case ')':	goto yy28;
		case ':':	goto yy8;
		default:	goto yy26;
		}
yy28:
		yych = (char)*++*p;
		switch (yych) {
		case ':':	goto yy29;
		default:	goto yy8;
		}
yy29:
		yych = (char)*++*p;
		switch (yych) {
		case ':':	goto yy30;
		default:	goto yy8;
		}
yy30:
		++*p;
		{ return MATCH; }
yy32:
		yych = (char)*++*p;
		switch (yych) {
		case 'r':	goto yy33;
		default:	goto yy8;
		}
yy33:
		yych = (char)*++*p;
		switch (yych) {
		case 'e':	goto yy34;
		default:	goto yy8;
		}
yy34:
		yych = (char)*++*p;
		switch (yych) {
		case 'n':	goto yy35;
		default:	goto yy8;
		}
yy35:
		yych = (char)*++*p;
		switch (yych) {
		case 'c':	goto yy36;
		default:	goto yy8;
		}
yy36:
		yych = (char)*++*p;
		switch (yych) {
		case 'e':	goto yy37;
		default:	goto yy8;
		}
yy37:
		yych = (char)*++*p;
		switch (yych) {
		case ':':	goto yy38;
		default:	goto yy8;
		}
yy38:
		yych = (char)*++*p;
		switch (yych) {
		case ':':	goto yy39;
		default:	goto yy8;
		}
yy39:
		yych = (char)*++*p;
		switch (yych) {
		case '(':	goto yy40;
		default:	goto yy8;
		}
yy40:
		yych = (char)*++*p;
		switch (yych) {
		case ')':	goto yy8;
		default:	goto yy41;
		}
yy41:
		++*p;
		yych = (char)**p;
		switch (yych) {
		case ')':	goto yy43;
		default:	goto yy41;
		}
yy43:
		yych = (char)*++*p;
		switch (yych) {
		case ':':	goto yy44;
		default:	goto yy8;
		}
yy44:
		++*p;
		{ return REFERENCE; }
yy46:
		yych = (char)*++*p;
		switch (yych) {
		case 's':	goto yy47;
		default:	goto yy8;
		}
yy47:
		yych = (char)*++*p;
		switch (yych) {
		case 'c':	goto yy48;
		default:	goto yy8;
		}
yy48:
		yych = (char)*++*p;
		switch (yych) {
		case 'r':	goto yy49;
		default:	goto yy8;
		}
yy49:
		yych = (char)*++*p;
		switch (yych) {
		case 'i':	goto yy50;
		default:	goto yy8;
		}
yy50:
		yych = (char)*++*p;
		switch (yych) {
		case 'p':	goto yy51;
		default:	goto yy8;
		}
yy51:
		yych = (char)*++*p;
		switch (yych) {
		case 't':	goto yy52;
		default:	goto yy8;
		}
yy52:
		yych = (char)*++*p;
		switch (yych) {
		case 'i':	goto yy53;
		default:	goto yy8;
		}
yy53:
		yych = (char)*++*p;
		switch (yych) {
		case 'o':	goto yy54;
		default:	goto yy8;
		}
yy54:
		yych = (char)*++*p;
		switch (yych) {
		case 'n':	goto yy55;
		default:	goto yy8;
		}
yy55:
		yych = (char)*++*p;
		switch (yych) {
		case ':':	goto yy56;
		default:	goto yy8;
		}
yy56:
		yych = (char)*++*p;
		switch (yych) {
		case ':':	goto yy57;
		default:	goto yy8;
		}
yy57:
		yych = (char)*++*p;
		switch (yych) {
		case '(':	goto yy58;
		default:	goto yy8;
		}
yy58:
		yych = (char)*++*p;
		switch (yych) {
		case ')':	goto yy8;
		default:	goto yy60;
		}
yy59:
		++*p;
		yych = (char)**p;
yy60:
		switch (yych) {
		case ')':	goto yy61;
		case ':':	goto yy8;
		default:	goto yy59;
		}
yy61:
		yych = (char)*++*p;
		switch (yych) {
		case ':':	goto yy62;
		default:	goto yy8;
		}
yy62:
		yych = (char)*++*p;
		switch (yych) {
		case ':':	goto yy63;
		default:	goto yy8;
		}
yy63:
		++*p;
		{ return DESCRIPTION; }
yy65:
		yych = (char)*++*p;
		switch (yych) {
		case 't':	goto yy66;
		default:	goto yy8;
		}
yy66:
		yych = (char)*++*p;
		switch (yych) {
		case 'l':	goto yy67;
		default:	goto yy8;
		}
yy67:
		yych = (char)*++*p;
		switch (yych) {
		case 'e':	goto yy68;
		default:	goto yy8;
		}
yy68:
		yych = (char)*++*p;
		switch (yych) {
		case ':':	goto yy69;
		default:	goto yy8;
		}
yy69:
		yych = (char)*++*p;
		switch (yych) {
		case ':':	goto yy70;
		default:	goto yy8;
		}
yy70:
		yych = (char)*++*p;
		switch (yych) {
		case '(':	goto yy71;
		default:	goto yy8;
		}
yy71:
		yych = (char)*++*p;
		switch (yych) {
		case ')':	goto yy8;
		default:	goto yy73;
		}
yy72:
		++*p;
		yych = (char)**p;
yy73:
		switch (yych) {
		case ')':	goto yy74;
		case ':':	goto yy8;
		default:	goto yy72;
		}
yy74:
		yych = (char)*++*p;
		switch (yych) {
		case ':':	goto yy75;
		default:	goto yy8;
		}
yy75:
		yych = (char)*++*p;
		switch (yych) {
		case ':':	goto yy76;
		default:	goto yy8;
		}
yy76:
		++*p;
		{ return TITLE; }
	}

    }
}


int match_test(const char *string,const char *expression)
{
	const char *err;
	int errofs=0,offset=0;
	int ovector[100];

	pcre *re = pcre_compile(expression, 0, &err, &errofs, NULL);

	if (re == NULL) 
	{
		DEBUG(" regex compilation failed\n");
		exit(0);
	}
	const int rc = pcre_exec(re, NULL, string, strlen(string), offset, 0, ovector, array_elements(ovector));
	pcre_free(re);

	return rc > 0;

}
