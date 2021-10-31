This program use RSA to encrypt/decrypt message. 

To compile, type "make", and an executable called rsa will be generated.

To run, type "./rsa p q", where p, q are two prime numbers. 

The program will then prompt you to enter command, and valid command includes: 

EXIT: Gracefully terminate the program.

DECRYPT [input] [output]: Opens the file at [input], reads the contents of the file, decrypts the message, and overwrites the contents of the file at [output] with the decrypted message.

ENCRYPT [filename] [n] [message]: Creates/overwrites the file at the specified path, writing an encrypted version of [message], which is a string of lowercase letters a-z and spaces. [n] is an integer which will be used in the encryption process, which is equal to p * q.

After you successfully complete a task, the program will prompt you back to enter another command, until you enter EXIT.

Note: If you make invalid command, make bad choice of p and q, or give invalid filename, an error message will be shown and the program will terminate gracefully.
