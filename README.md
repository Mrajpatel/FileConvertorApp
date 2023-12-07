# FileConvertorApp
 Console application which reads XML data and converts it into HTML content for web browser.


## Install and build instructions

1. Download or clone files in a directory
   
   ```
   git clone https://github.com/Mrajpatel/FileConvertorApp.git
   ```
2. Open project in Visual Studio
3. Click `F5` or `Local Windows Debugger` to run the application 
4. To build the executable (.exe); Select `Build Solution` from Build menu bar or simple hit `Ctrl + Shift + B`


## Run instructions
- Click `F5` or `Local Windows Debugger` to run the application or run the executable file from Visual Studio
- When running it requires XML filename in this case `cd_catalog.xml` (or path of the xml file)
- Once `output_content.html` file is generated it will open in a browser automatically 


## Application Structure/Design  

- Application is written for x64 platform
- When running it requires XML filename in this case `cd_catalog.xml` (or path of the xml file)
- It reads the XML file and calls the method `convertXMLtoHTML` function 
- [`convertXMLtoHTML`](https://github.com/Mrajpatel/FileConvertorApp/blob/ae7e272db0df98d3ebc3a34003b1a140926b199a/FileConverter/FileConverter.cpp#L19) function uses RapidXML library to read the XML content in file [cd_catalog.xml](https://github.com/Mrajpatel/FileConvertorApp/blob/main/FileConverter/cd_catalog.xml)
  - Application uses RapidXML because it does not require any additional external dependencies, easy to install/use, lightweight and fast (for small files/documents such as cd_catalog.xml)
  - Function returns the HTML data as a string 
- HTML string which is returned is then stored into `.html` file called `output_content.html`
- Application will automatically open generated `.html` file in default browser

#### Use of RapidXML:
- Application uses RapidXML for XML parsing because of its efficiency, particularly handaling small/medium size XML documents; for fast and simple parser without external dependencies
#### Functional Decomposition:
- Code structure is seperated using function `convertXMLtoHTML` for conversion login, which promotes modularity and code maintainability
#### Error Handling:
- Application includes simple error handling for file accessibility

(This application can further be imporoved to add more dynamic xml file reading capability in `convertXMLtoHTML` function, imporving cross-platform compatibility for opening the HTML file in a browser and finally adding more error handling for edge cases)
