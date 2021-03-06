#include "parse.h"
#include <gdal/ogr_api.h>
#include <gdal/ogr_geometry.h>

int main(int argc, char **argv) {

  //if (argc != 2) return 1;
  xmlDoc* doc = NULL;
  if (argc == 2) {
    std::string filename(argv[1]);
    if (filename == "--header") {
      std::cout << "\"id\";\"naam\";\"status\";\"begin_geldigheid\";" << 
        "\"eind_geldigheid\";\"geometrie_wkt\";\"x\";\"y\"" << std::endl;
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

  xmlNode* node = find_first(root->children, "Woonplaats");

  while(node = find_first(node, "Woonplaats")) {
    std::cout << '"' << get_data(node->children, "identificatie") << '"' << ';';
    std::cout << '"' << get_data(node->children, "woonplaatsNaam") << '"' << ';';
    std::cout << '"' << get_data(node->children, "woonplaatsStatus") << '"' << ';';

    xmlNode* geld = find_first(node->children, "tijdvakgeldigheid");
    if (geld) {
      std::cout << '"' << get_data(geld->children, "begindatumTijdvakGeldigheid") << '"' << ';';
      std::cout << '"' << get_data(geld->children, "einddatumTijdvakGeldigheid") << '"' << ';';
    }

    xmlNode* geom = find_first(node->children, "woonplaatsGeometrie");
    if (geom) {
      // The geometry is encoded in GML; first extract the GML
      xmlBufferPtr buffer = xmlBufferCreate();
      int size = xmlNodeDump(buffer, doc, geom->children, 0, 0);
      std::string gml = xml_to_string(buffer->content);
      // Convert the GML to Well-known Text format using OGR
      OGRGeometryH res = OGR_G_CreateFromGML(gml.c_str());
      char* oglbuffer = 0;
      OGR_G_ExportToWkt(res, &oglbuffer);
      std::string wkt(oglbuffer);
      OGRFree(oglbuffer);
      std::cout << '"' << wkt << '"' << ';';
      // Extract coordinate of centroid
      OGRPoint centroid;
      OGR_G_Centroid(res, reinterpret_cast<void*>(&centroid));
      std::cout << '"' << centroid.getX() << '"' << ';';
      std::cout << '"' << centroid.getY() << '"';
    } else {
      std::cout << "not found";
    }

    std::cout << "\n";
    node = node->next;
  }

  xmlFreeDoc(doc);
  xmlCleanupParser();

  return 0;

}

