#include <stdio.h>
#include<stdlib.h>
#include <string.h>
typedef struct pcb        //定义PCB结构
{
    char name[20];       /*进程标识符*/
    int cputime;          /*进程占用CPU时间*/
    int startTime;      /*进程开始时间*/
    int needtime;         /*进程到完成还需要的CPU时间*/
    struct pcb *next;    /*链指针*/
}PCB;
PCB *run, *finished, *finished_tail, *creating;
PCB *queue1, *queue1_tail, *queue2, *queue2_tail, *queue3, *queue3_tail;
void output(int t)      /*输出3个队列*/
{
    PCB *p;
    printf("当前时间:___%d___\n", t);
    printf("______________________\n");
    printf("进程名\t状态\t已运行\t剩余\n");
    if (run != NULL)
        printf("%s\t运行\t%d\t%d\n", run->name, run->cputime, run->needtime);
    else
        printf("*运行状态为空\n");
    p = queue1;
    if (p != NULL)
    {
        while (p != NULL)
        {
            printf("%s\t就绪1\t%d\t%d\n", p->name, p->cputime, p->needtime);
            p = p->next;
        }
    }
    else
        printf("*一级就绪队列为空\n");
    p = queue2;
    if (p != NULL)
    {
        while (p != NULL)
        {
            printf("%s\t就绪2\t%d\t%d\n", p->name, p->cputime, p->needtime);
            p = p->next;
        }
    }
    else
        printf("*二级就绪队列为空\n");
    p = queue3;
    if (p != NULL)
    {
        while (p != NULL)
        {
            printf("%s\t就绪3\t%d\t%d\n", p->name, p->cputime, p->needtime);
            p = p->next;
        }
    }
    else
        printf("*三级就绪队列为空\n");
    p = finished;
    if (p != NULL)
    {
        while (p != NULL)
        {
            printf("%s\t完成\t%d\t%d\n", p->name, p->cputime, p->needtime);
            p = p->next;
        }
    }
    else
        printf("*完成队列为空\n");
    p = creating;
    if (p != NULL)
    {
        while (p != NULL)
        {
            printf("%s\t未提交\t%d\t%d\n", p->name, p->cputime, p->needtime);
            p = p->next;
        }
    }
    getchar();
}
PCB* establish()/*建立未完成队列*/
{
    printf("建立作业队列\n\n");
    int i, proc_num, nt, pr;
    PCB *p, *q, *head;
    proc_num = 0;
    while (1)
    {
        printf("请输入进程的个数(有效范围1-100)：");
        scanf("%d", &proc_num);
        printf("\n");
        if (proc_num >= 1 && proc_num <= 100)
            break;
        else
            printf("输入有误。请重新输入!\n");
        getchar();
    }
    head = (struct pcb*)malloc(sizeof(struct pcb));
    printf("输入第1个进程的名称:");
    scanf("%s", head->name);
    // 输入运行时间
    while (1)
    {
        printf("需要的运行时间:");
        scanf("%d", &nt);
        if (nt > 0)
            break;
        else
        {
            printf("输入无效，重新输入!\n");
            getchar();
        }
    }
    head->needtime = nt;
    // 输入开始时间
    printf("开始时间:");
    scanf("%d", &pr);
    head->startTime = pr;
    head->cputime = 0;    /*进程已获得的运行时间*/
    head->next = NULL;
    q = head;
    for (i = 1; i < proc_num; i++)
    {
        printf("\n");
        p = (struct pcb*)malloc(sizeof(struct pcb));
        printf("输入第%d进程的名称:", i + 1);
        scanf("%s", p->name);
        printf("需要的运行时间:");
        scanf("%d", &nt);
        p->needtime = nt;
        printf("开始时间:");
        scanf("%d", &pr);
        p->startTime = pr;
        p->cputime = 0;/*进程已获得的运行时间*/
        p->next = NULL;
        q->next = p;
        q = p;
    }
    creating = head;
    return head;
}


void dispatch() {
    PCB* p, *tail, *last;
    int t = 0;
    bool dont_finish;
    creating = establish();
    int cur_time = 0;        // 时间
    while (true)            // 时间流逝
    {
        // 从未提交队列中选择队列
        p = creating;
        last = NULL;
        while (p != NULL) {
            // 如果程序已经可以运行了, 则从未提交队列移除
            if (p->startTime <= cur_time) {
                if (last == NULL)
                    creating = p->next;
                else
                    last->next = p->next;
                // 添加到就绪队列
                if (queue1 == NULL) {
                    queue1 = p;
                    queue1_tail = p;
                }
                else {
                    queue1_tail->next = p;
                    queue1_tail = p;
                }
                p = p->next;
                queue1_tail->next = NULL;
            }
            else {
                last = p;
                p = p->next;
            }
        }
        // 从就绪队列中选择一级队列
        if (queue1 != NULL) {
            p = queue1;        // 取出队头
            queue1 = queue1->next;
            p->next = NULL;        // 将next清空
            p->cputime++;        // 修改属性
            p->needtime--;
            cur_time++;
            run = p;
            output(cur_time);
            run = NULL;
            if (p->needtime <= 0) {    // 如果剩余时间归零
                if (finished == NULL) finished = p;
                else finished_tail->next = p;
                finished_tail = p;
            }
            else {
                if (queue2 == NULL) queue2 = p;
                else queue2_tail->next = p;
                queue2_tail = p;
            }
        }
        else if (queue2 != NULL) {
            p = queue2;        // 取出队头
            queue2 = queue2->next;
            p->next = NULL;        // 将next清空
            p->cputime += 2;
            p->needtime = p->needtime < 2 ? 0 : p->needtime - 2;
            cur_time += 2;
            run = p;
            output(cur_time);
            run = NULL;
            if (p->needtime <= 0) {    // 如果剩余时间归零
                if (finished == NULL) finished = p;
                else finished_tail->next = p;
                finished_tail = p;
            }
            else {
                if (queue3 == NULL) queue3 = p;
                else queue3_tail->next = p;
                queue3_tail = p;
            }
        }
        else if (queue3 != NULL) {
            p = queue3;
            queue3 = queue3->next;
            p->next = NULL;
            p->cputime += 4;
            p->needtime = p->needtime < 4 ? 0 : p->needtime - 4;
            cur_time += 4;
            run = p;
            output(cur_time);
            run = NULL;
            if (p->needtime <= 0) {    // 如果剩余时间归零
                if (finished == NULL) finished = p;
                else finished_tail->next = p;
                finished_tail = p;
            }
            else {
                if (queue3 == NULL) queue3 = p;
                else queue3_tail->next = p;
                queue3_tail = p;
            }
        }
        else {
            cur_time++;
            printf("CPU空闲! 时间=%d\n\n", cur_time);
            if (creating == NULL)break;
        }

    }
    printf("运行结束!\n");
}

/*主程序*/
int main()
{
    int N;
    while (1)
    {
        run = NULL;
        queue1 = NULL;
        queue1_tail = NULL;
        finished = NULL;
        finished_tail = NULL;
        printf("===================\n");
        printf("进程调度算法演示程序 \n");
        printf("===================\n");
        printf("      1:多级反馈队列调度算法\n");
        printf("      2:退出\n");
        printf("\n");
        printf("   请选择：");
        scanf("%d", &N);
        if (N == 1) {
            dispatch();
        }
        else if (N == 2) {
            break;
        }
        else {
            printf("您输入的信息有误，请重新输入!\n\n");
            getchar();
        }
    }
    return 0;
}
