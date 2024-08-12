#include<stdio.h>
struct product{
    int prod_num;
    char pname[50];
    int price;
    int quantity;
    int totalPrice;
};
void input(struct product *p1){
    printf("Enter the Product numbers:");
    scanf("%d",&p1->prod_num);
    printf("Enter the name of the products name:");
    scanf("%s",&p1->pname);
    printf("Enter the price:");
    scanf("%d",&p1->price);
    printf("Enter the quantity:");
    scanf("%d",&p1->quantity);


}
void display(struct product *p1){{
    printf("\nProduct Numbers: %d\n", p1->prod_num);
    printf("\nProduct Name: %s\n", p1->pname);
    printf("\nProduct Price: %d\n", p1->price);
    printf("\nProduct Quantity: %d\n", p1->quantity);
    printf("\nProduct Total pr ice: %d\n", p1->price*p1->quantity);
}

}
int main(){
    struct product p1;
    
    input(&p1);
    display(&p1);

    return 0;
}
