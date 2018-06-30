#include <stdio.h>
#include "BubbleSort.h"

LSQ_Container* bubbleSort(LSQ_HandleT handle){
    LSQ_Container* mass = CONT(handle);
    LSQ_Iterator* tmpIt;
    LSQ_BaseTypeT tmp;
    LSQ_Iterator* iterator;
    for(int i = 0; i < mass->size ; i++){
        for(int j = 0; j < mass->size-1; j++){
            if (*LSQ_DereferenceIterator(LSQ_GetElementByIndex(mass,j)) > *LSQ_DereferenceIterator(LSQ_GetElementByIndex(mass,j + 1))) { //a < b
                tmpIt = ITER(LSQ_GetElementByIndex(mass,j + 1));
                iterator = ITER(LSQ_GetElementByIndex(mass, j));
                tmp = *LSQ_DereferenceIterator(iterator);
                LSQ_DeleteGivenElement(iterator);
                LSQ_InsertElementBeforeGiven(tmpIt, tmp);
            }
        }
    }
    return mass;
}



