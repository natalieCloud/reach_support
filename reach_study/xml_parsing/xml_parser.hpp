#ifndef POINT_SUPPORT_XML_PARSER_H
#define POINT_SUPPORT_XML_PARSER_H

#include "../include/rapidxml.hpp"
#include "array_transform.hpp"
#include <eigen3/Eigen/Geometry>

#include <stdio.h>
#include <stdlib.h>

#include <fstream>

#include <vector>
#include <string>

/**
 * @author Natalie Chmura 
 * 
 * @brief This contains a class that reads information from the XML file genrated by the reach study
 * and parses it into an array of data nodes! (^u^)
 */

/**
 * @namespace ReachXML
*/
namespace ReachXML {

/**
 * @class XMLParser
 * 
 * @brief This class takes the results generated by the reach study done by the ros-industrial reach
 * (Generated into an xml format) and parses the information into a vector of "PoseData" nodes. 
 * This parsing is done by leveraging the use of the rapidxml package!
*/
class XMLParser {

    public:
    
        /**
         * @struct PoseData
         * @brief Struct that contains the pose and score data.
         * 
         * @param translation: A 3x1 vector that represents the pose's xyz coordinates
         * @param quater: A quaternion that represents the pose's rotation
         * @param reachResult: Is the pose considered "reachable", 0 no 1 yes
         * @param reachScore: Score for the reachability of the pose
         */ 
        struct PoseData {
            Eigen::Vector3d translation;
            Eigen::Quaternion<_Float64> quater;
            int reachResult;
            _Float64 reachScore; 
        };

        /**
         * @brief This function takes the name of a file and parses it into a vector of data structs that
         * contian a pose in space, and an associated reachability score
         * 
         * @param fname: The name of the file that the user pases in for the xml to read from.
         */
        static std::vector<PoseData> parseXML(const std::string fname);

        /**
         * @brief The size of the pose matrix (Will be uneeded? if we change to a quaternion!)
         */
        static const int MATRIX_SIZE = 16; 

    private:

        /**
         * @brief This function takes the root of a tree and traces through its
         *  children to obtain the number of child "item" nodes.
         * 
         * @param root_node: The node at the root of the file
         * 
         * @returns The count of all of the item nodes
         */
        static int getItemCount(rapidxml::xml_node<> * root_node);

        /**
         * @brief This function takes the root node of an xml tree and traces through its
         * children to obtain the first instance of the child "item" node that contains the
         * pose matrix and reachability score for that pose. 
         * 
         * @param root_node: The node at the root of the file
         * 
         * @returns A pointer to the the first item child node
         */
        static rapidxml::xml_node<> * descendToItem(rapidxml::xml_node<> * root_node);

        /**
         * @brief This function creates a vector with populated PoseData structs
         * 
         * @param item_node: The first child node in the xml tree
         * 
         * @param count: The number of item child nodes in the xml tree
         * 
         * @returns A vector populated with filled PoseData nodes 
         */
        static std::vector<PoseData> populatePoses(rapidxml::xml_node<> * root_node, int count);

        /**
         * @brief This function populates a struct with all the pose and reach data
         * 
         * @param item_node: The first child node in the xml tree
         * 
         * @param data: A pointer to the struct that will contain the data
         */
        static void populateStruct(rapidxml::xml_node<> * item_node, struct PoseData *data);

        /**
         * @brief Obtains the data from the xml tree ( represented by an Isometry#D pose matrix)
         * and represents the matrix in array format.
         * 
         * @param item_node: The first child node in the xml tree
         * 
         * @returns An array of Isometery3D data
         */
        static _Float64 * getPoseMatrix(rapidxml::xml_node<> * item_node); 

};

} //namespace ReachXML 

#endif // POINT_SUPPORT_XML_PARSER_H