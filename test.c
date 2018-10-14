#include <stdio.h>

int cicle (int x, int y)
{
  int i;
  for ( i = 0; i < x; i++) {
    printf ("%d", i);
    if (i < y){
      printf("[ i > %d", y);
    }
    else{
      printf("i < %d ]", y);
    }
  }

  printf("\n");
}

int main (void)
{
  int numb;
  int val;
  printf ("input number:");
  scanf("%d", &numb);

  printf ("input value:");
  scanf("%d", &val);
  cicle( val, numb );

  return 0;
}
