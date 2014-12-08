#include "file_ops.h"
#include "mem_ops.h"
#include "string_ops.h"

int WriteFile(char *file,char *str)
{
	FILE *arq;
 
	arq=fopen(file,"a"); 

	if ( arq == NULL ) 
	{
		DEBUG("error in WriteFile() %s",file); 
		exit(1);
	}

	fprintf(arq,"%s\n",str); 

	if( fclose(arq) == EOF )
	{
		DEBUG("error in Write() file %s",file);
		exit(1);
	}
	arq=NULL;
 

	return 1;
}

//read lines of file
char *ReadLines(char * NameFile)
{
	FILE * arq;

	arq = fopen(NameFile, "rx");

// todo think implement fcntl() ,toctou mitigation...
	if( arq == NULL )
	{
		DEBUG("error in to open() file"); 	 
		exit(1);
	}

	char *lineBuffer=xcalloc(1,1); 
	char line[512];
	memset(line,0,511);

	while( fgets(line,sizeof line,arq) )  
	{
		lineBuffer=xrealloc(lineBuffer,strlen(lineBuffer)+strlen(line)+2);
		strncat(lineBuffer,line,strlen(lineBuffer)-1);
	}

 
	if( fclose(arq) == EOF )
	{
		DEBUG("Error in close() file %s",NameFile);
		exit(1);
	}

	arq=NULL;

	lineBuffer[strlen(lineBuffer)-1]='\0';


	free(lineBuffer);

	return lineBuffer;
}

//read lines of file
char *Search_for(char * NameFile,char *regex)
{
	FILE * arq;
	int match=0;
	int count=1;

	arq = fopen(NameFile, "rx");

// todo think implement fcntl() ,toctou mitigation...
	if( arq == NULL )
	{
		DEBUG("error in to open() file"); 	 
		exit(1);
	}

	char *lineBuffer=xcalloc(1,1); 
	char line[2048];
	char tmpline[2128];
	memset(line,0,1023);

	while( fgets(line,1023,arq) )  
	{
		match=match_test(line,regex);
		if(match)
		{
			//fprintf(stdout,"Line: %d - %s \n",count,line);
			lineBuffer=xrealloc(lineBuffer,strlen(lineBuffer)+2128);
			snprintf(tmpline,2127," Line: %d -  %s",count,line);
			strncat(lineBuffer,tmpline,2127);
		}
		count++;
	}

 
	if( fclose(arq) == EOF )
	{
		DEBUG("Error in close() file %s",NameFile);
		exit(1);
	}

	arq=NULL;

	lineBuffer[strlen(lineBuffer)-1]='\0';

	free(lineBuffer);

	return lineBuffer;
}


void fly_to_analyse(char *path, char *config)
{
	char *p = ReadLines(config);
	char *last = p;
	char *result2=NULL;
	char title[128],description[128],reference[128],match[128];	
	int result=0,sz=0;


	while(!result )
		switch (parse_eggs(&p, &last)) 
		{
			case TITLE:
					sz = p - last - 1;
					memset(title,0,127);
					snprintf(title,127,"%.*s", sz, last);
					strcpy(title,ClearStr(title,10));
				break;


			case DESCRIPTION:
				
 					sz = p - last - 1;
					memset(description,0,127);
					snprintf(description,127,"%.*s", sz, last);
					strcpy(description,ClearStr(description,16));
				break;

			case REFERENCE:

					sz = p - last - 1;
					memset(reference,0,127);
					snprintf(reference,127,"%.*s", sz, last);
					strcpy(reference,ClearStr(reference,14));
				break;
/*
TODO* fix bug in parse "::Regex_Match::"

*/
			case MATCH:
					sz = p - last - 1;
					memset(match,0,127);
					snprintf(match,127,"%.*s", sz, last);
					strcpy(match,ClearStr(match,16));

					if(result2!=NULL)
					{
						memset(result2,0,strlen(result2)-1);
					}

					result2=Search_for(path,match);

					if(strlen(result2)>2)
					{
						fprintf(stdout,"\n-------------------\n %sTitle:%s  %s  \n %sDescription:%s %s \n %sReference:%s %s \n %sMatch:%s %s  \n%s%s%s\n",YELLOW,LAST,title,YELLOW,LAST,description,YELLOW,LAST,reference,YELLOW,LAST,match,CYAN,result2,LAST);

						if(log_file != NULL)
						{
							WriteFile(log_file," Path: ");
							WriteFile(log_file,path);
							WriteFile(log_file,"\n Module: ");
							WriteFile(log_file,config);
							WriteFile(log_file,"\n Title: ");
							WriteFile(log_file,title);
							WriteFile(log_file,"\n Description: ");
							WriteFile(log_file,description);
							WriteFile(log_file,"\n reference: ");
							WriteFile(log_file,reference);
							WriteFile(log_file,"\n Match: ");
							WriteFile(log_file,match);
							WriteFile(log_file,"\n Result: \n");
							WriteFile(log_file,result2);
		 
						}
					}
				break;


			case END:
				result=1;	
				break;
    		}

}



void mosca_start (const char * dir_name, char * extension, char * config)
{
	DIR * d;
	char tmp_path[512];	

 	d = opendir (dir_name);

	if (! d) 
	{
		DEBUG ("Cannot open directory '%s': %s\n", dir_name, strerror (errno));
 		exit (EXIT_FAILURE);
	}

	while (1) 
	{
		struct dirent * entry;
 		const char * d_name;

		entry = readdir (d);

		if (! entry) 
		{
			break;
		}

		d_name = entry->d_name;

// TODO* i need improve that extension check
		if(strcmp(d_name,".") && strcmp(d_name,"..") && match_test(d_name,extension))
		{
			snprintf(tmp_path,511,"%s/%s",dir_name,d_name);
			printf("\n=====================================\n%s Path:%s %s \n %sUse Module:%s %s\n",YELLOW,LAST,tmp_path,YELLOW,LAST,config);
			fly_to_analyse(tmp_path, config);
			memset(tmp_path,0,511);
		}


	        if (entry->d_type & DT_DIR) 
		{

            
	            if (strcmp (d_name, "..") != 0 && strcmp (d_name, ".") != 0) 
		    {
	  		int path_length;
			char path[PATH_MAX];
 
			path_length = snprintf (path, PATH_MAX, "%s/%s", dir_name, d_name);


     	                if (path_length >= PATH_MAX) 
			{
               		     DEBUG("Path length has got too long.\n");
               		     exit(0);
               		}

                	mosca_start (path,extension,config);
	         }
	}
    }

    if(closedir(d)) 
    {
        DEBUG("Could not close '%s': %s\n", dir_name, strerror (errno));
        exit(0);
    }
}
