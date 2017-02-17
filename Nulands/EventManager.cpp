#include "EventManager.h"

map<type_index, vector<shared_ptr<IDelegate>>> EventManager::m_dMap;
map<type_index, vector<type_index>> EventManager::m_manifest;
