#include "XML_Loader.h"

int main(int argc, char **argv)
{
    XMLDocument doc;
    if (XMLDocument_load(&doc, "test.xml"))
    {
        printf("%s : %s \n", doc.root->tag, doc.root->inner_text);

        XML_Node node = *doc.root;

        printf("Attribute of tag: %s\n", node.tag);
        for (int i = 0; i < node.attributes.size; i++)
        {
            printf("   %s -> \"%s\"\n", node.attributes.data[i].key, node.attributes.data[i].value);
        }

        XMLDocument_free(&doc);
    }
    return 0;
}
