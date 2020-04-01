#include <malloc.h>
#define WeightType int
typedef struct hafman
{
    WeightType weight;
    HuffmanTree *left;
    HuffmanTree *right;
} HuffmanTree;

typedef struct minheap
{
    WeightType weight;
    int size;
} MinHeap;

MinHeap *deleteMin(MinHeap *heap);
void insert(MinHeap *heap, HuffmanTree *treeNode);

HuffmanTree *constructHuffmanTree(MinHeap *heap)
{
    HuffmanTree *huffman;
    for (int i = 1; i < heap->size; ++i) //size nodes need size-1 times insert
    {
        huffman = (HuffmanTree *)malloc(sizeof(HuffmanTree));
        huffman->left = deleteMin(heap);
        huffman->right = deleteMin(heap);
        huffman->weight = huffman->left->weight +
                          huffman->right->weight;
        insert(heap, huffman);
    }
    return deleteMin(heap);
}