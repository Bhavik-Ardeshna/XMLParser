#include "XML_Loader.h"

int main(int argc, char **argv)
{
    XMLDocument doc;
    if (XMLDocument_load(&doc, "test.xml"))
    {
        printf("%s : %s \n", doc.root->tag, doc.root->inner_text);
        XMLDocument_free(&doc);
    }
    return 0;
}
