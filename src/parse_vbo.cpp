#include "parse.h"

#include <gdal/ogr_api.h>
#include <gdal/ogr_geometry.h>

int main(int argc, char **argv) {

  //if (argc != 2) return 1;
  xmlDoc* doc = NULL;
  if (argc == 2) {
    std::string filename(argv[1]);
    if (filename == "--header") {
      std::cout << "\"id\";\"gebruiksdoel\";\"oppervlakte\";\"status\";" << 
        "\"hoofdadres\";\"pand\";\"begin_geldigheid\";\"eind_geldigheid\";" << 
        "\"geometrie_wkt\";\"x\";\"y\"" << std::endl;
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

    node = find_first(stand, "Verblijfsobject");

  //while(node = find_first(node, "Verblijfsobject")) {
    std::cout << '"' << get_data(node->children, "identificatie", false) << '"' << ';';
    std::cout << '"' << get_data(node->children, "gebruiksdoel") << '"' << ';';
    std::cout << '"' << get_data(node->children, "oppervlakte") << '"' << ';';
    std::cout << '"' << get_data(node->children, "status") << '"' << ';';

    // lees gerelateerde hoofdadres
    xmlNode* addr = find_first(node->children, "heeftAlsHoofdadres");
    if (addr) {
      std::cout << '"' << get_data(addr, "NummeraanduidingRef") << '"' << ';';
    }
    // lees gerelateerde pand
    xmlNode* pand = find_first(node->children, "maaktDeelUitVan");
    if (pand) {
      std::cout << '"' << get_data(pand->children, "PandRef") << '"' << ';';
    }
    // geldigheid
    xmlNode* geld = find_first(node->children, "Voorkomen");
    if (geld) {
      std::cout << '"' << get_data(geld->children, "beginGeldigheid") << '"' << ';';
      std::cout << '"' << get_data(geld->children, "eindGeldigheid") << '"' << ';';
    }
    // geometry
    xmlNode* geom = find_first(node->children, "Point");
    if (geom) {
      // The geometry is encoded in GML; first extract the GML
      xmlBufferPtr buffer = xmlBufferCreate();
      int size = xmlNodeDump(buffer, doc, geom, 0, 0);
      std::string gml = xml_to_string(buffer->content);
      // Convert the GML to Well-known Text format using OGR
      OGRGeometryH res = OGR_G_CreateFromGML(gml.c_str());
      char* oglbuffer = 0;
      OGR_G_ExportToWkt(res, &oglbuffer);
      std::string wkt(oglbuffer);
      CPLFree(oglbuffer);
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
    stand = stand->next;
  }

  xmlFreeDoc(doc);
  xmlCleanupParser();

  return 0;

}

