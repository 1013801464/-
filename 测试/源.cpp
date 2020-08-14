#include <stdio.h>
#include<stdlib.h>
#include <string.h>
typedef struct pcb        //����PCB�ṹ
{
    char name[20];       /*���̱�ʶ��*/
    int cputime;          /*����ռ��CPUʱ��*/
    int startTime;      /*���̿�ʼʱ��*/
    int needtime;         /*���̵���ɻ���Ҫ��CPUʱ��*/
    struct pcb *next;    /*��ָ��*/
}PCB;
PCB *run, *finished, *finished_tail, *creating;
PCB *queue1, *queue1_tail, *queue2, *queue2_tail, *queue3, *queue3_tail;
void output(int t)      /*���3������*/
{
    PCB *p;
    printf("��ǰʱ��:___%d___\n", t);
    printf("______________________\n");
    printf("������\t״̬\t������\tʣ��\n");
    if (run != NULL)
        printf("%s\t����\t%d\t%d\n", run->name, run->cputime, run->needtime);
    else
        printf("*����״̬Ϊ��\n");
    p = queue1;
    if (p != NULL)
    {
        while (p != NULL)
        {
            printf("%s\t����1\t%d\t%d\n", p->name, p->cputime, p->needtime);
            p = p->next;
        }
    }
    else
        printf("*һ����������Ϊ��\n");
    p = queue2;
    if (p != NULL)
    {
        while (p != NULL)
        {
            printf("%s\t����2\t%d\t%d\n", p->name, p->cputime, p->needtime);
            p = p->next;
        }
    }
    else
        printf("*������������Ϊ��\n");
    p = queue3;
    if (p != NULL)
    {
        while (p != NULL)
        {
            printf("%s\t����3\t%d\t%d\n", p->name, p->cputime, p->needtime);
            p = p->next;
        }
    }
    else
        printf("*������������Ϊ��\n");
    p = finished;
    if (p != NULL)
    {
        while (p != NULL)
        {
            printf("%s\t���\t%d\t%d\n", p->name, p->cputime, p->needtime);
            p = p->next;
        }
    }
    else
        printf("*��ɶ���Ϊ��\n");
    p = creating;
    if (p != NULL)
    {
        while (p != NULL)
        {
            printf("%s\tδ�ύ\t%d\t%d\n", p->name, p->cputime, p->needtime);
            p = p->next;
        }
    }
    getchar();
}
PCB* establish()/*����δ��ɶ���*/
{
    printf("������ҵ����\n\n");
    int i, proc_num, nt, pr;
    PCB *p, *q, *head;
    proc_num = 0;
    while (1)
    {
        printf("��������̵ĸ���(��Ч��Χ1-100)��");
        scanf("%d", &proc_num);
        printf("\n");
        if (proc_num >= 1 && proc_num <= 100)
            break;
        else
            printf("������������������!\n");
        getchar();
    }
    head = (struct pcb*)malloc(sizeof(struct pcb));
    printf("�����1�����̵�����:");
    scanf("%s", head->name);
    // ��������ʱ��
    while (1)
    {
        printf("��Ҫ������ʱ��:");
        scanf("%d", &nt);
        if (nt > 0)
            break;
        else
        {
            printf("������Ч����������!\n");
            getchar();
        }
    }
    head->needtime = nt;
    // ���뿪ʼʱ��
    printf("��ʼʱ��:");
    scanf("%d", &pr);
    head->startTime = pr;
    head->cputime = 0;    /*�����ѻ�õ�����ʱ��*/
    head->next = NULL;
    q = head;
    for (i = 1; i < proc_num; i++)
    {
        printf("\n");
        p = (struct pcb*)malloc(sizeof(struct pcb));
        printf("�����%d���̵�����:", i + 1);
        scanf("%s", p->name);
        printf("��Ҫ������ʱ��:");
        scanf("%d", &nt);
        p->needtime = nt;
        printf("��ʼʱ��:");
        scanf("%d", &pr);
        p->startTime = pr;
        p->cputime = 0;/*�����ѻ�õ�����ʱ��*/
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
    int cur_time = 0;        // ʱ��
    while (true)            // ʱ������
    {
        // ��δ�ύ������ѡ�����
        p = creating;
        last = NULL;
        while (p != NULL) {
            // ��������Ѿ�����������, ���δ�ύ�����Ƴ�
            if (p->startTime <= cur_time) {
                if (last == NULL)
                    creating = p->next;
                else
                    last->next = p->next;
                // ��ӵ���������
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
        // �Ӿ���������ѡ��һ������
        if (queue1 != NULL) {
            p = queue1;        // ȡ����ͷ
            queue1 = queue1->next;
            p->next = NULL;        // ��next���
            p->cputime++;        // �޸�����
            p->needtime--;
            cur_time++;
            run = p;
            output(cur_time);
            run = NULL;
            if (p->needtime <= 0) {    // ���ʣ��ʱ�����
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
            p = queue2;        // ȡ����ͷ
            queue2 = queue2->next;
            p->next = NULL;        // ��next���
            p->cputime += 2;
            p->needtime = p->needtime < 2 ? 0 : p->needtime - 2;
            cur_time += 2;
            run = p;
            output(cur_time);
            run = NULL;
            if (p->needtime <= 0) {    // ���ʣ��ʱ�����
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
            if (p->needtime <= 0) {    // ���ʣ��ʱ�����
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
            printf("CPU����! ʱ��=%d\n\n", cur_time);
            if (creating == NULL)break;
        }

    }
    printf("���н���!\n");
}

/*������*/
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
        printf("���̵����㷨��ʾ���� \n");
        printf("===================\n");
        printf("      1:�༶�������е����㷨\n");
        printf("      2:�˳�\n");
        printf("\n");
        printf("   ��ѡ��");
        scanf("%d", &N);
        if (N == 1) {
            dispatch();
        }
        else if (N == 2) {
            break;
        }
        else {
            printf("���������Ϣ��������������!\n\n");
            getchar();
        }
    }
    return 0;
}
