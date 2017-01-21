//http://qiita.com/alaif-net@github/items/e4432c374985dc38e038
#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include <string.h>
#define MAX_BUF 65535

int cutHTML(int i);
static char wr_buf[MAX_BUF];
static int  wr_index = 0;

typedef struct node{
  char url[200];
  char title[200];
  char desc[200];
  char data[100];
  struct node *next;
  struct node *before;
}list;

list datelist[50];
int cutHTML(int i){
  for(int j=0;j<2;i++){
    if(wr_buf[i]=='['){
      j++;
    }
  }
  return i;
}
int Nokogiri(){
  //initialize
  for(int t=0;t<50;t++){
    /*
    datelist[t].url="";
    datelist[t].desc="";
    datelist[t].data="";
    datelist[t].title="";
    */
    datelist[t].next=NULL;
    datelist[t].before=NULL;
  }
  int num=0;
  int i=0;
  int date_num=0;
  while(num<=17){
    if(wr_buf[i]=='\n')num++;
    i++;
  }
  //take title
  for(date_num=0;date_num<27;date_num++){
  i=cutHTML(i);
  int j=i;
  while(wr_buf[i]!=']'){
    datelist[date_num].title[i-j]=wr_buf[i];
    i++;
  }
  //take description
  for(;wr_buf[i]!='\n';i++);
  i=cutHTML(i);
  j=i;
  while(wr_buf[i]!=']'){
    datelist[date_num].desc[i-j]=wr_buf[i];
    i++;
  }
  for(;wr_buf[i]!='\n';i++);
  //take url
  for(;wr_buf[i]!='>';i++);
  i++;
  j=i;
  while(wr_buf[i]!='<'){
    datelist[date_num].url[i-j]=wr_buf[i];
    i++;
  }
  for(;wr_buf[i]!='\n';i++);
  i++;
  for(;wr_buf[i]!='\n';i++);
  for(;wr_buf[i]!='>';i++);
  i++;
  j=i;
  while(wr_buf[i]!='<'){
    datelist[date_num].data[i-j]=wr_buf[i];
    i++;
  }
  num=0;
  while(num<=3){
    if(wr_buf[i]=='\n')num++;
    i++;
  }
  if(date_num!=26){
    datelist[date_num].next=&datelist[date_num+1];
  }else{
    datelist[date_num].next=&datelist[0];
  }
  if(date_num!=0){
    datelist[date_num].before=&datelist[date_num-1];
  }else{
    datelist[date_num].before=&datelist[26];
  }
  }
  return 0;
}
size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp)
{
  int segsize = size * nmemb;
  if ((wr_index + segsize) > MAX_BUF) {
    *(int *)userp = 1;
    return 0;
  }
  memcpy((void *)&wr_buf[wr_index], buffer, (size_t)segsize);
  wr_index += segsize;
  wr_buf[wr_index] = '\0';
  return segsize;
}

int main(void)
{
  CURL *curl;
  CURLcode ret;
  int wr_error = 0;
  curl = curl_easy_init();
  if (curl == NULL) {
    fprintf(stderr, "curl_easy_init failed.\n");
    return 1;
  }
//http://feeds.bbci.co.uk/news/world/asia/rss.xml
  curl_easy_setopt(curl, CURLOPT_URL, "feeds.bbci.co.uk/news/world/asia/rss.xml");
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&wr_error);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
  ret = curl_easy_perform(curl);

  printf("ret=%d (write_error=%d)\n", ret, wr_error);

  if (ret == 0) {
    Nokogiri();
  }
  list *p;
  p=&datelist[0];
  char input[50];
  char hogehoge[200]="firefox ";
  int flag=0;
  for(;;){
    system ("clear\n");
    printf("\x1b[32m");
    printf("--Title--\n");
    printf("\x1b[37m");
    printf("%s\n",p->title);
    printf("\x1b[33m");
    printf("--Description--\n");
    printf("\x1b[37m");
    printf("%s\n",p->desc);
    printf("\x1b[34m");
    printf("--Url--\n");
    printf("\x1b[37m");
    printf("%s\n",p->url);
    printf("\x1b[35m");
    printf("--Date--\n");
    printf("\x1b[37m");
    printf("%s\n\n\n",p->data);



    if(flag){
      printf("\n\n\n\ninvalid operation\n");
      printf("input \"next\" or \"before\" \"open\" \"halt\" \n");
      flag=0;
    }else{
      printf("\n\n\n\ninput \"next\" or \"before\" \"open\" \"halt\" \n");
    }
        LABEL:
    scanf("%s",input);
    if(strcmp(input,"next")==0){
      p=p->next;
      continue;
    }else if(strcmp(input,"before")==0){
      p=p->before;
    }else if(strcmp(input,"open")==0){
      strcat(hogehoge,datelist[0].url);
      system(hogehoge);
      strcpy(hogehoge,"firefox ");
      goto LABEL;
    }else if(strcmp(input,"exit")==0||strcmp(input,"halt")==0){
      break;
    }else{
      flag=1;
    }
  }
  curl_easy_cleanup(curl);
  return 0;
}
