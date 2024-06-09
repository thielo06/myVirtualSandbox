#pragma once

// C++ Standard Library Headers
#include <string>
#include <vector>

// External Library Headers

// System- and Framework-specific Headers
#include <windows.h> // Basic Windows-API
#include <windowsx.h> // Additional Macros and Inline-Functions
#include <mmsystem.h> // Header-File for Multimedia-Functions
#include <dwmapi.h> // Header-File for Desktop Window Manager

// Project-specific Headers
#include "resource.h"

// .NET Libraries
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
