
""" exceptions for functions """

class FunctionsException(Exception):
    """ main exception """
    def __init__(self, message):
        self.message = message

class NoTextSectionError(FunctionsException):
    """ there is no section .text """
    def __init__(self, message):
        self.message = message

class NoSymbolsSectionError(FunctionsException):
    """ there is no section SYMBOL TABLE: """
    def __init__(self, message):
        self.message = message

class ObjdumpFailure(FunctionsException):
    """ objdump does't work """
    def __init__(self, message):
        self.message = message
