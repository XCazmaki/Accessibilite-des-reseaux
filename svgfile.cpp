#include <sstream>

#include "svgfile.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>


const std::string svgHeader =
    "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
    "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" ";

const std::string svgEnding = "\n\n</svg>\n";

/// Effets "Boule en relief", voir données à la fin de ce fichier
extern const std::string svgBallGradients;

std::set<std::string> Svgfile::s_openfiles;

Svgfile::Svgfile(std::string _filename, int _width, int _height) :
    m_filename{_filename}, m_width{_width}, m_height{_height}
{

    //std::cout << "Opening SVG output file : "
             // << m_filename << std::endl;

    if ( s_openfiles.count(m_filename) )
        throw std::runtime_error( "File " + m_filename + " already open !" );

    m_ostrm.open(m_filename);
    s_openfiles.insert(m_filename);

    if (!m_ostrm)
    {
        std::cout << "Problem opening " << m_filename << std::endl;
        throw std::runtime_error("Could not open file " + m_filename );
    }

    //std::cout << "OK" << std::endl;

    // Writing the header into the SVG file
    m_ostrm << svgHeader;
    m_ostrm << "width=\"" << m_width << "\" height=\"" << m_height << "\">\n\n";
}

Svgfile::~Svgfile()
{
    // Writing the ending into the SVG file
    m_ostrm << svgEnding;

    // Removing this file from the list of open files
    s_openfiles.erase(m_filename);

    // No need to explicitly close the ofstream object (automatic upon destruction)
}

// Helper templated function
template<typename T>
std::string attrib(std::string name, T val)
{
    std::ostringstream oss;
    oss << name << "=\"" << val << "\" ";
    return oss.str();
}

void Svgfile::addDisk(double x, double y, double r, std::string color)
{
    m_ostrm << "<circle "
            << attrib("cx", x)
            << attrib("cy", y)
            << attrib("r",  r)
            << attrib("fill", color )
            << "/>\n";
}

void Svgfile::addCircle(double x, double y, double r, double ep, std::string color)
{
    m_ostrm << "<circle "
            << attrib("cx", x)
            << attrib("cy", y)
            << attrib("r",  r)
            << attrib("fill", "none")
            << attrib("stroke", color )
            << attrib("stroke-width", ep )
            << "/>\n";
}

/// <polygon points="200,10 250,190 160,210" style="fill:lime;stroke:purple;stroke-width:1" />
void Svgfile::addTriangle(double x1, double y1, double x2, double y2,
                          double x3, double y3, std::string colorFill,
                          double thickness, std::string colorStroke)
{

    m_ostrm << "<polygon points=\" "
            << x1 << "," << y1 << " "
            << x2 << "," << y2 << " "
            << x3 << "," << y3
            << "\" style=\"fill:" << colorFill
            << ";stroke:" << colorStroke
            << ";stroke-width:" << thickness
            << "\" />\n";
}


void Svgfile::addTriangle(double x1, double y1, double x2, double y2,
                          double x3, double y3, std::string colorFill)
{
    m_ostrm << "<polygon points=\" "
            << x1 << "," << y1 << " "
            << x2 << "," << y2 << " "
            << x3 << "," << y3
            << "\" style=\"fill:" << colorFill
            << "\" />\n";
}

void Svgfile::addLine(double x1, double y1, double x2, double y2, std::string color)
{
    m_ostrm << "<line "
            << attrib("x1", x1)
            << attrib("y1", y1)
            << attrib("x2", x2)
            << attrib("y2", y2)
            << attrib("stroke", color)
            << "/>\n";
}

void Svgfile::addCross(double x, double y, double span, std::string color)
{
    addLine(x-span, y-span, x+span, y+span, color);
    addLine(x-span, y+span, x+span, y-span, color);
}

void Svgfile::addText(double x, double y, std::string text, std::string color)
{
    /// <text x="180" y="60">Un texte</text>
    m_ostrm << "<text "
            << attrib("x", x)
            << attrib("y", y)
            << attrib("fill", color)
            << ">" << text << "</text>\n";
}

void Svgfile::addText(double x, double y, double val, std::string color)
{
    std::ostringstream oss;
    oss << val;
    addText(x, y, oss.str(), color);
}

void Svgfile::addGrid(double span, bool numbering, std::string color)
{
    double y=0;
    while (y<=m_height)
    {
        addLine(0, y, m_width, y, color);
        if (numbering)
            addText(5, y-5, y, color);
        y+=span;
    }

    double x=0;
    while (x<=m_width)
    {
        addLine(x, 0, x, m_height, color);
        if (numbering)
            addText(x+5, 15, x, color);
        x+=span;
    }
}

std::string Svgfile::makeRGB(int r, int g, int b)
{
    std::ostringstream oss;
    oss << "rgb(" << r << "," << g << "," << b << ")";
    return oss.str();
}

void Svgfile::addRectangle(double x1, double y1, double x2, double y2,
                           double x3, double y3, double x4, double y4, std::string colorFill)
{

    //blindage(x1,y1,x2,y2,x3,y3,x4,y4);

    m_ostrm << "<polygon points=\" "
            << x1 << "," << y1 << " "
            << x2 << "," << y2 << " "
            << x3 << "," << y3 << " "
            << x4 << "," << y4
            << "\" style=\"fill:" << colorFill
            << "\" />\n";
}//end addRectangle

void Svgfile::addRectangle(double x1, double y1, double x2, double y2,
                           double x3, double y3, double x4, double y4, std::string colorFill,
                           double thickness, std::string colorStroke)
{
    //blindage(x1,y1,x2,y2,x3,y3,x4,y4);

    m_ostrm << "<polygon points=\" "
            << x1 << "," << y1 << " "
            << x2 << "," << y2 << " "
            << x3 << "," << y3 << " "
            << x4 << "," << y4
            << "\" style=\"fill:" << colorFill
            << ";stroke:" << colorStroke
            << ";stroke-width:" << thickness
            << "\" />\n";
}//end addRectangle

double min_4(double& val_1, double& val_2, double& val_3, double& val_4)
{
    double val_m = std::min(val_1,val_2);
    val_m = std::min(val_m, val_3);
    val_m = std::min(val_m,val_4);
    return val_m;
}//end min_4

double max_4(double& val_1, double& val_2, double& val_3, double& val_4)
{
    double val_m = std::max(val_1,val_2);
    val_m = std::max(val_m, val_3);
    val_m = std::max(val_m,val_4);
    return val_m;
}//end max_4

void blindage(double& x1, double& y1, double& x2, double& y2, double& x3, double& y3, double& x4, double& y4)
//permet de blinder le dessin d'un rectangle pour ne pas avoir un sablier mais cela empèche la ratotion
{
    // Blindage //
    double x_1 = min_4(x1,x2,x3,x4);
    double y_1 = min_4(y1,y2,y3,y4);
    double x_3 = max_4(x1,x2,x3,x4);
    double y_3 = max_4(y1,y2,y3,y4);
    double x_2;
    double y_2;
    double x_4;
    double y_4;

    if (x1 == x_1 && y1 == y_3)
    {
        x_4 = x1;
        y_4 = y1;
    }//end if
    else if (x2 == x_1 && y2 == y_3)
    {
        x_4 = x2;
        y_4 = y2;
    }//end else if
    else if (x3 == x_1 && y3 == y_3)
    {
        x_4 = x3;
        y_4 = y3;
    }//end else if
    else
    {
        x_4 = x4;
        y_4 = y4;
    }//end else

    if (x1 == x_3 && y1 == y_1)
    {
        x_2 = x1;
        y_2 = y1;
    }//end if
    else if (x2 == x_3 && y2 == y_1)
    {
        x_2 = x2;
        y_2 = y2;
    }//end else if
    else if (x3 == x_3 && y3 == y_1)
    {
        x_2 = x3;
        y_2 = y3;
    }//end else if
    else
    {
        x_2 = x4;
        y_2 = y4;
    }//end else

    x1 = x_1;
    y1 = y_1;
    x2 = x_2;
    y2 = y_2;
    x3 = x_3;
    y3 = y_3;
    x4 = x_4;
    y4 = y_4;
}//end blindage
