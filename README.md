#Description: This keylogger record keyboard strokes using system hooks.
It then writes the keystrokes to log file hidden in the AppData folder in encrypted form. 
It also sends an email to the specified email id with the encrypted log file attached.
There's also a timer function to control the frequency of sending mail.


#Note: The code is written in C++.
It works on Windows 7, 8, 10.
The code can be compiled in Codeblocks by enabling C++11 standards and the -mwindows flag.
App password must be set for gmail and it must be used in place of gmail account password to enable sending of mails.
