#include "parse.h"
#include <gdal/ogr_api.h>
#include <gdal/ogr_geometry.h>

int main(int argc, char **argv) {

  //if (argc != 2) return 1;
  xmlDoc* doc = NULL;
  if (argc == 2) {
    std::string filename(argv[1]);
    if (filename == "--header") {
      std::cout << "\"woonplaats_id\";\"gemeente_id\";\"status\";\"begin_geldigheid\";" << 
        "\"eind_geldigheid\"" << std::endl;
      return 0;
    } else doc = xmlReadFile(argv[1], NULL, 0);
  } else {
    doc = xmlReadFd(STDIN_FILENO, NULL, NULL, 0);
  }

  if (doc == NULL) {
    std::cerr << "Error could not parse '" << argv[1] << "'.\n";
  }

  xmlNode* root = xmlDocGetRootElement(doc);


  xmlNode* node = find_first(root->children, "GemeenteWoonplaatsRelatie");

  while(node = find_first(node, "GemeenteWoonplaatsRelatie")) {

    xmlNode* wpl = find_first(node->children, "gerelateerdeWoonplaats");
    if (wpl) {
      std::cout << '"' << get_data(wpl->children, "identificatie") << '"' << ';';
    }

    xmlNode* gem = find_first(node->children, "gerelateerdeGemeente");
    if (gem) {
      std::cout << '"' << get_data(gem->children, "identificatie") << '"' << ';';
    }

    std::cout << '"' << get_data(node->children, "status") << '"' << ';';

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

