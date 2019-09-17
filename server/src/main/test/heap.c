#include <stdlib.h>

struct HeapStruct;
struct Element;

typedef struct HeapStruct *PriorityQueue;
typedef struct Element *Element;

PriorityQueue Initialize(int Max);
void Destroy(PriorityQueue queue);
PriorityQueue MakeEmpty(PriorityQueue queue);
void Insert(PriorityQueue queue, Element e);
Element DeleteMin(PriorityQueue queue);
Element FindMin(PriorityQueue queue);
int IsEmpty(PriorityQueue queue);
int IsFull(PriorityQueue queue);

struct Element
{
    int value;
};

struct Element MIN_DATA =
    {
        -1};

struct HeapStruct
{
    int capacity;
    int size;
    Element *elements;
};

PriorityQueue Initialize(int max)
{
    PriorityQueue queue;
    queue = malloc(sizeof(struct HeapStruct));
    if (queue == NULL)
    {
        //Not Enough Memory
        return NULL;
    }

    queue->capacity = max;
    queue->size = 0;
    //why plus one
    queue->elements = malloc(sizeof(Element *) * (max + 1));
    if (queue->elements == NULL)
    {
        //NOT ENMOUGH MEMORY
        return NULL;
    }

    //保存一个最小数，在首元素，该值必须小于等于堆中任一元素
    queue->elements[0] = &MIN_DATA;

    return queue;
}

void Insert(PriorityQueue queue, Element e)
{
    int i;
    if (IsFull(queue))
    {
        //Queue is full
        return;
    }
    /**
     * 在尾部添加一个空节点，并向上与父节点进行对比，直至找到合适的插入位置。（若i=1，则与存储于0位置的最小元素进行对比，保证在根节点时退出循环。）
     */
    for (i = ++queue->size; (queue->elements[i / 2]->value) > (e->value); i /= 2)
    {
        queue->elements[i] = queue->elements[i / 2];
    }
    queue->elements[i] = e;
}

Element DeleteMin(PriorityQueue queue)
{
    int i, child;
    if (IsEmpty(queue))
    {
        return queue->elements[0];
    }

    Element last = queue->elements[queue->size--];
    Element min = queue->elements[1];

    for (i = 1; i * 2 < queue->size; i = child)
    {
        /* code */
        child = 2 * i;
        if (child != queue->size && queue->elements[child]->value > queue->elements[child + 1]->value)
        {
            //寻找儿子节点中的较小节点
            child++;
        }

        if (queue->elements[child]->value < last->value)
        {
            /* code */
            queue->elements[i] = queue->elements[child];
        }
        else
        {
            break;
        }
    }

    queue->elements[i] = last;
    return min;
}