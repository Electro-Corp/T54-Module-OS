#include "stdlib.h"

int memcmp(const void* aptr, const void* bptr, int size) {
  const unsigned char* a = (const unsigned char*) aptr;
  const unsigned char* b = (const unsigned char*) bptr;
  for (int i = 0; i < size; i++) {
    if (a[i] < b[i]){
      return -1;
        }
    else if (b[i] < a[i]){
      return 1;
        }
    }
  return 0;
}

void* memcpy(void* restrict dstptr, const void* restrict srcptr, int size) {
  return memcpyBounded(dstptr, srcptr, 0, size);
}


void* memcpyBounded(void* restrict dstptr, const void* restrict srcptr, int start, int size){
    unsigned char* dst = (unsigned char*) dstptr;
  const unsigned char* src = (const unsigned char*) srcptr;
  for (int i = start; i < start + size; i++)
    dst[i] = src[i];
  return dstptr;
}

void reverse(char str[], int length) {
    int start = 0;
    int end = length - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        end--;
        start++;
    }
}

char* itoa(int num, int base, char* str) {
    // Validate the base
    if (base < 2 || base > 16) {
        *str = '\0';  // Invalid base, return empty string
        return str;
    }

    // Handle 0 explicitly, otherwise empty string is used
    if (num == 0) {
        str[0] = '0';
        str[1] = '\0';
        return str;
    }

    // Handle negative numbers only for base 10
    int i = 0;
    int neg = 0;
    if (num < 0 && base == 10) {
        neg = 1;
        num = -num;
    }

    // Process individual digits
    while (num != 0) {
        int rem = num % base;
        str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        num /= base;
    }

    // Append negative sign for base 10
    if (neg) {
        str[i++] = '-';
    }

    str[i] = '\0'; // Null-terminate string

    // Reverse the string
    reverse(str, i);

    return str;
}

int charToInt(const char *str) {
    int result = 0;
    int sign = 1; 

    if (*str == '-') {
        sign = -1;
        str++;
    }

    while (*str != '\0') {
        if (*str < '0' || *str > '9') {
            return 0; 
        }
        result = result * 10 + (*str - '0');
        str++;
    }

    return sign * result;
}
