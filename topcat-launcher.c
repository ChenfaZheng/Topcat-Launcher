#include <stdio.h>
#include <windows.h>

int main(void){
	// set program name
	char* programName = "Topcat Launcher";
	SetConsoleTitle(programName);

	// hide window
	HWND hWnd = GetForegroundWindow();
	if (hWnd != NULL) {
		ShowWindow(hWnd, SW_HIDE);
	}

	// check if the file path exists
	char* filePath = "topcat.jar";
	if (GetFileAttributes(filePath) == INVALID_FILE_ATTRIBUTES) {
		// pop up error message
		// show name with format string
		char* errorMessage = "Error: %s not found.";
		char* error = malloc(strlen(errorMessage) + strlen(filePath) + 1);
		sprintf(error, errorMessage, filePath);
		MessageBox(NULL, error, "Error", MB_OK);
		return -1;
	}
	
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	// Start the child process.
	char* command = "java -jar %s";
	char* commandLine = malloc(strlen(command) + strlen(filePath) + 1);
	sprintf(commandLine, command, filePath);
	if(!CreateProcess(NULL,   // No module name (use command line)
		commandLine,        // Command line
		NULL,           // Process handle not inheritable
		NULL,           // Thread handle not inheritable
		FALSE,          // Set handle inheritance to FALSE
		0,              // No creation flags
		NULL,           // Use parent's environment block
		NULL,           // Use parent's starting directory
		&si,            // Pointer to STARTUPINFO structure
		&pi )           // Pointer to PROCESS_INFORMATION structure
	) {
		// pop up error message
		MessageBox(NULL, "Error: CreateProcess failed.", "Error", MB_OK);
		return -1;
	}

	// Wait until child process exits.
	WaitForSingleObject(pi.hProcess, INFINITE);

	// Close process and thread handles.
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	return 0;
}