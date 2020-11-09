#include "XML_Loader.h"

int main(int argc, char **argv)
{
    XMLDocument doc;
    if (XMLDocument_load(&doc, "test.xml"))
    {
        printf("%s : %s \n", doc.root->tag, doc.root->inner_text);

        XML_Node node = *doc.root;
        printf("Attributes (%s) :\n", doc.root->tag);
        for (int i = 0; i < node.attributes.size; i++)
        {
            XML_Attr attr = node.attributes.data[i];
            printf("    %s => \"%s\"\n", attr.key, attr.value);
        }
        XMLDocument_free(&doc);
    }

    return 0;
}
