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

void interface();//输出程序欢迎界面
int hand_input(char*stu_p,STU* stu);//手动输入全体学生信息
int student_input(char* stu_p,STU* stu);//输入全体学生信息
void filename_get();//将交了作业同学学号输入到workIN.txt中
int student_get(int *stu_id_get);//将交了作业学生学号输入数组
void who_get(STU* stu,int *stu_id_get,int flag_student_number,int work_number_get);//统计哪些学生交了，并标记
void int_print(int flag_student_number,STU* stu);//输出结果到屏幕和文件workOUT.txt中

int main()
{

    STU stu[stu_number];
    STU *STU_p=stu;
    char stu_p[20],de_p[14]="student.txt",con;
    int work_number_get,flag_student_number;
    int *stu_id_get;
    interface();//输出界面
Begain:printf("\n请将包含全体学生信息的文件复制到程序所在文件夹内，并输入其文件名：^_^\n\n(注意：请输入文件全名！如：要打开student.txt 请连同后缀.txt一起输入。)\n\n");
printf("\n文件名： ");
    scanf("%s",stu_p);
    if(!strcmp(stu_p,"exit"))//输入exit退出
    exit(0);
    if(!strcmp(stu_p,"1"))//输入1表示默认文件student.txt
    strcpy(stu_p,de_p);
    //---------------------------全体学生输入--------------------------------
    if(!strcmp(stu_p,"2"))//输入2表示手动输入
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
            goto Begain;               //如果文件名输入错误，重新输入。
        }
    }
    stu_id_get=(int*)malloc(flag_student_number*sizeof(int));
    //_______________________________交作业情况______________________________
    filename_get();
    work_number_get=student_get(stu_id_get);
    //-------------------------情况统计--------------------------------
    who_get(STU_p,stu_id_get,flag_student_number,work_number_get);
    //-----------------------输出到屏幕和指定文件中--------------------------------
    int_print(flag_student_number,STU_p);
    free(stu_id_get);
    printf("\n还需要重新统计吗？\n输入y重新统计。输入n退出程序。\n");
     getchar();
    con=getchar();
    if(con=='y'||con=='Y')
    goto Begain;
    return 0;
}

void interface()
{
    printf("********************************************************************************\n");
    printf("**                           欢迎使用电解作业统计系统                         **\n");
    printf("********************************************************************************\n");
    printf("**  功能键： exit  ：退出程序。                                               **\n");
    printf("**           1     ：按照默认输入。                                           **\n");
    printf("**           2     ：手动添加学生信息到student.txt。                          **\n");
    printf("********************************************************************************\n");
    printf("********************************************************************************\n");
}

int hand_input(char*stu_p,STU* stu)
{
    FILE* student;
    int flag_number=0;
    int i;
    printf("请输入要添加的学生信息。输入0 0表示结束输入。\n例：0123456789 电解\n    0 0\n\n学生学号 学生姓名：");
    if((student=fopen("student.txt","a"))==NULL)
    {
        printf("i can't open it!(stu) :(\n");    //打开全部学生信息的文件
        return 0;
    }
     for(i=0;1;i++)
    {
        scanf("%d %s",&stu[i].id,stu[i].name);
        if(stu[i].id==0)
            break;
        fprintf(student,"\n%d%s",stu[i].id,stu[i].name);
        flag_number++;                          //将学生信息输入到struct stu之中，并标记学生总人数
    }
    fclose(student) ;
    return flag_number; //返回学生总人数
}

int student_input(char* stu_p,STU* stu)
{
    FILE* student;
    int flag_number=0;
    int i;
    
    if((student=fopen(stu_p,"r"))==NULL)
    {
        printf("i can't open it!(stu) :(\n");    //打开全部学生信息的文件
        return 0;
    }
       for(i=0;feof(student)==0;i++)
    {
        fscanf(student,"%d%s\n",&stu[i].id,stu[i].name);
        flag_number++;                          //将学生信息输入到struct stu之中，并标记学生总人数
    }
    fclose(student);
    return flag_number; //返回学生总人数
}

void filename_get()
{
    int i;
    int flag1=0,flag2=0,flag3=0,flag4=0;
    struct _finddata_t  finfo;
    int Handle;
    FILE* workIN;
    char *doc="\\*.doc",*docx="\\*.docx",*wps="\\*.wps",*txt="\\*.txt",*rar="\\*.rar",*zip="\\*.zip";//定义可能出现的文件后缀
    char pathway[100],temp[110],s[100];
    printf("\n请输入已交作业文件目录,输入1默认搜索当前目录。\n如：I:\\\\统计  表示已交作业文件在I盘“统计”文件夹下\n\n目录名：");
b_src:scanf("%s",pathway);
    getcwd(s,100);
    if(!strcmp(pathway,"1"))
    strcpy(pathway,s);
    if(!strcmp(pathway,"exit"))//输入exit退出
    exit(0);
     if((workIN=fopen("workIN.txt","w+"))==NULL)
    {
        printf("i can't open it!(in) :(\n");
        exit(0);
    }
    //rar
    
     strcpy(temp,pathway);
    strcat(temp,rar);                  //将文件目录和要找的文件类型连接，为搜索提供正确标准的参数
     if((Handle=_findfirst(temp,&finfo))!=-1)
    {
        flag1=1;//找到.rar的作业
        for(i=0;finfo.name[i]!=0;i++)
        {
            if(finfo.name[i]>='0'&&finfo.name[i]<='9')
            fprintf(workIN,"%c",finfo.name[i]);

        }
        if(finfo.name[0]>='0'&&finfo.name[0]<='9')//将交了作业的学生学号输入到workIN.txt中
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
    strcat(temp,zip);                  //将文件目录和要找的文件类型连接，为搜索提供正确标准的参数
     if((Handle=_findfirst(temp,&finfo))!=-1)
    {
        flag1=1;//找到.zip的作业
        for(i=0;finfo.name[i]!=0;i++)
        {
            if(finfo.name[i]>='0'&&finfo.name[i]<='9')
            fprintf(workIN,"%c",finfo.name[i]);

        }
        if(finfo.name[0]>='0'&&finfo.name[0]<='9')//将交了作业的学生学号输入到workIN.txt中
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
    
    //----------------------------搜索.docx的作业---------------------------------------
    strcpy(temp,pathway);
    strcat(temp,docx);                  //将文件目录和要找的文件类型连接，为搜索提供正确标准的参数
     if((Handle=_findfirst(temp,&finfo))!=-1)
    {
        flag1=1;//找到.docx的作业
        for(i=0;finfo.name[i]!=0;i++)
        {
            if(finfo.name[i]>='0'&&finfo.name[i]<='9')
            fprintf(workIN,"%c",finfo.name[i]);

        }
        if(finfo.name[0]>='0'&&finfo.name[0]<='9')//将交了作业的学生学号输入到workIN.txt中
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
    //----------------------------搜索.wps的作业---------------------------------------
    strcpy(temp,pathway);
    strcat(temp,wps);
    if((Handle=_findfirst(temp,&finfo))!=-1)
    {
        flag2=1;//找到.wps的作业
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
    //----------------------------搜索.txt的作业---------------------------------------
    strcpy(temp,pathway);
    strcat(temp,txt);
    if((Handle=_findfirst(temp,&finfo))!=-1)
    {
        flag3=1;//找到.txt的作业
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
    //----------------------------搜索.doc的作业---------------------------------------
    if((Handle=_findfirst(temp,&finfo))!=-1)      //如果一份作业也未找到，提示重新输入目录名
    {
        flag4=1;//找到.doc的作业
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
        printf("悲剧了！没有找到任何此类型文件！莫非没有一个人交！？\n\n试试重新输入正确的目录\n\n  目录名：");
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
        fscanf(workIN,"%d\n",&stu_id_get[i]); //将交了作业的学生学号存储到数组中
        work_number_get=i+1;
    }
    fclose(workIN);
    return work_number_get; //将交了的学生人数返回
}

void who_get(STU* stu,int* stu_id_get,int flag_student_number,int work_number_get)
{
    int flag_get=0;
    int i,j;
    for(j=0;j<flag_student_number&&flag_get<work_number_get;j++)
    {
        for(i=0;i<work_number_get;i++)  //让每个学生遍历交了作业的学号
            {
                if(stu_id_get[i]==stu[j].id)
                {
                    stu[j].y_n=1;       //如果其学号与交了作业的学号匹配，标记1.
                    flag_get++;         //累计交了的学生人数，用于判断循环的结束
                    break;
                }
            }
    }
}

void int_print(int flag_student_number,STU* stu)
{
    FILE* workOUT;
    int i,j;
    //----------------------在文件中输出-----------------------------
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
            (j==6)?fprintf(workOUT,"              交\n"):fprintf(workOUT,"                交\n");
        }  //控制输出格式，使其美观
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
            (j==6)?fprintf(workOUT,"            未交\n"):fprintf(workOUT,"              未交\n");
        }     //控制输出格式，使其美观

    }
   fclose(workOUT);
   //-----------------------在屏幕上输出----------------------------
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
        (j==6)?printf("              交\n"):printf("                交\n");
        } //控制输出格式，使其美观
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
        (j==6)?printf("            未交\n"):printf("              未交\n");
        }   //控制输出格式，使其美观
    }
        printf("\n\n提示：恭喜！全部结果已输出到文件workOUT.txt!
      已交作业学生学号统计结果已输出到文件workIN.txt!^_^\n\n注意：下次运行时，统计结果将被清空，请及时备份数据！\n");


}
