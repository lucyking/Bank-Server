//
// Created by xiadaqiang on 2017/5/10.
//
#include<stdio.h>
#include<errno.h>
#include <cstring>
void fail(char *msg)
{
    printf("FAIL: %s, caused by %s\n", msg, strerror(errno));
}