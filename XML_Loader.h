#ifndef __XML_LOADER__H__
#define __XML_LOADER__H__

#include "XML_Node.h"

//
// Defination
//

struct _XMLDocument
{
    XML_Node *root;
};
typedef struct _XMLDocument XMLDocument;

int XMLDocument_loader(XMLDocument *doc, const char *path);
void XMLDocument_free(XMLDocument *doc);

//
//Implementation
//

//Load the XML file and do specific operation
int XMLDocument_load(XMLDocument *doc, const char *path)
{
    FILE *fp = fopen(path, "r");

    if (!fp)
    {
        printf("Error in loading file '%s'\n", path);
        return FALSE;
    }
    //Go To last line to calculate Size
    fseek(fp, 0, SEEK_END);
    int size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char *buf = (char *)malloc(sizeof(char) * (size + 1));

    fread(buf, sizeof(char), size, fp);
    fclose(fp);

    //Add null to last byte of buf
    buf[size] = '\0';

    //From Here, We created new node for each tag and make beautiful DSA!!! :)
    char lex[256];
    int lexi = 0;
    int i = 0;

    doc->root = XMLNode_new(NULL);
    XML_Node *cur_node = NULL;

    while (buf[i] != '\0')
    {
        if (buf[i] == '<')
        {
            lex[lexi] = '\0';
            //Catch error if inner text is outside tag
            if (lexi > 0)
            {
                if (!cur_node)
                {
                    fprintf(stderr, "Text is outside the tag or document !!\n");
                    return FALSE;
                }
                //if node will there it consider as innertext and copy it
                cur_node->inner_text = strdup(lex);
                lexi = 0;
            }

            //End of tag
            if (buf[i + 1] == '/')
            {
                i += 2;
                while (buf[i] != '>')
                    lex[lexi++] = buf[i++];
                lex[lexi] = '\0';

                if (!cur_node)
                {
                    fprintf(stderr, "Already at root !!\n");
                    return FALSE;
                }
                if (strcmp(cur_node->tag, lex))
                {
                    fprintf(stderr, "Mismatch of tag {%s != %s} \n", cur_node->tag, lex);
                    return FALSE;
                }

                i++;
                continue;
            }

            //Check of cur_node
            if (!cur_node)
                cur_node = doc->root;
            else
                cur_node = XMLNode_new(cur_node); //Make cur_node with prev node as parent

            i++;

            //Going through end tag
            while (buf[i] != '>')
                lex[lexi++] = buf[i++];
            lex[lexi] = '\0';

            //Copy tag name
            cur_node->tag = strdup(lex); //make duplicate of lex which currently holds tag name

            lexi = 0;
            i++;
            continue;
        }
        //Mainly it will go in else only if its inner text :-{
        else
        {
            lex[lexi++] = buf[i++];
        }
    }
    return TRUE;
}

//Free the doc file
void XMLDocument_free(XMLDocument *doc)
{
    XMLNode_free(doc->root);
}

#endif //!__XML_LOADER__H__