#ifndef __XML_ATTR__H__
#define __XML_ATTR__H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif
//
// Defination
//

//Holds single attr
struct _XMLAttribute
{
    char *key;
    char *value;
};
typedef struct _XMLAttribute XMLAttribute;

void XMLAttribute_free(XMLAttribute *attr);

//List of all attr
struct _XMLAttributeList
{
    int heap_size;
    int size;
    XMLAttribute *data;
};
typedef struct _XMLAttributeList XMLAttributeList;

void XMLAttributeList_init(XMLAttributeList *list);
void XMLAttributeList_add(XMLAttributeList *list, XMLAttribute *attr);

//
// Implementation
//

void XMLAttribute_free(XMLAttribute *attr)
{
    free(attr->key);
    free(attr->value);
}

void XMLAttributeList_init(XMLAttributeList *list)
{
    list->heap_size = 1;
    list->size = 0;
    list->data = (XMLAttribute *)malloc(sizeof(XMLAttribute) * list->heap_size);
}
void XMLAttributeList_add(XMLAttributeList *list, XMLAttribute *attr)
{
    //We will grow the heap or attr list if other attr are added (same as vector container)
    while (list->size >= list->heap_size)
    {
        list->heap_size *= 2;
        //reallocate the memory to data array
        list->data = (XMLAttribute *)realloc(list->data, sizeof(XMLAttribute) * list->heap_size);
    }
    list->data[list->size++] = *attr;
}

#endif //!__XML_ATTR__H__