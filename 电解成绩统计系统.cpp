#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<io.h>
#include<dir.h>
#define stu_number 100
typedef struct student
{
    int id;
    char name[10];
    int y_n;
}STU;

void interface();//�������ӭ����
int hand_input(char*stu_p,STU* stu);//�ֶ�����ȫ��ѧ����Ϣ
int student_input(char* stu_p,STU* stu);//����ȫ��ѧ����Ϣ
void filename_get();//��������ҵͬѧѧ�����뵽workIN.txt��
int student_get(int *stu_id_get);//��������ҵѧ��ѧ����������
void who_get(STU* stu,int *stu_id_get,int flag_student_number,int work_number_get);//ͳ����Щѧ�����ˣ������
void int_print(int flag_student_number,STU* stu);//����������Ļ���ļ�workOUT.txt��

int main()
{

    STU stu[stu_number];
    STU *STU_p=stu;
    char stu_p[20],de_p[14]="student.txt",con;
    int work_number_get,flag_student_number;
    int *stu_id_get;
    interface();//�������
Begain:printf("\n�뽫����ȫ��ѧ����Ϣ���ļ����Ƶ����������ļ����ڣ����������ļ�����^_^\n\n(ע�⣺�������ļ�ȫ�����磺Ҫ��student.txt ����ͬ��׺.txtһ�����롣)\n\n");
printf("\n�ļ����� ");
    scanf("%s",stu_p);
    if(!strcmp(stu_p,"exit"))//����exit�˳�
    exit(0);
    if(!strcmp(stu_p,"1"))//����1��ʾĬ���ļ�student.txt
    strcpy(stu_p,de_p);
    //---------------------------ȫ��ѧ������--------------------------------
    if(!strcmp(stu_p,"2"))//����2��ʾ�ֶ�����
    {
        hand_input(stu_p,STU_p);
        strcpy(stu_p,"student.txt");
        flag_student_number=student_input(stu_p,STU_p);
    }
    else
    {
        flag_student_number=student_input(stu_p,STU_p);
        if(flag_student_number==0)
        {
            goto Begain;               //����ļ�����������������롣
        }
    }
    stu_id_get=(int*)malloc(flag_student_number*sizeof(int));
    //_______________________________����ҵ���______________________________
    filename_get();
    work_number_get=student_get(stu_id_get);
    //-------------------------���ͳ��--------------------------------
    who_get(STU_p,stu_id_get,flag_student_number,work_number_get);
    //-----------------------�������Ļ��ָ���ļ���--------------------------------
    int_print(flag_student_number,STU_p);
    free(stu_id_get);
    printf("\n����Ҫ����ͳ����\n����y����ͳ�ơ�����n�˳�����\n");
     getchar();
    con=getchar();
    if(con=='y'||con=='Y')
    goto Begain;
    return 0;
}

void interface()
{
    printf("********************************************************************************\n");
    printf("**                           ��ӭʹ�õ����ҵͳ��ϵͳ                         **\n");
    printf("********************************************************************************\n");
    printf("**  ���ܼ��� exit  ���˳�����                                               **\n");
    printf("**           1     ������Ĭ�����롣                                           **\n");
    printf("**           2     ���ֶ����ѧ����Ϣ��student.txt��                          **\n");
    printf("********************************************************************************\n");
    printf("********************************************************************************\n");
}

int hand_input(char*stu_p,STU* stu)
{
    FILE* student;
    int flag_number=0;
    int i;
    printf("������Ҫ��ӵ�ѧ����Ϣ������0 0��ʾ�������롣\n����0123456789 ���\n    0 0\n\nѧ��ѧ�� ѧ��������");
    if((student=fopen("student.txt","a"))==NULL)
    {
        printf("i can't open it!(stu) :(\n");    //��ȫ��ѧ����Ϣ���ļ�
        return 0;
    }
     for(i=0;1;i++)
    {
        scanf("%d %s",&stu[i].id,stu[i].name);
        if(stu[i].id==0)
            break;
        fprintf(student,"\n%d%s",stu[i].id,stu[i].name);
        flag_number++;                          //��ѧ����Ϣ���뵽struct stu֮�У������ѧ��������
    }
    fclose(student) ;
    return flag_number; //����ѧ��������
}

int student_input(char* stu_p,STU* stu)
{
    FILE* student;
    int flag_number=0;
    int i;
    
    if((student=fopen(stu_p,"r"))==NULL)
    {
        printf("i can't open it!(stu) :(\n");    //��ȫ��ѧ����Ϣ���ļ�
        return 0;
    }
       for(i=0;feof(student)==0;i++)
    {
        fscanf(student,"%d%s\n",&stu[i].id,stu[i].name);
        flag_number++;                          //��ѧ����Ϣ���뵽struct stu֮�У������ѧ��������
    }
    fclose(student);
    return flag_number; //����ѧ��������
}

void filename_get()
{
    int i;
    int flag1=0,flag2=0,flag3=0,flag4=0;
    struct _finddata_t  finfo;
    int Handle;
    FILE* workIN;
    char *doc="\\*.doc",*docx="\\*.docx",*wps="\\*.wps",*txt="\\*.txt",*rar="\\*.rar",*zip="\\*.zip";//������ܳ��ֵ��ļ���׺
    char pathway[100],temp[110],s[100];
    printf("\n�������ѽ���ҵ�ļ�Ŀ¼,����1Ĭ��������ǰĿ¼��\n�磺I:\\\\ͳ��  ��ʾ�ѽ���ҵ�ļ���I�̡�ͳ�ơ��ļ�����\n\nĿ¼����");
b_src:scanf("%s",pathway);
    getcwd(s,100);
    if(!strcmp(pathway,"1"))
    strcpy(pathway,s);
    if(!strcmp(pathway,"exit"))//����exit�˳�
    exit(0);
     if((workIN=fopen("workIN.txt","w+"))==NULL)
    {
        printf("i can't open it!(in) :(\n");
        exit(0);
    }
    //rar
    
     strcpy(temp,pathway);
    strcat(temp,rar);                  //���ļ�Ŀ¼��Ҫ�ҵ��ļ��������ӣ�Ϊ�����ṩ��ȷ��׼�Ĳ���
     if((Handle=_findfirst(temp,&finfo))!=-1)
    {
        flag1=1;//�ҵ�.rar����ҵ
        for(i=0;finfo.name[i]!=0;i++)
        {
            if(finfo.name[i]>='0'&&finfo.name[i]<='9')
            fprintf(workIN,"%c",finfo.name[i]);

        }
        if(finfo.name[0]>='0'&&finfo.name[0]<='9')//��������ҵ��ѧ��ѧ�����뵽workIN.txt��
        fprintf(workIN,"\n");
        while(_findnext(Handle,&finfo)==0)
        {
            for(i=0;finfo.name[i]!=0;i++)
            {
                if(finfo.name[i]>='0'&&finfo.name[i]<='9')
                fprintf(workIN,"%c",finfo.name[i]);

            }
            if(finfo.name[0]>='0'&&finfo.name[0]<='9')
            fprintf(workIN,"\n");
        }
        _findclose(Handle);
    }
    
    //zip
     strcpy(temp,pathway);
    strcat(temp,zip);                  //���ļ�Ŀ¼��Ҫ�ҵ��ļ��������ӣ�Ϊ�����ṩ��ȷ��׼�Ĳ���
     if((Handle=_findfirst(temp,&finfo))!=-1)
    {
        flag1=1;//�ҵ�.zip����ҵ
        for(i=0;finfo.name[i]!=0;i++)
        {
            if(finfo.name[i]>='0'&&finfo.name[i]<='9')
            fprintf(workIN,"%c",finfo.name[i]);

        }
        if(finfo.name[0]>='0'&&finfo.name[0]<='9')//��������ҵ��ѧ��ѧ�����뵽workIN.txt��
        fprintf(workIN,"\n");
        while(_findnext(Handle,&finfo)==0)
        {
            for(i=0;finfo.name[i]!=0;i++)
            {
                if(finfo.name[i]>='0'&&finfo.name[i]<='9')
                fprintf(workIN,"%c",finfo.name[i]);

            }
            if(finfo.name[0]>='0'&&finfo.name[0]<='9')
            fprintf(workIN,"\n");
        }
        _findclose(Handle);
    }
    
    //----------------------------����.docx����ҵ---------------------------------------
    strcpy(temp,pathway);
    strcat(temp,docx);                  //���ļ�Ŀ¼��Ҫ�ҵ��ļ��������ӣ�Ϊ�����ṩ��ȷ��׼�Ĳ���
     if((Handle=_findfirst(temp,&finfo))!=-1)
    {
        flag1=1;//�ҵ�.docx����ҵ
        for(i=0;finfo.name[i]!=0;i++)
        {
            if(finfo.name[i]>='0'&&finfo.name[i]<='9')
            fprintf(workIN,"%c",finfo.name[i]);

        }
        if(finfo.name[0]>='0'&&finfo.name[0]<='9')//��������ҵ��ѧ��ѧ�����뵽workIN.txt��
        fprintf(workIN,"\n");
        while(_findnext(Handle,&finfo)==0)
        {
            for(i=0;finfo.name[i]!=0;i++)
            {
                if(finfo.name[i]>='0'&&finfo.name[i]<='9')
                fprintf(workIN,"%c",finfo.name[i]);

            }
            if(finfo.name[0]>='0'&&finfo.name[0]<='9')
            fprintf(workIN,"\n");
        }
        _findclose(Handle);
    }
    //----------------------------����.wps����ҵ---------------------------------------
    strcpy(temp,pathway);
    strcat(temp,wps);
    if((Handle=_findfirst(temp,&finfo))!=-1)
    {
        flag2=1;//�ҵ�.wps����ҵ
        for(i=0;finfo.name[i]!=0;i++)
        {
            if(finfo.name[i]>='0'&&finfo.name[i]<='9')
            fprintf(workIN,"%c",finfo.name[i]);

        }
        if(finfo.name[0]>='0'&&finfo.name[0]<='9')
        fprintf(workIN,"\n");
        while(_findnext(Handle,&finfo)==0)
        {
            for(i=0;finfo.name[i]!=0;i++)
            {
                if(finfo.name[i]>='0'&&finfo.name[i]<='9')
                fprintf(workIN,"%c",finfo.name[i]);

            }
            if(finfo.name[0]>='0'&&finfo.name[0]<='9')
            fprintf(workIN,"\n");
        }
        _findclose(Handle);
    }
    //----------------------------����.txt����ҵ---------------------------------------
    strcpy(temp,pathway);
    strcat(temp,txt);
    if((Handle=_findfirst(temp,&finfo))!=-1)
    {
        flag3=1;//�ҵ�.txt����ҵ
        for(i=0;finfo.name[i]!=0;i++)
        {
            if(finfo.name[i]>='0'&&finfo.name[i]<='9')
            {
            fprintf(workIN,"%c",finfo.name[i]);
            }
        }
        if(finfo.name[0]>='0'&&finfo.name[0]<='9')
        fprintf(workIN,"\n");
        while(_findnext(Handle,&finfo)==0)
        {
            for(i=0;finfo.name[i]!=0;i++)
            {
                if(finfo.name[i]>='0'&&finfo.name[i]<='9')
                {
                fprintf(workIN,"%c",finfo.name[i]);
                }
            }
            if(finfo.name[0]>='0'&&finfo.name[0]<='9')
            fprintf(workIN,"\n");
        }
        _findclose(Handle);
    }
    strcpy(temp,pathway);
    strcat(temp,doc);
    //----------------------------����.doc����ҵ---------------------------------------
    if((Handle=_findfirst(temp,&finfo))!=-1)      //���һ����ҵҲδ�ҵ�����ʾ��������Ŀ¼��
    {
        flag4=1;//�ҵ�.doc����ҵ
        for(i=0;finfo.name[i]>='0'&&finfo.name[i]<='9';i++)
        {
            if(finfo.name[i]>='0'&&finfo.name[i]<='9')
            fprintf(workIN,"%c",finfo.name[i]);

        }
        if(finfo.name[0]>='0'&&finfo.name[0]<='9')
        fprintf(workIN,"\n");
        while(_findnext(Handle,&finfo)==0)
        {
            for(i=0;finfo.name[i]!=0;i++)
            {
                if(finfo.name[i]>='0'&&finfo.name[i]<='9')
                fprintf(workIN,"%c",finfo.name[i]);

            }
            if(finfo.name[0]>='0'&&finfo.name[0]<='9')
            fprintf(workIN,"\n");
        }
        _findclose(Handle);
    }
    if(!flag1&&!flag2&&!flag3&&!flag4)
    {
        printf("�����ˣ�û���ҵ��κδ������ļ���Ī��û��һ���˽�����\n\n��������������ȷ��Ŀ¼\n\n  Ŀ¼����");
        goto b_src;
    }
    fclose(workIN);
}

int student_get(int *stu_id_get)
{
    FILE* workIN;
    int i;
    int work_number_get;
    if((workIN=fopen("workIN.txt","r"))==NULL)
    {
        printf("i can't open it!(in) :(");
        exit(0);
    }

    for(i=0;feof(workIN)==0;i++)
    {
        fscanf(workIN,"%d\n",&stu_id_get[i]); //��������ҵ��ѧ��ѧ�Ŵ洢��������
        work_number_get=i+1;
    }
    fclose(workIN);
    return work_number_get; //�����˵�ѧ����������
}

void who_get(STU* stu,int* stu_id_get,int flag_student_number,int work_number_get)
{
    int flag_get=0;
    int i,j;
    for(j=0;j<flag_student_number&&flag_get<work_number_get;j++)
    {
        for(i=0;i<work_number_get;i++)  //��ÿ��ѧ������������ҵ��ѧ��
            {
                if(stu_id_get[i]==stu[j].id)
                {
                    stu[j].y_n=1;       //�����ѧ���뽻����ҵ��ѧ��ƥ�䣬���1.
                    flag_get++;         //�ۼƽ��˵�ѧ�������������ж�ѭ���Ľ���
                    break;
                }
            }
    }
}

void int_print(int flag_student_number,STU* stu)
{
    FILE* workOUT;
    int i,j;
    //----------------------���ļ������-----------------------------
    if((workOUT=fopen("workOUT.txt","w+"))==NULL)
    {
        printf("i can't open it!(out) :(");
        exit(0);
    }
    for(i=0;i<flag_student_number;i++)
    {
        if(stu[i].y_n==1)
        {
            if(stu[i].id>100000000)
                fprintf(workOUT,"%d  ",stu[i].id);
            else
                fprintf(workOUT,"0%d  ",stu[i].id);
            for(j=0;stu[i].name[j]!=0;j++)
            {
                fprintf(workOUT,"%c",stu[i].name[j]);
            }
            (j==6)?fprintf(workOUT,"              ��\n"):fprintf(workOUT,"                ��\n");
        }  //���������ʽ��ʹ������
       else
        {
            if(stu[i].id>100000000)
                fprintf(workOUT,"%d  ",stu[i].id);
            else
                fprintf(workOUT,"0%d  ",stu[i].id);
            for(j=0;stu[i].name[j]!=0;j++)
            {
                fprintf(workOUT,"%c",stu[i].name[j]);
            }
            (j==6)?fprintf(workOUT,"            δ��\n"):fprintf(workOUT,"              δ��\n");
        }     //���������ʽ��ʹ������

    }
   fclose(workOUT);
   //-----------------------����Ļ�����----------------------------
    for(i=0;i<flag_student_number;i++)
    {
        if(stu[i].y_n==1)
        {
         if(stu[i].id>100000000)
            printf("%d  ",stu[i].id);
        else
            printf("0%d  ",stu[i].id);
        for(j=0;stu[i].name[j]!=0;j++)
        {
            printf("%c",stu[i].name[j]);
        }
        (j==6)?printf("              ��\n"):printf("                ��\n");
        } //���������ʽ��ʹ������
        else
        {
        if(stu[i].id>100000000)
            printf("%d  ",stu[i].id);
        else
            printf("0%d  ",stu[i].id);
        for(j=0;stu[i].name[j]!=0;j++)
        {
            printf("%c",stu[i].name[j]);
        }
        (j==6)?printf("            δ��\n"):printf("              δ��\n");
        }   //���������ʽ��ʹ������
    }
        printf("\n\n��ʾ����ϲ��ȫ�������������ļ�workOUT.txt!
      �ѽ���ҵѧ��ѧ��ͳ�ƽ����������ļ�workIN.txt!^_^\n\nע�⣺�´�����ʱ��ͳ�ƽ��������գ��뼰ʱ�������ݣ�\n");


}
