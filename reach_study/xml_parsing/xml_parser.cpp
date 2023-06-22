#include "xml_parser.hpp"

#include <stdio.h>

#include <iostream>
#include <fstream>

#include <vector>
#include <string>

/*
 * @Author Natalie Chmura
 * 
 * @Description
 * This program takes the results generated by the reach study (done in the xml format) and parses those results into a list of data structs.
 * This parsing is done by leveraging rapidxml! 
*/

namespace reachXML {

void xmlParser::parseXML(std::string fname) {

    rapidxml::xml_document<> doc;
    rapidxml::xml_node<> * root_node;
    //Read the file into a vector
    std::ifstream theFile (fname);
    std::vector<char> buffer((std::istreambuf_iterator<char>(theFile)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');
	// Parse the buffer using the xml file parsing library into doc 
	doc.parse<0>(&buffer[0]);
    //Find the root of the data, in our case, boost_serialization
    root_node = doc.first_node(0);

    

    //TEST PRINT START
    std::string sttr = root_node->first_attribute()->value();
    std::cout << sttr << std::endl;
    std::cout << "Num points: " << count << std::endl; 
    //TEST PRINT END

    poseData data = xmlParser::populatePoses(item_node);

}

int xmlParser::getItemCount(rapidxml::xml_node<> * root_node) {

    root_node = root_node->first_node(0); // <db>
    root_node = root_node->first_node(0); // <results>
    root_node = root_node->first_node(0); // <count>
    root_node = root_node->next_sibling(); // <item_version>
    root_node = root_node->next_sibling(); // <item>
    root_node = root_node->first_node(0); // <count>
    return std::stoi(root_node->value());
}

rapidxml::xml_node<> * xmlParser::descendToItem(rapidxml::xml_node<> * root_node){

    root_node = root_node->first_node(0); // <db>
    root_node = root_node->first_node(0); // <results>
    root_node = root_node->first_node(0); // <count>
    root_node = root_node->next_sibling(); // <item_version>
    root_node = root_node->next_sibling(); // <item>
    root_node = root_node->first_node(0); // <count>
    root_node = root_node->next_sibling(); // <item_version>
    root_node = root_node->next_sibling(); // <item>

    return root_node;
}

poseData * populatePoses(rapidxml::xml_node<> * root_node) {

    rapidxml::xml_node<> * item_node = descendToItem(root_node);
    int count = getItemCount(root_node);

    poseData dataArr[count];

    for (int i = 0; i < count; i++) {

        //func call to populate struct

        item_node = item_node->next_sibling();
    }
}

} //namespace reachXML