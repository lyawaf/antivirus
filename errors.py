
""" exceptions for functions """

class FunctionsException(Exception):
    """ main exception """
    def __init__(self, message):
        self.message = message

class ObjdumpFailure(FunctionsException):
    """ objdump does't work """
    def __init__(self, message):
        self.message = message

class ObjdumpErrors(FunctionsException):
    """ objdump errors """
    def __init__(self, message):
        self.message = message
