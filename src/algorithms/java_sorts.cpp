//
// Created by vinc on 2/1/22.
//

#include "java_sorts.h"

void arraycopy(class SortArray &Src, size_t srcPos, class SortArray &Dest, size_t destPos, size_t length)
{
    for (size_t i = 0; i < length; i++)
    {
        Src.mark(srcPos + i);
        Dest.mark(destPos + i);
        Dest.set(destPos + i, Src[srcPos + i]);
        Src.unmark(srcPos + i);
        Dest.unmark(destPos + i);
    }
}

void reverseRange(class SortArray &A, size_t lo, size_t hi)
{
    hi--;
    while (lo < hi)
    {
        A.mark(lo);
        A.mark(hi);
        A.swap(lo++, hi--);
        A.unmark(lo - 1);
        A.unmark(hi + 1);
    }
}

size_t countRunAndMakeAscending(class SortArray &A, size_t lo, size_t hi)
{
    size_t runHi = lo + 1;
    if (runHi == hi)
    {
        return 1;
    }

    // Find end of run, and reverse range if descending
    A.mark(lo);
    A.mark(lo + 1);
    A.unmark(lo + 1);
    if (A[runHi++] < A[lo]) // Descending
    {
        A.mark(runHi);
        A.mark(runHi - 1);
        while (runHi < hi && A[runHi] < A[runHi - 1])
        {
            A.unmark(runHi);
            A.unmark(runHi - 1);
            runHi++;
            A.mark(runHi);
            A.mark(runHi - 1);
        }
        A.unmark(runHi);
        A.unmark(runHi - 1);
        reverseRange(A, lo, runHi);
    }
    else // Ascending
    {
        A.mark(runHi);
        A.mark(runHi - 1);
        while (runHi < hi && A[runHi] >= A[runHi - 1])
        {
            A.unmark(runHi);
            A.unmark(runHi - 1);
            runHi++;
            A.mark(runHi);
            A.mark(runHi - 1);
        }
        A.unmark(runHi);
        A.unmark(runHi - 1);
    }
    A.unmark(lo);

    return runHi - lo;
}

void binarySort(class SortArray &A, size_t lo, size_t hi, size_t start)
{
    if (start == lo)
    {
        start++;
    }
    for (; start < hi; start++)
    {
        A.mark(start, 3);
        value_type pivot = A[start];

        // Set left (and right) to the index where A[start] (pivot) belongs
        size_t left = lo;
        size_t right = start;
        /*
         * Invariants:
         *   pivot >= all in [lo, left).
         *   pivot <  all in [right, start).
         */
        while (left < right)
        {
            size_t mid = (left + right) >> 1;
            A.mark(mid);
            if (pivot < A[mid])
            {
                right = mid;
            }
            else
            {
                left = mid + 1;
            }
            A.unmark(mid);
        }

        /*
         * The invariants still hold: pivot >= all in [lo, left) and
         * pivot < all in [left, start), so pivot belongs at left.  Note
         * that if there are elements equal to pivot, left points to the
         * first slot after them -- that's why this sort is stable.
         * Slide elements over to make room for pivot.
         */
        size_t n = start - left;  // The number of elements to move
        // Switch is just an optimization for arraycopy in default case
        switch (n)
        {
            case 2:
                A.mark(left + 1);
                A.mark(left + 2);
                A.set(left + 2, A[left + 1]);
                A.unmark(left + 2);
                A.unmark(left + 1);
            case 1:
                A.mark(left);
                A.mark(left + 1);
                A.set(left + 1, A[left]);
                A.unmark(left + 1);
                A.unmark(left);
                break;
            default:
                arraycopy(A, left, A, left + 1, n);
        }
        A.mark(left);
        A.set(left, pivot);
        A.unmark(left);
        A.unmark(start);
    }
}

void Sort(class SortArray &a, size_t lo, size_t hi)
{
    size_t nRemaining = hi - lo;
    if (nRemaining < 2) // Arrays of size 0 and 1 are always sorted
    {
        return;
    }

    // If array is small, do a "mini-TimSort" with no merges
    if (nRemaining < MIN_MERGE)
    {
        size_t initRunLen = countRunAndMakeAscending(a, lo, hi);
        binarySort(a, lo, hi, lo + initRunLen);
        return;
    }
}

void JavaSort(class SortArray &a)
{
    Sort(a, 0, a.size());
}
