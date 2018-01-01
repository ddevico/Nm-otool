# nm-otool

Basic implementation of Nm and Otool MacOSX commands - 42 school project
Handles Mach-O executable 32 and 64 bits, dynamically linked shared library and object files.

# Functions

*nm*
--
``
void			nm(char *ptr, char *name)
``
The nm () list symbols from object files.

*otool*
--
``
void			otool(void *ptr, char *name)
``
The   otool  command  displays  specified  parts  of  object  files  or libraries.

# Start the program

- ```make```
- ```./ft_nm [-jpuU] [file]```

- ```./ft_otool [-th] [file]```
