#ifndef __BUILD_DATABASE_H__
#define __BUILD_DATABASE_H__

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <sstream>

#include "../src/sqlite/sqlite3.h"
#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_utils.hpp"

using namespace std;
using namespace rapidxml;

typedef xml_node<> node_t;
typedef xml_document<> doc_t;

#include "games-row.h"

bool execute_file(ifstream& fin, sqlite3* db);
bool add_games_to_db(sqlite3* db, const doc_t* games_xml, games_row* row);

#endif
