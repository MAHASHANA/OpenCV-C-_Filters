# OpenCV-C-_Filters
Srinivas Peri 

OS: Windows 11

IDE: visual Studio 2022 

opencv version: 4.6.0. 2022-06-12, using build vc15

After downloading the ConsoleApplication1 zip file add it to your vs 2022 file path and
->Now go to the project icon on the top and to Properties.

->Then in properties go to C/C++ --> General 

->In General Additional Include Directories in place of C:\opencv\build\include give your_file_path\opencv\build\include. 

->Then go to Linker --> General

->In General Additional Library Directories in place of C:\opencv\build\x64\vc15\lib give your yoyu_file_path\opencv\build\x64\vc15\lib 

->Then Go to Linker --> Input

->In Input Additional Dependencies go to the dropdown and choose Edit and add opencv_world460.lib in the empty box.

->Apply all the changes and you should not see any errors.

Now go to Build  and click on build solution.
And Set your configuration manager to Release and x64
you are good to go.

Press 'a' to check the rainbow extenction output.

****************Note*****************

1. For Task 1 I have just given imDisplay.cpp and image please add to the current project and 
comment out the vidDisplay.cpp to run the imDispaly.cpp file.

2. When you are implimenting cartonization to exit from the loop  press and hold p for a second.

3. keep the curser on the main video window and hold q for 2 seconds to quit from all the windows.

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

***If you are not using the Zip file, I have also included the necessary files. Please make use of them as you see fit.***


###########################

Reason for late submission:
For this semester, I took Machine learning and pattern recognition (MLPR) and Pattern recognition and computer vision (PRCV), 
and I didn't attend the first PRCV sessions because of MLPR. MLPR has now been dropped.

																		
																^^Thank you.^^
