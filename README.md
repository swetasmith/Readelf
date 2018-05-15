This project is basically to list down the shared libraries being used by the given apk file.
The Approch used is:
	1. Unarchive the .apk file & list out the shared libraries.
	2. Read the Shared Libraries it is basically ELF.
	3. ELF Header contains all information about tha Arch Type & ABI info's.
	4. Display the output.

Code base is running fine with .zip extension and it is giving the output for shared object ELF's as expected.
	->To run it one can execute below command: 
		$./junzip_demo <File Name>.zip

Note: The same containt can be unachive & achive it to the zip formate. Run above command it will give the expected output.

For APK file's I am having below queries:
1. What is the APK Signature Scheme ?It will be better if APK Signature Scheme is known, Share your thoughts for the same.
2. Do share the Header format for the .apk files, though it's a extended form of .zip but I am getting issues with header.
