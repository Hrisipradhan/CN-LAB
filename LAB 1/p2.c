#include<stdio.h>

struct employee{
    int emp_id;
    char emp_name[50];
    int bs;
    int da;
    int ta;
    int gp;
};

void input(struct employee *e){
    printf("Enther the employee id :");
    scanf("%d",&e->emp_id);
    printf("Enter the employee name :");
    scanf("%s",&e->emp_name);
    printf("Enter the basic salary :");
    scanf("%d",&e->bs);
    e->da = e->bs*0.12;
    e->ta = e->bs*0.3;
    e->gp = e->bs + e->da + e->ta;
}
void display(struct employee *e){
    printf("\nEmployee id: %d\n", e->emp_id);
    printf("\nEmployee name: %s\n", e->emp_name);
    printf("\nEmployee bs: %d\n", e->bs);
    // printf("\nEmployee da: %d\n", e->da);
    // printf("\nEmployee ta: %d\n", e->ta);
    printf("\nEmployee Toal salaty: %d\n", e->gp);

}
int main(){
    struct employee e;

    input(&e);
    display(&e);

    return 0;
}