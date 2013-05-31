#include <stdio.h>
#include "includes.h"

/*
struct tag_iter_file{
	FILE *fp;
	char line[500];
	int isEnd;
};
*/
int isSkipLine(char *line)
{
	int i;
	
	if(line[0]=='#'){
		return 1;
	}
	for(i=0;line[i];i++){
		if(line[i]==' '||line[i]=='\t'||line[i]=='\n'||line[i]=='\r'){
			continue;
		}
		return 0;
	}
	return 1;
}
static void fill_buf(struct tag_iter_file *pIter)
{
	for(;;){
		char *result;
		
		result=fgets(pIter->line,sizeof(pIter->line),pIter->fp);
		if(result==NULL){
			pIter->isEnd=1;
			break;
		}
		if(isSkipLine(pIter->line)){
			continue;
		}
		break;
	}
}
int iter_file_init(struct tag_iter_file *pIter,const char *file_name)
{
	pIter->fp=fopen(file_name,"r");
	ASSERT_MINE(pIter->fp!=NULL);
	pIter->isEnd=0;
	fill_buf(pIter);
	return 0;
}
char *iter_peek_file(struct tag_iter_file *pIter)
{
	if(pIter->isEnd){
		return NULL;
	}else{
		return pIter->line;
	}
}
void iter_next_file(struct tag_iter_file *pIter)
{
	fill_buf(pIter);
}
