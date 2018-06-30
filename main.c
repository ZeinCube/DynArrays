#include <stdio.h>
#include "linear_sequence.h"
#include "BubbleSort.h"


int main(){
    LSQ_HandleT container = LSQ_CreateSequence();
    LSQ_InsertRearElement(container,-285);
    LSQ_InsertRearElement(container,-300);
    LSQ_InsertRearElement(container,12314);
    LSQ_InsertRearElement(container,123);
    LSQ_InsertRearElement(container,275);
    LSQ_InsertRearElement(container,5820);
    LSQ_InsertRearElement(container,59872);
    LSQ_InsertRearElement(container,4025);
    LSQ_InsertRearElement(container,-4025);

    printf("%s","Before sort hahaha ");

    LSQ_Iterator *iterator = LSQ_GetElementByIndex(container,0);
    for(int i = 0; i < iterator->container->size;i++){
        printf("%d", *LSQ_DereferenceIterator(iterator));
        LSQ_AdvanceOneElement(iterator);
        printf("%c", ' ');
    }

    container = bubbleSort(container);
    iterator = LSQ_GetElementByIndex(container,0);
    printf("%c", '\n');
    for(int i = 0; i < iterator->container->size;i++){
        printf("%d", *LSQ_DereferenceIterator(iterator));
        LSQ_AdvanceOneElement(iterator);
        printf("%c", ' ');
    }
    return 0;
}