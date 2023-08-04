#include "AppFunctions.h"
#include "Header.h"

void AppFunctions::InitializeXmlDocument() {
    XmlDocument^ doc = gcnew XmlDocument();
    doc->LoadXml("<root></root>");
    doc->Save("dataCache.xml");
}

void AppFunctions::DrawPoint(HWND hWnd, POINT point, COLORREF penColor) {
    HDC hDeviceContext;

    hDeviceContext = GetDC(hWnd);

    SetPixel(hDeviceContext, point.x, point.y, penColor);

    // Load data cache file and write point coordinates to it.
    XmlDocument^ xmlDoc = gcnew XmlDocument();
    xmlDoc->Load("dataCache.xml");

    XmlElement^ xmlPoint;

    xmlPoint = AppFunctions::SerializePoint(xmlDoc, point);

    xmlDoc->DocumentElement->AppendChild(xmlPoint);

    xmlDoc->Save("dataCache.xml");
}

XmlElement^ AppFunctions::SerializePoint(XmlDocument^ xmlDoc, POINT point) {
    XmlElement^ xmlPoint = xmlDoc->CreateElement("point");

    // New elements are "pushed" into the XML-Structure from above, 
    // respectively attributes are "pushed" from the left. Hence it is 
    // necessary to set the attribute that shall occure at the very 
    // left at first.
    xmlPoint->SetAttribute("y", point.y.ToString());
    xmlPoint->SetAttribute("x", point.x.ToString());

    return xmlPoint;
}