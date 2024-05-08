STARTUPINFO si;
PROCESS_INFORMATION pi;
ZeroMemory(&si, sizeof(si));
si.cb = sizeof(si);
ZeroMemory(&pi, sizeof(pi));
char* env = GetEnvironmentStrings();
CreateProcess(
    "cmd.exe",           
    "cmd.exe /c dir.bat",
    NULL,                
    NULL,                
    FALSE,               
    0,                   
    env,                 
    NULL,               
    &si,                 
    &pi                  
);
FreeEnvironmentStrings(env);
