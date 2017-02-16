#include "parse.h"


int main(int argc, char **argv) {

  //if (argc != 2) return 1;
  xmlDoc* doc = NULL;
  if (argc == 2) {
    std::string filename(argv[1]);
    if (filename == "--header") {
      std::cout << "\"id\";\"postcode\";\"huisnummer\";\"huisnummertoevoeging\";" << 
        "\"openbareruimte\";\"begin_geldigheid\";\"eind_geldigheid\"" << std::endl;
      return 0;
    } else doc = xmlReadFile(argv[1], NULL, 0);
  } else {
    doc = xmlReadFd(STDIN_FILENO, NULL, NULL, 0);
  }


  if (doc == NULL) {
    std::cerr << "Error could not parse '" << argv[1] << "'.\n";
  }

  xmlNode* root = xmlDocGetRootElement(doc);

  xmlNode* data = find_first(root->children, "LVC-product");

  xmlNode* node = find_first(root->children, "Nummeraanduiding");

  while(node = find_first(node, "Nummeraanduiding")) {
    std::cout << '"' << get_data(node->children, "identificatie") << '"' << ';';
    std::cout << '"' << get_data(node->children, "postcode") << '"' << ';';
    std::cout << '"' << get_data(node->children, "huisnummer") << '"' << ';';
    std::cout << '"' << get_data(node->children, "huisnummertoevoeging") << '"' << ';';

    xmlNode* openb = find_first(node->children, "gerelateerdeOpenbareRuimte");
    if (openb) {
      std::cout << '"' << get_data(openb->children, "identificatie") << '"' << ';';
    }

    xmlNode* geld = find_first(node->children, "tijdvakgeldigheid");
    if (geld) {
      std::cout << '"' << get_data(geld->children, "begindatumTijdvakGeldigheid") << '"' << ';';
      std::cout << '"' << get_data(geld->children, "einddatumTijdvakGeldigheid") << '"';
    }
    std::cout << "\n";
    node = node->next;
  }

  xmlFreeDoc(doc);
  xmlCleanupParser();

  return 0;

}

