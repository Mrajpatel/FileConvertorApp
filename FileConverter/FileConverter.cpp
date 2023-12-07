#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <windows.h>


// Using RapidXMl as it does not require external dependecies, lightweight and fast (for small documents)
#include "rapidxml/rapidxml.hpp"

/**
 * @brief Simple function that reads XML data and converts it into HTML.
 *
 * This function takes a string as input which contains XML data and returns string as HTML
 *
 * @param   xmlContent The XML string.
 * @return  The string which has HTML content.
 */
static std::string convertXmlToHtml(const std::string& xmlContent) {
    rapidxml::xml_document<> doc;
    doc.parse<0>(const_cast<char*>(xmlContent.c_str()));

    // Setup headers 
    std::stringstream htmlContent;
    htmlContent << "<html>\n<head>\n<title>CD Catalog</title>\n</head>\n<body>\n<table border='1'>\n"
        "<tr>\n<th>Title</th>\n<th>Artist</th>\n<th>Company</th>\n<th>Country</th>\n<th>Price</th>\n<th>Year</th>\n</tr>\n";

    // Loop through each node to get the element values
    for (rapidxml::xml_node<>* cdNode = doc.first_node("CATALOG")->first_node("CD"); 
            cdNode; 
            cdNode = cdNode->next_sibling()) {
        std::vector<std::string> cdData;

        for (rapidxml::xml_node<>* dataNode = cdNode->first_node(); dataNode; dataNode = dataNode->next_sibling()) {
            // Handle "&amp;" conversion
            std::string value = dataNode->value();
            size_t ampPos;
            while ((ampPos = value.find("&amp;")) != std::string::npos) {
                value.replace(ampPos, 5, "&");
            }

            cdData.push_back(value);
        }

        // Check of there is no missing node and add data to HTML content
        if (cdData.size() == 6) {
            htmlContent << "<tr>\n";
            for (const auto& value : cdData) {
                htmlContent << "<td>" << value << "</td>\n";
            }
            htmlContent << "</tr>\n";
        }
    }

    htmlContent << "</table>\n</body>\n</html>";
    return htmlContent.str();
}


// Main
int main() {
    // Read XML content from a file
    std::cout << "Enter the XML filename (or relative/absolute path): ";
    std::string xmlFileName;
    std::cin >> xmlFileName;

    std::ifstream xmlFile(xmlFileName);

    // Check file accessibility
    if (!xmlFile.is_open()) {
        std::cerr << "Error: Unable to open XML file." << std::endl;
        return 1;
    }

    std::stringstream buffer;
    buffer << xmlFile.rdbuf();
    std::string xmlContent = buffer.str();
    xmlFile.close();

    // Convert XML to HTML using RapidXML
    std::string htmlContent = convertXmlToHtml(xmlContent);

    // Write HTML content
    std::ofstream htmlFile("output_content.html");
    if (htmlFile.is_open()) {
        htmlFile << htmlContent;
        htmlFile.close();
        std::cout << "Conversion successful! HTML file created: output_content.html" << std::endl;
    }
    else {
        std::cerr << "Error: Unable to open HTML file for writing." << std::endl;
        return 1;
    }

    // Using shell to open the file in a web browser
    ShellExecuteA(NULL, "open", "output_content.html", NULL, NULL, SW_SHOWNORMAL);

    return 0;
}
