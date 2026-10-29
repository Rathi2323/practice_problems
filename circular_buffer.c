#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define RING_BUFFER_SIZE 8U
#define RING_BUFFER_MASK (RING_BUFFER_SIZE-1U)

typedef struct
{
    
    uint8_t buffer[RING_BUFFER_SIZE];
    uint32_t head;
    uint32_t tail;
    
}ring_buffer_t;

void ring_buffer_init(ring_buffer_t *rb)
{
    rb->head = 0;
    rb->tail = 0;
}

bool ring_buffer_isEmpty(const ring_buffer_t *rb)
{
    return(rb->head == rb->tail);
}

bool ring_buffer_isFull(const ring_buffer_t *rb)
{
    return(((rb->head + 1U)& RING_BUFFER_MASK) == rb->tail);
}

bool ring_buffer_push(ring_buffer_t *rb, uint8_t data)
{
    uint32_t next_head = (rb->head+1U) & RING_BUFFER_MASK;
    
    if(next_head==rb->tail)
    {
        return false; 
    }
    
    rb->buffer[rb->head] = data;
    rb->head = next_head;
    return true;
}

bool ring_buffer_pop(ring_buffer_t *rb, uint8_t *data)
{
    if(rb->head==rb->tail)
    {
        return false;
    }
    *data = rb->buffer[rb->tail];
    rb->tail = (rb->tail + 1U) & RING_BUFFER_MASK;
    return true;
}

int main(void)
{
    ring_buffer_t rb;
    uint8_t val=0;
    
    ring_buffer_init(&rb);
    
    printf("Initial state: \n");
    printf("Empty: %s | Full: %s\n", ring_buffer_isEmpty(&rb) ? "true":"false", ring_buffer_isFull(&rb) ? "true":"false");
    
    printf("Pushing 7 items ('A' to 'G'): \n");
    for(char c = 'A'; c <= 'G';c++)
    {
        if(ring_buffer_push(&rb,(uint8_t)c))
        {
            printf("Pushed: %c -> head: %u, tail: %u\n",c,rb.head, rb.tail);
        }
    }
    printf("Empty: %s | Full: %s\n", ring_buffer_isEmpty(&rb) ? "true":"false", ring_buffer_isFull(&rb) ? "true":"false");
    
    printf("Attempting to push 8th item('H'): \n");
    if(!ring_buffer_push(&rb, 'H'))
    {
        printf("Push failed as expected: buffer is full!\n");
    }
    
    printf("Popping 3 items:\n");
    for(int i=0; i<3; i++)
    {
        if(ring_buffer_pop(&rb, &val))
        {
            printf("Popped: %c -> head: %u, tail: %u\n",val,rb.head,rb.tail);
        }
    }
    
    printf("Pushing 'X', 'Y', 'Z' (Demonstrating wrap-around):\n");
    char extra[] = {'X','Y','Z'};
    
    for(int i=0; i<3; i++)
    {
        if(ring_buffer_push(&rb, (uint8_t)(extra[i])))
        {
            printf("Pushed: %c->head: %u, tail: %u\n",extra[i],rb.head,rb.tail);
        }
    }
    
    printf("Draining Remaining items:\n");
    
    while(ring_buffer_pop(&rb, &val))
    {
        printf("Popped: %c->head: %u, tail: %u\n",val,rb.head,rb.tail);
    }
    
    printf("Final Check:\n");
    printf("Empty: %s | Full: %s\n", ring_buffer_isEmpty(&rb) ? "true":"false", ring_buffer_isFull(&rb) ? "true":"false");
    
    if(!ring_buffer_pop(&rb, &val))
    {
        printf("Pop Failed as expected: Buffer is Empty!");
    }
    return 0;
}