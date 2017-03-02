#ifndef parse_h
#define parse_h

#include <libxml/parser.h>
#include <libxml/tree.h>
#include <gdal/ogr_api.h>
#include <gdal/ogr_geometry.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <unistd.h>

std::string xml_to_string(const xmlChar* str) {
  int len = xmlStrlen(str);
  std::string res(len, ' ');
  for (int i = 0; i < len; ++i) res[i] = str[i];
  return res;
}

xmlNode* find_first(xmlNode* node, const std::string& name) {
  for (xmlNode* c = node; c; c = c->next) {
    if (c->type == XML_ELEMENT_NODE) {
      std::string cname = xml_to_string(c->name);
      if (name == cname) return c;
      xmlNode* res = find_first(c->children, name);
      if (res) return res;
    }
  }
  return NULL;
}

xmlNode* find_first_child(xmlNode* node, const std::string& name) {
  for (xmlNode* c = node; c; c = c->next) {
    if (c->type == XML_ELEMENT_NODE) {
      std::string cname = xml_to_string(c->name);
      if (name == cname) return c;
    }
  }
  return NULL;
}

std::string get_data(xmlNode* node, const std::string& name, bool depth_first = true, 
    bool clean = true) {
  xmlNode* res = NULL;
  if (depth_first) {
    res = find_first(node, name);
  } else {
    res = find_first_child(node, name);
  }
  if (res == NULL) return std::string("");
  std::string result = xml_to_string(res->children->content);
  if (clean) {
    // remove newlines from string
    std::replace(result.begin(), result.end(), '\n', ' ');
  }

  return result;
}


#endif
