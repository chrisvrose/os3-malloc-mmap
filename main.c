#include<stdio.h>
#include<mapmanagement.h>

int main(){
    float* a = smalloc(sizeof(float));
    float* b = smalloc(sizeof(float));
    float* c = smalloc(sizeof(float));
    int* array = scalloc(sizeof(int),10);
    printf("Enter 2 numbers\n:");
    scanf("%f %f",b,c);
    *a = *b + *c;
    printf("%f = %f + %f\n",*a,*b,*c);

    printf("Original array\n:");
    for(int i=0;i<10;i++){
        printf("a[%d] = %d ",i,array[i]);
        *(array+i) = i*i;
    }

    //printf("")
    printf("\nNew Array\n:");
    for(int i=0;i<10;i++){
        printf("a[%d] = %d \n",i,array[i]);
        fflush(NULL);
    }

    sfree(a);
    spurge();
    return 0;
}