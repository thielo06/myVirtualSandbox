#pragma once

#include <dwmapi.h>
#include <string>
#include <windows.h>
#include <windowsx.h>

#include "Resource.h"

// Following DLL are part of the .NET desktop development workload 
// which is a framework that is not native to C++.
#using <System.dll>
#using <System.Xml.dll>

using namespace System;
using namespace System::Xml;

// Global constants
const int CANVAS_HOR_OFFSET = 10;
const int CANVAS_VER_OFFSET = 10;
const int CANVAS_WIDTH = 640;
const int CANVAS_HEIGHT = 480;

const int OUTPUT_VER_OFFSET = 10;
const int OUTPUT_HEIGHT = 120;

const int BUTTON_HOR_OFFSET = 10;
const int BUTTON_VER_OFFSET = 10;
const int BUTTON_WIDTH = 100;
const int BUTTON_HEIGHT = 30;

const int SYMBOL_BUTTON_HEIGHT = 20;
const int SYMBOL_BUTTON_WIDTH = 20;

const char STORAGE[] = "dataCache.xml";

enum class ToolState {
	empty,
	addPoint,
	selectPoint
};

// Global variable
extern ToolState CurrentToolState;

ref class XmlStorage {
public:
	static XmlDocument^ XmlDocument;
	static String^ FileName = gcnew String(STORAGE);
};

extern bool prevPointFlag;
extern int prevPointId;
