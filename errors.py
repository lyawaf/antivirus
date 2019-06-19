
""" exceptions for functions """

class FunctionsException(Exception):
    """ main exception """
    def __init__(self, message):
        self.message = message

class ObjdumpFailure(FunctionsException):
    """ objdump does't work """
    def __init__(self, message):
        self.message = message

class NoSectionError(FunctionsException):
    """ no section error """
    def __init__(self, message):
        self.message = message
