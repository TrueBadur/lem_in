# The places to look for the tinyxml2 folders
set(FIND_FT_PATHS libft)

# The location of the include folder (and thus the header files)
# find_path uses the paths we defined above as places to look
# Saves the location of the header files in a variable called TINYXML2_INCLUDE_DIR
find_path(ft_INCLUDE_DIR libft.h   # The variable to store the path in and the name of the header files
		PATH_SUFFIXES includes              # The folder name containing the header files
		PATHS ${FIND_FT_PATHS})       # Where to look (defined above)

# The location of the lib folder (and thus the .a file)
# find_library uses the paths we defined above as places to look
# Saves the location of the .a file in a variable called TINYXML2_LIBRARY
find_library(ft_LIBRARY               # The variable to store where it found the .a files
		NAMES ft                      # The name of the .a file (without the extension and without the 'lib')
		PAT_SUFFIXES lib
		PATHS ${FIND_FT_PATHS})               # Where to look (defined above)
