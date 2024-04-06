import enum


working_directory = "binary's directory here"
executable_path = working_directory + "BooleanFuncMinimizer.exe"
output_file_name = "output.txt"


class Char(enum.Enum):
    THREE_DASH = "0110110"
    DASH = "0111111"
    C = "1000110"
    A = "0001000"
    P = "0001100"
    E = "0000110"

