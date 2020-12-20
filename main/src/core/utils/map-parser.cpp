#include "map-parser.hpp"

using ast::MapParser;

/*
* Internal structure for xml reading and writing helper functions
*/
struct MapParser::Internal
{
    TiXmlDocument* xml_document;

	void loadXML(const std::string & file) {
        xml_document = new TiXmlDocument("assets/maps/" + file);
        bool loadValid = xml_document->LoadFile();

		if (loadValid)
            printf("ast::MapParser::loadXML: Successfully loaded XML File\n");
        else
            printf("ast::MapParser::loadXML: Failed to load XML File\n");
	}

    TiXmlDocument* GetXmlDocument()
    {
        return xml_document;
    }
};

/*
* Constructer
*/
MapParser::MapParser() : internal(ast::make_internal_ptr<Internal>()) {}

/*
* Parse XML map data
*/
void MapParser::parse(const char* file)
{
    internal->loadXML(file);

    TiXmlElement* root = internal->GetXmlDocument()->RootElement();
    int layerID, rowcount, colcount = 0;

    root->Attribute("width", &rowcount);
    root->Attribute("height", &colcount);

    for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
    {
        if (e->Value() == std::string("layer"))
        {
            parseLayer(e, layerID=0, rowcount, colcount);
        }
    }
}

void MapParser::parseLayer(TiXmlElement* element, int layerID, int rowcount, int colcount)
{
    element->Attribute("id", &layerID);

    std::cout << "Parsing Map Data..." << std::endl;

    TiXmlElement* data;
    for (TiXmlElement* e = element->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
    {
        if (e->Value() == std::string("data"))
        {
            data = e;
            break;
        }
    }

    std::string tile_matrix(data->GetText());
    std::istringstream iss(tile_matrix);
    std::string id;

    int** tile_arr = new int*[rowcount];
    for (int i = 0; i < rowcount; i++)
        tile_arr[i] = new int[colcount];

    for (int row = 0; row < rowcount; row++)
    {
        for (int col = 0; col < colcount; col++)
        {
            std::getline(iss, id, ',');
            std::stringstream convertor(id);
            convertor >> tile_arr[row][col];
            std::cout << tile_arr[row][col];
        }
    }

    this->gameLayers.insert({ layerID, tile_arr });
}