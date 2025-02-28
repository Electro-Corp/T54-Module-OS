/*
  Basic string operations
*/
#ifndef STRING_H
#define STRING_H

static int strlen(const char *str){
	const char *s;
	for (s = str; *s; ++s);
	return (s - str);
}

static char* strcat(char *dst, const char *src){
  int n = strlen(src);
  if (n != 0) {
    char *d = dst;
    const char *s = src;
    while (*d != 0)
      d++;
    do {
      if ((*d = *s++) == 0)
        break;
      d++;
    } while (--n != 0);
    *d = 0;
  }
  return (dst);
}

static char* strcpy(char *dst, const char *src){
  int n = strlen(src);
  if (n != 0) {
    char *d = dst;
    const char *s = src;
    do {
      if((*d++ = *s++) == 0) {
        /* NUL pad the remaining n-1 bytes */
        while(--n != 0)
          *d++ = 0;
        break;
      }
    }while (--n != 0);
  }
  return (dst);
}

static char* strncpy(char *dst, const char *src, int n){
  if (n != 0) {
    char *d = dst;
    const char *s = src;
    do {
      if((*d++ = *s++) == 0) {
        /* NUL pad the remaining n-1 bytes */
        while(--n != 0)
          *d++ = 0;
        break;
      }
    }while (--n != 0);
  }
  return (dst);
}

static int strcmp(const char *s1, const char *s2){
  while (*s1 == *s2++)
    if (*s1++ == 0)
      return (0);
  return (*(unsigned char *)s1 - *(unsigned char *)--s2);
}


static int strclr(const char *s1){
  int n = strlen(s1);
  char *s = s1;
  for(int i = 0; i < n; i++){
    *s++ = '\0';
  }
}

#endif