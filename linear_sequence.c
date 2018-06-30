#include "linear_sequence.h"

#include <string.h>

LSQ_Iterator *CreateIterator(LSQ_HandleT handle, LSQ_IntegerIndexT index) {
    LSQ_Iterator *iterator = malloc(sizeof(LSQ_Iterator));
    if (iterator == LSQ_HandleInvalid) return LSQ_HandleInvalid;
    iterator->container = CONT(handle);
    iterator->index = index;
    return iterator;
}

LSQ_HandleT LSQ_CreateSequence(void) {
    LSQ_Container *container = malloc(sizeof(LSQ_Container));
    if (container == LSQ_HandleInvalid) return LSQ_HandleInvalid;
    container->size = 0;
    container->mas = NULL;
    return container;
}

void LSQ_DestroySequence(LSQ_HandleT handle) {
    if (handle == LSQ_HandleInvalid) return;

    free(CONT(handle)->mas);
    free(CONT(handle));
}

LSQ_IntegerIndexT LSQ_GetSize(LSQ_HandleT handle) {
    if (handle == LSQ_HandleInvalid) return 0;

    return CONT(handle)->size;
}

int LSQ_IsIteratorDereferencable(LSQ_IteratorT iterator) {
    if (!iterator) return 0;

    LSQ_Iterator *iter = ITER(iterator);
    return (iter->index >= 0 && iter->index < iter->container->size) ? 1 : 0;
}

int LSQ_IsIteratorPastRear(LSQ_IteratorT iterator) {
    if (!iterator) return 1;

    LSQ_Iterator *iter = ITER(iterator);
    return (iter->index >= iter->container->size);
}

int LSQ_IsIteratorBeforeFirst(LSQ_IteratorT iterator) {
    if (!iterator) return 1;

    return (ITER(iterator)->index < 0);
}

LSQ_BaseTypeT *LSQ_DereferenceIterator(LSQ_IteratorT iterator) {
    if (!iterator) return NULL;

    if (LSQ_IsIteratorDereferencable(iterator)) {
        return ITER(iterator)->container->mas + ITER(iterator)->index;
    } else return NULL;
}

LSQ_IteratorT LSQ_GetElementByIndex(LSQ_HandleT handle, LSQ_IntegerIndexT index) {
    if (handle == LSQ_HandleInvalid) return LSQ_HandleInvalid;
    return CreateIterator(handle, index);
}

LSQ_IteratorT LSQ_GetFrontElement(LSQ_HandleT handle) {
    if (handle == LSQ_HandleInvalid) return LSQ_HandleInvalid;
    return CreateIterator(handle, 0);
}

LSQ_IteratorT LSQ_GetPastRearElement(LSQ_HandleT handle) {
    if (handle == LSQ_HandleInvalid) return LSQ_HandleInvalid;
    return CreateIterator(handle, CONT(handle)->size);
}

void LSQ_DestroyIterator(LSQ_IteratorT iterator) {
    if (!iterator) return;

    free(ITER(iterator));
}

void LSQ_AdvanceOneElement(LSQ_IteratorT iterator) {
    if (!iterator) return;

    ITER(iterator)->index++;
}

void LSQ_RewindOneElement(LSQ_IteratorT iterator) {
    if (!iterator) return;

    ITER(iterator)->index--;
}

void LSQ_ShiftPosition(LSQ_IteratorT iterator, LSQ_IntegerIndexT shift) {
    if (!iterator) return;

    ITER(iterator)->index += shift;
}

void LSQ_SetPosition(LSQ_IteratorT iterator, LSQ_IntegerIndexT pos) {
    if (!iterator) return;

    ITER(iterator)->index = pos;
}

void LSQ_InsertFrontElement(LSQ_HandleT handle, LSQ_BaseTypeT element) {
    if (handle == LSQ_HandleInvalid) return;

    LSQ_Container *container = CONT(handle);
    container->mas = realloc(container->mas, sizeof(LSQ_BaseTypeT) * (container->size + 1));
    memmove(container->mas + 1, container->mas, sizeof(LSQ_BaseTypeT) * container->size);
    container->mas[0] = element;
    container->size++;
}

void LSQ_InsertRearElement(LSQ_HandleT handle, LSQ_BaseTypeT element) {
    if (handle == LSQ_HandleInvalid) return;

    LSQ_Container *container = CONT(handle);
    container->size++;
    container->mas = realloc(container->mas, sizeof(LSQ_BaseTypeT) * container->size);
    container->mas[container->size - 1] = element;
}

void LSQ_InsertElementBeforeGiven(LSQ_IteratorT iterator, LSQ_BaseTypeT newElement) {
    if (!iterator) return;

    LSQ_Container *container = ITER(iterator)->container;
    LSQ_IntegerIndexT indexBefore = ITER(iterator)->index;
    container->mas = realloc(container->mas, sizeof(LSQ_BaseTypeT) * (container->size + 1));
    memmove(container->mas + indexBefore + 1, container->mas + indexBefore, sizeof(LSQ_BaseTypeT) * (container->size - indexBefore));
    container->mas[indexBefore] = newElement;
    container->size++;
}

void LSQ_DeleteFrontElement(LSQ_HandleT handle) {
    if (handle == LSQ_HandleInvalid) return;

    LSQ_Container *container = CONT(handle);
    if (container->size > 0) {
        container->size--;
        memmove(container->mas, container->mas + 1, sizeof(LSQ_BaseTypeT) * container->size);
        container->mas = realloc(container->mas, sizeof(LSQ_BaseTypeT) * container->size);
    }
}

void LSQ_DeleteRearElement(LSQ_HandleT handle) {
    if (handle == LSQ_HandleInvalid) return;

    LSQ_Container *container = CONT(handle);
    if (container->size > 0) {
        container->mas = realloc(container->mas, sizeof(LSQ_BaseTypeT) * --container->size);
    }
}

void LSQ_DeleteGivenElement(LSQ_IteratorT iterator) {
    if (!iterator) return;

    LSQ_Container *container = ITER(iterator)->container;
    LSQ_IntegerIndexT index = ITER(iterator)->index;
    if (container->size > 0 && LSQ_IsIteratorDereferencable(iterator)) {
        memcpy(container->mas + index, container->mas + index + 1, sizeof(LSQ_BaseTypeT) * (container->size - index));
        container->mas = realloc(container->mas, sizeof(LSQ_BaseTypeT) * (container->size - 1));
        container->size--;
    }
}