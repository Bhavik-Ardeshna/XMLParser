#ifndef __XML_NODE__H__
#define __XML_NODE__H__

#include "XML_Attr.h"

//
// Defination
//

struct _XML_Node
{
    char *tag;
    char *inner_text;
    struct _XML_Node *parent;
    XML_AttrList attributes;
};
typedef struct _XML_Node XML_Node;

XML_Node *XMLNode_new(XML_Node *parent);
void XMLNode_free(XML_Node *node);

//
// Implementation
//

XML_Node *XMLNode_new(XML_Node *parent)
{
    XML_Node *node = (XML_Node *)malloc(sizeof(XML_Node));
    node->parent = parent;
    node->tag = NULL;
    node->inner_text = NULL;
    XMLAttrList_init(&node->attributes);
    return node;
}

//Free individual components
void XMLNode_free(XML_Node *node)
{
    if (node->tag)
        free(node->tag);
    if (node->inner_text)
        free(node->inner_text);

    for (int i = 0; i < node->attributes.size; i++)
    {
        XMLAttr_free(&node->attributes.data[i]);
    }

    free(node);
}

#endif //!__XML_NODE__H__