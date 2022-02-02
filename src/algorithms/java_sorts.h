//
// Created by vinc on 2/1/22.
//

#ifndef SOUND_OF_SORTING_JAVA_SORTS_H
#define SOUND_OF_SORTING_JAVA_SORTS_H

#include "../SortAlgo.h"

typedef ArrayItem value_type;

size_t MIN_MERGE = 32;

size_t MIN_GALLOP = 7;

size_t INITIAL_TMP_STORAGE_LENGTH = 256;

void JavaSort(class SortArray &a);

#endif //SOUND_OF_SORTING_JAVA_SORTS_H
