/*
 * @Author: S 
 * @Date: 2018-07-11 11:25:16 
 * @Last Modified by: S
 * @Last Modified time: 2019-04-03 10:14:33
 * 
 * 服务器进程入口文件
 */

#include <stdio.h>
// #include <pjlib.h>
// #include <pjlib-util.h>
// #include <pjmedia.h>
// #include <pjmedia-codec.h>
// #include <pjsip.h>
// #include <pjsip_simple.h>
// #include <pjsip_ua.h>
// #include <pjsua-lib/pjsua.h>
// #include <pj/timer.h>
#include <sys/time.h>
#include <sys/sysctl.h>
#include <unistd.h>
/**
 * @brief 主程序入口
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */

char *stackPointerTest(void)
{
    char *abc = "hello";
    return abc; // 禁止使用栈内指针，函数执行结束后销毁
}

// void ppTest(char **p, int num)
// {
//     printf("[pointer] **p:");
//     *p = (char *)malloc(sizeof(char) * num);
// }

char *itoa(int num, char *ret, int redias)
{
    printf("[itoa] format num:%d to redias:%d\n", num, redias);
    char index[] = "0123456789ABCDEF";
    unsigned unum;
    int i = 0, j, k;
    //十进制负数
    if (num < 0 && redias == 10)
    {
        ret[i++] = '-';
        unum = (unsigned)-num;
    }
    else
    {
        unum = (unsigned)num;
    }

    do
    {
        ret[i++] = index[unum % (unsigned)redias];
    } while ((unum /= redias) != 0);

    ret[i] = '\0';

    if (ret[0] == '-')
    {
        k = 1;
    }
    else
    {
        k = 0;
    }

    char temp;
    for (j = k; j <= (i - 1) / 2; j++)
    {
        temp = ret[j];
        ret[j] = ret[i - 1 - j + k];
        ret[i - 1 - j + k] = temp;
    }

    return ret;
}

// void numPrint(int *a)
// {
//     printf("number array is :%s", a);
// }

void timeTest(void)
{
    struct timeval now;
    struct timezone currentZone;

    gettimeofday(&now, &currentZone);

    printf("current time sec:%ld\n", now.tv_sec);
    printf("current time us:%d\n", now.tv_usec);
    printf("current time tz_minuteswest:%d\n", currentZone.tz_minuteswest);
    printf("current time zone:%d\n", currentZone.tz_dsttime);
}

#define CTL_KERN 1
static int64_t get_boottime()
{
    struct timeval boottime;
    int mib[2] = {CTL_KERN, KERN_BOOTTIME};
    size_t size = sizeof(boottime);
    int rc;

    rc = sysctl(mib, 2, &boottime, &size, NULL, 0);
    if (rc != 0)
        return 0;

    return (int64_t)boottime.tv_sec * 1000000 + (int64_t)boottime.tv_usec;
}
void pjTimeTest(void)
{
    int64_t before_now, after_now;
    struct timeval now;

    after_now = get_boottime();
    //why???
    do
    {
        printf("before now:%lld\n", before_now);
        printf("after now:%lld\n", after_now);
        before_now = after_now;
        gettimeofday(&now, NULL);
        after_now = get_boottime();
        printf("before now:%lld\n", before_now);
        printf("after now:%lld\n", after_now);
    } while (after_now != before_now);

    // pj_uint64_t ts;

    // ts = (int64_t)now.tv_sec * 1000000 + (int64_t)now.tv_usec;
    // ts -= before_now;
    // ts *= 1000;

    // printf("ret == :%lld", ts);
}

// #define time_after(a, b)            \
//     (typecheck(unsigned long, a) && \
//      typecheck(unsigned long, b) && \
//      ((long)(b) - (long)(a) < 0))
// #define time_before(a, b) time_after(b, a)

void ultol()
{
    printf("long size is :%ld\n", sizeof(long));
    unsigned long a = 0xFFFFFFFFFFFFFFFF;
    unsigned long b = a + 3;
    printf("a:%lu\n", a);
    printf("b:%lu\n", b);

    int ret = ((long)(b) - (long)(a) < 0);

    printf("result:%d\n", ret);
}

struct str_test
{
    int16_t a;
    char b;
};

typedef struct str_test *str_test;

void structSizeTest()
{
    printf("size of str_test:%lu\n", sizeof(str_test));
    printf("size of str_test*:%lu\n", sizeof(struct str_test *));
}

void charAsteriskTest(const char *str)
{
    printf("[sp][parse] pj_cis_add_str:%s", str);
    while (*str)
    {
        printf("str char is :%d\n", *str);
        ++str;
    }
}

/*******fixme Char array cast to Struct Test *******/
void test_char_array_cast_to_struct()
{
    unsigned char a[] = "0123456789ABCDEF";
    struct A
    {
        int a;//对应"0123"--转ascii "48 49 50 51" 48<<24 + 49<<16 + 50<< 8 + 51 = 805306368
        char b;
        char c;
        char d;
        int e;
    };

    int *n = (int *)"0";
    printf("n = %d\n", *n);

    int *m = (int *)"0123";
    printf("m = %d\n", *m);

    struct A *struct_a = (struct A *)a;

    printf("struct a.a = %d\n", struct_a->a);
    printf("struct a.b = %c\n", struct_a->b);
    printf("struct a.c = %c\n", struct_a->c);
    printf("struct a.d = %c\n", struct_a->d);
    printf("struct a.e = %d\n", struct_a->e);
}

int main(int argc, char const *argv[])
{
    test_char_array_cast_to_struct();
    // charAsteriskTest(",\r\n");
    printf("size of unsigned int:%lu\n", sizeof(unsigned int));
    printf("size of  int:%lu\n", sizeof(int));
    printf("size of void*:%lu\n", sizeof(void *));

    // structSizeTest();
    // ultol();
    // pjTimeTest();
#if 0
    char string[25];
    itoa(121, string, 2);
    printf("result is :%s\n", string);

    itoa(121, string, 8);
    printf("result is :%s\n", string);

    itoa(121, string, 16);
    printf("result is :%s\n", string);

    itoa(-121, string, 10);
    printf("result is :%s\n", string);





    char *pc = "test";
    printf("[pointer] pc addr:%p\n", pc);
    char **ppc = &pc;
    printf("[pointer] ppc addr:%p\n", ppc);
    printf("[pointer] *pc addr:%p\n", pc);
    char *c;
    ppTest(&c, 3);
    printf("[pointer] c addr:%s\n", c);

    char *stackPointer = stackPointerTest();
    printf("pointer is %s\n", stackPointer);

    /* code */
    printf("size of test:%lu\n", sizeof(test));

    //new struct instance
    struct str_test *newItem = malloc(sizeof(struct str_test));
    newItem->a = 1;

    printf("print struct with s test:%s", newItem);

    struct str_test newItem2;
    newItem2.a = 2;

    printf("newItem addr: %p\n", newItem);
    printf("newItem1 addr: %p\n", &newItem2);

    pj_memcpy(newItem, &newItem2, sizeof(struct str_test));

    printf("item1 after cpyed:%d \n ", newItem->a);

    /**
     *  cast struct to long
     */
    long aL = (long)newItem; //将内存地址转到aL中保存
    long bL = (long)&newItem2;

    printf("al is %ld\n", aL);
    printf("bl is %ld\n", bL);

    int aI = 5;

    /************** unsigned Test
     * unsigned a  == unsigned int a
     *  ***************/
    printf("unsigned -1==%d\n", (unsigned)-1);

    unsigned a = 1;
    int b = -2;

    unsigned plus = a + b;

    printf("result %d \n", plus);

    if (a)
    {
        printf("a == yes\n");
    }
    else
    {
        printf("a === no\n");
    }

    if (b)
    {
        printf("b -- yes \n");
    }
    else
    {
        printf("b -- no \n");
    }

    // int c = b;

    // printf("c==%d\n", c);
    // printf("c + a = %d\n", c + a);

    return 0;
#endif
}
