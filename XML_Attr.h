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

struct _XML_Attr
{
    char *key;
    char *value;
};
typedef struct _XML_Attr XML_Attr;

void XMLAttr_free(XML_Attr *attr);

struct _XML_AttrList
{
    int heap_size;
    int size;
    XML_Attr *data;
};
typedef struct _XML_AttrList XML_AttrList;

void XMLAttrList_init(XML_AttrList *list);
void XMLAttrList_add(XML_AttrList *list, XML_Attr *attr);

//
// Implementation
//

void XMLAttr_free(XML_Attr *attr)
{
    free(attr->key);
    free(attr->value);
}
void XMLAttrList_init(XML_AttrList *list)
{
    list->heap_size = 1;
    list->size = 0;
    list->data = (XML_Attr *)malloc(sizeof(XML_Attr) * list->heap_size);
}
void XMLAttrList_add(XML_AttrList *list, XML_Attr *attr)
{
    while (list->size >= list->heap_size)
    {
        list->heap_size *= 2;
        list->data = (XML_Attr *)realloc(list->data, sizeof(XML_Attr) * list->heap_size);
    }
    list->data[list->size++] = *attr;
}

#endif //!__XML_ATTR__H__