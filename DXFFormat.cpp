#include "DXFFormat.h"
        
std::string DXFFormat::getBaseLayer()
{
    return "1";
}

std::string DXFFormat::output()
{
    std::stringstream outstr;
        
    outstr << "0" << std::endl;
    outstr << "SECTION" << std::endl;
    outstr << "2" << std::endl;
    outstr << "ENTITIES" << std::endl;
    outstr << stream.str();		
    outstr << "0" << std::endl;
    outstr << "ENDSEC" << std::endl;
    outstr << "0" << std::endl;
    outstr << "EOF" << std::endl;

    return outstr.str();
}

void DXFFormat::beginPolygon(std::string layer, bool isFirst)
{
    currentLayer = layer;
}

void DXFFormat::endPolygon(std::string layer, bool isFirst)
{
}

void DXFFormat::beginPath()
{
    firstPoint = true;
}

void DXFFormat::addPoint(double x, double y)
{
    if (firstPoint) {
        lX = fX = x;
        lY = fY = y;
        firstPoint = false;
    } else {
        stream << "0" << std::endl;
        stream << "LINE" << std::endl;
        stream << "10" << std::endl;
        stream << lX << std::endl;
        stream << "20" << std::endl;
        stream << lY << std::endl;
        stream << "11" << std::endl;
        stream << x << std::endl;
        stream << "21" << std::endl;
        stream << y << std::endl;
        stream << "62" << std::endl;
        stream << currentLayer << std::endl;

        lX = x;
        lY = y;
    }
}

void DXFFormat::endPath()
{
    if (!firstPoint) {
        stream << "0" << std::endl;
        stream << "LINE" << std::endl;
        stream << "10" << std::endl;
        stream << lX << std::endl;
        stream << "20" << std::endl;
        stream << lY << std::endl;
        stream << "11" << std::endl;
        stream << fY << std::endl;
        stream << "21" << std::endl;
        stream << fY << std::endl;
        stream << "62" << std::endl;
        stream << currentLayer << std::endl;
    }
}