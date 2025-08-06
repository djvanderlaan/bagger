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

  xmlNode* stand = find_first(root->children, "stand");
  xmlNode* node = 0;

  while(stand = find_first(stand, "stand")) {

    node = find_first(stand, "Nummeraanduiding");

    std::cout << '"' << get_data(node->children, "identificatie") << '"' << ';';
    std::cout << '"' << get_data(node->children, "postcode") << '"' << ';';
    std::cout << '"' << get_data(node->children, "huisnummer") << '"' << ';';
    std::cout << '"' << get_data(node->children, "huisletter") << '"' << ';';
    //std::cout << '"' << get_data(node->children, "status") << '"' << ';';

    xmlNode* ligtaan = find_first(node->children, "ligtAan");
    if (ligtaan) {
      std::cout << '"' << get_data(ligtaan->children, "OpenbareRuimteRef") << '"' << ';';
    }

    // geldigheid
    xmlNode* geld = find_first(node->children, "Voorkomen");
    if (geld) {
      std::cout << '"' << get_data(geld->children, "beginGeldigheid") << '"' << ';';
      std::cout << '"' << get_data(geld->children, "eindGeldigheid") << '"' << ';';
    }
    std::cout << "\n";
    stand = stand->next;
  }

  xmlFreeDoc(doc);
  xmlCleanupParser();

  return 0;

}


