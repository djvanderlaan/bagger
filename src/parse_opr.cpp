#include "parse.h"


int main(int argc, char **argv) {

  //if (argc != 2) return 1;
  xmlDoc* doc = NULL;
  if (argc == 2) {
    std::string filename(argv[1]);
    if (filename == "--header") {
      std::cout << "\"id\";\"naam\";\"type\";\"woonplaats\";" << 
        "\"begin_geldigheid\";\"eind_geldigheid\"" << std::endl;
      return 0;
    } else doc = xmlReadFile(argv[1], NULL, 0);
  } else {
    doc = xmlReadFd(STDIN_FILENO, NULL, NULL, 0);
  }


  if (doc == NULL) {
    std::cerr << "Error could not parse '" << argv[1] << "'.\n";
  }

  xmlNode* root = xmlDocGetRootElement(doc);

  xmlNode* stand = find_first(root->children, "stand");
  xmlNode* node = 0;

  while(stand = find_first(stand, "stand")) {
    node = find_first(stand->children, "OpenbareRuimte");

    std::cout << '"' << get_data(node->children, "identificatie") << '"' << ';';
    std::cout << '"' << get_data(node->children, "naam") << '"' << ';';
    std::cout << '"' << get_data(node->children, "type") << '"' << ';';

    xmlNode* openb = find_first(node->children, "ligtIn");
    if (openb) {
      std::cout << '"' << get_data(openb->children, "WoonplaatsRef") << '"' << ';';
    }

    xmlNode* geld = find_first(node->children, "Voorkomen");
    if (geld) {
      std::cout << '"' << get_data(geld->children, "beginGeldigheid") << '"' << ';';
      std::cout << '"' << get_data(geld->children, "eindGeldigheid") << '"';
    }
    std::cout << "\n";
    stand = stand->next;
  }

  xmlFreeDoc(doc);
  xmlCleanupParser();

  return 0;

}

