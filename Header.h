#pragma once

#include <dwmapi.h>
#include <string>
#include <windowsx.h>
#include <vector>

#include "Resource.h"

// Following DLL are part of the .NET desktop development workload 
// which is a framework that is not native to C++.
#using <System.dll>

using namespace System;
using namespace System::Diagnostics;

using namespace std;

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

const int ENTRY_HOR_OFFSET = 10;
const int ENTRY_VER_OFFSET = 10;
const int ENTRY_WIDTH = 60;
const int ENTRY_HEIGHT = 20;

const int SYMBOL_BUTTON_HEIGHT = 20;
const int SYMBOL_BUTTON_WIDTH = 20;

enum class ToolState {
	Empty,
	AddPoint
};

enum class SelectionState {
	Empty,
	Hovering,
	Selected
};

// Global variables
extern ToolState CurrentToolState;

extern bool activePointFlag;
extern int activePointId;
