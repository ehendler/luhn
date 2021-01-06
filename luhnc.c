#include"luhnc.h"
int luhn_char_pointer(const char * ccnum){
  int cclen=strlen(ccnum);
  int sum=0;
  for(int i=cclen-1;i>=0;i--){
    int n=ccnum[i]-48;
    if((i-cclen-1)%2){
      int d=n*2;
      sum+=d>=10?d-9:d;
    }
    else sum+=n;
  }
  return sum%10;
}
int luhn_int_pointer(environment * env){
  int sum=0;
  for(int i=env->cclen-1;i>=0;i--){
    if((i-env->cclen-1)%2){
      int d=env->ccint[i]*2;
      sum+=d>=10?d-9:d;
    }
    else sum+=env->ccint[i];
  }
  return sum%10;
}
void last_six(environment * env){
  int index=env->ccint[env->cclen-6]*10+env->ccint[env->cclen-5];
  if(!env->last_six[index])printf("%02d\n",index);
  env->last_six[index]=1;
}
void full(environment * env){
  for(int j=0;j<env->cclen;j++)
    printf("%d",env->ccint[j]);
  printf("\n");
}
int print_all_valid_numbers(const char * ccnum,void(*format)()){
  environment env;
  env.ccnum=ccnum;
  env.cclen=strlen(ccnum);
  env.wildcards=malloc(sizeof(int)*env.cclen);
  memset(env.wildcards,0,env.cclen);
  env.ccint=malloc(sizeof(int)*env.cclen);
  env.last_six=malloc(sizeof(int)*100);
  env.wildcard_count=0;
  for(int i=0;i<env.cclen;i++){
    if(ccnum[i]=='*'){
      env.ccint[i]=0;
      env.wildcards[env.wildcard_count++]=i;
    }
    else env.ccint[i]=ccnum[i]-48;
  }
  int i=env.wildcard_count-1;
  while(i>=0&&(env.ccint[env.wildcards[i]]++)<=10){
    if(env.ccint[env.wildcards[i]]==10){
      env.ccint[env.wildcards[i]]=0;
      i--;
      continue;
    }
    else if((env.wildcard_count-1)!=i){
      i++;
      while(((env.wildcard_count-1)!=i)&&env.ccint[env.wildcards[i+1]]==0)i++;
    }
     if(!luhn_int_pointer(&env))format(&env);
  }
  free(env.ccint);
  free(env.last_six);
  free(env.wildcards);
}
int main(){
  char ccnum[]="4242**42***4242*";
  print_all_valid_numbers(ccnum,&full);
}
